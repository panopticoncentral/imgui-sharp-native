# Correctness and completeness review

Reviewed commit: `8440028` (`0.3.0-preview.1`). Reference: the checked-out
Dear ImGui `v1.92.7` submodule, with `IMGUI_DISABLE_OBSOLETE_FUNCTIONS`.

## Findings

### 1. P1 — Standalone draw lists are returned without required initialization

Location: `src/imgui_sharp.cpp:1427`.

`IGSharp_DrawList_Create` only invokes the upstream constructor. That constructor
zeroes the object and attaches shared data; it does not initialize it for drawing.
In particular, the command buffer is empty, the initial flags are absent, and
the anti-aliasing fringe scale is zero. `PushClipRectFullScreen` immediately
accesses the nonexistent last command. The required `_ResetForNewFrame` method
is not exposed, so consumers also lack the supported reset operation for reusing
standalone lists across frames.

Reproduced after creating a context, setting a valid display size and
`RendererHasTextures`, and calling `NewFrame`:

```cpp
auto dl = IGSharp_DrawList_Create(IGSharp_GetDrawListSharedData());
IGSharp_DrawList_PushClipRectFullScreen(dl); // SIGSEGV
```

The test printed `commands=0 flags=0 fringe=0` and exited with signal 11.
Adding a direct C++ `dl->_ResetForNewFrame()` before the clip operation changed
those values to `commands=1 flags=7 fringe=1`; pushing a texture and drawing a
line then succeeded with four vertices and six indices.

Recommendation: initialize new lists for use and expose a reset-for-new-frame
operation, with its context/frame and shared-data lifetime requirements documented.
Simply adding an empty command does not restore the other initialization state.

### 2. P2 — The backend header is not self-contained C

Location: `src/imgui_sharp_backend.h:16-32`.

The SDL forward declarations declare struct/union tags, but the prototypes use
bare type names without typedefs. Those names work in C++, but not in C unless
the caller has already included SDL's definitions. The core header explicitly
supports C and compiles on its own.

Reproduction:

```sh
clang -x c -std=c11 -fsyntax-only -I src \
  -include imgui_sharp_backend.h /dev/null
```

Result: six errors requiring `struct` or `union` tags. Both C++ compilation and
C compilation with `SDL3/SDL.h` included first succeed, isolating the problem
to the header's declarations.

Recommendation: use C-compatible typedef forward declarations or qualified tags
in the prototypes; check both public headers independently as C and C++.

### 3. P2 — SDL_GPU rendering cannot accept a custom pipeline

Location: `src/imgui_sharp_backend.cpp:41-42`.

Upstream `ImGui_ImplSDLGPU3_RenderDrawData` accepts an optional
`SDL_GPUGraphicsPipeline*`. The wrapper removes the parameter and always passes
`nullptr`, forcing the backend's default pipeline. Applications needing a custom
blend, depth, or shader pipeline cannot use this upstream feature through the C
wrapper. Binding a pipeline before the call is insufficient: upstream binds the
selected pipeline inside its render-state setup.

Recommendation: add a pipeline-capable variant while keeping the existing
entry point as the default-pipeline convenience form. This is a backend
completeness gap; normal default-pipeline rendering is unaffected.

### 4. P3 — Truncated glyph ranges violate the documented termination contract

Locations: `src/imgui_sharp.h:2364-2367`, `src/imgui_sharp.cpp:1665-1673`.

The header describes the copied range list as terminated by a trailing zero.
The implementation copies an arbitrary prefix, so an undersized destination
may contain neither the terminator nor complete start/end pairs.

Reproduced by adding `"AC"` and supplying capacity three: the function returned
five and wrote `[65, 65, 67]`. Passing that partial list to an API expecting
terminated ranges is unsafe. The documented two-pass allocation pattern works
when callers allocate the returned size; the issue is the truncation contract.

Recommendation: explicitly document that output is unusable when the return
value exceeds capacity, or define safe truncation that preserves complete pairs
and a terminator. Keep the required-size query behavior.

## Completeness observations

- No missing non-variadic ImGui namespace function names were found in the
  source comparison. Widget and utility forwarding was inspected for argument
  loss and wrong overloads. This is not a formal proof of behavioral equivalence.
- Mirrored enum differences found by the inventory were obsolete aliases and
  internal masks, rather than missing supported public enum values.
- `ImGuiSelectionBasicStorage::Swap` is explicitly omitted in the wrapper
  header. This is an existing intentional exclusion, but README's claim that
  only variadic and docking APIs are omitted is broader than the implementation.
- SDL_GPU also lacks wrappers for `CreateDeviceObjects`, `DestroyDeviceObjects`,
  and `UpdateTexture`, plus a C mirror/accessors for its callback render state
  (including sampler selection). These limit device-reset, manually scheduled
  texture-update, and sampler-control workflows. The core API coverage claim
  should distinguish backend coverage.
- Opaque helper objects intentionally omit internal fields. For example,
  `TextFilter` can be initialized with text or edited through its built-in UI,
  but cannot expose/edit its input buffer through the wrapper. These are scope
  limitations rather than newly introduced regressions.

## Verification and limits

- Local macOS Debug build passed, including compile-time layout and enum checks.
- All 864 declared C functions were present in the built library's exports;
  no undeclared `IGSharp_*` exports were found.
- Core header: standalone C and C++ checks passed. Backend header: standalone
  C failed as described; C++ and C with SDL included first passed.
- Native probes reproduced the draw-list crash, demonstrated the initialization
  fix, and verified the glyph-range truncation behavior.
- The existing macOS dylib references `@loader_path/libSDL3.dylib` as intended.
- Windows architectures, NuGet publication, managed end-to-end execution, and
  interactive GPU rendering were not executed. Backend pipeline findings are
  based on the pinned source and signatures, not a GPU rendering experiment.
- Existing documentation describing `IGSharp_CheckVersion` as checking caller
  layouts is inaccurate: it supplies the native library's own sizes/version.
  `IGSharp_ValidateLayouts` is the separate binding-facing size check; neither
  same-size semantic changes nor arbitrary field-offset mismatches in a binding
  are detected by that size-only check.

No implementation changes were made during this review.

## Resolution

The four findings have been addressed in the working tree:

1. Lists with shared data initialize on creation; a new reset entry point supports
   reuse. NULL shared data remains supported for storage-only lists.
2. SDL forward declarations now use typedefs valid in both C and C++.
3. An additive `RenderDrawDataWithPipeline` entry point preserves custom pipelines.
4. The glyph-range contract now explicitly requires retrying undersized copies.

Opt-in headless regression tests cover these cases, including C/C++ header
compilation and backend forwarding stubs compiled against upstream headers.
README now distinguishes core and backend coverage and corrects the version/layout
validation explanation. The additional backend features listed as completeness
observations remain documented exclusions.
