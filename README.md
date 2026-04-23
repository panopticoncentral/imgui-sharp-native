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
