# imgui-sharp-native — TODO

Hand-written C wrapper for Dear ImGui, producing `libimgui_sharp` shared library.
Used by `SdlSharp.ImGui` in the `../sdl-sharp/` project.

## Done ✅

- CMake build system (imgui core + SDL3 backends + C wrapper → single shared lib)
- Full master-branch public API coverage (~825 exported functions) — the
  everyday widget surface plus all previously-skipped categories: logging,
  ini settings serialization, clipboard/IME/allocator override setters,
  debug and error-recovery tools, font introspection, and the
  `ImGuiStorage` / `ImGuiTextFilter` / `ImGuiTextBuffer` helpers. Only
  variadic/`V`-suffix overloads and docking/multi-viewport remain out of
  scope. NOTE: the C# consumer (`SdlSharp.ImGui`) must add matching
  `[StructLayout]` mirrors and P/Invoke declarations for this new surface.
- DrawList API (primitives, path builder, images, clipping)
- Misc utilities (CalcTextSize, GetColorU32, ColorConvert*, key/mouse queries, viewport)
- Font loading (TTF from file, memory, compressed memory; PushFont/PopFont; font default)
- ListClipper (virtualized large lists)
- ImGuiIO / ImGuiStyle exposed as layout-compatible C mirror structs
  (`IGSharp_IO`, `IGSharp_Style`); access via `IGSharp_GetIO()` /
  `IGSharp_GetStyle()` and read/write fields directly. Event-queue and
  ScaleAllSizes wrappers take an explicit pointer. Layout asserts in
  `src/imgui_sharp_layout_check.cpp` catch upstream drift at build time.
- InputText callbacks (completion/history/edit/charfilter/resize with full CallbackData access)
- Plot widgets (PlotLines/PlotHistogram, both array and callback variants)
- Drag and drop (source/target + ImGuiPayload accessors)
- Multi-select (BeginMultiSelect/EndMultiSelect + ImGuiMultiSelectIO/ImGuiSelectionRequest accessors)
- Table sort specs (TableGetSortSpecs + ImGuiTableSortSpecs/ImGuiTableColumnSortSpecs accessors)
- SDL3 platform backend wrapper
- SDL_GPU renderer backend wrapper
- Self-contained source tree (ImGui as `third_party/imgui` git submodule; SDL3 fetched by scripts)
- CI/CD pipeline (GitHub Actions matrix for win-x64, win-x86, win-arm64, osx-x64, osx-arm64)
- NuGet packaging as `ImguiSharp.Redist` (runtimes baked from CI artifacts)
- Trusted-publishing release workflow (tag → nuget.org via OIDC)
- CI green across win-x64/win-x86/win-arm64/osx-x64/osx-arm64; publish to nuget.org working

## TODO

### Cross-platform builds
- [ ] Linux build support (requires building SDL3 from source — upstream ships no Linux binaries)

### Maintenance
- [ ] Track Dear ImGui version updates (currently pinned to v1.92.7 via submodule)
- [x] Coordinate `SdlSharp.ImGui` update for the IGSharp_IO / IGSharp_Style
  refactor — done: the C# side now declares layout-matching mirrors, validated
  at startup via `IGSharp_ValidateLayouts`, and regenerates its P/Invoke layer
  from this header with `sdl-sharp/scripts/gen-imgui-native.py`.

### Requested from C# consumer (`sdl-sharp/SdlSharp.ImGui`)

Wrapper exports that the managed side needs to finish closing specific API gaps.
Each unblocks a corresponding feature that is currently stubbed or deferred.

- [x] **`ImGuiInputTextCallbackData` buffer mutation** — `_SetBuf`, `_SetBufSize`, and
  `_ResizeBuf(void*, char*, int)` helper. Unblocks unbounded managed-string `InputText`
  via `ImGuiInputTextFlags_CallbackResize`.
- [x] **`TableSetBgColor`** — exported as `IGSharp_TableSetBgColor(int target, unsigned int color, int column_n)`.
- [x] **Mouse cursor get/set** — `IGSharp_GetMouseCursor` and `IGSharp_SetMouseCursor`.
- [x] **Extra demo/debug windows** — `ShowDebugLogWindow`, `ShowIDStackToolWindow`,
  `ShowAboutWindow`, `ShowStyleEditor` (no-arg), `ShowStyleSelector`, `ShowFontSelector`,
  `ShowUserGuide`.
- [x] **`PushItemFlag` / `PopItemFlag`** — exported.
- [x] **Scalar widget variants** — `DragScalar{N}`, `SliderScalar{N}`, `InputScalar{N}`,
  `VSliderScalar`. The `ImGuiDataType` enum can be enumerated on the C# side.
- [x] **Item utilities** — `GetItemID`, `IsAnyItemHovered/Active/Focused`.
- [x] **Table column metadata** — `TableGetColumnCount`, `TableGetColumnIndex`,
  `TableGetRowIndex`, `TableGetColumnName`, `TableGetColumnFlags`, `TableSetColumnEnabled`,
  `TableGetHoveredColumn`.
- [x] **Scroll API** — `GetScrollX/Y`, `SetScrollX/Y`, `GetScrollMaxX/Y`,
  `SetScrollHereX/Y`, `SetScrollFromPosX/Y`.
- [x] **Focus / activation helpers** — `SetKeyboardFocusHere`, `SetNextItemAllowOverlap`.
- [x] **`SetNextWindowSizeConstraints` / `SetNextWindowContentSize` / `SetNextWindowScroll`**
  — exported. `SetNextWindowSizeConstraints` now takes the full `(min, max,
  IGSharp_SizeCallback custom_callback, void* custom_callback_data)` form.

Resolved without an export change:

- **`GetCurrentContext` / `SetCurrentContext(NULL)`** — passing `NULL` to
  `IGSharp_SetCurrentContext` is supported (it just clears the implicit `GImGui` pointer);
  no UB. Safe for managed code to detach contexts temporarily.
