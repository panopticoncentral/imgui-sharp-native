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

// --- Mirrored enums --------------------------------------------------------
// IGSharp_Key / IGSharp_Col mirror ImGuiKey / ImGuiCol_ 1:1. Per-value
// static_asserts catch reordering, renaming, or value drift on a Dear ImGui
// bump and point at the offending entry by name.

#define KEY_VAL(F) static_assert((int)IGSharp_Key_##F == (int)ImGuiKey_##F, "IGSharp_Key_" #F " value drift")
KEY_VAL(None);
KEY_VAL(NamedKey_BEGIN);
KEY_VAL(Tab);
KEY_VAL(LeftArrow);
KEY_VAL(RightArrow);
KEY_VAL(UpArrow);
KEY_VAL(DownArrow);
KEY_VAL(PageUp);
KEY_VAL(PageDown);
KEY_VAL(Home);
KEY_VAL(End);
KEY_VAL(Insert);
KEY_VAL(Delete);
KEY_VAL(Backspace);
KEY_VAL(Space);
KEY_VAL(Enter);
KEY_VAL(Escape);
KEY_VAL(LeftCtrl);  KEY_VAL(LeftShift);  KEY_VAL(LeftAlt);  KEY_VAL(LeftSuper);
KEY_VAL(RightCtrl); KEY_VAL(RightShift); KEY_VAL(RightAlt); KEY_VAL(RightSuper);
KEY_VAL(Menu);
KEY_VAL(0); KEY_VAL(1); KEY_VAL(2); KEY_VAL(3); KEY_VAL(4); KEY_VAL(5); KEY_VAL(6); KEY_VAL(7); KEY_VAL(8); KEY_VAL(9);
KEY_VAL(A); KEY_VAL(B); KEY_VAL(C); KEY_VAL(D); KEY_VAL(E); KEY_VAL(F); KEY_VAL(G); KEY_VAL(H); KEY_VAL(I); KEY_VAL(J);
KEY_VAL(K); KEY_VAL(L); KEY_VAL(M); KEY_VAL(N); KEY_VAL(O); KEY_VAL(P); KEY_VAL(Q); KEY_VAL(R); KEY_VAL(S); KEY_VAL(T);
KEY_VAL(U); KEY_VAL(V); KEY_VAL(W); KEY_VAL(X); KEY_VAL(Y); KEY_VAL(Z);
KEY_VAL(F1);  KEY_VAL(F2);  KEY_VAL(F3);  KEY_VAL(F4);  KEY_VAL(F5);  KEY_VAL(F6);
KEY_VAL(F7);  KEY_VAL(F8);  KEY_VAL(F9);  KEY_VAL(F10); KEY_VAL(F11); KEY_VAL(F12);
KEY_VAL(F13); KEY_VAL(F14); KEY_VAL(F15); KEY_VAL(F16); KEY_VAL(F17); KEY_VAL(F18);
KEY_VAL(F19); KEY_VAL(F20); KEY_VAL(F21); KEY_VAL(F22); KEY_VAL(F23); KEY_VAL(F24);
KEY_VAL(Apostrophe);
KEY_VAL(Comma);
KEY_VAL(Minus);
KEY_VAL(Period);
KEY_VAL(Slash);
KEY_VAL(Semicolon);
KEY_VAL(Equal);
KEY_VAL(LeftBracket);
KEY_VAL(Backslash);
KEY_VAL(RightBracket);
KEY_VAL(GraveAccent);
KEY_VAL(CapsLock);
KEY_VAL(ScrollLock);
KEY_VAL(NumLock);
KEY_VAL(PrintScreen);
KEY_VAL(Pause);
KEY_VAL(Keypad0); KEY_VAL(Keypad1); KEY_VAL(Keypad2); KEY_VAL(Keypad3); KEY_VAL(Keypad4);
KEY_VAL(Keypad5); KEY_VAL(Keypad6); KEY_VAL(Keypad7); KEY_VAL(Keypad8); KEY_VAL(Keypad9);
KEY_VAL(KeypadDecimal);
KEY_VAL(KeypadDivide);
KEY_VAL(KeypadMultiply);
KEY_VAL(KeypadSubtract);
KEY_VAL(KeypadAdd);
KEY_VAL(KeypadEnter);
KEY_VAL(KeypadEqual);
KEY_VAL(AppBack);
KEY_VAL(AppForward);
KEY_VAL(Oem102);
KEY_VAL(GamepadStart);
KEY_VAL(GamepadBack);
KEY_VAL(GamepadFaceLeft);
KEY_VAL(GamepadFaceRight);
KEY_VAL(GamepadFaceUp);
KEY_VAL(GamepadFaceDown);
KEY_VAL(GamepadDpadLeft);
KEY_VAL(GamepadDpadRight);
KEY_VAL(GamepadDpadUp);
KEY_VAL(GamepadDpadDown);
KEY_VAL(GamepadL1);
KEY_VAL(GamepadR1);
KEY_VAL(GamepadL2);
KEY_VAL(GamepadR2);
KEY_VAL(GamepadL3);
KEY_VAL(GamepadR3);
KEY_VAL(GamepadLStickLeft);
KEY_VAL(GamepadLStickRight);
KEY_VAL(GamepadLStickUp);
KEY_VAL(GamepadLStickDown);
KEY_VAL(GamepadRStickLeft);
KEY_VAL(GamepadRStickRight);
KEY_VAL(GamepadRStickUp);
KEY_VAL(GamepadRStickDown);
KEY_VAL(MouseLeft); KEY_VAL(MouseRight); KEY_VAL(MouseMiddle); KEY_VAL(MouseX1); KEY_VAL(MouseX2); KEY_VAL(MouseWheelX); KEY_VAL(MouseWheelY);
KEY_VAL(ReservedForModCtrl); KEY_VAL(ReservedForModShift); KEY_VAL(ReservedForModAlt); KEY_VAL(ReservedForModSuper);
KEY_VAL(NamedKey_END);
KEY_VAL(NamedKey_COUNT);
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
KEY_VAL(COUNT);
#endif
#undef KEY_VAL

#define MOD_VAL(F) static_assert((int)IGSharp_Mod_##F == (int)ImGuiMod_##F, "IGSharp_Mod_" #F " value drift")
MOD_VAL(None);
MOD_VAL(Ctrl);
MOD_VAL(Shift);
MOD_VAL(Alt);
MOD_VAL(Super);
MOD_VAL(Mask_);
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
MOD_VAL(Shortcut);
#endif
#undef MOD_VAL

#define COL_VAL(F) static_assert((int)IGSharp_Col_##F == (int)ImGuiCol_##F, "IGSharp_Col_" #F " value drift")
COL_VAL(Text);
COL_VAL(TextDisabled);
COL_VAL(WindowBg);
COL_VAL(ChildBg);
COL_VAL(PopupBg);
COL_VAL(Border);
COL_VAL(BorderShadow);
COL_VAL(FrameBg);
COL_VAL(FrameBgHovered);
COL_VAL(FrameBgActive);
COL_VAL(TitleBg);
COL_VAL(TitleBgActive);
COL_VAL(TitleBgCollapsed);
COL_VAL(MenuBarBg);
COL_VAL(ScrollbarBg);
COL_VAL(ScrollbarGrab);
COL_VAL(ScrollbarGrabHovered);
COL_VAL(ScrollbarGrabActive);
COL_VAL(CheckMark);
COL_VAL(SliderGrab);
COL_VAL(SliderGrabActive);
COL_VAL(Button);
COL_VAL(ButtonHovered);
COL_VAL(ButtonActive);
COL_VAL(Header);
COL_VAL(HeaderHovered);
COL_VAL(HeaderActive);
COL_VAL(Separator);
COL_VAL(SeparatorHovered);
COL_VAL(SeparatorActive);
COL_VAL(ResizeGrip);
COL_VAL(ResizeGripHovered);
COL_VAL(ResizeGripActive);
COL_VAL(InputTextCursor);
COL_VAL(TabHovered);
COL_VAL(Tab);
COL_VAL(TabSelected);
COL_VAL(TabSelectedOverline);
COL_VAL(TabDimmed);
COL_VAL(TabDimmedSelected);
COL_VAL(TabDimmedSelectedOverline);
COL_VAL(PlotLines);
COL_VAL(PlotLinesHovered);
COL_VAL(PlotHistogram);
COL_VAL(PlotHistogramHovered);
COL_VAL(TableHeaderBg);
COL_VAL(TableBorderStrong);
COL_VAL(TableBorderLight);
COL_VAL(TableRowBg);
COL_VAL(TableRowBgAlt);
COL_VAL(TextLink);
COL_VAL(TextSelectedBg);
COL_VAL(TreeLines);
COL_VAL(DragDropTarget);
COL_VAL(DragDropTargetBg);
COL_VAL(UnsavedMarker);
COL_VAL(NavCursor);
COL_VAL(NavWindowingHighlight);
COL_VAL(NavWindowingDimBg);
COL_VAL(ModalWindowDimBg);
COL_VAL(COUNT);
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
COL_VAL(TabActive);
COL_VAL(TabUnfocused);
COL_VAL(TabUnfocusedActive);
COL_VAL(NavHighlight);
#endif
#undef COL_VAL

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
