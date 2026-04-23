# imgui-sharp-native — TODO

Hand-written C wrapper for Dear ImGui, producing `libimgui_sharp` shared library.
Used by `SdlSharp.ImGui` in the `../sdl-sharp/` project.

## Done ✅

- CMake build system (imgui core + SDL3 backends + C wrapper → single shared lib)
- Core widget subset (~120 exported functions)
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
- [ ] ListClipper (create, begin, step, end, destroy)
- [ ] DrawList API (GetWindowDrawList, AddLine, AddRect, AddCircle, AddText, etc.)
- [ ] Font loading (AddFontFromFileTTF, AddFontFromMemoryTTF, font config)
- [ ] Full IO struct access (individual getter/setter functions for display size, delta time, etc.)
- [ ] Style struct access (getter/setter for all ImGuiStyle fields)
- [ ] Plot widgets (PlotLines, PlotHistogram — need array + callback variants)
- [ ] Table sort specs (TableGetSortSpecs — needs struct marshalling)
- [ ] Viewport access (GetMainViewport)
- [ ] Misc utilities (CalcTextSize, GetColorU32, ColorConvert*, IsKeyPressed, IsMouseClicked)

### Maintenance
- [ ] Track Dear ImGui version updates (currently pinned to v1.92.6 via submodule)
- [ ] Document which ImGui APIs are intentionally skipped and why
