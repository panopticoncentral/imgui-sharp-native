# C wrapper mapping review — imgui.h → imgui_sharp.h

**Date:** 2026-06-09
**Scope:** Full review of the mapping from upstream `third_party/imgui/imgui.h`
(pinned v1.92.7, `IMGUI_DISABLE_OBSOLETE_FUNCTIONS`, no docking) to
`src/imgui_sharp.h` / `src/imgui_sharp.cpp` / `src/imgui_sharp_layout_check.cpp`.
**Method:** 19 section-by-section comparison agents + adversarial verification of
every factual claim (50 agents total). Every finding below survived an agent
explicitly prompted to refute it; 0 claims were refuted.

## Resolution (2026-06-24)

All 26 confirmed findings were fixed (28 new exported functions; syntax-gate +
full `cmake` link verified). Summary:

- **High #1 (TexRef):** added 7 `*TextureData` image/drawlist variants that take an
  `ImTextureData*` and preserve deferred ImTextureID resolution; renamed the
  misleading `IGSharp_FontAtlas_GetTexRef` → `GetTexID` (now documented as the
  resolved, post-upload id) with `GetTexData` as the indirection-preserving path.
- **High #2 (DrawCmd indexing):** added `IGSharp_DrawList_GetCmd(draw_list, index)`.
- **Mediums:** `IGSharp_SizeCallback` typedef + full `SetNextWindowSizeConstraints`
  signature; `dst` param on the three `StyleColors*`; `font_cfg`/`glyph_ranges` on
  the six `AddFont*` (file/compressed/default) variants; `TextLinkOpenURL` returns
  `bool`; `DrawList_Create`/`Destroy` (CloneOutput leak); `IGSHARP_DRAWCALLBACK_RESETRENDERSTATE`;
  `TextureData_GetUpdatesCount`/`GetUpdate`; `FontAtlas_SetTexPixelsUseColors`;
  `Font_Get/SetEllipsisAutoBake`; `PlatformIO_GetTexturesCount`/`GetTexture`.
- **Lows:** static_asserts for `ImDrawIdx`, `ImWchar`, `ImTextureID`, `IGSharp_Vec2/Vec4`,
  and ImVector member order; `IGSHARP_TEXTUREID_INVALID`, `IGSHARP_PAYLOAD_TYPE_COLOR_3F/4F`
  defines; `IGSharp_DrawCallback` typedef; accessors for `InputTextCallbackData::Ctx`,
  `FontAtlas::FontLoaderFlags`, `Font::OwnerAtlas`, `Font`/`FontBaked::ClearOutputData`,
  `FontGlyph::PackId`, `FontBaked` glyph enumeration, `DrawData::SetTextures`; and a
  comment documenting why ImGuiViewport core fields are read-only.
- **Deliberately skipped:** the optional `IGSharp_Viewport` opaque typedef (pure
  style; `void*` and a typedef'd struct pointer are ABI-identical, and the review
  marked it likely-intentional). The `.cpp` was not reorganized to match the new
  header order — tracked as a follow-up.

---

Companion change (landed with this review): `imgui_sharp.h` was reorganized so
sections, groups, and within-group declaration order match `imgui.h` exactly.
All ~25 appended `fn-*`/`struct-accessors-*` blocks were merged into their
topical groups. No declaration changed — verified by multiset comparison of all
1786 non-comment lines plus the syntax-only static_assert gate and a full
`cmake --build` link.

## High severity (2)

1. **`IGSharp_FontAtlas_GetTexRef` performs the lossy ImTextureRef→ImTextureID
   conversion upstream explicitly warns against** (imgui.h:365).
   `imgui_sharp.cpp` returns `TexRef.GetTexID()`; before the backend uploads the
   atlas texture (first frame, or after atlas growth) this is
   `ImTextureID_Invalid`, so a caller binding the atlas for custom-rect drawing
   bakes an invalid/stale ID into draw commands, bypassing deferred resolution.
   The name also promises a TexRef but returns a TexID.
   *Fix:* expose an `ImTextureRef`-shaped value (or an `ImTextureData*`-based
   accessor) so the `_TexData` indirection survives until render.

2. **`IGSharp_DrawList_GetCmdBufferData` returns a raw `ImDrawCmd*` array that C
   callers cannot index.** `ImDrawCmd` is opaque in the wrapper, and
   `sizeof(ImDrawCmd)` is platform-dependent (~72 bytes, contains ImTextureRef +
   pointers), so there is no safe way to produce `draw_cmd` pointers for
   index > 0 to feed the `IGSharp_DrawCmd_Get*` accessors. A .NET renderer
   cannot enumerate draw commands without hardcoding an ABI-fragile stride.
   *Fix:* add `IGSharp_DrawList_GetCmd(void* draw_list, int index)` (analogous
   to `IGSharp_DrawData_GetCmdList`) or an `IGSharp_DrawCmd_SizeOf()` helper.

## Medium severity

### Dropped default parameters (violate the "defaults become explicit C params" convention)

3. **`SetNextWindowSizeConstraints` drops `custom_callback`/`custom_callback_data`,
   and no `IGSharp_SizeCallback` typedef exists** — which makes the five shipped
   `IGSharp_SizeCallbackData_*` accessors **dead API** (the callback is the only
   way ImGui ever hands out an `ImGuiSizeCallbackData*`). Known in TODO.md but
   not documented in the header. *Fix:* add
   `typedef void (*IGSharp_SizeCallback)(void* data);` next to
   `IGSharp_InputTextCallback` and a `...Callback` variant (or two extra params).

4. **`StyleColorsDark/Light/Classic` drop the `ImGuiStyle* dst` parameter**
   (write palette into a non-current style), undocumented. `IGSharp_Style*`
   already exists as a typed pointer, so adding the param is straightforward.

5. **`ImFontAtlas::AddFontFromFileTTF` drops `font_cfg` + `glyph_ranges`** — a
   caller cannot load a file font with MergeMode/Oversample/GlyphOffset etc.
   without re-implementing file loading and going through `IGSharp_FontAtlas_AddFont`.

6. **`AddFontFromMemoryCompressedTTF` / `AddFontFromMemoryCompressedBase85TTF`
   drop `font_cfg` + `glyph_ranges` — with NO workaround**: decompression
   (stb_decompress) happens inside the upstream function and is not exposed, so
   merging a compressed icon font is impossible through the C API.

7. **`AddFontDefault` / `AddFontDefaultVector` / `AddFontDefaultBitmap` drop
   `font_cfg`** — cannot merge icons into or set SizePixels on the embedded
   default font (the embedded font data is not otherwise reachable).
   (Related, noted as likely-intentional: `AddFontFromMemoryTTF` replaces
   `font_cfg` with a `transfer_ownership` bool and drops `glyph_ranges`; full
   config is reachable via `AddFont`, so acceptable but deviates from convention.)

### Wrong/lossy signatures

8. **`IGSharp_TextLinkOpenURL` returns `void`; upstream returns `bool`**
   (clicked indication is discarded). Should return bool like `IGSharp_TextLink`.

### Missing API surface

9. **`IGSharp_DrawList_CloneOutput` leaks**: it returns an `IM_NEW`'d
   `ImDrawList` but there is no `IGSharp_DrawList_Destroy`, and the
   `ImDrawList(ImDrawListSharedData*)` constructor is unwrapped despite
   `IGSharp_GetDrawListSharedData` existing.

10. **`ImDrawCallback_ResetRenderState` sentinel `((ImDrawCallback)(-8))` has no
    C-side constant** — backends comparing `IGSharp_DrawCmd_GetUserCallback`
    must hardcode `-8`.

11. **`ImTextureData::Updates` (`ImVector<ImTextureRect>`) has no accessors** —
    a renderer backend handling `ImTextureStatus_WantUpdates` is supposed to
    iterate the per-rect update list; only the bounding `UpdateRect` is exposed.

12. **`ImFontAtlas::TexPixelsUseColors` has a getter but no setter**, although
    upstream docs instruct users to set it when rendering colored custom rects
    (and AddCustomRect/GetCustomRect ARE wrapped, so the workflow dead-ends).

13. **`ImFont::EllipsisAutoBake` has no accessor**, but
    `IGSharp_Font_SetEllipsisChar` is exposed and upstream docs say to clear
    EllipsisAutoBake when swapping EllipsisChar — the documented swap/restore
    workflow can't be done correctly from C.

14. **`ImGuiPlatformIO::Textures` has no accessors** (documented as intentional
    in the header, but noted: at renderer-backend *shutdown* there is no valid
    ImDrawData, so a C# backend implementing `RendererHasTextures` cannot
    enumerate remaining textures to destroy them. The DrawData route does not
    cover this case.)

### Missing compile-time guards

15. **No `static_assert(sizeof(ImDrawIdx) == sizeof(unsigned short))`** — the
    wrapper bakes 16-bit indices into `PrimWriteIdx` and buffer accessors; an
    imconfig override would silently corrupt index buffers.

## Low severity

- **Missing layout asserts:** `ImWchar` (== unsigned short; an
  `IMGUI_USE_WCHAR32` build would silently change glyph-range stride — the
  existing `ImVector<ImWchar>` assert would *not* catch it),
  `ImTextureID` (== unsigned long long), `IGSharp_Vec2`/`IGSharp_Vec4`
  (validated only indirectly through parent structs), and ImVector's own
  Size/Capacity/Data member order (asserted only via the IO mirror's expanded
  triplet).
- **Missing constants:** `ImTextureID_Invalid`,
  `IMGUI_PAYLOAD_TYPE_COLOR_3F`/`_4F` payload-type strings, and an
  `IGSharp_DrawCallback` function-pointer typedef (AddCallback takes `void*`).
- **Missing accessors (flag for deliberate decision):**
  `ImGuiInputTextCallbackData::Ctx`, atlas-level `ImFontAtlas::FontLoaderFlags`
  (per-config one exists), `ImFont::OwnerAtlas`, `ImFont::ClearOutputData` /
  `ImFontBaked::ClearOutputData` (siblings in the same [Internal] block ARE
  wrapped), `ImDrawData::Textures` setter, `ImFontGlyph::PackId` (needed to
  refresh glyph UVs via GetCustomRect), ImFontBaked glyph enumeration
  (FindGlyph only; no count/index accessors), ImGuiViewport field setters
  (read-only is reasonable on master; just undocumented).
- **Style:** ImGuiViewport accessors take untyped `void*` while ImGuiPlatformIO
  got a dedicated opaque typedef; an `IGSharp_Viewport` typedef would match.

## Implementation-quality notes (non-blocking)

- `.cpp` organization still reflects the old append-era layout (e.g. ImFontAtlas
  functions split across three regions, `CBD`/`PL` accessor macros never
  `#undef`'d, ListClipper UserIndex accessors detached from the main block).
  The header reorganization did not touch the `.cpp`; a follow-up pass could
  mirror the new section order there.
- Format-string forwarding was checked across all text APIs: all wrappers
  correctly forward user text via `"%s"` (no format-string hazards found).
- ImGuiStyle and ImGuiIO mirrors: every field present, in order, fully asserted
  — no findings.
- All mirrored enum values are covered by per-value static_asserts; no missing
  enum values were found anywhere.

## Section-by-section verdicts

| Section | Verdict |
|---|---|
| Forward declarations / basic types | Clean except SizeCallback + assert gaps (#3, lows) |
| Texture identifiers | `(no wrappers yet)` placeholder; TexRef finding #1, ImTextureID lows |
| End-user API functions | Near-complete; #3, #4, #8 + ordering (fixed by reorg) |
| Flags & Enumerations | Complete, all values asserted; ordering fixed by reorg |
| Tables | Complete incl. SortSpecs accessors; ordering fixed by reorg |
| ImGuiStyle / ImGuiIO | Complete, fully asserted, no findings |
| Misc data structures | Complete; SizeCallbackData accessors dead until #3 |
| Helpers (TextFilter/TextBuffer/Storage/ListClipper) | Complete; was under wrong banner (fixed) |
| Multi-Select | Complete (documented intentional omissions); ordering fixed |
| Drawing API | Findings #2, #9, #10, #15 + lows |
| Texture API | Complete except #11 |
| Font API | Largest gap cluster: #5, #6, #7, #12, #13 + lows |
| Viewports / Platform | Complete; #14 noted; ordering fixed |
