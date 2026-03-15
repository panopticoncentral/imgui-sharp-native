# imgui-sharp-native — TODO

Hand-written C wrapper for Dear ImGui, producing `libimgui_sharp` shared library.
Used by `SdlSharp.ImGui` in the `../sdl-sharp/` project.

## Done ✅

- CMake build system (imgui core + SDL3 backends + C wrapper → single shared lib)
- Core widget subset (~120 exported functions)
- SDL3 platform backend wrapper
- SDL_GPU renderer backend wrapper

## TODO

### Cross-platform builds
- [ ] Test Windows build (MSVC, `imgui_sharp.dll`)
- [ ] Test Linux build (GCC/Clang, `libimgui_sharp.so`)
- [ ] CI/CD pipeline for multi-platform builds
- [ ] Packaging as NuGet native redist (mirror `sdl-sharp-redist` pattern)

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
- [ ] Track Dear ImGui version updates (currently v1.92.7)
- [ ] Document which ImGui APIs are intentionally skipped and why
