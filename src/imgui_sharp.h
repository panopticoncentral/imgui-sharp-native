#pragma once

#include <stddef.h>

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

// Types - layout-compatible with ImVec2/ImVec4
typedef struct { float x, y; } IGSharp_Vec2;
typedef struct { float x, y, z, w; } IGSharp_Vec4;

// Opaque types
typedef struct ImGuiContext ImGuiContext;

// --- Context & Lifecycle ---
IGSHARP_API ImGuiContext* IGSharp_CreateContext(void);
IGSHARP_API void          IGSharp_DestroyContext(ImGuiContext* ctx);
IGSHARP_API ImGuiContext* IGSharp_GetCurrentContext(void);
IGSHARP_API void          IGSharp_SetCurrentContext(ImGuiContext* ctx);
IGSHARP_API void          IGSharp_NewFrame(void);
IGSHARP_API void          IGSharp_Render(void);
IGSHARP_API void          IGSharp_EndFrame(void);
IGSHARP_API void*         IGSharp_GetDrawData(void);
IGSHARP_API const char*   IGSharp_GetVersion(void);
IGSHARP_API void          IGSharp_CheckVersion(void);

// --- IO Accessors ---
IGSHARP_API bool IGSharp_IO_GetWantCaptureMouse(void);
IGSHARP_API bool IGSharp_IO_GetWantCaptureKeyboard(void);
IGSHARP_API void IGSharp_IO_SetConfigFlags(int flags);
IGSHARP_API int  IGSharp_IO_GetConfigFlags(void);
IGSHARP_API void IGSharp_IO_SetIniFilename(const char* filename);
IGSHARP_API float IGSharp_IO_GetFramerate(void);

// --- Demo / Styles ---
IGSHARP_API void IGSharp_ShowDemoWindow(bool* p_open);
IGSHARP_API void IGSharp_ShowMetricsWindow(bool* p_open);
IGSHARP_API void IGSharp_StyleColorsDark(void);
IGSHARP_API void IGSharp_StyleColorsLight(void);
IGSHARP_API void IGSharp_StyleColorsClassic(void);

// --- Style Scale ---
IGSHARP_API void IGSharp_Style_ScaleAllSizes(float scale);
IGSHARP_API void IGSharp_Style_SetFontScaleDpi(float scale);

// --- Windows ---
IGSHARP_API bool IGSharp_Begin(const char* name, bool* p_open, int flags);
IGSHARP_API void IGSharp_End(void);
IGSHARP_API bool IGSharp_BeginChild(const char* str_id, IGSharp_Vec2 size, int child_flags, int window_flags);
IGSHARP_API void IGSharp_EndChild(void);

IGSHARP_API bool IGSharp_IsWindowAppearing(void);
IGSHARP_API bool IGSharp_IsWindowCollapsed(void);
IGSHARP_API bool IGSharp_IsWindowFocused(int flags);
IGSHARP_API bool IGSharp_IsWindowHovered(int flags);
IGSHARP_API IGSharp_Vec2 IGSharp_GetWindowPos(void);
IGSHARP_API IGSharp_Vec2 IGSharp_GetWindowSize(void);
IGSHARP_API float IGSharp_GetWindowWidth(void);
IGSHARP_API float IGSharp_GetWindowHeight(void);

IGSHARP_API void IGSharp_SetNextWindowPos(IGSharp_Vec2 pos, int cond, IGSharp_Vec2 pivot);
IGSHARP_API void IGSharp_SetNextWindowSize(IGSharp_Vec2 size, int cond);
IGSHARP_API void IGSharp_SetNextWindowCollapsed(bool collapsed, int cond);
IGSHARP_API void IGSharp_SetNextWindowFocus(void);
IGSHARP_API void IGSharp_SetNextWindowBgAlpha(float alpha);

// --- Layout ---
IGSHARP_API void IGSharp_Separator(void);
IGSHARP_API void IGSharp_SameLine(float offset_from_start_x, float spacing);
IGSHARP_API void IGSharp_NewLine(void);
IGSHARP_API void IGSharp_Spacing(void);
IGSHARP_API void IGSharp_Dummy(IGSharp_Vec2 size);
IGSHARP_API void IGSharp_Indent(float indent_w);
IGSHARP_API void IGSharp_Unindent(float indent_w);
IGSHARP_API void IGSharp_BeginGroup(void);
IGSHARP_API void IGSharp_EndGroup(void);
IGSHARP_API IGSharp_Vec2 IGSharp_GetCursorPos(void);
IGSHARP_API void IGSharp_SetCursorPos(IGSharp_Vec2 local_pos);
IGSHARP_API IGSharp_Vec2 IGSharp_GetCursorScreenPos(void);
IGSHARP_API void IGSharp_SetCursorScreenPos(IGSharp_Vec2 screen_pos);
IGSHARP_API IGSharp_Vec2 IGSharp_GetContentRegionAvail(void);
IGSHARP_API void IGSharp_AlignTextToFramePadding(void);
IGSHARP_API float IGSharp_GetTextLineHeight(void);
IGSHARP_API float IGSharp_GetTextLineHeightWithSpacing(void);
IGSHARP_API float IGSharp_GetFrameHeight(void);
IGSHARP_API float IGSharp_GetFrameHeightWithSpacing(void);

// --- ID Stack ---
IGSHARP_API void IGSharp_PushIDStr(const char* str_id);
IGSHARP_API void IGSharp_PushIDInt(int int_id);
IGSHARP_API void IGSharp_PopID(void);
IGSHARP_API unsigned int IGSharp_GetIDStr(const char* str_id);

// --- Style Stack ---
IGSHARP_API void IGSharp_PushStyleColorU32(int idx, unsigned int col);
IGSHARP_API void IGSharp_PushStyleColorVec4(int idx, IGSharp_Vec4 col);
IGSHARP_API void IGSharp_PopStyleColor(int count);
IGSHARP_API void IGSharp_PushStyleVarFloat(int idx, float val);
IGSHARP_API void IGSharp_PushStyleVarVec2(int idx, IGSharp_Vec2 val);
IGSHARP_API void IGSharp_PopStyleVar(int count);
IGSHARP_API void IGSharp_PushItemWidth(float item_width);
IGSHARP_API void IGSharp_PopItemWidth(void);
IGSHARP_API void IGSharp_SetNextItemWidth(float item_width);
IGSHARP_API float IGSharp_CalcItemWidth(void);
IGSHARP_API void IGSharp_PushTextWrapPos(float wrap_local_pos_x);
IGSHARP_API void IGSharp_PopTextWrapPos(void);

// --- Widgets: Text ---
IGSHARP_API void IGSharp_TextUnformatted(const char* text, const char* text_end);
IGSHARP_API void IGSharp_Text(const char* text);
IGSHARP_API void IGSharp_TextColored(IGSharp_Vec4 col, const char* text);
IGSHARP_API void IGSharp_TextDisabled(const char* text);
IGSHARP_API void IGSharp_TextWrapped(const char* text);
IGSHARP_API void IGSharp_LabelText(const char* label, const char* text);
IGSHARP_API void IGSharp_BulletText(const char* text);
IGSHARP_API void IGSharp_SeparatorText(const char* label);

// --- Widgets: Buttons ---
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

// --- Widgets: Images ---
IGSHARP_API void IGSharp_Image(unsigned long long tex_id, IGSharp_Vec2 image_size, IGSharp_Vec2 uv0, IGSharp_Vec2 uv1, IGSharp_Vec4 tint_col, IGSharp_Vec4 border_col);
IGSHARP_API bool IGSharp_ImageButton(const char* str_id, unsigned long long tex_id, IGSharp_Vec2 image_size, IGSharp_Vec2 uv0, IGSharp_Vec2 uv1, IGSharp_Vec4 bg_col, IGSharp_Vec4 tint_col);

// --- Widgets: Combo ---
IGSHARP_API bool IGSharp_BeginCombo(const char* label, const char* preview_value, int flags);
IGSHARP_API void IGSharp_EndCombo(void);

// --- Widgets: Drag ---
IGSHARP_API bool IGSharp_DragFloat(const char* label, float* v, float v_speed, float v_min, float v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_DragFloat2(const char* label, float v[2], float v_speed, float v_min, float v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_DragFloat3(const char* label, float v[3], float v_speed, float v_min, float v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_DragFloat4(const char* label, float v[4], float v_speed, float v_min, float v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_DragInt(const char* label, int* v, float v_speed, int v_min, int v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_DragInt2(const char* label, int v[2], float v_speed, int v_min, int v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_DragInt3(const char* label, int v[3], float v_speed, int v_min, int v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_DragInt4(const char* label, int v[4], float v_speed, int v_min, int v_max, const char* format, int flags);

// --- Widgets: Slider ---
IGSHARP_API bool IGSharp_SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_SliderFloat2(const char* label, float v[2], float v_min, float v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_SliderFloat3(const char* label, float v[3], float v_min, float v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_SliderFloat4(const char* label, float v[4], float v_min, float v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_SliderAngle(const char* label, float* v_rad, float v_degrees_min, float v_degrees_max, const char* format, int flags);
IGSHARP_API bool IGSharp_SliderInt(const char* label, int* v, int v_min, int v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_SliderInt2(const char* label, int v[2], int v_min, int v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_SliderInt3(const char* label, int v[3], int v_min, int v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_SliderInt4(const char* label, int v[4], int v_min, int v_max, const char* format, int flags);

// --- Widgets: Input ---
IGSHARP_API bool IGSharp_InputText(const char* label, char* buf, size_t buf_size, int flags);
IGSHARP_API bool IGSharp_InputTextMultiline(const char* label, char* buf, size_t buf_size, IGSharp_Vec2 size, int flags);
IGSHARP_API bool IGSharp_InputTextWithHint(const char* label, const char* hint, char* buf, size_t buf_size, int flags);
IGSHARP_API bool IGSharp_InputFloat(const char* label, float* v, float step, float step_fast, const char* format, int flags);
IGSHARP_API bool IGSharp_InputFloat2(const char* label, float v[2], const char* format, int flags);
IGSHARP_API bool IGSharp_InputFloat3(const char* label, float v[3], const char* format, int flags);
IGSHARP_API bool IGSharp_InputFloat4(const char* label, float v[4], const char* format, int flags);
IGSHARP_API bool IGSharp_InputInt(const char* label, int* v, int step, int step_fast, int flags);
IGSHARP_API bool IGSharp_InputInt2(const char* label, int v[2], int flags);
IGSHARP_API bool IGSharp_InputInt3(const char* label, int v[3], int flags);
IGSHARP_API bool IGSharp_InputInt4(const char* label, int v[4], int flags);
IGSHARP_API bool IGSharp_InputDouble(const char* label, double* v, double step, double step_fast, const char* format, int flags);

// --- Widgets: Color ---
IGSHARP_API bool IGSharp_ColorEdit3(const char* label, float col[3], int flags);
IGSHARP_API bool IGSharp_ColorEdit4(const char* label, float col[4], int flags);
IGSHARP_API bool IGSharp_ColorPicker3(const char* label, float col[3], int flags);
IGSHARP_API bool IGSharp_ColorPicker4(const char* label, float col[4], int flags, const float* ref_col);
IGSHARP_API bool IGSharp_ColorButton(const char* desc_id, IGSharp_Vec4 col, int flags, IGSharp_Vec2 size);

// --- Widgets: Trees ---
IGSHARP_API bool IGSharp_TreeNode(const char* label);
IGSHARP_API bool IGSharp_TreeNodeEx(const char* label, int flags);
IGSHARP_API void IGSharp_TreePop(void);
IGSHARP_API float IGSharp_GetTreeNodeToLabelSpacing(void);
IGSHARP_API bool IGSharp_TreeNodeGetOpen(unsigned int storage_id);
IGSHARP_API bool IGSharp_CollapsingHeader(const char* label, int flags);
IGSHARP_API bool IGSharp_CollapsingHeaderClosable(const char* label, bool* p_visible, int flags);
IGSHARP_API void IGSharp_SetNextItemOpen(bool is_open, int cond);

// --- Widgets: Selectable ---
IGSHARP_API bool IGSharp_Selectable(const char* label, bool selected, int flags, IGSharp_Vec2 size);
IGSHARP_API bool IGSharp_SelectablePtr(const char* label, bool* p_selected, int flags, IGSharp_Vec2 size);

// --- Widgets: List Box ---
IGSHARP_API bool IGSharp_BeginListBox(const char* label, IGSharp_Vec2 size);
IGSHARP_API void IGSharp_EndListBox(void);

// --- Widgets: Menus ---
IGSHARP_API bool IGSharp_BeginMenuBar(void);
IGSHARP_API void IGSharp_EndMenuBar(void);
IGSHARP_API bool IGSharp_BeginMainMenuBar(void);
IGSHARP_API void IGSharp_EndMainMenuBar(void);
IGSHARP_API bool IGSharp_BeginMenu(const char* label, bool enabled);
IGSHARP_API void IGSharp_EndMenu(void);
IGSHARP_API bool IGSharp_MenuItem(const char* label, const char* shortcut, bool selected, bool enabled);
IGSHARP_API bool IGSharp_MenuItemPtr(const char* label, const char* shortcut, bool* p_selected, bool enabled);

// --- Widgets: Tooltips ---
IGSHARP_API bool IGSharp_BeginTooltip(void);
IGSHARP_API void IGSharp_EndTooltip(void);
IGSHARP_API void IGSharp_SetTooltip(const char* text);
IGSHARP_API bool IGSharp_BeginItemTooltip(void);

// --- Widgets: Popups ---
IGSHARP_API bool IGSharp_BeginPopup(const char* str_id, int flags);
IGSHARP_API bool IGSharp_BeginPopupModal(const char* name, bool* p_open, int flags);
IGSHARP_API void IGSharp_EndPopup(void);
IGSHARP_API void IGSharp_OpenPopup(const char* str_id, int popup_flags);
IGSHARP_API void IGSharp_CloseCurrentPopup(void);
IGSHARP_API bool IGSharp_BeginPopupContextItem(const char* str_id, int popup_flags);
IGSHARP_API bool IGSharp_BeginPopupContextWindow(const char* str_id, int popup_flags);
IGSHARP_API bool IGSharp_IsPopupOpen(const char* str_id, int flags);

// --- Widgets: Tables ---
IGSHARP_API bool IGSharp_BeginTable(const char* str_id, int columns, int flags, IGSharp_Vec2 outer_size, float inner_width);
IGSHARP_API void IGSharp_EndTable(void);
IGSHARP_API void IGSharp_TableNextRow(int row_flags, float min_row_height);
IGSHARP_API bool IGSharp_TableNextColumn(void);
IGSHARP_API bool IGSharp_TableSetColumnIndex(int column_n);
IGSHARP_API void IGSharp_TableSetupColumn(const char* label, int flags, float init_width_or_weight, unsigned int user_id);
IGSHARP_API void IGSharp_TableSetupScrollFreeze(int cols, int rows);
IGSHARP_API void IGSharp_TableHeadersRow(void);
IGSHARP_API void IGSharp_TableHeader(const char* label);

// --- Widgets: Tabs ---
IGSHARP_API bool IGSharp_BeginTabBar(const char* str_id, int flags);
IGSHARP_API void IGSharp_EndTabBar(void);
IGSHARP_API bool IGSharp_BeginTabItem(const char* label, bool* p_open, int flags);
IGSHARP_API void IGSharp_EndTabItem(void);
IGSHARP_API bool IGSharp_TabItemButton(const char* label, int flags);
IGSHARP_API void IGSharp_SetTabItemClosed(const char* tab_or_docked_window_label);

// --- Disabling ---
IGSHARP_API void IGSharp_BeginDisabled(bool disabled);
IGSHARP_API void IGSharp_EndDisabled(void);

// --- Item Utilities ---
IGSHARP_API bool IGSharp_IsItemHovered(int flags);
IGSHARP_API bool IGSharp_IsItemActive(void);
IGSHARP_API bool IGSharp_IsItemFocused(void);
IGSHARP_API bool IGSharp_IsItemClicked(int mouse_button);
IGSHARP_API bool IGSharp_IsItemVisible(void);
IGSHARP_API bool IGSharp_IsItemEdited(void);
IGSHARP_API bool IGSharp_IsItemActivated(void);
IGSHARP_API bool IGSharp_IsItemDeactivated(void);
IGSHARP_API bool IGSharp_IsItemDeactivatedAfterEdit(void);
IGSHARP_API bool IGSharp_IsItemToggledOpen(void);
IGSHARP_API IGSharp_Vec2 IGSharp_GetItemRectMin(void);
IGSHARP_API IGSharp_Vec2 IGSharp_GetItemRectMax(void);
IGSHARP_API IGSharp_Vec2 IGSharp_GetItemRectSize(void);
IGSHARP_API void IGSharp_SetItemDefaultFocus(void);

// --- Misc Utilities ---
IGSHARP_API IGSharp_Vec2 IGSharp_CalcTextSize(const char* text, const char* text_end, bool hide_text_after_double_hash, float wrap_width);
IGSHARP_API unsigned int IGSharp_GetColorU32(int idx, float alpha_mul);
IGSHARP_API unsigned int IGSharp_GetColorU32Vec4(IGSharp_Vec4 col);
IGSHARP_API unsigned int IGSharp_GetColorU32Packed(unsigned int col, float alpha_mul);
IGSHARP_API IGSharp_Vec4 IGSharp_ColorConvertU32ToFloat4(unsigned int in);
IGSHARP_API unsigned int IGSharp_ColorConvertFloat4ToU32(IGSharp_Vec4 in);
IGSHARP_API void IGSharp_ColorConvertRGBtoHSV(float r, float g, float b, float* out_h, float* out_s, float* out_v);
IGSHARP_API void IGSharp_ColorConvertHSVtoRGB(float h, float s, float v, float* out_r, float* out_g, float* out_b);

// --- Keyboard / Mouse Input ---
IGSHARP_API bool IGSharp_IsKeyDown(int key);
IGSHARP_API bool IGSharp_IsKeyPressed(int key, bool repeat);
IGSHARP_API bool IGSharp_IsKeyReleased(int key);
IGSHARP_API bool IGSharp_IsKeyChordPressed(int key_chord);
IGSHARP_API bool IGSharp_IsMouseDown(int button);
IGSHARP_API bool IGSharp_IsMouseClicked(int button, bool repeat);
IGSHARP_API bool IGSharp_IsMouseReleased(int button);
IGSHARP_API bool IGSharp_IsMouseDoubleClicked(int button);
IGSHARP_API bool IGSharp_IsMouseHoveringRect(IGSharp_Vec2 r_min, IGSharp_Vec2 r_max, bool clip);
IGSHARP_API bool IGSharp_IsMousePosValid(const IGSharp_Vec2* mouse_pos);
IGSHARP_API IGSharp_Vec2 IGSharp_GetMousePos(void);
IGSHARP_API bool IGSharp_IsMouseDragging(int button, float lock_threshold);
IGSHARP_API IGSharp_Vec2 IGSharp_GetMouseDragDelta(int button, float lock_threshold);

// --- Viewport ---
IGSHARP_API void* IGSharp_GetMainViewport(void);
IGSHARP_API IGSharp_Vec2 IGSharp_Viewport_GetPos(void* viewport);
IGSHARP_API IGSharp_Vec2 IGSharp_Viewport_GetSize(void* viewport);
IGSHARP_API IGSharp_Vec2 IGSharp_Viewport_GetWorkPos(void* viewport);
IGSHARP_API IGSharp_Vec2 IGSharp_Viewport_GetWorkSize(void* viewport);

// --- DrawList: Accessors ---
IGSHARP_API void* IGSharp_GetWindowDrawList(void);
IGSHARP_API void* IGSharp_GetBackgroundDrawList(void);
IGSHARP_API void* IGSharp_GetForegroundDrawList(void);

// --- DrawList: Clipping ---
IGSHARP_API void IGSharp_DrawList_PushClipRect(void* draw_list, IGSharp_Vec2 clip_rect_min, IGSharp_Vec2 clip_rect_max, bool intersect_with_current);
IGSHARP_API void IGSharp_DrawList_PushClipRectFullScreen(void* draw_list);
IGSHARP_API void IGSharp_DrawList_PopClipRect(void* draw_list);

// --- DrawList: Primitives ---
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

// --- DrawList: Images ---
IGSHARP_API void IGSharp_DrawList_AddImage(void* draw_list, unsigned long long tex_id, IGSharp_Vec2 p_min, IGSharp_Vec2 p_max, IGSharp_Vec2 uv_min, IGSharp_Vec2 uv_max, unsigned int col);
IGSHARP_API void IGSharp_DrawList_AddImageQuad(void* draw_list, unsigned long long tex_id, IGSharp_Vec2 p1, IGSharp_Vec2 p2, IGSharp_Vec2 p3, IGSharp_Vec2 p4, IGSharp_Vec2 uv1, IGSharp_Vec2 uv2, IGSharp_Vec2 uv3, IGSharp_Vec2 uv4, unsigned int col);
IGSHARP_API void IGSharp_DrawList_AddImageRounded(void* draw_list, unsigned long long tex_id, IGSharp_Vec2 p_min, IGSharp_Vec2 p_max, IGSharp_Vec2 uv_min, IGSharp_Vec2 uv_max, unsigned int col, float rounding, int flags);

// --- DrawList: Path API ---
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

// --- Drag and Drop ---
IGSHARP_API bool  IGSharp_BeginDragDropSource(int flags);
IGSHARP_API bool  IGSharp_SetDragDropPayload(const char* type, const void* data, size_t sz, int cond);
IGSHARP_API void  IGSharp_EndDragDropSource(void);
IGSHARP_API bool  IGSharp_BeginDragDropTarget(void);
IGSHARP_API void* IGSharp_AcceptDragDropPayload(const char* type, int flags);
IGSHARP_API void  IGSharp_EndDragDropTarget(void);
IGSHARP_API void* IGSharp_GetDragDropPayload(void);

// --- Payload Accessors ---
IGSHARP_API void*       IGSharp_Payload_GetData(void* payload);
IGSHARP_API int         IGSharp_Payload_GetDataSize(void* payload);
IGSHARP_API const char* IGSharp_Payload_GetDataType(void* payload);
IGSHARP_API bool        IGSharp_Payload_IsDataType(void* payload, const char* type);
IGSHARP_API bool        IGSharp_Payload_IsPreview(void* payload);
IGSHARP_API bool        IGSharp_Payload_IsDelivery(void* payload);

// --- Multi-Select ---
IGSHARP_API void* IGSharp_BeginMultiSelect(int flags, int selection_size, int items_count);
IGSHARP_API void* IGSharp_EndMultiSelect(void);
IGSHARP_API void  IGSharp_SetNextItemSelectionUserData(long long selection_user_data);
IGSHARP_API bool  IGSharp_IsItemToggledSelection(void);

// --- MultiSelectIO Accessors ---
IGSHARP_API int       IGSharp_MultiSelectIO_GetRequestsCount(void* io);
IGSHARP_API void*     IGSharp_MultiSelectIO_GetRequest(void* io, int index);
IGSHARP_API long long IGSharp_MultiSelectIO_GetRangeSrcItem(void* io);
IGSHARP_API long long IGSharp_MultiSelectIO_GetNavIdItem(void* io);
IGSHARP_API bool      IGSharp_MultiSelectIO_GetNavIdSelected(void* io);
IGSHARP_API bool      IGSharp_MultiSelectIO_GetRangeSrcReset(void* io);
IGSHARP_API void      IGSharp_MultiSelectIO_SetRangeSrcReset(void* io, bool v);
IGSHARP_API int       IGSharp_MultiSelectIO_GetItemsCount(void* io);

// --- SelectionRequest Accessors ---
IGSHARP_API int       IGSharp_SelectionRequest_GetType(void* request);
IGSHARP_API bool      IGSharp_SelectionRequest_GetSelected(void* request);
IGSHARP_API int       IGSharp_SelectionRequest_GetRangeDirection(void* request);
IGSHARP_API long long IGSharp_SelectionRequest_GetRangeFirstItem(void* request);
IGSHARP_API long long IGSharp_SelectionRequest_GetRangeLastItem(void* request);

// --- Table Sort Specs ---
IGSHARP_API void* IGSharp_TableGetSortSpecs(void);
IGSHARP_API int   IGSharp_TableSortSpecs_GetSpecsCount(void* specs);
IGSHARP_API void* IGSharp_TableSortSpecs_GetSpec(void* specs, int index);
IGSHARP_API bool  IGSharp_TableSortSpecs_GetSpecsDirty(void* specs);
IGSHARP_API void  IGSharp_TableSortSpecs_SetSpecsDirty(void* specs, bool v);

IGSHARP_API unsigned int IGSharp_TableColumnSortSpecs_GetColumnUserID(void* spec);
IGSHARP_API int          IGSharp_TableColumnSortSpecs_GetColumnIndex(void* spec);
IGSHARP_API int          IGSharp_TableColumnSortSpecs_GetSortOrder(void* spec);
IGSHARP_API int          IGSharp_TableColumnSortSpecs_GetSortDirection(void* spec);

// --- InputText with callback ---
typedef int (*IGSharp_InputTextCallback)(void* data); // data = ImGuiInputTextCallbackData*

IGSHARP_API bool IGSharp_InputTextEx(const char* label, char* buf, size_t buf_size, int flags, IGSharp_InputTextCallback callback, void* user_data);
IGSHARP_API bool IGSharp_InputTextMultilineEx(const char* label, char* buf, size_t buf_size, IGSharp_Vec2 size, int flags, IGSharp_InputTextCallback callback, void* user_data);
IGSHARP_API bool IGSharp_InputTextWithHintEx(const char* label, const char* hint, char* buf, size_t buf_size, int flags, IGSharp_InputTextCallback callback, void* user_data);

// --- InputTextCallbackData: Field Accessors ---
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

// --- InputTextCallbackData: Helper Methods ---
IGSHARP_API void IGSharp_InputTextCallbackData_DeleteChars(void* data, int pos, int bytes_count);
IGSHARP_API void IGSharp_InputTextCallbackData_InsertChars(void* data, int pos, const char* text, const char* text_end);
IGSHARP_API void IGSharp_InputTextCallbackData_SelectAll(void* data);
IGSHARP_API void IGSharp_InputTextCallbackData_ClearSelection(void* data);
IGSHARP_API bool IGSharp_InputTextCallbackData_HasSelection(void* data);

// --- Plot Widgets ---
typedef float (*IGSharp_PlotValuesGetter)(void* data, int idx);

IGSHARP_API void IGSharp_PlotLines(const char* label, const float* values, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, IGSharp_Vec2 graph_size, int stride);
IGSHARP_API void IGSharp_PlotLinesCallback(const char* label, IGSharp_PlotValuesGetter values_getter, void* data, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, IGSharp_Vec2 graph_size);
IGSHARP_API void IGSharp_PlotHistogram(const char* label, const float* values, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, IGSharp_Vec2 graph_size, int stride);
IGSHARP_API void IGSharp_PlotHistogramCallback(const char* label, IGSharp_PlotValuesGetter values_getter, void* data, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, IGSharp_Vec2 graph_size);

// --- Fonts: Atlas Loading ---
IGSHARP_API void* IGSharp_IO_GetFonts(void);
IGSHARP_API void* IGSharp_FontAtlas_AddFontDefault(void* atlas);
IGSHARP_API void* IGSharp_FontAtlas_AddFontFromFileTTF(void* atlas, const char* filename, float size_pixels);
IGSHARP_API void* IGSharp_FontAtlas_AddFontFromMemoryTTF(void* atlas, void* font_data, int font_data_size, float size_pixels, bool transfer_ownership);
IGSHARP_API void* IGSharp_FontAtlas_AddFontFromMemoryCompressedTTF(void* atlas, const void* compressed_data, int compressed_size, float size_pixels);
IGSHARP_API bool  IGSharp_FontAtlas_Build(void* atlas);
IGSHARP_API void  IGSharp_FontAtlas_Clear(void* atlas);
IGSHARP_API void  IGSharp_FontAtlas_ClearFonts(void* atlas);
IGSHARP_API int   IGSharp_FontAtlas_GetFontCount(void* atlas);
IGSHARP_API void* IGSharp_FontAtlas_GetFont(void* atlas, int index);
IGSHARP_API void  IGSharp_IO_SetFontDefault(void* font);
IGSHARP_API void* IGSharp_IO_GetFontDefault(void);

// --- Fonts: Push/Pop/Query ---
IGSHARP_API void  IGSharp_PushFont(void* font, float font_size_base_unscaled);
IGSHARP_API void  IGSharp_PopFont(void);
IGSHARP_API void* IGSharp_GetFont(void);
IGSHARP_API float IGSharp_GetFontSize(void);

// --- ListClipper ---
IGSHARP_API void* IGSharp_ListClipper_New(void);
IGSHARP_API void  IGSharp_ListClipper_Delete(void* clipper);
IGSHARP_API void  IGSharp_ListClipper_Begin(void* clipper, int items_count, float items_height);
IGSHARP_API void  IGSharp_ListClipper_End(void* clipper);
IGSHARP_API bool  IGSharp_ListClipper_Step(void* clipper);
IGSHARP_API void  IGSharp_ListClipper_IncludeItemsByIndex(void* clipper, int item_begin, int item_end);
IGSHARP_API void  IGSharp_ListClipper_SeekCursorForItem(void* clipper, int item_index);
IGSHARP_API int   IGSharp_ListClipper_GetDisplayStart(void* clipper);
IGSHARP_API int   IGSharp_ListClipper_GetDisplayEnd(void* clipper);

// --- IO: Field Accessors (Read/Write) ---
IGSHARP_API IGSharp_Vec2 IGSharp_IO_GetDisplaySize(void);
IGSHARP_API void         IGSharp_IO_SetDisplaySize(IGSharp_Vec2 v);
IGSHARP_API IGSharp_Vec2 IGSharp_IO_GetDisplayFramebufferScale(void);
IGSHARP_API void         IGSharp_IO_SetDisplayFramebufferScale(IGSharp_Vec2 v);
IGSHARP_API float        IGSharp_IO_GetDeltaTime(void);
IGSHARP_API void         IGSharp_IO_SetDeltaTime(float v);
IGSHARP_API IGSharp_Vec2 IGSharp_IO_GetMousePos(void);
IGSHARP_API IGSharp_Vec2 IGSharp_IO_GetMouseDelta(void);
IGSHARP_API float        IGSharp_IO_GetMouseWheel(void);
IGSHARP_API float        IGSharp_IO_GetMouseWheelH(void);
IGSHARP_API bool         IGSharp_IO_GetKeyCtrl(void);
IGSHARP_API bool         IGSharp_IO_GetKeyShift(void);
IGSHARP_API bool         IGSharp_IO_GetKeyAlt(void);
IGSHARP_API bool         IGSharp_IO_GetKeySuper(void);
IGSHARP_API bool         IGSharp_IO_GetWantTextInput(void);
IGSHARP_API bool         IGSharp_IO_GetWantSetMousePos(void);
IGSHARP_API bool         IGSharp_IO_GetWantSaveIniSettings(void);
IGSHARP_API void         IGSharp_IO_SetWantSaveIniSettings(bool v);
IGSHARP_API bool         IGSharp_IO_GetNavActive(void);
IGSHARP_API bool         IGSharp_IO_GetNavVisible(void);
IGSHARP_API int          IGSharp_IO_GetMetricsRenderVertices(void);
IGSHARP_API int          IGSharp_IO_GetMetricsRenderIndices(void);
IGSHARP_API int          IGSharp_IO_GetMetricsRenderWindows(void);
IGSHARP_API int          IGSharp_IO_GetMetricsActiveWindows(void);
IGSHARP_API int          IGSharp_IO_GetBackendFlags(void);
IGSHARP_API void         IGSharp_IO_SetBackendFlags(int v);
IGSHARP_API float        IGSharp_IO_GetMouseDoubleClickTime(void);
IGSHARP_API void         IGSharp_IO_SetMouseDoubleClickTime(float v);
IGSHARP_API float        IGSharp_IO_GetMouseDoubleClickMaxDist(void);
IGSHARP_API void         IGSharp_IO_SetMouseDoubleClickMaxDist(float v);
IGSHARP_API float        IGSharp_IO_GetMouseDragThreshold(void);
IGSHARP_API void         IGSharp_IO_SetMouseDragThreshold(float v);
IGSHARP_API float        IGSharp_IO_GetKeyRepeatDelay(void);
IGSHARP_API void         IGSharp_IO_SetKeyRepeatDelay(float v);
IGSHARP_API float        IGSharp_IO_GetKeyRepeatRate(void);
IGSHARP_API void         IGSharp_IO_SetKeyRepeatRate(float v);

// --- IO: Event Queue ---
IGSHARP_API void IGSharp_IO_AddKeyEvent(int key, bool down);
IGSHARP_API void IGSharp_IO_AddKeyAnalogEvent(int key, bool down, float v);
IGSHARP_API void IGSharp_IO_AddMousePosEvent(float x, float y);
IGSHARP_API void IGSharp_IO_AddMouseButtonEvent(int button, bool down);
IGSHARP_API void IGSharp_IO_AddMouseWheelEvent(float wheel_x, float wheel_y);
IGSHARP_API void IGSharp_IO_AddMouseSourceEvent(int source);
IGSHARP_API void IGSharp_IO_AddFocusEvent(bool focused);
IGSHARP_API void IGSharp_IO_AddInputCharacter(unsigned int c);
IGSHARP_API void IGSharp_IO_AddInputCharacterUTF16(unsigned short c);
IGSHARP_API void IGSharp_IO_AddInputCharactersUTF8(const char* str);
IGSHARP_API void IGSharp_IO_SetAppAcceptingEvents(bool accepting);
IGSHARP_API void IGSharp_IO_ClearEventsQueue(void);
IGSHARP_API void IGSharp_IO_ClearInputKeys(void);
IGSHARP_API void IGSharp_IO_ClearInputMouse(void);

// --- Style: Scalar Fields ---
IGSHARP_API float IGSharp_Style_GetFontSizeBase(void);
IGSHARP_API void  IGSharp_Style_SetFontSizeBase(float v);
IGSHARP_API float IGSharp_Style_GetFontScaleMain(void);
IGSHARP_API void  IGSharp_Style_SetFontScaleMain(float v);
IGSHARP_API float IGSharp_Style_GetFontScaleDpi(void);
IGSHARP_API float IGSharp_Style_GetAlpha(void);
IGSHARP_API void  IGSharp_Style_SetAlpha(float v);
IGSHARP_API float IGSharp_Style_GetDisabledAlpha(void);
IGSHARP_API void  IGSharp_Style_SetDisabledAlpha(float v);
IGSHARP_API float IGSharp_Style_GetWindowRounding(void);
IGSHARP_API void  IGSharp_Style_SetWindowRounding(float v);
IGSHARP_API float IGSharp_Style_GetWindowBorderSize(void);
IGSHARP_API void  IGSharp_Style_SetWindowBorderSize(float v);
IGSHARP_API float IGSharp_Style_GetChildRounding(void);
IGSHARP_API void  IGSharp_Style_SetChildRounding(float v);
IGSHARP_API float IGSharp_Style_GetChildBorderSize(void);
IGSHARP_API void  IGSharp_Style_SetChildBorderSize(float v);
IGSHARP_API float IGSharp_Style_GetPopupRounding(void);
IGSHARP_API void  IGSharp_Style_SetPopupRounding(float v);
IGSHARP_API float IGSharp_Style_GetPopupBorderSize(void);
IGSHARP_API void  IGSharp_Style_SetPopupBorderSize(float v);
IGSHARP_API float IGSharp_Style_GetFrameRounding(void);
IGSHARP_API void  IGSharp_Style_SetFrameRounding(float v);
IGSHARP_API float IGSharp_Style_GetFrameBorderSize(void);
IGSHARP_API void  IGSharp_Style_SetFrameBorderSize(float v);
IGSHARP_API float IGSharp_Style_GetIndentSpacing(void);
IGSHARP_API void  IGSharp_Style_SetIndentSpacing(float v);
IGSHARP_API float IGSharp_Style_GetColumnsMinSpacing(void);
IGSHARP_API void  IGSharp_Style_SetColumnsMinSpacing(float v);
IGSHARP_API float IGSharp_Style_GetScrollbarSize(void);
IGSHARP_API void  IGSharp_Style_SetScrollbarSize(float v);
IGSHARP_API float IGSharp_Style_GetScrollbarRounding(void);
IGSHARP_API void  IGSharp_Style_SetScrollbarRounding(float v);
IGSHARP_API float IGSharp_Style_GetGrabMinSize(void);
IGSHARP_API void  IGSharp_Style_SetGrabMinSize(float v);
IGSHARP_API float IGSharp_Style_GetGrabRounding(void);
IGSHARP_API void  IGSharp_Style_SetGrabRounding(float v);
IGSHARP_API float IGSharp_Style_GetImageRounding(void);
IGSHARP_API void  IGSharp_Style_SetImageRounding(float v);
IGSHARP_API float IGSharp_Style_GetImageBorderSize(void);
IGSHARP_API void  IGSharp_Style_SetImageBorderSize(float v);
IGSHARP_API float IGSharp_Style_GetTabRounding(void);
IGSHARP_API void  IGSharp_Style_SetTabRounding(float v);
IGSHARP_API float IGSharp_Style_GetTabBorderSize(void);
IGSHARP_API void  IGSharp_Style_SetTabBorderSize(float v);
IGSHARP_API float IGSharp_Style_GetSeparatorSize(void);
IGSHARP_API void  IGSharp_Style_SetSeparatorSize(float v);
IGSHARP_API float IGSharp_Style_GetMouseCursorScale(void);
IGSHARP_API void  IGSharp_Style_SetMouseCursorScale(float v);
IGSHARP_API bool  IGSharp_Style_GetAntiAliasedLines(void);
IGSHARP_API void  IGSharp_Style_SetAntiAliasedLines(bool v);
IGSHARP_API bool  IGSharp_Style_GetAntiAliasedFill(void);
IGSHARP_API void  IGSharp_Style_SetAntiAliasedFill(bool v);
IGSHARP_API float IGSharp_Style_GetCurveTessellationTol(void);
IGSHARP_API void  IGSharp_Style_SetCurveTessellationTol(float v);
IGSHARP_API float IGSharp_Style_GetCircleTessellationMaxError(void);
IGSHARP_API void  IGSharp_Style_SetCircleTessellationMaxError(float v);

// --- Style: Vec2 Fields ---
IGSHARP_API IGSharp_Vec2 IGSharp_Style_GetWindowPadding(void);
IGSHARP_API void         IGSharp_Style_SetWindowPadding(IGSharp_Vec2 v);
IGSHARP_API IGSharp_Vec2 IGSharp_Style_GetWindowMinSize(void);
IGSHARP_API void         IGSharp_Style_SetWindowMinSize(IGSharp_Vec2 v);
IGSHARP_API IGSharp_Vec2 IGSharp_Style_GetWindowTitleAlign(void);
IGSHARP_API void         IGSharp_Style_SetWindowTitleAlign(IGSharp_Vec2 v);
IGSHARP_API IGSharp_Vec2 IGSharp_Style_GetFramePadding(void);
IGSHARP_API void         IGSharp_Style_SetFramePadding(IGSharp_Vec2 v);
IGSHARP_API IGSharp_Vec2 IGSharp_Style_GetItemSpacing(void);
IGSHARP_API void         IGSharp_Style_SetItemSpacing(IGSharp_Vec2 v);
IGSHARP_API IGSharp_Vec2 IGSharp_Style_GetItemInnerSpacing(void);
IGSHARP_API void         IGSharp_Style_SetItemInnerSpacing(IGSharp_Vec2 v);
IGSHARP_API IGSharp_Vec2 IGSharp_Style_GetCellPadding(void);
IGSHARP_API void         IGSharp_Style_SetCellPadding(IGSharp_Vec2 v);
IGSHARP_API IGSharp_Vec2 IGSharp_Style_GetTouchExtraPadding(void);
IGSHARP_API void         IGSharp_Style_SetTouchExtraPadding(IGSharp_Vec2 v);
IGSHARP_API IGSharp_Vec2 IGSharp_Style_GetButtonTextAlign(void);
IGSHARP_API void         IGSharp_Style_SetButtonTextAlign(IGSharp_Vec2 v);
IGSHARP_API IGSharp_Vec2 IGSharp_Style_GetSelectableTextAlign(void);
IGSHARP_API void         IGSharp_Style_SetSelectableTextAlign(IGSharp_Vec2 v);
IGSHARP_API IGSharp_Vec2 IGSharp_Style_GetSeparatorTextAlign(void);
IGSHARP_API void         IGSharp_Style_SetSeparatorTextAlign(IGSharp_Vec2 v);
IGSHARP_API IGSharp_Vec2 IGSharp_Style_GetSeparatorTextPadding(void);
IGSHARP_API void         IGSharp_Style_SetSeparatorTextPadding(IGSharp_Vec2 v);
IGSHARP_API IGSharp_Vec2 IGSharp_Style_GetDisplayWindowPadding(void);
IGSHARP_API void         IGSharp_Style_SetDisplayWindowPadding(IGSharp_Vec2 v);
IGSHARP_API IGSharp_Vec2 IGSharp_Style_GetDisplaySafeAreaPadding(void);
IGSHARP_API void         IGSharp_Style_SetDisplaySafeAreaPadding(IGSharp_Vec2 v);

// --- Style: Colors ---
IGSHARP_API IGSharp_Vec4 IGSharp_Style_GetColor(int idx);
IGSHARP_API void         IGSharp_Style_SetColor(int idx, IGSharp_Vec4 col);

// --- Scrolling ---
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

// --- Item Flags ---
IGSHARP_API void IGSharp_PushItemFlag(int option, bool enabled);
IGSHARP_API void IGSharp_PopItemFlag(void);

// --- Focus / Activation ---
IGSHARP_API void IGSharp_SetKeyboardFocusHere(int offset);
IGSHARP_API void IGSharp_SetNextItemAllowOverlap(void);

// --- Item Utilities (extra) ---
IGSHARP_API unsigned int IGSharp_GetItemID(void);
IGSHARP_API bool         IGSharp_IsAnyItemHovered(void);
IGSHARP_API bool         IGSharp_IsAnyItemActive(void);
IGSHARP_API bool         IGSharp_IsAnyItemFocused(void);

// --- Mouse Cursor ---
IGSHARP_API int  IGSharp_GetMouseCursor(void);
IGSHARP_API void IGSharp_SetMouseCursor(int cursor_type);

// --- Window Manipulation (extra) ---
IGSHARP_API void IGSharp_SetNextWindowSizeConstraints(IGSharp_Vec2 size_min, IGSharp_Vec2 size_max);
IGSHARP_API void IGSharp_SetNextWindowContentSize(IGSharp_Vec2 size);
IGSHARP_API void IGSharp_SetNextWindowScroll(IGSharp_Vec2 scroll);

// --- Tables (extra) ---
IGSHARP_API void        IGSharp_TableSetBgColor(int target, unsigned int color, int column_n);
IGSHARP_API int         IGSharp_TableGetColumnCount(void);
IGSHARP_API int         IGSharp_TableGetColumnIndex(void);
IGSHARP_API int         IGSharp_TableGetRowIndex(void);
IGSHARP_API const char* IGSharp_TableGetColumnName(int column_n);
IGSHARP_API int         IGSharp_TableGetColumnFlags(int column_n);
IGSHARP_API void        IGSharp_TableSetColumnEnabled(int column_n, bool v);
IGSHARP_API int         IGSharp_TableGetHoveredColumn(void);

// --- Demo / Debug Windows (extra) ---
IGSHARP_API void IGSharp_ShowDebugLogWindow(bool* p_open);
IGSHARP_API void IGSharp_ShowIDStackToolWindow(bool* p_open);
IGSHARP_API void IGSharp_ShowAboutWindow(bool* p_open);
IGSHARP_API void IGSharp_ShowStyleEditor(void);
IGSHARP_API bool IGSharp_ShowStyleSelector(const char* label);
IGSHARP_API void IGSharp_ShowFontSelector(const char* label);
IGSHARP_API void IGSharp_ShowUserGuide(void);

// --- InputTextCallbackData: Resize Helpers ---
IGSHARP_API void IGSharp_InputTextCallbackData_SetBuf(void* data, char* buf);
IGSHARP_API void IGSharp_InputTextCallbackData_SetBufSize(void* data, int size);
IGSHARP_API void IGSharp_InputTextCallbackData_ResizeBuf(void* data, char* new_buf, int new_buf_size);

// --- Widgets: Scalar (generic) ---
IGSHARP_API bool IGSharp_DragScalar(const char* label, int data_type, void* p_data, float v_speed, const void* p_min, const void* p_max, const char* format, int flags);
IGSHARP_API bool IGSharp_DragScalarN(const char* label, int data_type, void* p_data, int components, float v_speed, const void* p_min, const void* p_max, const char* format, int flags);
IGSHARP_API bool IGSharp_SliderScalar(const char* label, int data_type, void* p_data, const void* p_min, const void* p_max, const char* format, int flags);
IGSHARP_API bool IGSharp_SliderScalarN(const char* label, int data_type, void* p_data, int components, const void* p_min, const void* p_max, const char* format, int flags);
IGSHARP_API bool IGSharp_VSliderScalar(const char* label, IGSharp_Vec2 size, int data_type, void* p_data, const void* p_min, const void* p_max, const char* format, int flags);
IGSHARP_API bool IGSharp_InputScalar(const char* label, int data_type, void* p_data, const void* p_step, const void* p_step_fast, const char* format, int flags);
IGSHARP_API bool IGSharp_InputScalarN(const char* label, int data_type, void* p_data, int components, const void* p_step, const void* p_step_fast, const char* format, int flags);

// --- Backend: SDL3 Platform ---
struct SDL_Window;
union SDL_Event;

IGSHARP_API bool IGSharp_ImplSDL3_InitForSDLGPU(SDL_Window* window);
IGSHARP_API void IGSharp_ImplSDL3_Shutdown(void);
IGSHARP_API void IGSharp_ImplSDL3_NewFrame(void);
IGSHARP_API bool IGSharp_ImplSDL3_ProcessEvent(const SDL_Event* event);

// --- Backend: SDL_GPU Renderer ---
struct SDL_GPUDevice;
struct SDL_GPUCommandBuffer;
struct SDL_GPURenderPass;

IGSHARP_API bool IGSharp_ImplSDLGPU3_Init(SDL_GPUDevice* device, int color_target_format, int msaa_samples);
IGSHARP_API void IGSharp_ImplSDLGPU3_Shutdown(void);
IGSHARP_API void IGSharp_ImplSDLGPU3_NewFrame(void);
IGSHARP_API void IGSharp_ImplSDLGPU3_PrepareDrawData(void* draw_data, SDL_GPUCommandBuffer* command_buffer);
IGSHARP_API void IGSharp_ImplSDLGPU3_RenderDrawData(void* draw_data, SDL_GPUCommandBuffer* command_buffer, SDL_GPURenderPass* render_pass);
