// dear imgui sharp

#pragma once

//-----------------------------------------------------------------------------
// [SECTION] Header mess
//-----------------------------------------------------------------------------

#include <stddef.h>
#ifndef __cplusplus
#include <stdbool.h>
#endif

// Export macro
#if defined(_WIN32)
    #if defined(IMGUI_SHARP_EXPORT)
        #define IGSHARP_API extern "C" __declspec(dllexport)
    #else
        #define IGSHARP_API extern "C" __declspec(dllimport)
    #endif
#else
    #if defined(IMGUI_SHARP_EXPORT)
        #define IGSHARP_API extern "C" __attribute__((visibility("default")))
    #else
        #define IGSHARP_API extern "C"
    #endif
#endif

IGSHARP_API void IGSharp_CheckVersion(void);

//-----------------------------------------------------------------------------
// [SECTION] Forward declarations and basic types
//-----------------------------------------------------------------------------

// Forward declarations: ImGui layer
typedef struct IGSharp_Context IGSharp_Context;
typedef struct IGSharp_IO    IGSharp_IO;
typedef struct IGSharp_Style IGSharp_Style;

// Callback typedefs
typedef int         (*IGSharp_InputTextCallback)(void* data); // data = ImGuiInputTextCallbackData*
typedef float       (*IGSharp_PlotValuesGetter)(void* data, int idx);

typedef struct {
    float x, y;
} IGSharp_Vec2;

typedef struct {
    float x, y, z, w;
} IGSharp_Vec4;

typedef struct {
    bool  Down;
    float DownDuration;
    float DownDurationPrev;
    float AnalogValue;
} IGSharp_KeyData;

//-----------------------------------------------------------------------------
// [SECTION] Texture identifiers (ImTextureID, ImTextureRef)
//-----------------------------------------------------------------------------
// (no wrappers yet)

//-----------------------------------------------------------------------------
// [SECTION] Dear ImGui end-user API functions
// (Note that ImGui:: being a namespace, you can add extra ImGui:: functions in your own separate file. Please don't modify imgui source files!)
//-----------------------------------------------------------------------------

// Context creation and access
IGSHARP_API IGSharp_Context* IGSharp_CreateContext(void); // MISSING: ImFontAtlas
IGSHARP_API void             IGSharp_DestroyContext(IGSharp_Context* ctx);
IGSHARP_API IGSharp_Context* IGSharp_GetCurrentContext(void);
IGSHARP_API void             IGSharp_SetCurrentContext(IGSharp_Context* ctx);

// Main
IGSHARP_API IGSharp_IO*    IGSharp_GetIO(void);
IGSHARP_API IGSharp_Style* IGSharp_GetStyle(void);
// MISSING: GetPlatformIO
IGSHARP_API void  IGSharp_NewFrame(void);
IGSHARP_API void  IGSharp_EndFrame(void);
IGSHARP_API void  IGSharp_Render(void);
IGSHARP_API void* IGSharp_GetDrawData(void);

// Demo, Debug, Information
IGSHARP_API void        IGSharp_ShowDemoWindow(bool* p_open);
IGSHARP_API void        IGSharp_ShowMetricsWindow(bool* p_open);
IGSHARP_API void        IGSharp_ShowDebugLogWindow(bool* p_open);
IGSHARP_API void        IGSharp_ShowIDStackToolWindow(bool* p_open);
IGSHARP_API void        IGSharp_ShowAboutWindow(bool* p_open);
IGSHARP_API void        IGSharp_ShowStyleEditor(void); // MISSING: ImGuiStyle
IGSHARP_API bool        IGSharp_ShowStyleSelector(const char* label);
IGSHARP_API void        IGSharp_ShowFontSelector(const char* label);
IGSHARP_API void        IGSharp_ShowUserGuide(void);
IGSHARP_API const char* IGSharp_GetVersion(void);

// Styles
IGSHARP_API void IGSharp_StyleColorsDark(void);
IGSHARP_API void IGSharp_StyleColorsLight(void);
IGSHARP_API void IGSharp_StyleColorsClassic(void);

// Windows
IGSHARP_API bool IGSharp_Begin(const char* name, bool* p_open, int flags);
IGSHARP_API void IGSharp_End(void);

// Child Windows
IGSHARP_API bool IGSharp_BeginChild(const char* str_id, IGSharp_Vec2 size, int child_flags, int window_flags);
IGSHARP_API void IGSharp_EndChild(void);

// Windows Utilities
IGSHARP_API bool         IGSharp_IsWindowAppearing(void);
IGSHARP_API bool         IGSharp_IsWindowCollapsed(void);
IGSHARP_API bool         IGSharp_IsWindowFocused(int flags);
IGSHARP_API bool         IGSharp_IsWindowHovered(int flags);
IGSHARP_API IGSharp_Vec2 IGSharp_GetWindowPos(void);
IGSHARP_API IGSharp_Vec2 IGSharp_GetWindowSize(void);
IGSHARP_API float        IGSharp_GetWindowWidth(void);
IGSHARP_API float        IGSharp_GetWindowHeight(void);

// Window manipulation
IGSHARP_API void IGSharp_SetNextWindowPos(IGSharp_Vec2 pos, int cond, IGSharp_Vec2 pivot);
IGSHARP_API void IGSharp_SetNextWindowSize(IGSharp_Vec2 size, int cond);
IGSHARP_API void IGSharp_SetNextWindowSizeConstraints(IGSharp_Vec2 size_min, IGSharp_Vec2 size_max);
IGSHARP_API void IGSharp_SetNextWindowContentSize(IGSharp_Vec2 size);
IGSHARP_API void IGSharp_SetNextWindowCollapsed(bool collapsed, int cond);
IGSHARP_API void IGSharp_SetNextWindowFocus(void);
IGSHARP_API void IGSharp_SetNextWindowScroll(IGSharp_Vec2 scroll);
IGSHARP_API void IGSharp_SetNextWindowBgAlpha(float alpha);

// Windows Scrolling
IGSHARP_API float IGSharp_GetScrollX(void);
IGSHARP_API float IGSharp_GetScrollY(void);
IGSHARP_API void  IGSharp_SetScrollX(float scroll_x);
IGSHARP_API void  IGSharp_SetScrollY(float scroll_y);
IGSHARP_API float IGSharp_GetScrollMaxX(void);
IGSHARP_API float IGSharp_GetScrollMaxY(void);
IGSHARP_API void  IGSharp_SetScrollHereX(float center_x_ratio);
IGSHARP_API void  IGSharp_SetScrollHereY(float center_y_ratio);
IGSHARP_API void  IGSharp_SetScrollFromPosX(float local_x, float center_x_ratio);
IGSHARP_API void  IGSharp_SetScrollFromPosY(float local_y, float center_y_ratio);

// Parameters stacks (font)
IGSHARP_API void  IGSharp_PushFont(void* font, float font_size_base_unscaled);
IGSHARP_API void  IGSharp_PopFont(void);
IGSHARP_API void* IGSharp_GetFont(void);
IGSHARP_API float IGSharp_GetFontSize(void);

// Parameters stacks (shared)
IGSHARP_API void IGSharp_PushStyleColorU32(int idx, unsigned int col);
IGSHARP_API void IGSharp_PushStyleColorVec4(int idx, IGSharp_Vec4 col);
IGSHARP_API void IGSharp_PopStyleColor(int count);
IGSHARP_API void IGSharp_PushStyleVarFloat(int idx, float val);
IGSHARP_API void IGSharp_PushStyleVarVec2(int idx, IGSharp_Vec2 val);
IGSHARP_API void IGSharp_PopStyleVar(int count);
IGSHARP_API void IGSharp_PushItemFlag(int option, bool enabled);
IGSHARP_API void IGSharp_PopItemFlag(void);

// Parameters stacks (current window)
IGSHARP_API void  IGSharp_PushItemWidth(float item_width);
IGSHARP_API void  IGSharp_PopItemWidth(void);
IGSHARP_API void  IGSharp_SetNextItemWidth(float item_width);
IGSHARP_API float IGSharp_CalcItemWidth(void);
IGSHARP_API void  IGSharp_PushTextWrapPos(float wrap_local_pos_x);
IGSHARP_API void  IGSharp_PopTextWrapPos(void);

// Style read access
IGSHARP_API unsigned int IGSharp_GetColorU32(int idx, float alpha_mul);
IGSHARP_API unsigned int IGSharp_GetColorU32Vec4(IGSharp_Vec4 col);
IGSHARP_API unsigned int IGSharp_GetColorU32Packed(unsigned int col, float alpha_mul);

// Layout cursor positioning
IGSHARP_API IGSharp_Vec2 IGSharp_GetCursorScreenPos(void);
IGSHARP_API void         IGSharp_SetCursorScreenPos(IGSharp_Vec2 screen_pos);
IGSHARP_API IGSharp_Vec2 IGSharp_GetCursorPos(void);
IGSHARP_API void         IGSharp_SetCursorPos(IGSharp_Vec2 local_pos);

// Other layout functions
IGSHARP_API void         IGSharp_Separator(void);
IGSHARP_API void         IGSharp_SameLine(float offset_from_start_x, float spacing);
IGSHARP_API void         IGSharp_NewLine(void);
IGSHARP_API void         IGSharp_Spacing(void);
IGSHARP_API void         IGSharp_Dummy(IGSharp_Vec2 size);
IGSHARP_API void         IGSharp_Indent(float indent_w);
IGSHARP_API void         IGSharp_Unindent(float indent_w);
IGSHARP_API void         IGSharp_BeginGroup(void);
IGSHARP_API void         IGSharp_EndGroup(void);
IGSHARP_API void         IGSharp_AlignTextToFramePadding(void);
IGSHARP_API float        IGSharp_GetTextLineHeight(void);
IGSHARP_API float        IGSharp_GetTextLineHeightWithSpacing(void);
IGSHARP_API float        IGSharp_GetFrameHeight(void);
IGSHARP_API float        IGSharp_GetFrameHeightWithSpacing(void);
IGSHARP_API IGSharp_Vec2 IGSharp_GetContentRegionAvail(void);

// ID stack/scopes
IGSHARP_API void         IGSharp_PushIDStr(const char* str_id);
IGSHARP_API void         IGSharp_PushIDInt(int int_id);
IGSHARP_API void         IGSharp_PopID(void);
IGSHARP_API unsigned int IGSharp_GetIDStr(const char* str_id);

// Widgets: Text
IGSHARP_API void IGSharp_TextUnformatted(const char* text, const char* text_end);
IGSHARP_API void IGSharp_Text(const char* text);
IGSHARP_API void IGSharp_TextColored(IGSharp_Vec4 col, const char* text);
IGSHARP_API void IGSharp_TextDisabled(const char* text);
IGSHARP_API void IGSharp_TextWrapped(const char* text);
IGSHARP_API void IGSharp_LabelText(const char* label, const char* text);
IGSHARP_API void IGSharp_BulletText(const char* text);
IGSHARP_API void IGSharp_SeparatorText(const char* label);

// Widgets: Main
IGSHARP_API bool IGSharp_Button(const char* label, IGSharp_Vec2 size);
IGSHARP_API bool IGSharp_SmallButton(const char* label);
IGSHARP_API bool IGSharp_InvisibleButton(const char* str_id, IGSharp_Vec2 size, int flags);
IGSHARP_API bool IGSharp_ArrowButton(const char* str_id, int dir);
IGSHARP_API bool IGSharp_Checkbox(const char* label, bool* v);
IGSHARP_API bool IGSharp_RadioButton(const char* label, bool active);
IGSHARP_API bool IGSharp_RadioButtonInt(const char* label, int* v, int v_button);
IGSHARP_API void IGSharp_ProgressBar(float fraction, IGSharp_Vec2 size_arg, const char* overlay);
IGSHARP_API void IGSharp_Bullet(void);
IGSHARP_API bool IGSharp_TextLink(const char* label);
IGSHARP_API void IGSharp_TextLinkOpenURL(const char* label, const char* url);

// Widgets: Images
IGSHARP_API void IGSharp_ImageWithBg(unsigned long long tex_id, IGSharp_Vec2 image_size, IGSharp_Vec2 uv0, IGSharp_Vec2 uv1, IGSharp_Vec4 bg_col, IGSharp_Vec4 tint_col);
IGSHARP_API bool IGSharp_ImageButton(const char* str_id, unsigned long long tex_id, IGSharp_Vec2 image_size, IGSharp_Vec2 uv0, IGSharp_Vec2 uv1, IGSharp_Vec4 bg_col, IGSharp_Vec4 tint_col);

// Widgets: Combo Box (Dropdown)
IGSHARP_API bool IGSharp_BeginCombo(const char* label, const char* preview_value, int flags);
IGSHARP_API void IGSharp_EndCombo(void);

// Widgets: Drag Sliders
IGSHARP_API bool IGSharp_DragFloat(const char* label, float* v, float v_speed, float v_min, float v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_DragFloat2(const char* label, float v[2], float v_speed, float v_min, float v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_DragFloat3(const char* label, float v[3], float v_speed, float v_min, float v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_DragFloat4(const char* label, float v[4], float v_speed, float v_min, float v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_DragInt(const char* label, int* v, float v_speed, int v_min, int v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_DragInt2(const char* label, int v[2], float v_speed, int v_min, int v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_DragInt3(const char* label, int v[3], float v_speed, int v_min, int v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_DragInt4(const char* label, int v[4], float v_speed, int v_min, int v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_DragScalar(const char* label, int data_type, void* p_data, float v_speed, const void* p_min, const void* p_max, const char* format, int flags);
IGSHARP_API bool IGSharp_DragScalarN(const char* label, int data_type, void* p_data, int components, float v_speed, const void* p_min, const void* p_max, const char* format, int flags);

// Widgets: Regular Sliders
IGSHARP_API bool IGSharp_SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_SliderFloat2(const char* label, float v[2], float v_min, float v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_SliderFloat3(const char* label, float v[3], float v_min, float v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_SliderFloat4(const char* label, float v[4], float v_min, float v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_SliderAngle(const char* label, float* v_rad, float v_degrees_min, float v_degrees_max, const char* format, int flags);
IGSHARP_API bool IGSharp_SliderInt(const char* label, int* v, int v_min, int v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_SliderInt2(const char* label, int v[2], int v_min, int v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_SliderInt3(const char* label, int v[3], int v_min, int v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_SliderInt4(const char* label, int v[4], int v_min, int v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_SliderScalar(const char* label, int data_type, void* p_data, const void* p_min, const void* p_max, const char* format, int flags);
IGSHARP_API bool IGSharp_SliderScalarN(const char* label, int data_type, void* p_data, int components, const void* p_min, const void* p_max, const char* format, int flags);
IGSHARP_API bool IGSharp_VSliderScalar(const char* label, IGSharp_Vec2 size, int data_type, void* p_data, const void* p_min, const void* p_max, const char* format, int flags);

// Widgets: Input with Keyboard
IGSHARP_API bool IGSharp_InputText(const char* label, char* buf, size_t buf_size, int flags);
IGSHARP_API bool IGSharp_InputTextMultiline(const char* label, char* buf, size_t buf_size, IGSharp_Vec2 size, int flags);
IGSHARP_API bool IGSharp_InputTextWithHint(const char* label, const char* hint, char* buf, size_t buf_size, int flags);
IGSHARP_API bool IGSharp_InputTextEx(const char* label, char* buf, size_t buf_size, int flags, IGSharp_InputTextCallback callback, void* user_data);
IGSHARP_API bool IGSharp_InputTextMultilineEx(const char* label, char* buf, size_t buf_size, IGSharp_Vec2 size, int flags, IGSharp_InputTextCallback callback, void* user_data);
IGSHARP_API bool IGSharp_InputTextWithHintEx(const char* label, const char* hint, char* buf, size_t buf_size, int flags, IGSharp_InputTextCallback callback, void* user_data);
IGSHARP_API bool IGSharp_InputFloat(const char* label, float* v, float step, float step_fast, const char* format, int flags);
IGSHARP_API bool IGSharp_InputFloat2(const char* label, float v[2], const char* format, int flags);
IGSHARP_API bool IGSharp_InputFloat3(const char* label, float v[3], const char* format, int flags);
IGSHARP_API bool IGSharp_InputFloat4(const char* label, float v[4], const char* format, int flags);
IGSHARP_API bool IGSharp_InputInt(const char* label, int* v, int step, int step_fast, int flags);
IGSHARP_API bool IGSharp_InputInt2(const char* label, int v[2], int flags);
IGSHARP_API bool IGSharp_InputInt3(const char* label, int v[3], int flags);
IGSHARP_API bool IGSharp_InputInt4(const char* label, int v[4], int flags);
IGSHARP_API bool IGSharp_InputDouble(const char* label, double* v, double step, double step_fast, const char* format, int flags);
IGSHARP_API bool IGSharp_InputScalar(const char* label, int data_type, void* p_data, const void* p_step, const void* p_step_fast, const char* format, int flags);
IGSHARP_API bool IGSharp_InputScalarN(const char* label, int data_type, void* p_data, int components, const void* p_step, const void* p_step_fast, const char* format, int flags);

// Widgets: Color Editor/Picker (tip: the ColorEdit* functions have a little color square that can be left-clicked to open a picker, and right-clicked to open an option menu.)
IGSHARP_API bool IGSharp_ColorEdit3(const char* label, float col[3], int flags);
IGSHARP_API bool IGSharp_ColorEdit4(const char* label, float col[4], int flags);
IGSHARP_API bool IGSharp_ColorPicker3(const char* label, float col[3], int flags);
IGSHARP_API bool IGSharp_ColorPicker4(const char* label, float col[4], int flags, const float* ref_col);
IGSHARP_API bool IGSharp_ColorButton(const char* desc_id, IGSharp_Vec4 col, int flags, IGSharp_Vec2 size);

// Widgets: Trees
IGSHARP_API bool  IGSharp_TreeNode(const char* label);
IGSHARP_API bool  IGSharp_TreeNodeEx(const char* label, int flags);
IGSHARP_API void  IGSharp_TreePop(void);
IGSHARP_API float IGSharp_GetTreeNodeToLabelSpacing(void);
IGSHARP_API bool  IGSharp_TreeNodeGetOpen(unsigned int storage_id);
IGSHARP_API bool  IGSharp_CollapsingHeader(const char* label, int flags);
IGSHARP_API bool  IGSharp_CollapsingHeaderClosable(const char* label, bool* p_visible, int flags);
IGSHARP_API void  IGSharp_SetNextItemOpen(bool is_open, int cond);

// Widgets: Selectables
IGSHARP_API bool IGSharp_Selectable(const char* label, bool selected, int flags, IGSharp_Vec2 size);
IGSHARP_API bool IGSharp_SelectablePtr(const char* label, bool* p_selected, int flags, IGSharp_Vec2 size);

// Multi-selection system for Selectable(), Checkbox(), TreeNode() functions [BETA]
IGSHARP_API void* IGSharp_BeginMultiSelect(int flags, int selection_size, int items_count);
IGSHARP_API void* IGSharp_EndMultiSelect(void);
IGSHARP_API void  IGSharp_SetNextItemSelectionUserData(long long selection_user_data);
IGSHARP_API bool  IGSharp_IsItemToggledSelection(void);

// Widgets: List Boxes
IGSHARP_API bool IGSharp_BeginListBox(const char* label, IGSharp_Vec2 size);
IGSHARP_API void IGSharp_EndListBox(void);

// Widgets: Data Plotting
IGSHARP_API void IGSharp_PlotLines(const char* label, const float* values, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, IGSharp_Vec2 graph_size, int stride);
IGSHARP_API void IGSharp_PlotLinesCallback(const char* label, IGSharp_PlotValuesGetter values_getter, void* data, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, IGSharp_Vec2 graph_size);
IGSHARP_API void IGSharp_PlotHistogram(const char* label, const float* values, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, IGSharp_Vec2 graph_size, int stride);
IGSHARP_API void IGSharp_PlotHistogramCallback(const char* label, IGSharp_PlotValuesGetter values_getter, void* data, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, IGSharp_Vec2 graph_size);

// Widgets: Menus
IGSHARP_API bool IGSharp_BeginMenuBar(void);
IGSHARP_API void IGSharp_EndMenuBar(void);
IGSHARP_API bool IGSharp_BeginMainMenuBar(void);
IGSHARP_API void IGSharp_EndMainMenuBar(void);
IGSHARP_API bool IGSharp_BeginMenu(const char* label, bool enabled);
IGSHARP_API void IGSharp_EndMenu(void);
IGSHARP_API bool IGSharp_MenuItem(const char* label, const char* shortcut, bool selected, bool enabled);
IGSHARP_API bool IGSharp_MenuItemPtr(const char* label, const char* shortcut, bool* p_selected, bool enabled);

// Tooltips
IGSHARP_API bool IGSharp_BeginTooltip(void);
IGSHARP_API void IGSharp_EndTooltip(void);
IGSHARP_API void IGSharp_SetTooltip(const char* text);

// Tooltips: helpers for showing a tooltip when hovering an item
IGSHARP_API bool IGSharp_BeginItemTooltip(void);

// Popups, Modals
IGSHARP_API bool IGSharp_BeginPopup(const char* str_id, int flags);
IGSHARP_API bool IGSharp_BeginPopupModal(const char* name, bool* p_open, int flags);
IGSHARP_API void IGSharp_EndPopup(void);

// Popups: open/close functions
IGSHARP_API void IGSharp_OpenPopup(const char* str_id, int popup_flags);
IGSHARP_API void IGSharp_CloseCurrentPopup(void);

// Popups: Open+Begin popup combined functions helpers to create context menus.
IGSHARP_API bool IGSharp_BeginPopupContextItem(const char* str_id, int popup_flags);
IGSHARP_API bool IGSharp_BeginPopupContextWindow(const char* str_id, int popup_flags);

// Popups: query functions
IGSHARP_API bool IGSharp_IsPopupOpen(const char* str_id, int flags);

// Tables
IGSHARP_API bool IGSharp_BeginTable(const char* str_id, int columns, int flags, IGSharp_Vec2 outer_size, float inner_width);
IGSHARP_API void IGSharp_EndTable(void);
IGSHARP_API void IGSharp_TableNextRow(int row_flags, float min_row_height);
IGSHARP_API bool IGSharp_TableNextColumn(void);
IGSHARP_API bool IGSharp_TableSetColumnIndex(int column_n);

// Tables: Headers & Columns declaration
IGSHARP_API void IGSharp_TableSetupColumn(const char* label, int flags, float init_width_or_weight, unsigned int user_id);
IGSHARP_API void IGSharp_TableSetupScrollFreeze(int cols, int rows);
IGSHARP_API void IGSharp_TableHeadersRow(void);
IGSHARP_API void IGSharp_TableHeader(const char* label);

// Tables: Sorting & Miscellaneous functions
IGSHARP_API void*       IGSharp_TableGetSortSpecs(void);
IGSHARP_API int         IGSharp_TableGetColumnCount(void);
IGSHARP_API int         IGSharp_TableGetColumnIndex(void);
IGSHARP_API int         IGSharp_TableGetRowIndex(void);
IGSHARP_API const char* IGSharp_TableGetColumnName(int column_n);
IGSHARP_API int         IGSharp_TableGetColumnFlags(int column_n);
IGSHARP_API void        IGSharp_TableSetColumnEnabled(int column_n, bool v);
IGSHARP_API int         IGSharp_TableGetHoveredColumn(void);
IGSHARP_API void        IGSharp_TableSetBgColor(int target, unsigned int color, int column_n);

// Tab Bars, Tabs
IGSHARP_API bool IGSharp_BeginTabBar(const char* str_id, int flags);
IGSHARP_API void IGSharp_EndTabBar(void);
IGSHARP_API bool IGSharp_BeginTabItem(const char* label, bool* p_open, int flags);
IGSHARP_API void IGSharp_EndTabItem(void);
IGSHARP_API bool IGSharp_TabItemButton(const char* label, int flags);
IGSHARP_API void IGSharp_SetTabItemClosed(const char* tab_or_docked_window_label);

// Drag and Drop
IGSHARP_API bool  IGSharp_BeginDragDropSource(int flags);
IGSHARP_API bool  IGSharp_SetDragDropPayload(const char* type, const void* data, size_t sz, int cond);
IGSHARP_API void  IGSharp_EndDragDropSource(void);
IGSHARP_API bool  IGSharp_BeginDragDropTarget(void);
IGSHARP_API void* IGSharp_AcceptDragDropPayload(const char* type, int flags);
IGSHARP_API void  IGSharp_EndDragDropTarget(void);
IGSHARP_API void* IGSharp_GetDragDropPayload(void);

// Disabling [BETA API]
IGSHARP_API void IGSharp_BeginDisabled(bool disabled);
IGSHARP_API void IGSharp_EndDisabled(void);

// Focus, Activation
IGSHARP_API void IGSharp_SetKeyboardFocusHere(int offset);
IGSHARP_API void IGSharp_SetItemDefaultFocus(void);

// Overlapping mode
IGSHARP_API void IGSharp_SetNextItemAllowOverlap(void);

// Item/Widgets Utilities and Query Functions
IGSHARP_API bool         IGSharp_IsItemHovered(int flags);
IGSHARP_API bool         IGSharp_IsItemActive(void);
IGSHARP_API bool         IGSharp_IsItemFocused(void);
IGSHARP_API bool         IGSharp_IsItemClicked(int mouse_button);
IGSHARP_API bool         IGSharp_IsItemVisible(void);
IGSHARP_API bool         IGSharp_IsItemEdited(void);
IGSHARP_API bool         IGSharp_IsItemActivated(void);
IGSHARP_API bool         IGSharp_IsItemDeactivated(void);
IGSHARP_API bool         IGSharp_IsItemDeactivatedAfterEdit(void);
IGSHARP_API bool         IGSharp_IsItemToggledOpen(void);
IGSHARP_API IGSharp_Vec2 IGSharp_GetItemRectMin(void);
IGSHARP_API IGSharp_Vec2 IGSharp_GetItemRectMax(void);
IGSHARP_API IGSharp_Vec2 IGSharp_GetItemRectSize(void);
IGSHARP_API unsigned int IGSharp_GetItemID(void);
IGSHARP_API bool         IGSharp_IsAnyItemHovered(void);
IGSHARP_API bool         IGSharp_IsAnyItemActive(void);
IGSHARP_API bool         IGSharp_IsAnyItemFocused(void);

// Viewports
IGSHARP_API void* IGSharp_GetMainViewport(void);

// Background/Foreground Draw Lists
IGSHARP_API void* IGSharp_GetWindowDrawList(void);
IGSHARP_API void* IGSharp_GetBackgroundDrawList(void);
IGSHARP_API void* IGSharp_GetForegroundDrawList(void);

// Text Utilities
IGSHARP_API IGSharp_Vec2 IGSharp_CalcTextSize(const char* text, const char* text_end, bool hide_text_after_double_hash, float wrap_width);

// Color Utilities
IGSHARP_API IGSharp_Vec4 IGSharp_ColorConvertU32ToFloat4(unsigned int in);
IGSHARP_API unsigned int IGSharp_ColorConvertFloat4ToU32(IGSharp_Vec4 in);
IGSHARP_API void         IGSharp_ColorConvertRGBtoHSV(float r, float g, float b, float* out_h, float* out_s, float* out_v);
IGSHARP_API void         IGSharp_ColorConvertHSVtoRGB(float h, float s, float v, float* out_r, float* out_g, float* out_b);

// Inputs Utilities: Raw Keyboard/Mouse/Gamepad Access
IGSHARP_API bool IGSharp_IsKeyDown(int key);
IGSHARP_API bool IGSharp_IsKeyPressed(int key, bool repeat);
IGSHARP_API bool IGSharp_IsKeyReleased(int key);
IGSHARP_API bool IGSharp_IsKeyChordPressed(int key_chord);

// Inputs Utilities: Mouse
IGSHARP_API bool         IGSharp_IsMouseDown(int button);
IGSHARP_API bool         IGSharp_IsMouseClicked(int button, bool repeat);
IGSHARP_API bool         IGSharp_IsMouseReleased(int button);
IGSHARP_API bool         IGSharp_IsMouseDoubleClicked(int button);
IGSHARP_API bool         IGSharp_IsMouseHoveringRect(IGSharp_Vec2 r_min, IGSharp_Vec2 r_max, bool clip);
IGSHARP_API bool         IGSharp_IsMousePosValid(const IGSharp_Vec2* mouse_pos);
IGSHARP_API IGSharp_Vec2 IGSharp_GetMousePos(void);
IGSHARP_API bool         IGSharp_IsMouseDragging(int button, float lock_threshold);
IGSHARP_API IGSharp_Vec2 IGSharp_GetMouseDragDelta(int button, float lock_threshold);
IGSHARP_API int          IGSharp_GetMouseCursor(void);
IGSHARP_API void         IGSharp_SetMouseCursor(int cursor_type);

//-----------------------------------------------------------------------------
// [SECTION] Flags & Enumerations
//-----------------------------------------------------------------------------

// Mirrored from upstream Dear ImGui. Values must match upstream exactly —
// validated per-value by static_assert in imgui_sharp_layout_check.cpp.
// Used as array sizes in IGSharp_IO.KeysData and IGSharp_Style.Colors below,
// and exposed so consumers don't need to redefine these enums independently.
typedef enum {
    IGSharp_Key_None = 0,
    IGSharp_Key_NamedKey_BEGIN = 512,

    IGSharp_Key_Tab = 512,
    IGSharp_Key_LeftArrow,
    IGSharp_Key_RightArrow,
    IGSharp_Key_UpArrow,
    IGSharp_Key_DownArrow,
    IGSharp_Key_PageUp,
    IGSharp_Key_PageDown,
    IGSharp_Key_Home,
    IGSharp_Key_End,
    IGSharp_Key_Insert,
    IGSharp_Key_Delete,
    IGSharp_Key_Backspace,
    IGSharp_Key_Space,
    IGSharp_Key_Enter,
    IGSharp_Key_Escape,
    IGSharp_Key_LeftCtrl, IGSharp_Key_LeftShift, IGSharp_Key_LeftAlt, IGSharp_Key_LeftSuper,
    IGSharp_Key_RightCtrl, IGSharp_Key_RightShift, IGSharp_Key_RightAlt, IGSharp_Key_RightSuper,
    IGSharp_Key_Menu,
    IGSharp_Key_0, IGSharp_Key_1, IGSharp_Key_2, IGSharp_Key_3, IGSharp_Key_4, IGSharp_Key_5, IGSharp_Key_6, IGSharp_Key_7, IGSharp_Key_8, IGSharp_Key_9,
    IGSharp_Key_A, IGSharp_Key_B, IGSharp_Key_C, IGSharp_Key_D, IGSharp_Key_E, IGSharp_Key_F, IGSharp_Key_G, IGSharp_Key_H, IGSharp_Key_I, IGSharp_Key_J,
    IGSharp_Key_K, IGSharp_Key_L, IGSharp_Key_M, IGSharp_Key_N, IGSharp_Key_O, IGSharp_Key_P, IGSharp_Key_Q, IGSharp_Key_R, IGSharp_Key_S, IGSharp_Key_T,
    IGSharp_Key_U, IGSharp_Key_V, IGSharp_Key_W, IGSharp_Key_X, IGSharp_Key_Y, IGSharp_Key_Z,
    IGSharp_Key_F1, IGSharp_Key_F2, IGSharp_Key_F3, IGSharp_Key_F4, IGSharp_Key_F5, IGSharp_Key_F6,
    IGSharp_Key_F7, IGSharp_Key_F8, IGSharp_Key_F9, IGSharp_Key_F10, IGSharp_Key_F11, IGSharp_Key_F12,
    IGSharp_Key_F13, IGSharp_Key_F14, IGSharp_Key_F15, IGSharp_Key_F16, IGSharp_Key_F17, IGSharp_Key_F18,
    IGSharp_Key_F19, IGSharp_Key_F20, IGSharp_Key_F21, IGSharp_Key_F22, IGSharp_Key_F23, IGSharp_Key_F24,
    IGSharp_Key_Apostrophe,
    IGSharp_Key_Comma,
    IGSharp_Key_Minus,
    IGSharp_Key_Period,
    IGSharp_Key_Slash,
    IGSharp_Key_Semicolon,
    IGSharp_Key_Equal,
    IGSharp_Key_LeftBracket,
    IGSharp_Key_Backslash,
    IGSharp_Key_RightBracket,
    IGSharp_Key_GraveAccent,
    IGSharp_Key_CapsLock,
    IGSharp_Key_ScrollLock,
    IGSharp_Key_NumLock,
    IGSharp_Key_PrintScreen,
    IGSharp_Key_Pause,
    IGSharp_Key_Keypad0, IGSharp_Key_Keypad1, IGSharp_Key_Keypad2, IGSharp_Key_Keypad3, IGSharp_Key_Keypad4,
    IGSharp_Key_Keypad5, IGSharp_Key_Keypad6, IGSharp_Key_Keypad7, IGSharp_Key_Keypad8, IGSharp_Key_Keypad9,
    IGSharp_Key_KeypadDecimal,
    IGSharp_Key_KeypadDivide,
    IGSharp_Key_KeypadMultiply,
    IGSharp_Key_KeypadSubtract,
    IGSharp_Key_KeypadAdd,
    IGSharp_Key_KeypadEnter,
    IGSharp_Key_KeypadEqual,
    IGSharp_Key_AppBack,
    IGSharp_Key_AppForward,
    IGSharp_Key_Oem102,

    IGSharp_Key_GamepadStart,
    IGSharp_Key_GamepadBack,
    IGSharp_Key_GamepadFaceLeft,
    IGSharp_Key_GamepadFaceRight,
    IGSharp_Key_GamepadFaceUp,
    IGSharp_Key_GamepadFaceDown,
    IGSharp_Key_GamepadDpadLeft,
    IGSharp_Key_GamepadDpadRight,
    IGSharp_Key_GamepadDpadUp,
    IGSharp_Key_GamepadDpadDown,
    IGSharp_Key_GamepadL1,
    IGSharp_Key_GamepadR1,
    IGSharp_Key_GamepadL2,
    IGSharp_Key_GamepadR2,
    IGSharp_Key_GamepadL3,
    IGSharp_Key_GamepadR3,
    IGSharp_Key_GamepadLStickLeft,
    IGSharp_Key_GamepadLStickRight,
    IGSharp_Key_GamepadLStickUp,
    IGSharp_Key_GamepadLStickDown,
    IGSharp_Key_GamepadRStickLeft,
    IGSharp_Key_GamepadRStickRight,
    IGSharp_Key_GamepadRStickUp,
    IGSharp_Key_GamepadRStickDown,

    IGSharp_Key_MouseLeft, IGSharp_Key_MouseRight, IGSharp_Key_MouseMiddle, IGSharp_Key_MouseX1, IGSharp_Key_MouseX2, IGSharp_Key_MouseWheelX, IGSharp_Key_MouseWheelY,

    IGSharp_Key_ReservedForModCtrl, IGSharp_Key_ReservedForModShift, IGSharp_Key_ReservedForModAlt, IGSharp_Key_ReservedForModSuper,

    IGSharp_Key_NamedKey_END,
    IGSharp_Key_NamedKey_COUNT = IGSharp_Key_NamedKey_END - IGSharp_Key_NamedKey_BEGIN,

    IGSharp_Mod_None  = 0,
    IGSharp_Mod_Ctrl  = 1 << 12,
    IGSharp_Mod_Shift = 1 << 13,
    IGSharp_Mod_Alt   = 1 << 14,
    IGSharp_Mod_Super = 1 << 15,
    IGSharp_Mod_Mask_ = 0xF000,
} IGSharp_Key;

typedef enum {
    IGSharp_Col_Text,
    IGSharp_Col_TextDisabled,
    IGSharp_Col_WindowBg,
    IGSharp_Col_ChildBg,
    IGSharp_Col_PopupBg,
    IGSharp_Col_Border,
    IGSharp_Col_BorderShadow,
    IGSharp_Col_FrameBg,
    IGSharp_Col_FrameBgHovered,
    IGSharp_Col_FrameBgActive,
    IGSharp_Col_TitleBg,
    IGSharp_Col_TitleBgActive,
    IGSharp_Col_TitleBgCollapsed,
    IGSharp_Col_MenuBarBg,
    IGSharp_Col_ScrollbarBg,
    IGSharp_Col_ScrollbarGrab,
    IGSharp_Col_ScrollbarGrabHovered,
    IGSharp_Col_ScrollbarGrabActive,
    IGSharp_Col_CheckMark,
    IGSharp_Col_SliderGrab,
    IGSharp_Col_SliderGrabActive,
    IGSharp_Col_Button,
    IGSharp_Col_ButtonHovered,
    IGSharp_Col_ButtonActive,
    IGSharp_Col_Header,
    IGSharp_Col_HeaderHovered,
    IGSharp_Col_HeaderActive,
    IGSharp_Col_Separator,
    IGSharp_Col_SeparatorHovered,
    IGSharp_Col_SeparatorActive,
    IGSharp_Col_ResizeGrip,
    IGSharp_Col_ResizeGripHovered,
    IGSharp_Col_ResizeGripActive,
    IGSharp_Col_InputTextCursor,
    IGSharp_Col_TabHovered,
    IGSharp_Col_Tab,
    IGSharp_Col_TabSelected,
    IGSharp_Col_TabSelectedOverline,
    IGSharp_Col_TabDimmed,
    IGSharp_Col_TabDimmedSelected,
    IGSharp_Col_TabDimmedSelectedOverline,
    IGSharp_Col_PlotLines,
    IGSharp_Col_PlotLinesHovered,
    IGSharp_Col_PlotHistogram,
    IGSharp_Col_PlotHistogramHovered,
    IGSharp_Col_TableHeaderBg,
    IGSharp_Col_TableBorderStrong,
    IGSharp_Col_TableBorderLight,
    IGSharp_Col_TableRowBg,
    IGSharp_Col_TableRowBgAlt,
    IGSharp_Col_TextLink,
    IGSharp_Col_TextSelectedBg,
    IGSharp_Col_TreeLines,
    IGSharp_Col_DragDropTarget,
    IGSharp_Col_DragDropTargetBg,
    IGSharp_Col_UnsavedMarker,
    IGSharp_Col_NavCursor,
    IGSharp_Col_NavWindowingHighlight,
    IGSharp_Col_NavWindowingDimBg,
    IGSharp_Col_ModalWindowDimBg,
    IGSharp_Col_COUNT,
} IGSharp_Col;

//-----------------------------------------------------------------------------
// [SECTION] Tables API flags and structures (ImGuiTableFlags, ImGuiTableColumnFlags, ImGuiTableRowFlags, ImGuiTableBgTarget, ImGuiTableSortSpecs, ImGuiTableColumnSortSpecs)
//-----------------------------------------------------------------------------

IGSHARP_API int   IGSharp_TableSortSpecs_GetSpecsCount(void* specs);
IGSHARP_API void* IGSharp_TableSortSpecs_GetSpec(void* specs, int index);
IGSHARP_API bool  IGSharp_TableSortSpecs_GetSpecsDirty(void* specs);
IGSHARP_API void  IGSharp_TableSortSpecs_SetSpecsDirty(void* specs, bool v);

IGSHARP_API unsigned int IGSharp_TableColumnSortSpecs_GetColumnUserID(void* spec);
IGSHARP_API int          IGSharp_TableColumnSortSpecs_GetColumnIndex(void* spec);
IGSHARP_API int          IGSharp_TableColumnSortSpecs_GetSortOrder(void* spec);
IGSHARP_API int          IGSharp_TableColumnSortSpecs_GetSortDirection(void* spec);

//-----------------------------------------------------------------------------
// [SECTION] Helpers: Debug log, Memory allocations macros, ImVector<>
//-----------------------------------------------------------------------------

// ImGuiListClipper
IGSHARP_API void* IGSharp_ListClipper_New(void);
IGSHARP_API void  IGSharp_ListClipper_Delete(void* clipper);
IGSHARP_API void  IGSharp_ListClipper_Begin(void* clipper, int items_count, float items_height);
IGSHARP_API void  IGSharp_ListClipper_End(void* clipper);
IGSHARP_API bool  IGSharp_ListClipper_Step(void* clipper);
IGSHARP_API void  IGSharp_ListClipper_IncludeItemsByIndex(void* clipper, int item_begin, int item_end);
IGSHARP_API void  IGSharp_ListClipper_SeekCursorForItem(void* clipper, int item_index);
IGSHARP_API int   IGSharp_ListClipper_GetDisplayStart(void* clipper);
IGSHARP_API int   IGSharp_ListClipper_GetDisplayEnd(void* clipper);

//-----------------------------------------------------------------------------
// [SECTION] ImGuiStyle
//-----------------------------------------------------------------------------
// Layout-compatible C mirror of Dear ImGui's ImGuiStyle. Verified at compile
// time in src/imgui_sharp_layout_check.cpp.
//
// Obtain a pointer with IGSharp_GetStyle() and read/write fields directly.
// The single member function (ScaleAllSizes) is exported as a free function
// IGSharp_Style_ScaleAllSizes taking IGSharp_Style* as the first argument.
//-----------------------------------------------------------------------------

typedef struct IGSharp_Style {
    // Font scaling
    float        FontSizeBase;
    float        FontScaleMain;
    float        FontScaleDpi;

    float        Alpha;
    float        DisabledAlpha;
    IGSharp_Vec2 WindowPadding;
    float        WindowRounding;
    float        WindowBorderSize;
    float        WindowBorderHoverPadding;
    IGSharp_Vec2 WindowMinSize;
    IGSharp_Vec2 WindowTitleAlign;
    int          WindowMenuButtonPosition;       // ImGuiDir
    float        ChildRounding;
    float        ChildBorderSize;
    float        PopupRounding;
    float        PopupBorderSize;
    IGSharp_Vec2 FramePadding;
    float        FrameRounding;
    float        FrameBorderSize;
    IGSharp_Vec2 ItemSpacing;
    IGSharp_Vec2 ItemInnerSpacing;
    IGSharp_Vec2 CellPadding;
    IGSharp_Vec2 TouchExtraPadding;
    float        IndentSpacing;
    float        ColumnsMinSpacing;
    float        ScrollbarSize;
    float        ScrollbarRounding;
    float        ScrollbarPadding;
    float        GrabMinSize;
    float        GrabRounding;
    float        LogSliderDeadzone;
    float        ImageRounding;
    float        ImageBorderSize;
    float        TabRounding;
    float        TabBorderSize;
    float        TabMinWidthBase;
    float        TabMinWidthShrink;
    float        TabCloseButtonMinWidthSelected;
    float        TabCloseButtonMinWidthUnselected;
    float        TabBarBorderSize;
    float        TabBarOverlineSize;
    float        TableAngledHeadersAngle;
    IGSharp_Vec2 TableAngledHeadersTextAlign;
    int          TreeLinesFlags;                 // ImGuiTreeNodeFlags
    float        TreeLinesSize;
    float        TreeLinesRounding;
    float        DragDropTargetRounding;
    float        DragDropTargetBorderSize;
    float        DragDropTargetPadding;
    float        ColorMarkerSize;
    int          ColorButtonPosition;            // ImGuiDir
    IGSharp_Vec2 ButtonTextAlign;
    IGSharp_Vec2 SelectableTextAlign;
    float        SeparatorSize;
    float        SeparatorTextBorderSize;
    IGSharp_Vec2 SeparatorTextAlign;
    IGSharp_Vec2 SeparatorTextPadding;
    IGSharp_Vec2 DisplayWindowPadding;
    IGSharp_Vec2 DisplaySafeAreaPadding;
    float        MouseCursorScale;
    bool         AntiAliasedLines;
    bool         AntiAliasedLinesUseTex;
    bool         AntiAliasedFill;
    float        CurveTessellationTol;
    float        CircleTessellationMaxError;

    // Colors
    IGSharp_Vec4 Colors[IGSharp_Col_COUNT];

    // Behaviors
    float        HoverStationaryDelay;
    float        HoverDelayShort;
    float        HoverDelayNormal;
    int          HoverFlagsForTooltipMouse;      // ImGuiHoveredFlags
    int          HoverFlagsForTooltipNav;        // ImGuiHoveredFlags

    // [Internal] Maintained by Dear ImGui — do not rely on layout staying stable across versions.
    float        _MainScale;
    float        _NextFrameFontSizeBase;
} IGSharp_Style;

IGSHARP_API void IGSharp_Style_ScaleAllSizes(IGSharp_Style* style, float scale);

//-----------------------------------------------------------------------------
// [SECTION] ImGuiIO
//-----------------------------------------------------------------------------
// Layout-compatible C mirror of Dear ImGui's ImGuiIO. Field order, types and
// padding must match upstream exactly; verified at compile time in
// src/imgui_sharp_layout_check.cpp via sizeof + offsetof on every field.
//
// Obtain a pointer with IGSharp_GetIO() and read/write fields directly. The
// few member functions that ImGuiIO exposes (event queue, ClearInputKeys,
// etc.) are exported as IGSharp_IO_* free functions taking IGSharp_IO* as the
// first argument.
//-----------------------------------------------------------------------------

typedef struct IGSharp_IO {
    // Configuration
    int            ConfigFlags;                 // ImGuiConfigFlags
    int            BackendFlags;                // ImGuiBackendFlags
    IGSharp_Vec2   DisplaySize;
    IGSharp_Vec2   DisplayFramebufferScale;
    float          DeltaTime;
    float          IniSavingRate;
    const char*    IniFilename;
    const char*    LogFilename;
    void*          UserData;

    // Font system
    void*          Fonts;                       // ImFontAtlas*
    void*          FontDefault;                 // ImFont*
    bool           FontAllowUserScaling;

    // Keyboard/Gamepad navigation options
    bool           ConfigNavSwapGamepadButtons;
    bool           ConfigNavMoveSetMousePos;
    bool           ConfigNavCaptureKeyboard;
    bool           ConfigNavEscapeClearFocusItem;
    bool           ConfigNavEscapeClearFocusWindow;
    bool           ConfigNavCursorVisibleAuto;
    bool           ConfigNavCursorVisibleAlways;

    // Miscellaneous options
    bool           MouseDrawCursor;
    bool           ConfigMacOSXBehaviors;
    bool           ConfigInputTrickleEventQueue;
    bool           ConfigInputTextCursorBlink;
    bool           ConfigInputTextEnterKeepActive;
    bool           ConfigDragClickToInputText;
    bool           ConfigWindowsResizeFromEdges;
    bool           ConfigWindowsMoveFromTitleBarOnly;
    bool           ConfigWindowsCopyContentsWithCtrlC;
    bool           ConfigScrollbarScrollByPage;
    float          ConfigMemoryCompactTimer;

    // Inputs behaviors
    float          MouseDoubleClickTime;
    float          MouseDoubleClickMaxDist;
    float          MouseDragThreshold;
    float          KeyRepeatDelay;
    float          KeyRepeatRate;

    // Debug options
    bool           ConfigErrorRecovery;
    bool           ConfigErrorRecoveryEnableAssert;
    bool           ConfigErrorRecoveryEnableDebugLog;
    bool           ConfigErrorRecoveryEnableTooltip;
    bool           ConfigDebugIsDebuggerPresent;
    bool           ConfigDebugHighlightIdConflicts;
    bool           ConfigDebugHighlightIdConflictsShowItemPicker;
    bool           ConfigDebugBeginReturnValueOnce;
    bool           ConfigDebugBeginReturnValueLoop;
    bool           ConfigDebugIgnoreFocusLoss;
    bool           ConfigDebugIniSettings;

    // Platform identifiers (set by backend)
    const char*    BackendPlatformName;
    const char*    BackendRendererName;
    void*          BackendPlatformUserData;
    void*          BackendRendererUserData;
    void*          BackendLanguageUserData;

    // Output (updated by NewFrame()/EndFrame()/Render())
    bool           WantCaptureMouse;
    bool           WantCaptureKeyboard;
    bool           WantTextInput;
    bool           WantSetMousePos;
    bool           WantSaveIniSettings;
    bool           NavActive;
    bool           NavVisible;
    float          Framerate;
    int            MetricsRenderVertices;
    int            MetricsRenderIndices;
    int            MetricsRenderWindows;
    int            MetricsActiveWindows;
    IGSharp_Vec2   MouseDelta;

    // [Internal] Maintained by Dear ImGui — forward compatibility not guaranteed.
    IGSharp_Context* Ctx;
    IGSharp_Vec2     MousePos;
    bool             MouseDown[5];
    float            MouseWheel;
    float            MouseWheelH;
    int              MouseSource;                // ImGuiMouseSource
    bool             KeyCtrl;
    bool             KeyShift;
    bool             KeyAlt;
    bool             KeySuper;
    int              KeyMods;                    // ImGuiKeyChord
    IGSharp_KeyData  KeysData[IGSharp_Key_NamedKey_COUNT];
    bool             WantCaptureMouseUnlessPopupClose;
    IGSharp_Vec2     MousePosPrev;
    IGSharp_Vec2     MouseClickedPos[5];
    double           MouseClickedTime[5];
    bool             MouseClicked[5];
    bool             MouseDoubleClicked[5];
    unsigned short   MouseClickedCount[5];       // ImU16
    unsigned short   MouseClickedLastCount[5];   // ImU16
    bool             MouseReleased[5];
    double           MouseReleasedTime[5];
    bool             MouseDownOwned[5];
    bool             MouseDownOwnedUnlessPopupClose[5];
    bool             MouseWheelRequestAxisSwap;
    bool             MouseCtrlLeftAsRightClick;
    float            MouseDownDuration[5];
    float            MouseDownDurationPrev[5];
    float            MouseDragMaxDistanceSqr[5];
    float            PenPressure;
    bool             AppFocusLost;
    bool             AppAcceptingEvents;
    unsigned short   InputQueueSurrogate;        // ImWchar16

    // ImVector<ImWchar> InputQueueCharacters expanded to its three on-disk fields.
    // ImVector<T> layout is { int Size; int Capacity; T* Data; } — verified by static_assert.
    int              InputQueueCharacters_Size;
    int              InputQueueCharacters_Capacity;
    unsigned short*  InputQueueCharacters_Data;
} IGSharp_IO;

// Wrap ImGuiIO's C++ member functions; pass the IGSharp_IO* you got from IGSharp_GetIO().
IGSHARP_API void IGSharp_IO_AddKeyEvent(IGSharp_IO* io, int key, bool down);
IGSHARP_API void IGSharp_IO_AddKeyAnalogEvent(IGSharp_IO* io, int key, bool down, float v);
IGSHARP_API void IGSharp_IO_AddMousePosEvent(IGSharp_IO* io, float x, float y);
IGSHARP_API void IGSharp_IO_AddMouseButtonEvent(IGSharp_IO* io, int button, bool down);
IGSHARP_API void IGSharp_IO_AddMouseWheelEvent(IGSharp_IO* io, float wheel_x, float wheel_y);
IGSHARP_API void IGSharp_IO_AddMouseSourceEvent(IGSharp_IO* io, int source);
IGSHARP_API void IGSharp_IO_AddFocusEvent(IGSharp_IO* io, bool focused);
IGSHARP_API void IGSharp_IO_AddInputCharacter(IGSharp_IO* io, unsigned int c);
IGSHARP_API void IGSharp_IO_AddInputCharacterUTF16(IGSharp_IO* io, unsigned short c);
IGSHARP_API void IGSharp_IO_AddInputCharactersUTF8(IGSharp_IO* io, const char* str);
IGSHARP_API void IGSharp_IO_SetAppAcceptingEvents(IGSharp_IO* io, bool accepting);
IGSHARP_API void IGSharp_IO_ClearEventsQueue(IGSharp_IO* io);
IGSHARP_API void IGSharp_IO_ClearInputKeys(IGSharp_IO* io);
IGSHARP_API void IGSharp_IO_ClearInputMouse(IGSharp_IO* io);

//-----------------------------------------------------------------------------
// [SECTION] Misc data structures (ImGuiInputTextCallbackData, ImGuiSizeCallbackData, ImGuiPayload)
//-----------------------------------------------------------------------------

// ImGuiInputTextCallbackData: Field Accessors
IGSHARP_API int            IGSharp_InputTextCallbackData_GetEventFlag(void* data);
IGSHARP_API int            IGSharp_InputTextCallbackData_GetFlags(void* data);
IGSHARP_API void*          IGSharp_InputTextCallbackData_GetUserData(void* data);
IGSHARP_API int            IGSharp_InputTextCallbackData_GetEventKey(void* data);
IGSHARP_API unsigned short IGSharp_InputTextCallbackData_GetEventChar(void* data);
IGSHARP_API void           IGSharp_InputTextCallbackData_SetEventChar(void* data, unsigned short c);
IGSHARP_API bool           IGSharp_InputTextCallbackData_GetEventActivated(void* data);
IGSHARP_API char*          IGSharp_InputTextCallbackData_GetBuf(void* data);
IGSHARP_API int            IGSharp_InputTextCallbackData_GetBufTextLen(void* data);
IGSHARP_API void           IGSharp_InputTextCallbackData_SetBufTextLen(void* data, int v);
IGSHARP_API int            IGSharp_InputTextCallbackData_GetBufSize(void* data);
IGSHARP_API bool           IGSharp_InputTextCallbackData_GetBufDirty(void* data);
IGSHARP_API void           IGSharp_InputTextCallbackData_SetBufDirty(void* data, bool v);
IGSHARP_API int            IGSharp_InputTextCallbackData_GetCursorPos(void* data);
IGSHARP_API void           IGSharp_InputTextCallbackData_SetCursorPos(void* data, int v);
IGSHARP_API int            IGSharp_InputTextCallbackData_GetSelectionStart(void* data);
IGSHARP_API void           IGSharp_InputTextCallbackData_SetSelectionStart(void* data, int v);
IGSHARP_API int            IGSharp_InputTextCallbackData_GetSelectionEnd(void* data);
IGSHARP_API void           IGSharp_InputTextCallbackData_SetSelectionEnd(void* data, int v);

// ImGuiInputTextCallbackData: Helper Methods
IGSHARP_API void IGSharp_InputTextCallbackData_DeleteChars(void* data, int pos, int bytes_count);
IGSHARP_API void IGSharp_InputTextCallbackData_InsertChars(void* data, int pos, const char* text, const char* text_end);
IGSHARP_API void IGSharp_InputTextCallbackData_SelectAll(void* data);
IGSHARP_API void IGSharp_InputTextCallbackData_ClearSelection(void* data);
IGSHARP_API bool IGSharp_InputTextCallbackData_HasSelection(void* data);

// ImGuiInputTextCallbackData: Resize Helpers
IGSHARP_API void IGSharp_InputTextCallbackData_SetBuf(void* data, char* buf);
IGSHARP_API void IGSharp_InputTextCallbackData_SetBufSize(void* data, int size);
IGSHARP_API void IGSharp_InputTextCallbackData_ResizeBuf(void* data, char* new_buf, int new_buf_size);

// ImGuiPayload accessors
IGSHARP_API void*       IGSharp_Payload_GetData(void* payload);
IGSHARP_API int         IGSharp_Payload_GetDataSize(void* payload);
IGSHARP_API const char* IGSharp_Payload_GetDataType(void* payload);
IGSHARP_API bool        IGSharp_Payload_IsDataType(void* payload, const char* type);
IGSHARP_API bool        IGSharp_Payload_IsPreview(void* payload);
IGSHARP_API bool        IGSharp_Payload_IsDelivery(void* payload);

//-----------------------------------------------------------------------------
// [SECTION] Multi-Select API flags and structures (ImGuiMultiSelectFlags, ImGuiMultiSelectIO, ImGuiSelectionRequest, ImGuiSelectionBasicStorage, ImGuiSelectionExternalStorage)
//-----------------------------------------------------------------------------

// ImGuiMultiSelectIO accessors
IGSHARP_API int       IGSharp_MultiSelectIO_GetRequestsCount(void* io);
IGSHARP_API void*     IGSharp_MultiSelectIO_GetRequest(void* io, int index);
IGSHARP_API long long IGSharp_MultiSelectIO_GetRangeSrcItem(void* io);
IGSHARP_API long long IGSharp_MultiSelectIO_GetNavIdItem(void* io);
IGSHARP_API bool      IGSharp_MultiSelectIO_GetNavIdSelected(void* io);
IGSHARP_API bool      IGSharp_MultiSelectIO_GetRangeSrcReset(void* io);
IGSHARP_API void      IGSharp_MultiSelectIO_SetRangeSrcReset(void* io, bool v);
IGSHARP_API int       IGSharp_MultiSelectIO_GetItemsCount(void* io);

// ImGuiSelectionRequest accessors
IGSHARP_API int       IGSharp_SelectionRequest_GetType(void* request);
IGSHARP_API bool      IGSharp_SelectionRequest_GetSelected(void* request);
IGSHARP_API int       IGSharp_SelectionRequest_GetRangeDirection(void* request);
IGSHARP_API long long IGSharp_SelectionRequest_GetRangeFirstItem(void* request);
IGSHARP_API long long IGSharp_SelectionRequest_GetRangeLastItem(void* request);

//-----------------------------------------------------------------------------
// [SECTION] Drawing API (ImDrawCallback, ImDrawCmd, ImDrawIdx, ImDrawVert, ImDrawChannel, ImDrawListSplitter, ImDrawFlags, ImDrawListFlags, ImDrawList, ImDrawData)
//-----------------------------------------------------------------------------

// ImDrawList: Clipping
IGSHARP_API void IGSharp_DrawList_PushClipRect(void* draw_list, IGSharp_Vec2 clip_rect_min, IGSharp_Vec2 clip_rect_max, bool intersect_with_current);
IGSHARP_API void IGSharp_DrawList_PushClipRectFullScreen(void* draw_list);
IGSHARP_API void IGSharp_DrawList_PopClipRect(void* draw_list);

// ImDrawList: Primitives
IGSHARP_API void IGSharp_DrawList_AddLine(void* draw_list, IGSharp_Vec2 p1, IGSharp_Vec2 p2, unsigned int col, float thickness);
IGSHARP_API void IGSharp_DrawList_AddRect(void* draw_list, IGSharp_Vec2 p_min, IGSharp_Vec2 p_max, unsigned int col, float rounding, int flags, float thickness);
IGSHARP_API void IGSharp_DrawList_AddRectFilled(void* draw_list, IGSharp_Vec2 p_min, IGSharp_Vec2 p_max, unsigned int col, float rounding, int flags);
IGSHARP_API void IGSharp_DrawList_AddRectFilledMultiColor(void* draw_list, IGSharp_Vec2 p_min, IGSharp_Vec2 p_max, unsigned int col_ul, unsigned int col_ur, unsigned int col_br, unsigned int col_bl);
IGSHARP_API void IGSharp_DrawList_AddQuad(void* draw_list, IGSharp_Vec2 p1, IGSharp_Vec2 p2, IGSharp_Vec2 p3, IGSharp_Vec2 p4, unsigned int col, float thickness);
IGSHARP_API void IGSharp_DrawList_AddQuadFilled(void* draw_list, IGSharp_Vec2 p1, IGSharp_Vec2 p2, IGSharp_Vec2 p3, IGSharp_Vec2 p4, unsigned int col);
IGSHARP_API void IGSharp_DrawList_AddTriangle(void* draw_list, IGSharp_Vec2 p1, IGSharp_Vec2 p2, IGSharp_Vec2 p3, unsigned int col, float thickness);
IGSHARP_API void IGSharp_DrawList_AddTriangleFilled(void* draw_list, IGSharp_Vec2 p1, IGSharp_Vec2 p2, IGSharp_Vec2 p3, unsigned int col);
IGSHARP_API void IGSharp_DrawList_AddCircle(void* draw_list, IGSharp_Vec2 center, float radius, unsigned int col, int num_segments, float thickness);
IGSHARP_API void IGSharp_DrawList_AddCircleFilled(void* draw_list, IGSharp_Vec2 center, float radius, unsigned int col, int num_segments);
IGSHARP_API void IGSharp_DrawList_AddNgon(void* draw_list, IGSharp_Vec2 center, float radius, unsigned int col, int num_segments, float thickness);
IGSHARP_API void IGSharp_DrawList_AddNgonFilled(void* draw_list, IGSharp_Vec2 center, float radius, unsigned int col, int num_segments);
IGSHARP_API void IGSharp_DrawList_AddEllipse(void* draw_list, IGSharp_Vec2 center, IGSharp_Vec2 radius, unsigned int col, float rot, int num_segments, float thickness);
IGSHARP_API void IGSharp_DrawList_AddEllipseFilled(void* draw_list, IGSharp_Vec2 center, IGSharp_Vec2 radius, unsigned int col, float rot, int num_segments);
IGSHARP_API void IGSharp_DrawList_AddText(void* draw_list, IGSharp_Vec2 pos, unsigned int col, const char* text_begin, const char* text_end);
IGSHARP_API void IGSharp_DrawList_AddBezierCubic(void* draw_list, IGSharp_Vec2 p1, IGSharp_Vec2 p2, IGSharp_Vec2 p3, IGSharp_Vec2 p4, unsigned int col, float thickness, int num_segments);
IGSHARP_API void IGSharp_DrawList_AddBezierQuadratic(void* draw_list, IGSharp_Vec2 p1, IGSharp_Vec2 p2, IGSharp_Vec2 p3, unsigned int col, float thickness, int num_segments);
IGSHARP_API void IGSharp_DrawList_AddPolyline(void* draw_list, const IGSharp_Vec2* points, int num_points, unsigned int col, int flags, float thickness);
IGSHARP_API void IGSharp_DrawList_AddConvexPolyFilled(void* draw_list, const IGSharp_Vec2* points, int num_points, unsigned int col);
IGSHARP_API void IGSharp_DrawList_AddConcavePolyFilled(void* draw_list, const IGSharp_Vec2* points, int num_points, unsigned int col);

// ImDrawList: Images
IGSHARP_API void IGSharp_DrawList_AddImage(void* draw_list, unsigned long long tex_id, IGSharp_Vec2 p_min, IGSharp_Vec2 p_max, IGSharp_Vec2 uv_min, IGSharp_Vec2 uv_max, unsigned int col);
IGSHARP_API void IGSharp_DrawList_AddImageQuad(void* draw_list, unsigned long long tex_id, IGSharp_Vec2 p1, IGSharp_Vec2 p2, IGSharp_Vec2 p3, IGSharp_Vec2 p4, IGSharp_Vec2 uv1, IGSharp_Vec2 uv2, IGSharp_Vec2 uv3, IGSharp_Vec2 uv4, unsigned int col);
IGSHARP_API void IGSharp_DrawList_AddImageRounded(void* draw_list, unsigned long long tex_id, IGSharp_Vec2 p_min, IGSharp_Vec2 p_max, IGSharp_Vec2 uv_min, IGSharp_Vec2 uv_max, unsigned int col, float rounding, int flags);

// ImDrawList: Path API
IGSHARP_API void IGSharp_DrawList_PathClear(void* draw_list);
IGSHARP_API void IGSharp_DrawList_PathLineTo(void* draw_list, IGSharp_Vec2 pos);
IGSHARP_API void IGSharp_DrawList_PathLineToMergeDuplicate(void* draw_list, IGSharp_Vec2 pos);
IGSHARP_API void IGSharp_DrawList_PathFillConvex(void* draw_list, unsigned int col);
IGSHARP_API void IGSharp_DrawList_PathStroke(void* draw_list, unsigned int col, int flags, float thickness);
IGSHARP_API void IGSharp_DrawList_PathArcTo(void* draw_list, IGSharp_Vec2 center, float radius, float a_min, float a_max, int num_segments);
IGSHARP_API void IGSharp_DrawList_PathArcToFast(void* draw_list, IGSharp_Vec2 center, float radius, int a_min_of_12, int a_max_of_12);
IGSHARP_API void IGSharp_DrawList_PathBezierCubicCurveTo(void* draw_list, IGSharp_Vec2 p2, IGSharp_Vec2 p3, IGSharp_Vec2 p4, int num_segments);
IGSHARP_API void IGSharp_DrawList_PathBezierQuadraticCurveTo(void* draw_list, IGSharp_Vec2 p2, IGSharp_Vec2 p3, int num_segments);
IGSHARP_API void IGSharp_DrawList_PathRect(void* draw_list, IGSharp_Vec2 rect_min, IGSharp_Vec2 rect_max, float rounding, int flags);

//-----------------------------------------------------------------------------
// [SECTION] Texture API (ImTextureFormat, ImTextureStatus, ImTextureRect, ImTextureData)
//-----------------------------------------------------------------------------
// (no wrappers yet)

//-----------------------------------------------------------------------------
// [SECTION] Font API (ImFontConfig, ImFontGlyph, ImFontGlyphRangesBuilder, ImFontAtlasFlags, ImFontAtlas, ImFontBaked, ImFont)
//-----------------------------------------------------------------------------

// ImFontAtlas
IGSHARP_API void* IGSharp_FontAtlas_AddFontDefault(void* atlas);
IGSHARP_API void* IGSharp_FontAtlas_AddFontFromFileTTF(void* atlas, const char* filename, float size_pixels);
IGSHARP_API void* IGSharp_FontAtlas_AddFontFromMemoryTTF(void* atlas, void* font_data, int font_data_size, float size_pixels, bool transfer_ownership);
IGSHARP_API void* IGSharp_FontAtlas_AddFontFromMemoryCompressedTTF(void* atlas, const void* compressed_data, int compressed_size, float size_pixels);
IGSHARP_API void  IGSharp_FontAtlas_Clear(void* atlas);
IGSHARP_API void  IGSharp_FontAtlas_ClearFonts(void* atlas);
IGSHARP_API int   IGSharp_FontAtlas_GetFontCount(void* atlas);
IGSHARP_API void* IGSharp_FontAtlas_GetFont(void* atlas, int index);

//-----------------------------------------------------------------------------
// [SECTION] Viewports (ImGuiViewportFlags, ImGuiViewport)
//-----------------------------------------------------------------------------

IGSHARP_API IGSharp_Vec2 IGSharp_Viewport_GetPos(void* viewport);
IGSHARP_API IGSharp_Vec2 IGSharp_Viewport_GetSize(void* viewport);
IGSHARP_API IGSharp_Vec2 IGSharp_Viewport_GetWorkPos(void* viewport);
IGSHARP_API IGSharp_Vec2 IGSharp_Viewport_GetWorkSize(void* viewport);

//-----------------------------------------------------------------------------
// [SECTION] ImGuiPlatformIO + other Platform Dependent Interfaces (ImGuiPlatformImeData)
//-----------------------------------------------------------------------------
// (no wrappers yet)

//-----------------------------------------------------------------------------
// [SECTION] Obsolete functions and types
//-----------------------------------------------------------------------------
// (no wrappers yet)
