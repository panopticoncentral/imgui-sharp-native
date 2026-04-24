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
<PackageReference Include="ImguiSharp.Redist" Version="0.1.0-preview.1" />
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

Pinned by the `third_party/imgui` submodule SHA. Bump by checking out a new
tag inside the submodule and committing the updated pointer.

## API coverage

The wrapper exports ~500 `IGSharp_*` C functions covering the everyday
widget surface (windows, layout, ID/style stacks, all widget families,
popups, menus, tables, tabs), the DrawList API, fonts, ListClipper, full
`ImGuiIO` / `ImGuiStyle` field access, InputText callbacks, plots, drag
and drop, multi-select, and table sort specs. For a concrete list, see
[`src/imgui_sharp.h`](src/imgui_sharp.h).

### Intentionally skipped APIs

If you're looking for an ImGui function and can't find it, it may be
deliberately out of scope. The table below covers the categories — if
something you need is in an "addable on request" row, file an issue.

| Category | Examples | Reason | Addable? |
|---|---|---|---|
| Variadic / `V`-suffix overloads | `TextV`, `TextColoredV`, `BulletTextV`, `SeparatorTextV` | C# formats before calling `Text(...)` | No — format at call site |
| Scalar generics | `DragScalar`, `SliderScalar`, `InputScalar`, `*N` variants | Covered by typed `DragInt/Float`, `SliderInt/Float`, `InputInt/Float` | No — use typed variants |
| Columns (legacy) | `Columns`, `NextColumn`, `GetColumnIndex` | Superseded by Tables | No — use Tables |
| Logging | `LogToTTY/File/Clipboard`, `LogText`, `LogFinish` | Niche feature | Yes |
| Ini serialization | `LoadIniSettingsFromMemory`, `SaveIniSettingsToMemory`, disk variants | Rarely needed beyond the default | Yes |
| Clipboard / IME overrides | `SetClipboardTextFn`, `SetPlatformImeDataFn` | Backends handle this | Yes |
| Memory allocator overrides | `SetAllocatorFunctions` | Rare | Yes |
| Debug / error recovery tools | `DebugTextEncoding`, `DebugFlashStyleColor`, `ErrorCheckEndFrameRecover` | Dev-only | Yes |
| ImGui helper types | `ImGuiStorage`, `ImGuiTextFilter`, `ImGuiTextBuffer` | C# has equivalents | No — use .NET |
| Font introspection | `ImFont::FindGlyph`, `CalcTextSizeA`, per-glyph APIs | `ImFont*` stays opaque | Partial (file issue) |
| Multi-viewport / docking | `GetPlatformIO`, dock-builder APIs | We track the main branch, not docking | No (until upstream merges) |
