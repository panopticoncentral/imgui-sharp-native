# Complete the C wrapper header — design

**Date:** 2026-05-29
**Topic:** Bring `src/imgui_sharp.{h,cpp}` + `src/imgui_sharp_layout_check.cpp` to
full master-branch coverage of Dear ImGui (pinned `v1.92.7`), executed by a
multi-agent Workflow.

## Goal

Every non-variadic, non-docking public Dear ImGui API is exposed in C-friendly
form:

- **Functions:** every `IMGUI_API` free function in `imgui.h` has an
  `IGSharp_*` wrapper.
- **Enums:** every public enum is mirrored as `IGSharp_*` values with per-value
  `static_assert` mapping to upstream (the `KEY_VAL`/`COL_VAL` macro style
  already in `imgui_sharp_layout_check.cpp`).
- **Structs:** see the struct strategy below.

## Scope decisions (locked with the user)

1. **Coverage = all master-branch APIs.** Reverse the soft exclusions previously
   listed in `README.md` (logging, ini serialization, clipboard/allocator
   overrides, debug/error-recovery tools, font introspection,
   `ImGuiStorage`/`ImGuiTextFilter`/`ImGuiTextBuffer` helpers). These are now
   IN scope.
2. **Skip only two categories:**
   - **Variadic / `V`-suffix overloads** (`TextV`, `TextColoredV`, …) — C#
     formats at the call site before calling the non-variadic form.
   - **Docking / multi-viewport** — not on the pinned `master` branch at all
     (grep for `DockSpace`/`ImGuiDockNode`/`DockBuilder` returns 0). Requires a
     different upstream branch plus SDL3/SDL_GPU backend plumbing and a
     function-pointer `ImGuiPlatformIO` table. Out of reach via header work.
     - Exception: the **non-docking** parts of `ImGuiPlatformIO` that exist on
       master (clipboard / IME / monitor hooks) and `ImGuiPlatformImeData` ARE
       in scope.
3. **Struct strategy = layout mirrors where sound, accessors for the big
   behavioral objects.**
   - **POD / data structs → full layout-compatible mirror structs**, validated
     by `sizeof` + per-field `offsetof` static_asserts. Includes:
     `ImDrawVert`, `ImDrawCmd`, `ImDrawData`, `ImFontGlyph`, `ImFontConfig`,
     `ImGuiViewport`, `ImTextureData`/`ImTextureRect`, `ImGuiSizeCallbackData`,
     `ImGuiPlatformImeData`, and any other small public POD structs surfaced by
     discovery.
   - **`ImFontAtlas`, `ImFont`, `ImDrawList` → keep opaque + accessor
     functions** for the genuinely-useful fields (e.g. `ImFont` size/metrics,
     `ImFontAtlas` texture ref, `ImDrawList` cmd/vtx/idx buffer pointers for
     custom rendering). Rationale: `offsetof` validation is all-or-nothing, and
     these have large internal sections that churn across upstream versions
     (the v1.92 font-system rewrite). Accessors are immune to that churn.
   - **`ImGuiContext` stays fully opaque** (it lives in `imgui_internal.h`).
   - **Building blocks:** `ImVec2`/`ImVec4` map to existing `IGSharp_Vec2`/
     `IGSharp_Vec4`; `ImVector<T>` expands inline to `_Size`/`_Capacity`/
     `_Data` field triplets (the existing `InputQueueCharacters` precedent in
     `IGSharp_IO`).
   - Behavioral structs that gain a mirror still keep their method-style
     wrapper functions for mutation (geometry/logic that can't be reproduced by
     poking fields) — exactly like `IGSharp_IO` has both a mirror struct and
     event-queue functions.

## Verification gate

Dependency-free, no SDL3 required:

```
c++ -std=c++11 -fsyntax-only -DIMGUI_SHARP_EXPORT -DIMGUI_DISABLE_OBSOLETE_FUNCTIONS \
    -I third_party/imgui -I src src/imgui_sharp.cpp
c++ -std=c++11 -fsyntax-only -DIMGUI_SHARP_EXPORT -DIMGUI_DISABLE_OBSOLETE_FUNCTIONS \
    -I third_party/imgui -I src src/imgui_sharp_layout_check.cpp
```

`-fsyntax-only` runs the front-end, which **evaluates `static_assert`** — so it
catches both compile errors and layout-mirror drift. Both files compile clean
today (verified). Optional stronger final gate: `./scripts/fetch-sdl3.sh` then
`cmake --build build` for a full link.

## Workflow architecture

Work fans out along the existing `[SECTION]` boundaries in `imgui_sharp.h`,
which already mirror upstream `imgui.h` section-for-section. Sections own
disjoint functions/structs/enums → clean parallelism.

**Phase 1 — Discover** (fan-out, one agent per upstream section). Diff upstream
`imgui.h` against the current wrapper; emit a structured gap list per section:
missing functions, missing enums (with all values), missing struct mirrors /
accessors. Apply scope rules (drop variadic + docking; classify each struct as
mirror vs accessor per the strategy above). Returns structured JSON.

**Phase 2 — Generate** (pipeline per section). Each gap list → three code
artifacts keyed to the section's existing anchor comment:
(a) header declarations + mirror struct typedefs + enum definitions,
(b) `.cpp` implementations,
(c) `layout_check.cpp` asserts (per-value enum asserts; `sizeof` + per-field
`offsetof` for each mirror).
Agents follow the established naming (`IGSharp_<Thing>_<Member>`) and signature
conventions (value structs passed by value as `IGSharp_Vec2`, `bool*` for
optional out-params, opaque `void*` for handle args).

**Phase 3 — Integrate** (single writer; NO parallel edits to the 3 shared
files). Apply generated code section-by-section at the anchor comments.

**Phase 4 — Converge** (loop-until-clean). Run the syntax-only gate; parse
errors → dispatch fix agents with the failing snippet + error → re-integrate →
recompile. Repeat until both files are clean. Cap iterations and report any
residual gaps rather than looping forever.

**Phase 5 — Document.** Refresh the README API-coverage section and the
"Intentionally skipped APIs" table (now only variadic + docking) and `TODO.md`.

## Risks & mitigations

- **Shared-file write races** → single integrator (Phase 3), never parallel
  edits to `.h`/`.cpp`/`layout_check.cpp`.
- **Mirror drift / impossible mirrors** → strategy caps mirrors to POD structs;
  big behavioral structs use accessors.
- **Hidden internal fields breaking `offsetof`** → discovery must mirror the
  FULL public field list of any struct it marks as a mirror; if a struct has
  internal/private fields interleaved with public ones, downgrade it to
  accessors.
- **Runaway convergence loop** → iteration cap with explicit residual-gap
  report.

## Out of scope

- Variadic / `V`-suffix overloads.
- Docking / multi-viewport (different upstream branch + backend work).
- `ImGuiContext` mirror.
- C# side (`SdlSharp.ImGui`) updates — tracked separately in `TODO.md`.
