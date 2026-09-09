# imgui-sharp-native

Hand-written C wrapper around [Dear ImGui](https://github.com/ocornut/imgui)
with SDL3 + SDL_GPU backends, packaged as `ImguiSharp.Redist` on NuGet.
Consumed by [`SdlSharp.ImGui`](https://github.com/panopticoncentral/sdl-sharp)
via `P/Invoke` on `imgui_sharp`.

## Layout

```
src/                      C wrapper sources (imgui_sharp.cpp, .h, backend)
third_party/imgui/        Dear ImGui sources (git submodule, pinned tag)
scripts/                  SDL3 fetch helpers (sdl3-versions.json + fetch-sdl3.{sh,ps1})
nuget/ImguiSharp.Redist/  .csproj that packs runtimes/<rid>/native/*
.github/workflows/        CI build matrix + tag-triggered NuGet publish
```

## Building locally

Requirements: CMake 3.20+, a C++ toolchain, and either:

- an environment where `find_package(SDL3 CONFIG)` succeeds (system SDL3), or
- the bundled fetch script to download a pinned SDL3 dev package.

```bash
git submodule update --init --recursive

# macOS: fetch SDL3 framework from the upstream DMG
./scripts/fetch-sdl3.sh
cmake -S . -B build -DSDL3_ROOT="$SDL3_ROOT" -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

```powershell
# Windows: fetch SDL3 VC dev package
./scripts/fetch-sdl3.ps1
cmake -S . -B build -A x64 -DSDL3_ROOT="$env:SDL3_ROOT" -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

Output: `build/libimgui_sharp.dylib` (macOS) or `build/Release/imgui_sharp.dll` (Windows).

## Runtime SDL3 dependency

`libimgui_sharp` links against SDL3 but **does not ship it**. It expects
`libSDL3` to be co-located in the same directory at runtime — that's what
`SdlSharp.Redist` already provides. On macOS the SDL3 install name is
rewritten to `@loader_path/libSDL3.dylib` so both libraries share one
SDL3 instance.

## Consuming from a .NET project

```xml
<PackageReference Include="SdlSharp" Version="..." />
<PackageReference Include="ImguiSharp.Redist" Version="0.3.0-preview.3" />
```

`SdlSharp.ImGui` depends transitively via `SdlSharp`; applications only need
to add `ImguiSharp.Redist` if they use the ImGui binding directly.

## Publishing

Pushing a `v*` tag triggers `.github/workflows/release.yml` which builds
all RIDs, packs the `.nupkg`, and pushes to nuget.org via trusted publishing
(OIDC). First-time setup requires registering this repository as a trusted
publisher on nuget.org.

## Supported RIDs

`win-x64`, `win-x86`, `win-arm64`, `osx-x64`, `osx-arm64`. Linux is deferred
(no upstream-prebuilt SDL3 Linux binaries).

## ImGui version

Pinned by the `third_party/imgui` submodule SHA. See the current tag with
`git -C third_party/imgui describe --tags HEAD`.

### Bumping

```bash
cd third_party/imgui
git fetch --tags
git checkout vX.Y.Z         # pick the new release tag
cd ../..
git add third_party/imgui
git commit -m "Bump Dear ImGui to vX.Y.Z"
```

Then push — CI rebuilds all 5 RIDs and the new `ImguiSharp.Redist` preview
can be cut by pushing a `v*` release tag.

### After a bump, verify

1. **Read the upstream changelog** in `third_party/imgui/docs/CHANGELOG.txt`
   — skim for renamed/removed public APIs, struct layout changes, and new
   APIs worth wrapping.
2. **Local build still clean** — any rename of a field we read directly
   (on `ImGuiIO`, `ImGuiStyle`, `ImGuiListClipper`, `ImGuiPayload`,
   `ImGuiMultiSelectIO`, `ImGuiSelectionRequest`, `ImGuiTableSortSpecs`,
   `ImGuiInputTextCallbackData`) shows up as a compile error in
   `imgui_sharp.cpp` — fix the shim.
3. **Binding layout validation still passes at runtime.** The C# binding
   calls `IGSharp_ValidateLayouts` with its mirrored struct sizes. A false
   result requires matching binding updates before releasing. This checks
   sizes, not individual binding field offsets or same-size semantic changes.
   `IGSharp_CheckVersion` separately checks the native build against its own
   ImGui headers; it receives no caller version or layout information.
4. **CI green on all 5 matrix legs.**
5. **New APIs worth wrapping?** — `git -C third_party/imgui log vOLD..vNEW -- imgui.h`
   shows changes to the public header. Consider exposing any additions
   that fit the coverage criteria in the API table above.

### Version sensitivity

- Always ship `ImguiSharp.Redist` and the matching `SdlSharp.ImGui` binding
  together. The binding's startup size checks catch size mismatches, but do
  not guarantee compatibility across different ImGui versions.
- Breaking upstream changes warrant an `ImguiSharp.Redist` major version
  bump.
- The `-docking` tag is a separate upstream branch we don't track.
  Switching would require additional shims for multi-viewport,
  `ImGuiPlatformIO`, and dock-builder APIs.

## API coverage

The wrapper exports 867 `IGSharp_*` C functions covering essentially the
entire master-branch public API: the everyday widget surface (windows,
layout, ID/style stacks, all widget families, popups, menus, tables, tabs),
the DrawList API, fonts and font introspection, ListClipper, InputText
callbacks, plots, drag and drop, multi-select, table sort specs, logging,
ini settings serialization, clipboard/IME/allocator override setters,
debug and error-recovery tools, and the `ImGuiStorage` / `ImGuiTextFilter`
/ `ImGuiTextBuffer` helpers. Coverage excludes
variadic/`V`-suffix overloads, docking/multi-viewport, and a few helper operations
described below. Backend coverage is listed separately. For
a concrete list, see [`src/imgui_sharp.h`](src/imgui_sharp.h).

`ImGuiIO` and `ImGuiStyle` are exposed as layout-compatible C structs
(`IGSharp_IO`, `IGSharp_Style`) — call `IGSharp_GetIO()` /
`IGSharp_GetStyle()` to obtain a pointer and read or write fields
directly. Layout match with upstream is enforced at compile time by
the asserts in `src/imgui_sharp_layout_check.cpp`.

### Intentionally skipped APIs

The main exclusions are listed below. Opaque objects also hide internal fields,
and `ImGuiSelectionBasicStorage::Swap` is intentionally omitted.

| Category | Examples | Reason | Addable? |
|---|---|---|---|
| Variadic / `V`-suffix overloads | `TextV`, `TextColoredV`, `BulletTextV`, `SeparatorTextV` | The typed/non-variadic form is enough — C# formats at the call site before calling `Text(...)` | No — format at call site |
| Docking / multi-viewport | `DockSpace`, `DockBuilder*`, `ImGuiDockNode`, viewport-as-OS-window, the platform/renderer callback table | Not on the master branch we track, and our SDL3 + SDL_GPU backends are single-viewport | No (until upstream merges to master) |

## Standalone draw lists

After `IGSharp_NewFrame`, create a list with
`IGSharp_DrawList_Create(IGSharp_GetDrawListSharedData())`. It is initialized
for drawing; push a clip rect and texture before adding primitives. On each
subsequent frame, call `IGSharp_DrawList_ResetForNewFrame` after `NewFrame`,
then restore the clip rect and texture. Destroy the list before its context.
A list created with NULL shared data is storage-only. Clones are renderable
snapshots, not lists that can be reset or extended.

## Backend coverage

The SDL3 platform wrapper supports SDL_GPU initialization, events, frame setup,
and shutdown. The SDL_GPU renderer supports initialization, frame preparation,
rendering, and shutdown. `IGSharp_ImplSDLGPU3_RenderDrawDataWithPipeline` accepts
an optional custom graphics pipeline; the original `RenderDrawData` entry point
continues to use the default pipeline.

Device-object recreation, manual `UpdateTexture`, and typed access to the
SDL_GPU callback render state (including sampler selection) are not exposed.
Other SDL3 renderer initialization modes are also outside this backend's scope.

## Regression checks

The opt-in tests run headlessly and compile the public headers as C and C++.
They exercise standalone draw-list creation/reuse, glyph-range size queries
and copying, and custom/default pipeline forwarding against recording stubs.

```sh
cmake -S . -B build -DIMGUI_SHARP_BUILD_TESTS=ON -DSDL3_ROOT="/path/to/SDL3"
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

The pipeline forwarding test uses the real upstream declarations but does not
exercise GPU rendering. Run tests on a host that can execute the target architecture.
