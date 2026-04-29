// Compile-time validation that the C-mirror structs in imgui_sharp.h match
// upstream Dear ImGui layout exactly. Any drift (field reordering, type
// change, count macro mismatch, layout-breaking config change) fires a
// static_assert here and the build fails.
//
// This TU contains no runtime code — it exists purely for the asserts.

#include "imgui_sharp.h"
#include "imgui.h"
#include <stddef.h>

// offsetof on classes with (non-virtual) member functions is conditionally
// supported per C++11 but works on every compiler we ship to. Suppress the
// pedantic warning so this TU stays warning-clean.
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winvalid-offsetof"
#endif

// --- Count macros ----------------------------------------------------------

static_assert(IGSHARP_KEYS_DATA_COUNT == ImGuiKey_NamedKey_COUNT,
              "IGSHARP_KEYS_DATA_COUNT does not match ImGuiKey_NamedKey_COUNT — bump the macro in imgui_sharp.h");
static_assert(IGSHARP_COL_COUNT == ImGuiCol_COUNT,
              "IGSHARP_COL_COUNT does not match ImGuiCol_COUNT — bump the macro in imgui_sharp.h");

// --- IGSharp_KeyData -------------------------------------------------------

static_assert(sizeof(IGSharp_KeyData) == sizeof(ImGuiKeyData), "IGSharp_KeyData size mismatch");
static_assert(offsetof(IGSharp_KeyData, Down)             == offsetof(ImGuiKeyData, Down),             "IGSharp_KeyData.Down");
static_assert(offsetof(IGSharp_KeyData, DownDuration)     == offsetof(ImGuiKeyData, DownDuration),     "IGSharp_KeyData.DownDuration");
static_assert(offsetof(IGSharp_KeyData, DownDurationPrev) == offsetof(ImGuiKeyData, DownDurationPrev), "IGSharp_KeyData.DownDurationPrev");
static_assert(offsetof(IGSharp_KeyData, AnalogValue)      == offsetof(ImGuiKeyData, AnalogValue),      "IGSharp_KeyData.AnalogValue");

// --- ImVector<T> layout assumption -----------------------------------------
// IGSharp_IO expands ImVector<ImWchar> InputQueueCharacters into three explicit
// fields (Size, Capacity, Data). That only works if upstream ImVector really is
// just those three POD members in that order with no padding before the pointer.

static_assert(sizeof(ImVector<ImWchar>) == 2 * sizeof(int) + sizeof(ImWchar*),
              "ImVector layout assumption broken — expected { int Size; int Capacity; T* Data; }");

// --- IGSharp_IO ------------------------------------------------------------

static_assert(sizeof(IGSharp_IO) == sizeof(ImGuiIO), "IGSharp_IO size mismatch with ImGuiIO");

#define IO_OFFSET(F) static_assert(offsetof(IGSharp_IO, F) == offsetof(ImGuiIO, F), "IGSharp_IO." #F)

// Configuration
IO_OFFSET(ConfigFlags);
IO_OFFSET(BackendFlags);
IO_OFFSET(DisplaySize);
IO_OFFSET(DisplayFramebufferScale);
IO_OFFSET(DeltaTime);
IO_OFFSET(IniSavingRate);
IO_OFFSET(IniFilename);
IO_OFFSET(LogFilename);
IO_OFFSET(UserData);

// Font system
IO_OFFSET(Fonts);
IO_OFFSET(FontDefault);
IO_OFFSET(FontAllowUserScaling);

// Keyboard/Gamepad navigation options
IO_OFFSET(ConfigNavSwapGamepadButtons);
IO_OFFSET(ConfigNavMoveSetMousePos);
IO_OFFSET(ConfigNavCaptureKeyboard);
IO_OFFSET(ConfigNavEscapeClearFocusItem);
IO_OFFSET(ConfigNavEscapeClearFocusWindow);
IO_OFFSET(ConfigNavCursorVisibleAuto);
IO_OFFSET(ConfigNavCursorVisibleAlways);

// Miscellaneous options
IO_OFFSET(MouseDrawCursor);
IO_OFFSET(ConfigMacOSXBehaviors);
IO_OFFSET(ConfigInputTrickleEventQueue);
IO_OFFSET(ConfigInputTextCursorBlink);
IO_OFFSET(ConfigInputTextEnterKeepActive);
IO_OFFSET(ConfigDragClickToInputText);
IO_OFFSET(ConfigWindowsResizeFromEdges);
IO_OFFSET(ConfigWindowsMoveFromTitleBarOnly);
IO_OFFSET(ConfigWindowsCopyContentsWithCtrlC);
IO_OFFSET(ConfigScrollbarScrollByPage);
IO_OFFSET(ConfigMemoryCompactTimer);

// Inputs behaviors
IO_OFFSET(MouseDoubleClickTime);
IO_OFFSET(MouseDoubleClickMaxDist);
IO_OFFSET(MouseDragThreshold);
IO_OFFSET(KeyRepeatDelay);
IO_OFFSET(KeyRepeatRate);

// Debug options
IO_OFFSET(ConfigErrorRecovery);
IO_OFFSET(ConfigErrorRecoveryEnableAssert);
IO_OFFSET(ConfigErrorRecoveryEnableDebugLog);
IO_OFFSET(ConfigErrorRecoveryEnableTooltip);
IO_OFFSET(ConfigDebugIsDebuggerPresent);
IO_OFFSET(ConfigDebugHighlightIdConflicts);
IO_OFFSET(ConfigDebugHighlightIdConflictsShowItemPicker);
IO_OFFSET(ConfigDebugBeginReturnValueOnce);
IO_OFFSET(ConfigDebugBeginReturnValueLoop);
IO_OFFSET(ConfigDebugIgnoreFocusLoss);
IO_OFFSET(ConfigDebugIniSettings);

// Platform identifiers
IO_OFFSET(BackendPlatformName);
IO_OFFSET(BackendRendererName);
IO_OFFSET(BackendPlatformUserData);
IO_OFFSET(BackendRendererUserData);
IO_OFFSET(BackendLanguageUserData);

// Output
IO_OFFSET(WantCaptureMouse);
IO_OFFSET(WantCaptureKeyboard);
IO_OFFSET(WantTextInput);
IO_OFFSET(WantSetMousePos);
IO_OFFSET(WantSaveIniSettings);
IO_OFFSET(NavActive);
IO_OFFSET(NavVisible);
IO_OFFSET(Framerate);
IO_OFFSET(MetricsRenderVertices);
IO_OFFSET(MetricsRenderIndices);
IO_OFFSET(MetricsRenderWindows);
IO_OFFSET(MetricsActiveWindows);
IO_OFFSET(MouseDelta);

// Internal
IO_OFFSET(Ctx);
IO_OFFSET(MousePos);
IO_OFFSET(MouseDown);
IO_OFFSET(MouseWheel);
IO_OFFSET(MouseWheelH);
IO_OFFSET(MouseSource);
IO_OFFSET(KeyCtrl);
IO_OFFSET(KeyShift);
IO_OFFSET(KeyAlt);
IO_OFFSET(KeySuper);
IO_OFFSET(KeyMods);
IO_OFFSET(KeysData);
IO_OFFSET(WantCaptureMouseUnlessPopupClose);
IO_OFFSET(MousePosPrev);
IO_OFFSET(MouseClickedPos);
IO_OFFSET(MouseClickedTime);
IO_OFFSET(MouseClicked);
IO_OFFSET(MouseDoubleClicked);
IO_OFFSET(MouseClickedCount);
IO_OFFSET(MouseClickedLastCount);
IO_OFFSET(MouseReleased);
IO_OFFSET(MouseReleasedTime);
IO_OFFSET(MouseDownOwned);
IO_OFFSET(MouseDownOwnedUnlessPopupClose);
IO_OFFSET(MouseWheelRequestAxisSwap);
IO_OFFSET(MouseCtrlLeftAsRightClick);
IO_OFFSET(MouseDownDuration);
IO_OFFSET(MouseDownDurationPrev);
IO_OFFSET(MouseDragMaxDistanceSqr);
IO_OFFSET(PenPressure);
IO_OFFSET(AppFocusLost);
IO_OFFSET(AppAcceptingEvents);
IO_OFFSET(InputQueueSurrogate);

#undef IO_OFFSET

// ImVector<ImWchar> InputQueueCharacters mapping — three explicit fields land
// at the start, mid and tail of the upstream ImVector member.
static_assert(offsetof(IGSharp_IO, InputQueueCharacters_Size) ==
              offsetof(ImGuiIO,    InputQueueCharacters) + 0,
              "IGSharp_IO.InputQueueCharacters_Size offset");
static_assert(offsetof(IGSharp_IO, InputQueueCharacters_Capacity) ==
              offsetof(ImGuiIO,    InputQueueCharacters) + sizeof(int),
              "IGSharp_IO.InputQueueCharacters_Capacity offset");
static_assert(offsetof(IGSharp_IO, InputQueueCharacters_Data) ==
              offsetof(ImGuiIO,    InputQueueCharacters) + 2 * sizeof(int),
              "IGSharp_IO.InputQueueCharacters_Data offset");

// Obsolete tail — these only exist when IMGUI_DISABLE_OBSOLETE_FUNCTIONS is
// not defined (the default for our build). If a future config flips that,
// the size assert at the top will catch the drift.
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
static_assert(offsetof(IGSharp_IO, FontGlobalScale)    == offsetof(ImGuiIO, FontGlobalScale),    "IGSharp_IO.FontGlobalScale");
static_assert(offsetof(IGSharp_IO, GetClipboardTextFn) == offsetof(ImGuiIO, GetClipboardTextFn), "IGSharp_IO.GetClipboardTextFn");
static_assert(offsetof(IGSharp_IO, SetClipboardTextFn) == offsetof(ImGuiIO, SetClipboardTextFn), "IGSharp_IO.SetClipboardTextFn");
static_assert(offsetof(IGSharp_IO, ClipboardUserData)  == offsetof(ImGuiIO, ClipboardUserData),  "IGSharp_IO.ClipboardUserData");
#endif

// --- IGSharp_Style ---------------------------------------------------------

static_assert(sizeof(IGSharp_Style) == sizeof(ImGuiStyle), "IGSharp_Style size mismatch with ImGuiStyle");

#define ST_OFFSET(F) static_assert(offsetof(IGSharp_Style, F) == offsetof(ImGuiStyle, F), "IGSharp_Style." #F)

ST_OFFSET(FontSizeBase);
ST_OFFSET(FontScaleMain);
ST_OFFSET(FontScaleDpi);
ST_OFFSET(Alpha);
ST_OFFSET(DisabledAlpha);
ST_OFFSET(WindowPadding);
ST_OFFSET(WindowRounding);
ST_OFFSET(WindowBorderSize);
ST_OFFSET(WindowBorderHoverPadding);
ST_OFFSET(WindowMinSize);
ST_OFFSET(WindowTitleAlign);
ST_OFFSET(WindowMenuButtonPosition);
ST_OFFSET(ChildRounding);
ST_OFFSET(ChildBorderSize);
ST_OFFSET(PopupRounding);
ST_OFFSET(PopupBorderSize);
ST_OFFSET(FramePadding);
ST_OFFSET(FrameRounding);
ST_OFFSET(FrameBorderSize);
ST_OFFSET(ItemSpacing);
ST_OFFSET(ItemInnerSpacing);
ST_OFFSET(CellPadding);
ST_OFFSET(TouchExtraPadding);
ST_OFFSET(IndentSpacing);
ST_OFFSET(ColumnsMinSpacing);
ST_OFFSET(ScrollbarSize);
ST_OFFSET(ScrollbarRounding);
ST_OFFSET(ScrollbarPadding);
ST_OFFSET(GrabMinSize);
ST_OFFSET(GrabRounding);
ST_OFFSET(LogSliderDeadzone);
ST_OFFSET(ImageRounding);
ST_OFFSET(ImageBorderSize);
ST_OFFSET(TabRounding);
ST_OFFSET(TabBorderSize);
ST_OFFSET(TabMinWidthBase);
ST_OFFSET(TabMinWidthShrink);
ST_OFFSET(TabCloseButtonMinWidthSelected);
ST_OFFSET(TabCloseButtonMinWidthUnselected);
ST_OFFSET(TabBarBorderSize);
ST_OFFSET(TabBarOverlineSize);
ST_OFFSET(TableAngledHeadersAngle);
ST_OFFSET(TableAngledHeadersTextAlign);
ST_OFFSET(TreeLinesFlags);
ST_OFFSET(TreeLinesSize);
ST_OFFSET(TreeLinesRounding);
ST_OFFSET(DragDropTargetRounding);
ST_OFFSET(DragDropTargetBorderSize);
ST_OFFSET(DragDropTargetPadding);
ST_OFFSET(ColorMarkerSize);
ST_OFFSET(ColorButtonPosition);
ST_OFFSET(ButtonTextAlign);
ST_OFFSET(SelectableTextAlign);
ST_OFFSET(SeparatorSize);
ST_OFFSET(SeparatorTextBorderSize);
ST_OFFSET(SeparatorTextAlign);
ST_OFFSET(SeparatorTextPadding);
ST_OFFSET(DisplayWindowPadding);
ST_OFFSET(DisplaySafeAreaPadding);
ST_OFFSET(MouseCursorScale);
ST_OFFSET(AntiAliasedLines);
ST_OFFSET(AntiAliasedLinesUseTex);
ST_OFFSET(AntiAliasedFill);
ST_OFFSET(CurveTessellationTol);
ST_OFFSET(CircleTessellationMaxError);
ST_OFFSET(Colors);
ST_OFFSET(HoverStationaryDelay);
ST_OFFSET(HoverDelayShort);
ST_OFFSET(HoverDelayNormal);
ST_OFFSET(HoverFlagsForTooltipMouse);
ST_OFFSET(HoverFlagsForTooltipNav);
ST_OFFSET(_MainScale);
ST_OFFSET(_NextFrameFontSizeBase);

#undef ST_OFFSET

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
