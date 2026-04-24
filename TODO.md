# imgui-sharp-native — TODO

Hand-written C wrapper for Dear ImGui, producing `libimgui_sharp` shared library.
Used by `SdlSharp.ImGui` in the `../sdl-sharp/` project.

## Done ✅

- CMake build system (imgui core + SDL3 backends + C wrapper → single shared lib)
- Core widget subset (~430 exported functions)
- DrawList API (primitives, path builder, images, clipping)
- Misc utilities (CalcTextSize, GetColorU32, ColorConvert*, key/mouse queries, viewport)
- Font loading (TTF from file, memory, compressed memory; PushFont/PopFont; font default)
- ListClipper (virtualized large lists)
- Full ImGuiIO field access (display/delta/mouse/keys/metrics + event queue)
- Full ImGuiStyle field access (all spacing/rounding/alignment/color fields)
- SDL3 platform backend wrapper
- SDL_GPU renderer backend wrapper
- Self-contained source tree (ImGui as `third_party/imgui` git submodule; SDL3 fetched by scripts)
- CI/CD pipeline (GitHub Actions matrix for win-x64, win-x86, win-arm64, osx-x64, osx-arm64)
- NuGet packaging as `ImguiSharp.Redist` (runtimes baked from CI artifacts)
- Trusted-publishing release workflow (tag → nuget.org via OIDC)

## TODO

### Cross-platform builds
- [ ] Verify first CI run green on all 5 matrix legs (push to observe)
- [ ] Register trusted publisher on nuget.org for this repo + `release.yml`
- [ ] Cut `v0.1.0-preview.1` tag and verify nuget.org publish
- [ ] Linux build support (requires building SDL3 from source — upstream ships no Linux binaries)

### Expand API surface
- [ ] InputText with callback (function pointer + void* userdata passthrough)
- [ ] Drag and drop (BeginDragDropSource/Target, SetDragDropPayload, AcceptDragDropPayload)
- [ ] Multi-select (BeginMultiSelect/EndMultiSelect, ImGuiMultiSelectIO)
- [ ] Plot widgets (PlotLines, PlotHistogram — need array + callback variants)
- [ ] Table sort specs (TableGetSortSpecs — needs struct marshalling)

### Maintenance
- [ ] Track Dear ImGui version updates (currently pinned to v1.92.6 via submodule)
- [ ] Document which ImGui APIs are intentionally skipped and why
