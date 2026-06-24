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

// --- IGSharp_Vec2 / IGSharp_Vec4 -------------------------------------------
// POD mirrors of ImVec2/ImVec4. Function-call paths convert by value, but these
// types are also embedded in the layout-mirrored IGSharp_Style/IGSharp_IO/
// IGSharp_DrawVert/IGSharp_PlatformImeData structs, so pin their layout directly.
static_assert(sizeof(IGSharp_Vec2) == sizeof(ImVec2), "IGSharp_Vec2 size mismatch with ImVec2");
static_assert(offsetof(IGSharp_Vec2, x) == offsetof(ImVec2, x), "IGSharp_Vec2.x");
static_assert(offsetof(IGSharp_Vec2, y) == offsetof(ImVec2, y), "IGSharp_Vec2.y");
static_assert(sizeof(IGSharp_Vec4) == sizeof(ImVec4), "IGSharp_Vec4 size mismatch with ImVec4");
static_assert(offsetof(IGSharp_Vec4, x) == offsetof(ImVec4, x), "IGSharp_Vec4.x");
static_assert(offsetof(IGSharp_Vec4, y) == offsetof(ImVec4, y), "IGSharp_Vec4.y");
static_assert(offsetof(IGSharp_Vec4, z) == offsetof(ImVec4, z), "IGSharp_Vec4.z");
static_assert(offsetof(IGSharp_Vec4, w) == offsetof(ImVec4, w), "IGSharp_Vec4.w");

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
#undef KEY_VAL

#define MOD_VAL(F) static_assert((int)IGSharp_Mod_##F == (int)ImGuiMod_##F, "IGSharp_Mod_" #F " value drift")
MOD_VAL(None);
MOD_VAL(Ctrl);
MOD_VAL(Shift);
MOD_VAL(Alt);
MOD_VAL(Super);
MOD_VAL(Mask_);
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
// Pin the member order itself (not just the total size): Size@0, Capacity@sizeof(int), Data@2*sizeof(int).
static_assert(offsetof(ImVector<ImWchar>, Size) == 0, "ImVector::Size not at offset 0");
static_assert(offsetof(ImVector<ImWchar>, Capacity) == sizeof(int), "ImVector::Capacity not at offset sizeof(int)");
static_assert(offsetof(ImVector<ImWchar>, Data) == 2 * sizeof(int), "ImVector::Data not at offset 2*sizeof(int)");

// ImWchar width: the wrapper hardcodes 'unsigned short' for every ImWchar parameter/field
// (glyph ranges, EllipsisChar, InputQueueCharacters_Data, ...). A IMGUI_USE_WCHAR32 build would
// silently break those; pin it here.
static_assert(sizeof(ImWchar) == sizeof(unsigned short), "ImWchar is not 16-bit; the C wrapper assumes unsigned short (do not define IMGUI_USE_WCHAR32)");

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

#define WINDOWFLAGS_VAL(F) static_assert((int)IGSharp_WindowFlags_##F == (int)ImGuiWindowFlags_##F, "IGSharp_WindowFlags_" #F " value drift")
WINDOWFLAGS_VAL(None);
WINDOWFLAGS_VAL(NoTitleBar);
WINDOWFLAGS_VAL(NoResize);
WINDOWFLAGS_VAL(NoMove);
WINDOWFLAGS_VAL(NoScrollbar);
WINDOWFLAGS_VAL(NoScrollWithMouse);
WINDOWFLAGS_VAL(NoCollapse);
WINDOWFLAGS_VAL(AlwaysAutoResize);
WINDOWFLAGS_VAL(NoBackground);
WINDOWFLAGS_VAL(NoSavedSettings);
WINDOWFLAGS_VAL(NoMouseInputs);
WINDOWFLAGS_VAL(MenuBar);
WINDOWFLAGS_VAL(HorizontalScrollbar);
WINDOWFLAGS_VAL(NoFocusOnAppearing);
WINDOWFLAGS_VAL(NoBringToFrontOnFocus);
WINDOWFLAGS_VAL(AlwaysVerticalScrollbar);
WINDOWFLAGS_VAL(AlwaysHorizontalScrollbar);
WINDOWFLAGS_VAL(NoNavInputs);
WINDOWFLAGS_VAL(NoNavFocus);
WINDOWFLAGS_VAL(UnsavedDocument);
WINDOWFLAGS_VAL(NoNav);
WINDOWFLAGS_VAL(NoDecoration);
WINDOWFLAGS_VAL(NoInputs);
WINDOWFLAGS_VAL(ChildWindow);
WINDOWFLAGS_VAL(Tooltip);
WINDOWFLAGS_VAL(Popup);
WINDOWFLAGS_VAL(Modal);
WINDOWFLAGS_VAL(ChildMenu);
#undef WINDOWFLAGS_VAL

#define CHILDFLAGS_VAL(F) static_assert((int)IGSharp_ChildFlags_##F == (int)ImGuiChildFlags_##F, "IGSharp_ChildFlags_" #F " value drift")
CHILDFLAGS_VAL(None);
CHILDFLAGS_VAL(Borders);
CHILDFLAGS_VAL(AlwaysUseWindowPadding);
CHILDFLAGS_VAL(ResizeX);
CHILDFLAGS_VAL(ResizeY);
CHILDFLAGS_VAL(AutoResizeX);
CHILDFLAGS_VAL(AutoResizeY);
CHILDFLAGS_VAL(AlwaysAutoResize);
CHILDFLAGS_VAL(FrameStyle);
CHILDFLAGS_VAL(NavFlattened);
#undef CHILDFLAGS_VAL

#define ITEMFLAGS_VAL(F) static_assert((int)IGSharp_ItemFlags_##F == (int)ImGuiItemFlags_##F, "IGSharp_ItemFlags_" #F " value drift")
ITEMFLAGS_VAL(None);
ITEMFLAGS_VAL(NoTabStop);
ITEMFLAGS_VAL(NoNav);
ITEMFLAGS_VAL(NoNavDefaultFocus);
ITEMFLAGS_VAL(ButtonRepeat);
ITEMFLAGS_VAL(AutoClosePopups);
ITEMFLAGS_VAL(AllowDuplicateId);
ITEMFLAGS_VAL(Disabled);
#undef ITEMFLAGS_VAL

#define ITF_VAL(F) static_assert((int)IGSharp_InputTextFlags_##F == (int)ImGuiInputTextFlags_##F, "IGSharp_InputTextFlags_" #F " value drift")
ITF_VAL(None);
ITF_VAL(CharsDecimal);
ITF_VAL(CharsHexadecimal);
ITF_VAL(CharsScientific);
ITF_VAL(CharsUppercase);
ITF_VAL(CharsNoBlank);
ITF_VAL(AllowTabInput);
ITF_VAL(EnterReturnsTrue);
ITF_VAL(EscapeClearsAll);
ITF_VAL(CtrlEnterForNewLine);
ITF_VAL(ReadOnly);
ITF_VAL(Password);
ITF_VAL(AlwaysOverwrite);
ITF_VAL(AutoSelectAll);
ITF_VAL(ParseEmptyRefVal);
ITF_VAL(DisplayEmptyRefVal);
ITF_VAL(NoHorizontalScroll);
ITF_VAL(NoUndoRedo);
ITF_VAL(ElideLeft);
ITF_VAL(CallbackCompletion);
ITF_VAL(CallbackHistory);
ITF_VAL(CallbackAlways);
ITF_VAL(CallbackCharFilter);
ITF_VAL(CallbackResize);
ITF_VAL(CallbackEdit);
ITF_VAL(WordWrap);
#undef ITF_VAL

#define POPUPFLAGS_VAL(F) static_assert((int)IGSharp_PopupFlags_##F == (int)ImGuiPopupFlags_##F, "IGSharp_PopupFlags_" #F " value drift")
POPUPFLAGS_VAL(None);
POPUPFLAGS_VAL(MouseButtonLeft);
POPUPFLAGS_VAL(MouseButtonRight);
POPUPFLAGS_VAL(MouseButtonMiddle);
POPUPFLAGS_VAL(NoReopen);
POPUPFLAGS_VAL(NoOpenOverExistingPopup);
POPUPFLAGS_VAL(NoOpenOverItems);
POPUPFLAGS_VAL(AnyPopupId);
POPUPFLAGS_VAL(AnyPopupLevel);
POPUPFLAGS_VAL(AnyPopup);
POPUPFLAGS_VAL(MouseButtonShift_);
POPUPFLAGS_VAL(MouseButtonMask_);
POPUPFLAGS_VAL(InvalidMask_);
#undef POPUPFLAGS_VAL

#define COMBOFLAGS_VAL(F) static_assert((int)IGSharp_ComboFlags_##F == (int)ImGuiComboFlags_##F, "IGSharp_ComboFlags_" #F " value drift")
COMBOFLAGS_VAL(None);
COMBOFLAGS_VAL(PopupAlignLeft);
COMBOFLAGS_VAL(HeightSmall);
COMBOFLAGS_VAL(HeightRegular);
COMBOFLAGS_VAL(HeightLarge);
COMBOFLAGS_VAL(HeightLargest);
COMBOFLAGS_VAL(NoArrowButton);
COMBOFLAGS_VAL(NoPreview);
COMBOFLAGS_VAL(WidthFitPreview);
COMBOFLAGS_VAL(HeightMask_);
#undef COMBOFLAGS_VAL

#define TABBARFLAGS_VAL(F) static_assert((int)IGSharp_TabBarFlags_##F == (int)ImGuiTabBarFlags_##F, "IGSharp_TabBarFlags_" #F " value drift")
TABBARFLAGS_VAL(None);
TABBARFLAGS_VAL(Reorderable);
TABBARFLAGS_VAL(AutoSelectNewTabs);
TABBARFLAGS_VAL(TabListPopupButton);
TABBARFLAGS_VAL(NoCloseWithMiddleMouseButton);
TABBARFLAGS_VAL(NoTabListScrollingButtons);
TABBARFLAGS_VAL(NoTooltip);
TABBARFLAGS_VAL(DrawSelectedOverline);
TABBARFLAGS_VAL(FittingPolicyMixed);
TABBARFLAGS_VAL(FittingPolicyShrink);
TABBARFLAGS_VAL(FittingPolicyScroll);
TABBARFLAGS_VAL(FittingPolicyMask_);
TABBARFLAGS_VAL(FittingPolicyDefault_);
#undef TABBARFLAGS_VAL

#define TABITEMFLAGS_VAL(F) static_assert((int)IGSharp_TabItemFlags_##F == (int)ImGuiTabItemFlags_##F, "IGSharp_TabItemFlags_" #F " value drift")
TABITEMFLAGS_VAL(None);
TABITEMFLAGS_VAL(UnsavedDocument);
TABITEMFLAGS_VAL(SetSelected);
TABITEMFLAGS_VAL(NoCloseWithMiddleMouseButton);
TABITEMFLAGS_VAL(NoPushId);
TABITEMFLAGS_VAL(NoTooltip);
TABITEMFLAGS_VAL(NoReorder);
TABITEMFLAGS_VAL(Leading);
TABITEMFLAGS_VAL(Trailing);
TABITEMFLAGS_VAL(NoAssumedClosure);
#undef TABITEMFLAGS_VAL

// IGSharp_FocusedFlags mirrors ImGuiFocusedFlags_ 1:1. Per-value asserts.
#define FOCUSEDFLAGS_VAL(F) static_assert((int)IGSharp_FocusedFlags_##F == (int)ImGuiFocusedFlags_##F, "IGSharp_FocusedFlags_" #F " value drift")
FOCUSEDFLAGS_VAL(None);
FOCUSEDFLAGS_VAL(ChildWindows);
FOCUSEDFLAGS_VAL(RootWindow);
FOCUSEDFLAGS_VAL(AnyWindow);
FOCUSEDFLAGS_VAL(NoPopupHierarchy);
FOCUSEDFLAGS_VAL(RootAndChildWindows);
#undef FOCUSEDFLAGS_VAL

#define HOVERED_VAL(F) static_assert((int)IGSharp_HoveredFlags_##F == (int)ImGuiHoveredFlags_##F, "IGSharp_HoveredFlags_" #F " value drift")
HOVERED_VAL(None);
HOVERED_VAL(ChildWindows);
HOVERED_VAL(RootWindow);
HOVERED_VAL(AnyWindow);
HOVERED_VAL(NoPopupHierarchy);
HOVERED_VAL(AllowWhenBlockedByPopup);
HOVERED_VAL(AllowWhenBlockedByActiveItem);
HOVERED_VAL(AllowWhenOverlappedByItem);
HOVERED_VAL(AllowWhenOverlappedByWindow);
HOVERED_VAL(AllowWhenDisabled);
HOVERED_VAL(NoNavOverride);
HOVERED_VAL(AllowWhenOverlapped);
HOVERED_VAL(RectOnly);
HOVERED_VAL(RootAndChildWindows);
HOVERED_VAL(ForTooltip);
HOVERED_VAL(Stationary);
HOVERED_VAL(DelayNone);
HOVERED_VAL(DelayShort);
HOVERED_VAL(DelayNormal);
HOVERED_VAL(NoSharedDelay);
#undef HOVERED_VAL

#define DRAGDROPFLAGS_VAL(F) static_assert((int)IGSharp_DragDropFlags_##F == (int)ImGuiDragDropFlags_##F, "IGSharp_DragDropFlags_" #F " value drift")
DRAGDROPFLAGS_VAL(None);
DRAGDROPFLAGS_VAL(SourceNoPreviewTooltip);
DRAGDROPFLAGS_VAL(SourceNoDisableHover);
DRAGDROPFLAGS_VAL(SourceNoHoldToOpenOthers);
DRAGDROPFLAGS_VAL(SourceAllowNullID);
DRAGDROPFLAGS_VAL(SourceExtern);
DRAGDROPFLAGS_VAL(PayloadAutoExpire);
DRAGDROPFLAGS_VAL(PayloadNoCrossContext);
DRAGDROPFLAGS_VAL(PayloadNoCrossProcess);
DRAGDROPFLAGS_VAL(AcceptBeforeDelivery);
DRAGDROPFLAGS_VAL(AcceptNoDrawDefaultRect);
DRAGDROPFLAGS_VAL(AcceptNoPreviewTooltip);
DRAGDROPFLAGS_VAL(AcceptDrawAsHovered);
DRAGDROPFLAGS_VAL(AcceptPeekOnly);
#undef DRAGDROPFLAGS_VAL

#define DATATYPE_VAL(F) static_assert((int)IGSharp_DataType_##F == (int)ImGuiDataType_##F, "IGSharp_DataType_" #F " value drift")
DATATYPE_VAL(S8);
DATATYPE_VAL(U8);
DATATYPE_VAL(S16);
DATATYPE_VAL(U16);
DATATYPE_VAL(S32);
DATATYPE_VAL(U32);
DATATYPE_VAL(S64);
DATATYPE_VAL(U64);
DATATYPE_VAL(Float);
DATATYPE_VAL(Double);
DATATYPE_VAL(Bool);
DATATYPE_VAL(String);
DATATYPE_VAL(COUNT);
#undef DATATYPE_VAL

#define SORTDIR_VAL(F) static_assert((int)IGSharp_SortDirection_##F == (int)ImGuiSortDirection_##F, "IGSharp_SortDirection_" #F " value drift")
SORTDIR_VAL(None);
SORTDIR_VAL(Ascending);
SORTDIR_VAL(Descending);
#undef SORTDIR_VAL

#define INPUTFLAGS_VAL(F) static_assert((int)IGSharp_InputFlags_##F == (int)ImGuiInputFlags_##F, "IGSharp_InputFlags_" #F " value drift")
INPUTFLAGS_VAL(None);
INPUTFLAGS_VAL(Repeat);
INPUTFLAGS_VAL(RouteActive);
INPUTFLAGS_VAL(RouteFocused);
INPUTFLAGS_VAL(RouteGlobal);
INPUTFLAGS_VAL(RouteAlways);
INPUTFLAGS_VAL(RouteOverFocused);
INPUTFLAGS_VAL(RouteOverActive);
INPUTFLAGS_VAL(RouteUnlessBgFocused);
INPUTFLAGS_VAL(RouteFromRootWindow);
INPUTFLAGS_VAL(Tooltip);
#undef INPUTFLAGS_VAL

#define CONFIGFLAGS_VAL(F) static_assert((int)IGSharp_ConfigFlags_##F == (int)ImGuiConfigFlags_##F, "IGSharp_ConfigFlags_" #F " value drift")
CONFIGFLAGS_VAL(None);
CONFIGFLAGS_VAL(NavEnableKeyboard);
CONFIGFLAGS_VAL(NavEnableGamepad);
CONFIGFLAGS_VAL(NoMouse);
CONFIGFLAGS_VAL(NoMouseCursorChange);
CONFIGFLAGS_VAL(NoKeyboard);
CONFIGFLAGS_VAL(IsSRGB);
CONFIGFLAGS_VAL(IsTouchScreen);
#undef CONFIGFLAGS_VAL

// ImGuiBackendFlags_ value drift checks
#define BACKENDFLAGS_VAL(F) static_assert((int)IGSharp_BackendFlags_##F == (int)ImGuiBackendFlags_##F, "IGSharp_BackendFlags_" #F " value drift")
BACKENDFLAGS_VAL(None);
BACKENDFLAGS_VAL(HasGamepad);
BACKENDFLAGS_VAL(HasMouseCursors);
BACKENDFLAGS_VAL(HasSetMousePos);
BACKENDFLAGS_VAL(RendererHasVtxOffset);
BACKENDFLAGS_VAL(RendererHasTextures);
#undef BACKENDFLAGS_VAL

#define STYLEVAR_VAL(F) static_assert((int)IGSharp_StyleVar_##F == (int)ImGuiStyleVar_##F, "IGSharp_StyleVar_" #F " value drift")
STYLEVAR_VAL(Alpha);
STYLEVAR_VAL(DisabledAlpha);
STYLEVAR_VAL(WindowPadding);
STYLEVAR_VAL(WindowRounding);
STYLEVAR_VAL(WindowBorderSize);
STYLEVAR_VAL(WindowMinSize);
STYLEVAR_VAL(WindowTitleAlign);
STYLEVAR_VAL(ChildRounding);
STYLEVAR_VAL(ChildBorderSize);
STYLEVAR_VAL(PopupRounding);
STYLEVAR_VAL(PopupBorderSize);
STYLEVAR_VAL(FramePadding);
STYLEVAR_VAL(FrameRounding);
STYLEVAR_VAL(FrameBorderSize);
STYLEVAR_VAL(ItemSpacing);
STYLEVAR_VAL(ItemInnerSpacing);
STYLEVAR_VAL(IndentSpacing);
STYLEVAR_VAL(CellPadding);
STYLEVAR_VAL(ScrollbarSize);
STYLEVAR_VAL(ScrollbarRounding);
STYLEVAR_VAL(ScrollbarPadding);
STYLEVAR_VAL(GrabMinSize);
STYLEVAR_VAL(GrabRounding);
STYLEVAR_VAL(ImageRounding);
STYLEVAR_VAL(ImageBorderSize);
STYLEVAR_VAL(TabRounding);
STYLEVAR_VAL(TabBorderSize);
STYLEVAR_VAL(TabMinWidthBase);
STYLEVAR_VAL(TabMinWidthShrink);
STYLEVAR_VAL(TabBarBorderSize);
STYLEVAR_VAL(TabBarOverlineSize);
STYLEVAR_VAL(TableAngledHeadersAngle);
STYLEVAR_VAL(TableAngledHeadersTextAlign);
STYLEVAR_VAL(TreeLinesSize);
STYLEVAR_VAL(TreeLinesRounding);
STYLEVAR_VAL(ButtonTextAlign);
STYLEVAR_VAL(SelectableTextAlign);
STYLEVAR_VAL(SeparatorSize);
STYLEVAR_VAL(SeparatorTextBorderSize);
STYLEVAR_VAL(SeparatorTextAlign);
STYLEVAR_VAL(SeparatorTextPadding);
STYLEVAR_VAL(COUNT);
#undef STYLEVAR_VAL

#define CEF_VAL(F) static_assert((int)IGSharp_ColorEditFlags_##F == (int)ImGuiColorEditFlags_##F, "IGSharp_ColorEditFlags_" #F " value drift")
CEF_VAL(None);
CEF_VAL(NoAlpha);
CEF_VAL(NoPicker);
CEF_VAL(NoOptions);
CEF_VAL(NoSmallPreview);
CEF_VAL(NoInputs);
CEF_VAL(NoTooltip);
CEF_VAL(NoLabel);
CEF_VAL(NoSidePreview);
CEF_VAL(NoDragDrop);
CEF_VAL(NoBorder);
CEF_VAL(NoColorMarkers);
CEF_VAL(AlphaOpaque);
CEF_VAL(AlphaNoBg);
CEF_VAL(AlphaPreviewHalf);
CEF_VAL(AlphaBar);
CEF_VAL(HDR);
CEF_VAL(DisplayRGB);
CEF_VAL(DisplayHSV);
CEF_VAL(DisplayHex);
CEF_VAL(Uint8);
CEF_VAL(Float);
CEF_VAL(PickerHueBar);
CEF_VAL(PickerHueWheel);
CEF_VAL(InputRGB);
CEF_VAL(InputHSV);
CEF_VAL(DefaultOptions_);
CEF_VAL(AlphaMask_);
CEF_VAL(DisplayMask_);
CEF_VAL(DataTypeMask_);
CEF_VAL(PickerMask_);
CEF_VAL(InputMask_);
#undef CEF_VAL

#define SLIDERFLAGS_VAL(F) static_assert((int)IGSharp_SliderFlags_##F == (int)ImGuiSliderFlags_##F, "IGSharp_SliderFlags_" #F " value drift")
SLIDERFLAGS_VAL(None);
SLIDERFLAGS_VAL(Logarithmic);
SLIDERFLAGS_VAL(NoRoundToFormat);
SLIDERFLAGS_VAL(NoInput);
SLIDERFLAGS_VAL(WrapAround);
SLIDERFLAGS_VAL(ClampOnInput);
SLIDERFLAGS_VAL(ClampZeroRange);
SLIDERFLAGS_VAL(NoSpeedTweaks);
SLIDERFLAGS_VAL(ColorMarkers);
SLIDERFLAGS_VAL(AlwaysClamp);
SLIDERFLAGS_VAL(InvalidMask_);
#undef SLIDERFLAGS_VAL

#define MOUSECURSOR_VAL(F) static_assert((int)IGSharp_MouseCursor_##F == (int)ImGuiMouseCursor_##F, "IGSharp_MouseCursor_" #F " value drift")
MOUSECURSOR_VAL(None);
MOUSECURSOR_VAL(Arrow);
MOUSECURSOR_VAL(TextInput);
MOUSECURSOR_VAL(ResizeAll);
MOUSECURSOR_VAL(ResizeNS);
MOUSECURSOR_VAL(ResizeEW);
MOUSECURSOR_VAL(ResizeNESW);
MOUSECURSOR_VAL(ResizeNWSE);
MOUSECURSOR_VAL(Hand);
MOUSECURSOR_VAL(Wait);
MOUSECURSOR_VAL(Progress);
MOUSECURSOR_VAL(NotAllowed);
MOUSECURSOR_VAL(COUNT);
#undef MOUSECURSOR_VAL

#define MOUSESOURCE_VAL(F) static_assert((int)IGSharp_MouseSource_##F == (int)ImGuiMouseSource_##F, "IGSharp_MouseSource_" #F " value drift")
MOUSESOURCE_VAL(Mouse);
MOUSESOURCE_VAL(TouchScreen);
MOUSESOURCE_VAL(Pen);
MOUSESOURCE_VAL(COUNT);
#undef MOUSESOURCE_VAL

#define COND_VAL(F) static_assert((int)IGSharp_Cond_##F == (int)ImGuiCond_##F, "IGSharp_Cond_" #F " value drift")
COND_VAL(None);
COND_VAL(Always);
COND_VAL(Once);
COND_VAL(FirstUseEver);
COND_VAL(Appearing);
#undef COND_VAL

// ---- ImGuiTreeNodeFlags_ ----
#define TREENODEFLAGS_VAL(F) static_assert((int)IGSharp_TreeNodeFlags_##F == (int)ImGuiTreeNodeFlags_##F, "IGSharp_TreeNodeFlags_" #F " value drift")
TREENODEFLAGS_VAL(None);
TREENODEFLAGS_VAL(Selected);
TREENODEFLAGS_VAL(Framed);
TREENODEFLAGS_VAL(AllowOverlap);
TREENODEFLAGS_VAL(NoTreePushOnOpen);
TREENODEFLAGS_VAL(NoAutoOpenOnLog);
TREENODEFLAGS_VAL(DefaultOpen);
TREENODEFLAGS_VAL(OpenOnDoubleClick);
TREENODEFLAGS_VAL(OpenOnArrow);
TREENODEFLAGS_VAL(Leaf);
TREENODEFLAGS_VAL(Bullet);
TREENODEFLAGS_VAL(FramePadding);
TREENODEFLAGS_VAL(SpanAvailWidth);
TREENODEFLAGS_VAL(SpanFullWidth);
TREENODEFLAGS_VAL(SpanLabelWidth);
TREENODEFLAGS_VAL(SpanAllColumns);
TREENODEFLAGS_VAL(LabelSpanAllColumns);
TREENODEFLAGS_VAL(NavLeftJumpsToParent);
TREENODEFLAGS_VAL(CollapsingHeader);
TREENODEFLAGS_VAL(DrawLinesNone);
TREENODEFLAGS_VAL(DrawLinesFull);
TREENODEFLAGS_VAL(DrawLinesToNodes);
#undef TREENODEFLAGS_VAL

#define SELECTABLEFLAGS_VAL(F) static_assert((int)IGSharp_SelectableFlags_##F == (int)ImGuiSelectableFlags_##F, "IGSharp_SelectableFlags_" #F " value drift")
SELECTABLEFLAGS_VAL(None);
SELECTABLEFLAGS_VAL(NoAutoClosePopups);
SELECTABLEFLAGS_VAL(SpanAllColumns);
SELECTABLEFLAGS_VAL(AllowDoubleClick);
SELECTABLEFLAGS_VAL(Disabled);
SELECTABLEFLAGS_VAL(AllowOverlap);
SELECTABLEFLAGS_VAL(Highlight);
SELECTABLEFLAGS_VAL(SelectOnNav);
#undef SELECTABLEFLAGS_VAL

#define DIR_VAL(F) static_assert((int)IGSharp_Dir_##F == (int)ImGuiDir_##F, "IGSharp_Dir_" #F " value drift")
DIR_VAL(None);
DIR_VAL(Left);
DIR_VAL(Right);
DIR_VAL(Up);
DIR_VAL(Down);
DIR_VAL(COUNT);
#undef DIR_VAL

#define BTNFLAGS_VAL(F) static_assert((int)IGSharp_ButtonFlags_##F == (int)ImGuiButtonFlags_##F, "IGSharp_ButtonFlags_" #F " value drift")
BTNFLAGS_VAL(None);
BTNFLAGS_VAL(MouseButtonLeft);
BTNFLAGS_VAL(MouseButtonRight);
BTNFLAGS_VAL(MouseButtonMiddle);
BTNFLAGS_VAL(MouseButtonMask_);
BTNFLAGS_VAL(EnableNav);
BTNFLAGS_VAL(AllowOverlap);
#undef BTNFLAGS_VAL

#define MOUSEBUTTON_VAL(F) static_assert((int)IGSharp_MouseButton_##F == (int)ImGuiMouseButton_##F, "IGSharp_MouseButton_" #F " value drift")
MOUSEBUTTON_VAL(Left);
MOUSEBUTTON_VAL(Right);
MOUSEBUTTON_VAL(Middle);
MOUSEBUTTON_VAL(COUNT);
#undef MOUSEBUTTON_VAL

#define TABLEFLAGS_VAL(F) static_assert((int)IGSharp_TableFlags_##F == (int)ImGuiTableFlags_##F, "IGSharp_TableFlags_" #F " value drift")
TABLEFLAGS_VAL(None);
TABLEFLAGS_VAL(Resizable);
TABLEFLAGS_VAL(Reorderable);
TABLEFLAGS_VAL(Hideable);
TABLEFLAGS_VAL(Sortable);
TABLEFLAGS_VAL(NoSavedSettings);
TABLEFLAGS_VAL(ContextMenuInBody);
TABLEFLAGS_VAL(RowBg);
TABLEFLAGS_VAL(BordersInnerH);
TABLEFLAGS_VAL(BordersOuterH);
TABLEFLAGS_VAL(BordersInnerV);
TABLEFLAGS_VAL(BordersOuterV);
TABLEFLAGS_VAL(BordersH);
TABLEFLAGS_VAL(BordersV);
TABLEFLAGS_VAL(BordersInner);
TABLEFLAGS_VAL(BordersOuter);
TABLEFLAGS_VAL(Borders);
TABLEFLAGS_VAL(NoBordersInBody);
TABLEFLAGS_VAL(NoBordersInBodyUntilResize);
TABLEFLAGS_VAL(SizingFixedFit);
TABLEFLAGS_VAL(SizingFixedSame);
TABLEFLAGS_VAL(SizingStretchProp);
TABLEFLAGS_VAL(SizingStretchSame);
TABLEFLAGS_VAL(NoHostExtendX);
TABLEFLAGS_VAL(NoHostExtendY);
TABLEFLAGS_VAL(NoKeepColumnsVisible);
TABLEFLAGS_VAL(PreciseWidths);
TABLEFLAGS_VAL(NoClip);
TABLEFLAGS_VAL(PadOuterX);
TABLEFLAGS_VAL(NoPadOuterX);
TABLEFLAGS_VAL(NoPadInnerX);
TABLEFLAGS_VAL(ScrollX);
TABLEFLAGS_VAL(ScrollY);
TABLEFLAGS_VAL(SortMulti);
TABLEFLAGS_VAL(SortTristate);
TABLEFLAGS_VAL(HighlightHoveredColumn);
#undef TABLEFLAGS_VAL

#define TBLCOL_VAL(F) static_assert((int)IGSharp_TableColumnFlags_##F == (int)ImGuiTableColumnFlags_##F, "IGSharp_TableColumnFlags_" #F " value drift")
TBLCOL_VAL(None);
TBLCOL_VAL(Disabled);
TBLCOL_VAL(DefaultHide);
TBLCOL_VAL(DefaultSort);
TBLCOL_VAL(WidthStretch);
TBLCOL_VAL(WidthFixed);
TBLCOL_VAL(NoResize);
TBLCOL_VAL(NoReorder);
TBLCOL_VAL(NoHide);
TBLCOL_VAL(NoClip);
TBLCOL_VAL(NoSort);
TBLCOL_VAL(NoSortAscending);
TBLCOL_VAL(NoSortDescending);
TBLCOL_VAL(NoHeaderLabel);
TBLCOL_VAL(NoHeaderWidth);
TBLCOL_VAL(PreferSortAscending);
TBLCOL_VAL(PreferSortDescending);
TBLCOL_VAL(IndentEnable);
TBLCOL_VAL(IndentDisable);
TBLCOL_VAL(AngledHeader);
TBLCOL_VAL(IsEnabled);
TBLCOL_VAL(IsVisible);
TBLCOL_VAL(IsSorted);
TBLCOL_VAL(IsHovered);
#undef TBLCOL_VAL

static_assert((int)IGSharp_TableRowFlags_None == (int)ImGuiTableRowFlags_None, "IGSharp_TableRowFlags_None value drift");
static_assert((int)IGSharp_TableRowFlags_Headers == (int)ImGuiTableRowFlags_Headers, "IGSharp_TableRowFlags_Headers value drift");

static_assert((int)IGSharp_TableBgTarget_None  == (int)ImGuiTableBgTarget_None,  "IGSharp_TableBgTarget_None value drift");
static_assert((int)IGSharp_TableBgTarget_RowBg0 == (int)ImGuiTableBgTarget_RowBg0, "IGSharp_TableBgTarget_RowBg0 value drift");
static_assert((int)IGSharp_TableBgTarget_RowBg1 == (int)ImGuiTableBgTarget_RowBg1, "IGSharp_TableBgTarget_RowBg1 value drift");
static_assert((int)IGSharp_TableBgTarget_CellBg == (int)ImGuiTableBgTarget_CellBg, "IGSharp_TableBgTarget_CellBg value drift");

#define LISTCLIPPERFLAGS_VAL(F) static_assert((int)IGSharp_ListClipperFlags_##F == (int)ImGuiListClipperFlags_##F, "IGSharp_ListClipperFlags_" #F " value drift")
LISTCLIPPERFLAGS_VAL(None);
LISTCLIPPERFLAGS_VAL(NoSetTableRowCounters);
#undef LISTCLIPPERFLAGS_VAL

#define MSF_VAL(F) static_assert((int)IGSharp_MultiSelectFlags_##F == (int)ImGuiMultiSelectFlags_##F, "IGSharp_MultiSelectFlags_" #F " value drift")
MSF_VAL(None);
MSF_VAL(SingleSelect);
MSF_VAL(NoSelectAll);
MSF_VAL(NoRangeSelect);
MSF_VAL(NoAutoSelect);
MSF_VAL(NoAutoClear);
MSF_VAL(NoAutoClearOnReselect);
MSF_VAL(BoxSelect1d);
MSF_VAL(BoxSelect2d);
MSF_VAL(BoxSelectNoScroll);
MSF_VAL(ClearOnEscape);
MSF_VAL(ClearOnClickVoid);
MSF_VAL(ScopeWindow);
MSF_VAL(ScopeRect);
MSF_VAL(SelectOnAuto);
MSF_VAL(SelectOnClickAlways);
MSF_VAL(SelectOnClickRelease);
MSF_VAL(NavWrapX);
MSF_VAL(NoSelectOnRightClick);
MSF_VAL(SelectOnMask_);
#undef MSF_VAL

static_assert((int)IGSharp_SelectionRequestType_None    == (int)ImGuiSelectionRequestType_None,    "IGSharp_SelectionRequestType_None value drift");
static_assert((int)IGSharp_SelectionRequestType_SetAll  == (int)ImGuiSelectionRequestType_SetAll,  "IGSharp_SelectionRequestType_SetAll value drift");
static_assert((int)IGSharp_SelectionRequestType_SetRange == (int)ImGuiSelectionRequestType_SetRange, "IGSharp_SelectionRequestType_SetRange value drift");

// ImDrawFlags_
#define DRAWFLAGS_VAL(F) static_assert((int)IGSharp_DrawFlags_##F == (int)ImDrawFlags_##F, "IGSharp_DrawFlags_" #F " value drift")
DRAWFLAGS_VAL(None);
DRAWFLAGS_VAL(Closed);
DRAWFLAGS_VAL(RoundCornersTopLeft);
DRAWFLAGS_VAL(RoundCornersTopRight);
DRAWFLAGS_VAL(RoundCornersBottomLeft);
DRAWFLAGS_VAL(RoundCornersBottomRight);
DRAWFLAGS_VAL(RoundCornersNone);
DRAWFLAGS_VAL(RoundCornersTop);
DRAWFLAGS_VAL(RoundCornersBottom);
DRAWFLAGS_VAL(RoundCornersLeft);
DRAWFLAGS_VAL(RoundCornersRight);
DRAWFLAGS_VAL(RoundCornersAll);
DRAWFLAGS_VAL(RoundCornersDefault_);
DRAWFLAGS_VAL(RoundCornersMask_);
#undef DRAWFLAGS_VAL

// ImDrawListFlags_
#define DRAWLISTFLAGS_VAL(F) static_assert((int)IGSharp_DrawListFlags_##F == (int)ImDrawListFlags_##F, "IGSharp_DrawListFlags_" #F " value drift")
DRAWLISTFLAGS_VAL(None);
DRAWLISTFLAGS_VAL(AntiAliasedLines);
DRAWLISTFLAGS_VAL(AntiAliasedLinesUseTex);
DRAWLISTFLAGS_VAL(AntiAliasedFill);
DRAWLISTFLAGS_VAL(AllowVtxOffset);
#undef DRAWLISTFLAGS_VAL

// ImDrawVert
#ifndef IMGUI_OVERRIDE_DRAWVERT_STRUCT_LAYOUT
static_assert(sizeof(IGSharp_DrawVert) == sizeof(ImDrawVert), "IGSharp_DrawVert size mismatch with ImDrawVert");
static_assert(offsetof(IGSharp_DrawVert, pos) == offsetof(ImDrawVert, pos), "IGSharp_DrawVert.pos");
static_assert(offsetof(IGSharp_DrawVert, uv) == offsetof(ImDrawVert, uv), "IGSharp_DrawVert.uv");
static_assert(offsetof(IGSharp_DrawVert, col) == offsetof(ImDrawVert, col), "IGSharp_DrawVert.col");
#endif

// ImDrawIdx: the wrapper bakes in 16-bit indices (PrimWriteIdx/GetIdxBufferData document unsigned short).
static_assert(sizeof(ImDrawIdx) == sizeof(unsigned short), "ImDrawIdx is not 16-bit; the C wrapper assumes unsigned short index buffers");
// (ImDrawCallback_ResetRenderState == (ImDrawCallback)-8 cannot be static_assert'd: a function-pointer
//  cast is not a constant expression. IGSHARP_DRAWCALLBACK_RESETRENDERSTATE mirrors the -8 value by hand.)

// ImTextureFormat
#define TEXFMT_VAL(F) static_assert((int)IGSharp_TextureFormat_##F == (int)ImTextureFormat_##F, "IGSharp_TextureFormat_" #F " value drift")
TEXFMT_VAL(RGBA32);
TEXFMT_VAL(Alpha8);
#undef TEXFMT_VAL

// ImTextureStatus
#define TEXSTATUS_VAL(F) static_assert((int)IGSharp_TextureStatus_##F == (int)ImTextureStatus_##F, "IGSharp_TextureStatus_" #F " value drift")
TEXSTATUS_VAL(OK);
TEXSTATUS_VAL(Destroyed);
TEXSTATUS_VAL(WantCreate);
TEXSTATUS_VAL(WantUpdates);
TEXSTATUS_VAL(WantDestroy);
#undef TEXSTATUS_VAL

// ImTextureRect
static_assert(sizeof(IGSharp_TextureRect) == sizeof(ImTextureRect), "IGSharp_TextureRect size mismatch with ImTextureRect");
static_assert(offsetof(IGSharp_TextureRect, x) == offsetof(ImTextureRect, x), "IGSharp_TextureRect.x");
static_assert(offsetof(IGSharp_TextureRect, y) == offsetof(ImTextureRect, y), "IGSharp_TextureRect.y");
static_assert(offsetof(IGSharp_TextureRect, w) == offsetof(ImTextureRect, w), "IGSharp_TextureRect.w");
static_assert(offsetof(IGSharp_TextureRect, h) == offsetof(ImTextureRect, h), "IGSharp_TextureRect.h");

// ImTextureID (passed across the C API as unsigned long long; sentinel mirrored as IGSHARP_TEXTUREID_INVALID)
static_assert(sizeof(ImTextureID) == sizeof(unsigned long long), "ImTextureID is not 64-bit; the C wrapper passes it as unsigned long long");
static_assert((unsigned long long)ImTextureID_Invalid == IGSHARP_TEXTUREID_INVALID, "IGSHARP_TEXTUREID_INVALID drift from ImTextureID_Invalid");

// ImFontAtlasFlags_
#define FONTATLASFLAGS_VAL(F) static_assert((int)IGSharp_FontAtlasFlags_##F == (int)ImFontAtlasFlags_##F, "IGSharp_FontAtlasFlags_" #F " value drift")
FONTATLASFLAGS_VAL(None);
FONTATLASFLAGS_VAL(NoPowerOfTwoHeight);
FONTATLASFLAGS_VAL(NoMouseCursors);
FONTATLASFLAGS_VAL(NoBakedLines);
#undef FONTATLASFLAGS_VAL

// ImFontFlags_
#define FONTFLAGS_VAL(F) static_assert((int)IGSharp_FontFlags_##F == (int)ImFontFlags_##F, "IGSharp_FontFlags_" #F " value drift")
FONTFLAGS_VAL(None);
FONTFLAGS_VAL(NoLoadError);
FONTFLAGS_VAL(NoLoadGlyphs);
FONTFLAGS_VAL(LockBakedSizes);
#undef FONTFLAGS_VAL

// ImFontAtlasRect mirror
static_assert(sizeof(IGSharp_FontAtlasRect) == sizeof(ImFontAtlasRect), "IGSharp_FontAtlasRect size mismatch with ImFontAtlasRect");
static_assert(offsetof(IGSharp_FontAtlasRect, x)   == offsetof(ImFontAtlasRect, x),   "IGSharp_FontAtlasRect.x");
static_assert(offsetof(IGSharp_FontAtlasRect, y)   == offsetof(ImFontAtlasRect, y),   "IGSharp_FontAtlasRect.y");
static_assert(offsetof(IGSharp_FontAtlasRect, w)   == offsetof(ImFontAtlasRect, w),   "IGSharp_FontAtlasRect.w");
static_assert(offsetof(IGSharp_FontAtlasRect, h)   == offsetof(ImFontAtlasRect, h),   "IGSharp_FontAtlasRect.h");
static_assert(offsetof(IGSharp_FontAtlasRect, uv0) == offsetof(ImFontAtlasRect, uv0), "IGSharp_FontAtlasRect.uv0");
static_assert(offsetof(IGSharp_FontAtlasRect, uv1) == offsetof(ImFontAtlasRect, uv1), "IGSharp_FontAtlasRect.uv1");

// ImGuiViewportFlags_
#define VPFLAG_VAL(F) static_assert((int)IGSharp_ViewportFlags_##F == (int)ImGuiViewportFlags_##F, "IGSharp_ViewportFlags_" #F " value drift")
VPFLAG_VAL(None);
VPFLAG_VAL(IsPlatformWindow);
VPFLAG_VAL(IsPlatformMonitor);
VPFLAG_VAL(OwnedByApp);
#undef VPFLAG_VAL

// --- IGSharp_PlatformImeData -----------------------------------------------

static_assert(sizeof(IGSharp_PlatformImeData) == sizeof(ImGuiPlatformImeData), "IGSharp_PlatformImeData size mismatch with ImGuiPlatformImeData");
static_assert(offsetof(IGSharp_PlatformImeData, WantVisible)     == offsetof(ImGuiPlatformImeData, WantVisible),     "IGSharp_PlatformImeData.WantVisible");
static_assert(offsetof(IGSharp_PlatformImeData, WantTextInput)   == offsetof(ImGuiPlatformImeData, WantTextInput),   "IGSharp_PlatformImeData.WantTextInput");
static_assert(offsetof(IGSharp_PlatformImeData, InputPos)        == offsetof(ImGuiPlatformImeData, InputPos),        "IGSharp_PlatformImeData.InputPos");
static_assert(offsetof(IGSharp_PlatformImeData, InputLineHeight) == offsetof(ImGuiPlatformImeData, InputLineHeight), "IGSharp_PlatformImeData.InputLineHeight");
static_assert(offsetof(IGSharp_PlatformImeData, ViewportId)      == offsetof(ImGuiPlatformImeData, ViewportId),      "IGSharp_PlatformImeData.ViewportId");

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
