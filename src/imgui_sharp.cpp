#include "imgui_sharp.h"
#include "imgui.h"

// Helper: cast between our Vec2/Vec4 and ImGui's (layout-compatible)
static inline ImVec2 ToImVec2(IGSharp_Vec2 v) { return ImVec2(v.x, v.y); }
static inline ImVec4 ToImVec4(IGSharp_Vec4 v) { return ImVec4(v.x, v.y, v.z, v.w); }
static inline IGSharp_Vec2 FromImVec2(ImVec2 v) { return { v.x, v.y }; }

// --- Context & Lifecycle ---

ImGuiContext* IGSharp_CreateContext(void)       { return ImGui::CreateContext(); }
void          IGSharp_DestroyContext(ImGuiContext* ctx) { ImGui::DestroyContext(ctx); }
ImGuiContext* IGSharp_GetCurrentContext(void)   { return ImGui::GetCurrentContext(); }
void          IGSharp_SetCurrentContext(ImGuiContext* ctx) { ImGui::SetCurrentContext(ctx); }
void          IGSharp_NewFrame(void)            { ImGui::NewFrame(); }
void          IGSharp_Render(void)              { ImGui::Render(); }
void          IGSharp_EndFrame(void)            { ImGui::EndFrame(); }
void*         IGSharp_GetDrawData(void)         { return ImGui::GetDrawData(); }
const char*   IGSharp_GetVersion(void)          { return ImGui::GetVersion(); }

void IGSharp_CheckVersion(void)
{
    ImGui::DebugCheckVersionAndDataLayout(IMGUI_VERSION, sizeof(ImGuiIO), sizeof(ImGuiStyle),
        sizeof(ImVec2), sizeof(ImVec4), sizeof(ImDrawVert), sizeof(ImDrawIdx));
}

// --- IO Accessors ---

bool  IGSharp_IO_GetWantCaptureMouse(void)      { return ImGui::GetIO().WantCaptureMouse; }
bool  IGSharp_IO_GetWantCaptureKeyboard(void)   { return ImGui::GetIO().WantCaptureKeyboard; }
void  IGSharp_IO_SetConfigFlags(int flags)      { ImGui::GetIO().ConfigFlags = flags; }
int   IGSharp_IO_GetConfigFlags(void)           { return ImGui::GetIO().ConfigFlags; }
void  IGSharp_IO_SetIniFilename(const char* fn) { ImGui::GetIO().IniFilename = fn; }
float IGSharp_IO_GetFramerate(void)             { return ImGui::GetIO().Framerate; }

// --- Demo / Styles ---

void IGSharp_ShowDemoWindow(bool* p_open)       { ImGui::ShowDemoWindow(p_open); }
void IGSharp_ShowMetricsWindow(bool* p_open)    { ImGui::ShowMetricsWindow(p_open); }
void IGSharp_StyleColorsDark(void)              { ImGui::StyleColorsDark(); }
void IGSharp_StyleColorsLight(void)             { ImGui::StyleColorsLight(); }
void IGSharp_StyleColorsClassic(void)           { ImGui::StyleColorsClassic(); }

// --- Style Scale ---

void IGSharp_Style_ScaleAllSizes(float scale)   { ImGui::GetStyle().ScaleAllSizes(scale); }
void IGSharp_Style_SetFontScaleDpi(float scale) { ImGui::GetStyle().FontScaleDpi = scale; }

// --- Windows ---

bool IGSharp_Begin(const char* name, bool* p_open, int flags)
{ return ImGui::Begin(name, p_open, flags); }

void IGSharp_End(void) { ImGui::End(); }

bool IGSharp_BeginChild(const char* str_id, IGSharp_Vec2 size, int child_flags, int window_flags)
{ return ImGui::BeginChild(str_id, ToImVec2(size), child_flags, window_flags); }

void IGSharp_EndChild(void) { ImGui::EndChild(); }

bool IGSharp_IsWindowAppearing(void)            { return ImGui::IsWindowAppearing(); }
bool IGSharp_IsWindowCollapsed(void)            { return ImGui::IsWindowCollapsed(); }
bool IGSharp_IsWindowFocused(int flags)         { return ImGui::IsWindowFocused(flags); }
bool IGSharp_IsWindowHovered(int flags)         { return ImGui::IsWindowHovered(flags); }
IGSharp_Vec2 IGSharp_GetWindowPos(void)         { return FromImVec2(ImGui::GetWindowPos()); }
IGSharp_Vec2 IGSharp_GetWindowSize(void)        { return FromImVec2(ImGui::GetWindowSize()); }
float IGSharp_GetWindowWidth(void)              { return ImGui::GetWindowWidth(); }
float IGSharp_GetWindowHeight(void)             { return ImGui::GetWindowHeight(); }

void IGSharp_SetNextWindowPos(IGSharp_Vec2 pos, int cond, IGSharp_Vec2 pivot)
{ ImGui::SetNextWindowPos(ToImVec2(pos), cond, ToImVec2(pivot)); }

void IGSharp_SetNextWindowSize(IGSharp_Vec2 size, int cond)
{ ImGui::SetNextWindowSize(ToImVec2(size), cond); }

void IGSharp_SetNextWindowCollapsed(bool collapsed, int cond)
{ ImGui::SetNextWindowCollapsed(collapsed, cond); }

void  IGSharp_SetNextWindowFocus(void)          { ImGui::SetNextWindowFocus(); }
void  IGSharp_SetNextWindowBgAlpha(float alpha)  { ImGui::SetNextWindowBgAlpha(alpha); }

// --- Layout ---

void IGSharp_Separator(void)                    { ImGui::Separator(); }
void IGSharp_SameLine(float offset, float spacing) { ImGui::SameLine(offset, spacing); }
void IGSharp_NewLine(void)                      { ImGui::NewLine(); }
void IGSharp_Spacing(void)                      { ImGui::Spacing(); }
void IGSharp_Dummy(IGSharp_Vec2 size)           { ImGui::Dummy(ToImVec2(size)); }
void IGSharp_Indent(float indent_w)             { ImGui::Indent(indent_w); }
void IGSharp_Unindent(float indent_w)           { ImGui::Unindent(indent_w); }
void IGSharp_BeginGroup(void)                   { ImGui::BeginGroup(); }
void IGSharp_EndGroup(void)                     { ImGui::EndGroup(); }

IGSharp_Vec2 IGSharp_GetCursorPos(void)         { return FromImVec2(ImGui::GetCursorPos()); }
void IGSharp_SetCursorPos(IGSharp_Vec2 p)       { ImGui::SetCursorPos(ToImVec2(p)); }
IGSharp_Vec2 IGSharp_GetCursorScreenPos(void)   { return FromImVec2(ImGui::GetCursorScreenPos()); }
void IGSharp_SetCursorScreenPos(IGSharp_Vec2 p) { ImGui::SetCursorScreenPos(ToImVec2(p)); }
IGSharp_Vec2 IGSharp_GetContentRegionAvail(void){ return FromImVec2(ImGui::GetContentRegionAvail()); }
void  IGSharp_AlignTextToFramePadding(void)     { ImGui::AlignTextToFramePadding(); }
float IGSharp_GetTextLineHeight(void)           { return ImGui::GetTextLineHeight(); }
float IGSharp_GetTextLineHeightWithSpacing(void){ return ImGui::GetTextLineHeightWithSpacing(); }
float IGSharp_GetFrameHeight(void)              { return ImGui::GetFrameHeight(); }
float IGSharp_GetFrameHeightWithSpacing(void)   { return ImGui::GetFrameHeightWithSpacing(); }

// --- ID Stack ---

void IGSharp_PushIDStr(const char* str_id)      { ImGui::PushID(str_id); }
void IGSharp_PushIDInt(int int_id)              { ImGui::PushID(int_id); }
void IGSharp_PopID(void)                        { ImGui::PopID(); }
unsigned int IGSharp_GetIDStr(const char* str_id){ return ImGui::GetID(str_id); }

// --- Style Stack ---

void IGSharp_PushStyleColorU32(int idx, unsigned int col)
{ ImGui::PushStyleColor(idx, (ImU32)col); }

void IGSharp_PushStyleColorVec4(int idx, IGSharp_Vec4 col)
{ ImGui::PushStyleColor(idx, ToImVec4(col)); }

void  IGSharp_PopStyleColor(int count)          { ImGui::PopStyleColor(count); }

void IGSharp_PushStyleVarFloat(int idx, float val)
{ ImGui::PushStyleVar(idx, val); }

void IGSharp_PushStyleVarVec2(int idx, IGSharp_Vec2 val)
{ ImGui::PushStyleVar(idx, ToImVec2(val)); }

void  IGSharp_PopStyleVar(int count)            { ImGui::PopStyleVar(count); }
void  IGSharp_PushItemWidth(float w)            { ImGui::PushItemWidth(w); }
void  IGSharp_PopItemWidth(void)                { ImGui::PopItemWidth(); }
void  IGSharp_SetNextItemWidth(float w)         { ImGui::SetNextItemWidth(w); }
float IGSharp_CalcItemWidth(void)               { return ImGui::CalcItemWidth(); }
void  IGSharp_PushTextWrapPos(float pos)        { ImGui::PushTextWrapPos(pos); }
void  IGSharp_PopTextWrapPos(void)              { ImGui::PopTextWrapPos(); }

// --- Widgets: Text ---
// Note: we wrap printf-style functions with "%s" to prevent format-string attacks

void IGSharp_TextUnformatted(const char* text, const char* text_end)
{ ImGui::TextUnformatted(text, text_end); }

void IGSharp_Text(const char* text)             { ImGui::Text("%s", text); }
void IGSharp_TextColored(IGSharp_Vec4 col, const char* text)
{ ImGui::TextColored(ToImVec4(col), "%s", text); }

void IGSharp_TextDisabled(const char* text)     { ImGui::TextDisabled("%s", text); }
void IGSharp_TextWrapped(const char* text)      { ImGui::TextWrapped("%s", text); }
void IGSharp_LabelText(const char* label, const char* text)
{ ImGui::LabelText(label, "%s", text); }
void IGSharp_BulletText(const char* text)       { ImGui::BulletText("%s", text); }
void IGSharp_SeparatorText(const char* label)   { ImGui::SeparatorText(label); }

// --- Widgets: Buttons ---

bool IGSharp_Button(const char* label, IGSharp_Vec2 size)
{ return ImGui::Button(label, ToImVec2(size)); }

bool IGSharp_SmallButton(const char* label)     { return ImGui::SmallButton(label); }

bool IGSharp_InvisibleButton(const char* str_id, IGSharp_Vec2 size, int flags)
{ return ImGui::InvisibleButton(str_id, ToImVec2(size), flags); }

bool IGSharp_ArrowButton(const char* str_id, int dir)
{ return ImGui::ArrowButton(str_id, (ImGuiDir)dir); }

bool IGSharp_Checkbox(const char* label, bool* v)
{ return ImGui::Checkbox(label, v); }

bool IGSharp_RadioButton(const char* label, bool active)
{ return ImGui::RadioButton(label, active); }

bool IGSharp_RadioButtonInt(const char* label, int* v, int v_button)
{ return ImGui::RadioButton(label, v, v_button); }

void IGSharp_ProgressBar(float fraction, IGSharp_Vec2 size_arg, const char* overlay)
{ ImGui::ProgressBar(fraction, ToImVec2(size_arg), overlay); }

void IGSharp_Bullet(void)                       { ImGui::Bullet(); }
bool IGSharp_TextLink(const char* label)        { return ImGui::TextLink(label); }
void IGSharp_TextLinkOpenURL(const char* label, const char* url)
{ ImGui::TextLinkOpenURL(label, url); }

// --- Widgets: Images ---

void IGSharp_Image(unsigned long long tex_id, IGSharp_Vec2 image_size, IGSharp_Vec2 uv0, IGSharp_Vec2 uv1, IGSharp_Vec4 tint_col, IGSharp_Vec4 border_col)
{ ImGui::Image((ImTextureID)tex_id, ToImVec2(image_size), ToImVec2(uv0), ToImVec2(uv1), ToImVec4(tint_col), ToImVec4(border_col)); }

bool IGSharp_ImageButton(const char* str_id, unsigned long long tex_id, IGSharp_Vec2 image_size, IGSharp_Vec2 uv0, IGSharp_Vec2 uv1, IGSharp_Vec4 bg_col, IGSharp_Vec4 tint_col)
{ return ImGui::ImageButton(str_id, (ImTextureID)tex_id, ToImVec2(image_size), ToImVec2(uv0), ToImVec2(uv1), ToImVec4(bg_col), ToImVec4(tint_col)); }

// --- Widgets: Combo ---

bool IGSharp_BeginCombo(const char* label, const char* preview_value, int flags)
{ return ImGui::BeginCombo(label, preview_value, flags); }

void IGSharp_EndCombo(void) { ImGui::EndCombo(); }

// --- Widgets: Drag ---

bool IGSharp_DragFloat(const char* label, float* v, float v_speed, float v_min, float v_max, const char* format, int flags)
{ return ImGui::DragFloat(label, v, v_speed, v_min, v_max, format, flags); }

bool IGSharp_DragFloat2(const char* label, float v[2], float v_speed, float v_min, float v_max, const char* format, int flags)
{ return ImGui::DragFloat2(label, v, v_speed, v_min, v_max, format, flags); }

bool IGSharp_DragFloat3(const char* label, float v[3], float v_speed, float v_min, float v_max, const char* format, int flags)
{ return ImGui::DragFloat3(label, v, v_speed, v_min, v_max, format, flags); }

bool IGSharp_DragFloat4(const char* label, float v[4], float v_speed, float v_min, float v_max, const char* format, int flags)
{ return ImGui::DragFloat4(label, v, v_speed, v_min, v_max, format, flags); }

bool IGSharp_DragInt(const char* label, int* v, float v_speed, int v_min, int v_max, const char* format, int flags)
{ return ImGui::DragInt(label, v, v_speed, v_min, v_max, format, flags); }

bool IGSharp_DragInt2(const char* label, int v[2], float v_speed, int v_min, int v_max, const char* format, int flags)
{ return ImGui::DragInt2(label, v, v_speed, v_min, v_max, format, flags); }

bool IGSharp_DragInt3(const char* label, int v[3], float v_speed, int v_min, int v_max, const char* format, int flags)
{ return ImGui::DragInt3(label, v, v_speed, v_min, v_max, format, flags); }

bool IGSharp_DragInt4(const char* label, int v[4], float v_speed, int v_min, int v_max, const char* format, int flags)
{ return ImGui::DragInt4(label, v, v_speed, v_min, v_max, format, flags); }

// --- Widgets: Slider ---

bool IGSharp_SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format, int flags)
{ return ImGui::SliderFloat(label, v, v_min, v_max, format, flags); }

bool IGSharp_SliderFloat2(const char* label, float v[2], float v_min, float v_max, const char* format, int flags)
{ return ImGui::SliderFloat2(label, v, v_min, v_max, format, flags); }

bool IGSharp_SliderFloat3(const char* label, float v[3], float v_min, float v_max, const char* format, int flags)
{ return ImGui::SliderFloat3(label, v, v_min, v_max, format, flags); }

bool IGSharp_SliderFloat4(const char* label, float v[4], float v_min, float v_max, const char* format, int flags)
{ return ImGui::SliderFloat4(label, v, v_min, v_max, format, flags); }

bool IGSharp_SliderAngle(const char* label, float* v_rad, float v_degrees_min, float v_degrees_max, const char* format, int flags)
{ return ImGui::SliderAngle(label, v_rad, v_degrees_min, v_degrees_max, format, flags); }

bool IGSharp_SliderInt(const char* label, int* v, int v_min, int v_max, const char* format, int flags)
{ return ImGui::SliderInt(label, v, v_min, v_max, format, flags); }

bool IGSharp_SliderInt2(const char* label, int v[2], int v_min, int v_max, const char* format, int flags)
{ return ImGui::SliderInt2(label, v, v_min, v_max, format, flags); }

bool IGSharp_SliderInt3(const char* label, int v[3], int v_min, int v_max, const char* format, int flags)
{ return ImGui::SliderInt3(label, v, v_min, v_max, format, flags); }

bool IGSharp_SliderInt4(const char* label, int v[4], int v_min, int v_max, const char* format, int flags)
{ return ImGui::SliderInt4(label, v, v_min, v_max, format, flags); }

// --- Widgets: Input ---

bool IGSharp_InputText(const char* label, char* buf, size_t buf_size, int flags)
{ return ImGui::InputText(label, buf, buf_size, flags, nullptr, nullptr); }

bool IGSharp_InputTextMultiline(const char* label, char* buf, size_t buf_size, IGSharp_Vec2 size, int flags)
{ return ImGui::InputTextMultiline(label, buf, buf_size, ToImVec2(size), flags, nullptr, nullptr); }

bool IGSharp_InputTextWithHint(const char* label, const char* hint, char* buf, size_t buf_size, int flags)
{ return ImGui::InputTextWithHint(label, hint, buf, buf_size, flags, nullptr, nullptr); }

bool IGSharp_InputFloat(const char* label, float* v, float step, float step_fast, const char* format, int flags)
{ return ImGui::InputFloat(label, v, step, step_fast, format, flags); }

bool IGSharp_InputFloat2(const char* label, float v[2], const char* format, int flags)
{ return ImGui::InputFloat2(label, v, format, flags); }

bool IGSharp_InputFloat3(const char* label, float v[3], const char* format, int flags)
{ return ImGui::InputFloat3(label, v, format, flags); }

bool IGSharp_InputFloat4(const char* label, float v[4], const char* format, int flags)
{ return ImGui::InputFloat4(label, v, format, flags); }

bool IGSharp_InputInt(const char* label, int* v, int step, int step_fast, int flags)
{ return ImGui::InputInt(label, v, step, step_fast, flags); }

bool IGSharp_InputInt2(const char* label, int v[2], int flags)
{ return ImGui::InputInt2(label, v, flags); }

bool IGSharp_InputInt3(const char* label, int v[3], int flags)
{ return ImGui::InputInt3(label, v, flags); }

bool IGSharp_InputInt4(const char* label, int v[4], int flags)
{ return ImGui::InputInt4(label, v, flags); }

bool IGSharp_InputDouble(const char* label, double* v, double step, double step_fast, const char* format, int flags)
{ return ImGui::InputDouble(label, v, step, step_fast, format, flags); }

// --- Widgets: Color ---

bool IGSharp_ColorEdit3(const char* label, float col[3], int flags)
{ return ImGui::ColorEdit3(label, col, flags); }

bool IGSharp_ColorEdit4(const char* label, float col[4], int flags)
{ return ImGui::ColorEdit4(label, col, flags); }

bool IGSharp_ColorPicker3(const char* label, float col[3], int flags)
{ return ImGui::ColorPicker3(label, col, flags); }

bool IGSharp_ColorPicker4(const char* label, float col[4], int flags, const float* ref_col)
{ return ImGui::ColorPicker4(label, col, flags, ref_col); }

bool IGSharp_ColorButton(const char* desc_id, IGSharp_Vec4 col, int flags, IGSharp_Vec2 size)
{ return ImGui::ColorButton(desc_id, ToImVec4(col), flags, ToImVec2(size)); }

// --- Widgets: Trees ---

bool  IGSharp_TreeNode(const char* label)       { return ImGui::TreeNode(label); }
bool  IGSharp_TreeNodeEx(const char* label, int flags) { return ImGui::TreeNodeEx(label, flags); }
void  IGSharp_TreePop(void)                     { ImGui::TreePop(); }
float IGSharp_GetTreeNodeToLabelSpacing(void)   { return ImGui::GetTreeNodeToLabelSpacing(); }

bool IGSharp_CollapsingHeader(const char* label, int flags)
{ return ImGui::CollapsingHeader(label, flags); }

bool IGSharp_CollapsingHeaderClosable(const char* label, bool* p_visible, int flags)
{ return ImGui::CollapsingHeader(label, p_visible, flags); }

void IGSharp_SetNextItemOpen(bool is_open, int cond)
{ ImGui::SetNextItemOpen(is_open, cond); }

// --- Widgets: Selectable ---

bool IGSharp_Selectable(const char* label, bool selected, int flags, IGSharp_Vec2 size)
{ return ImGui::Selectable(label, selected, flags, ToImVec2(size)); }

bool IGSharp_SelectablePtr(const char* label, bool* p_selected, int flags, IGSharp_Vec2 size)
{ return ImGui::Selectable(label, p_selected, flags, ToImVec2(size)); }

// --- Widgets: List Box ---

bool IGSharp_BeginListBox(const char* label, IGSharp_Vec2 size)
{ return ImGui::BeginListBox(label, ToImVec2(size)); }

void IGSharp_EndListBox(void) { ImGui::EndListBox(); }

// --- Widgets: Menus ---

bool IGSharp_BeginMenuBar(void)                 { return ImGui::BeginMenuBar(); }
void IGSharp_EndMenuBar(void)                   { ImGui::EndMenuBar(); }
bool IGSharp_BeginMainMenuBar(void)             { return ImGui::BeginMainMenuBar(); }
void IGSharp_EndMainMenuBar(void)               { ImGui::EndMainMenuBar(); }
bool IGSharp_BeginMenu(const char* label, bool enabled) { return ImGui::BeginMenu(label, enabled); }
void IGSharp_EndMenu(void)                      { ImGui::EndMenu(); }

bool IGSharp_MenuItem(const char* label, const char* shortcut, bool selected, bool enabled)
{ return ImGui::MenuItem(label, shortcut, selected, enabled); }

bool IGSharp_MenuItemPtr(const char* label, const char* shortcut, bool* p_selected, bool enabled)
{ return ImGui::MenuItem(label, shortcut, p_selected, enabled); }

// --- Widgets: Tooltips ---

bool IGSharp_BeginTooltip(void)                 { return ImGui::BeginTooltip(); }
void IGSharp_EndTooltip(void)                   { ImGui::EndTooltip(); }
void IGSharp_SetTooltip(const char* text)       { ImGui::SetTooltip("%s", text); }
bool IGSharp_BeginItemTooltip(void)             { return ImGui::BeginItemTooltip(); }

// --- Widgets: Popups ---

bool IGSharp_BeginPopup(const char* str_id, int flags)
{ return ImGui::BeginPopup(str_id, flags); }

bool IGSharp_BeginPopupModal(const char* name, bool* p_open, int flags)
{ return ImGui::BeginPopupModal(name, p_open, flags); }

void IGSharp_EndPopup(void)                     { ImGui::EndPopup(); }
void IGSharp_OpenPopup(const char* str_id, int popup_flags)
{ ImGui::OpenPopup(str_id, popup_flags); }
void IGSharp_CloseCurrentPopup(void)            { ImGui::CloseCurrentPopup(); }

bool IGSharp_BeginPopupContextItem(const char* str_id, int popup_flags)
{ return ImGui::BeginPopupContextItem(str_id, popup_flags); }

bool IGSharp_BeginPopupContextWindow(const char* str_id, int popup_flags)
{ return ImGui::BeginPopupContextWindow(str_id, popup_flags); }

bool IGSharp_IsPopupOpen(const char* str_id, int flags)
{ return ImGui::IsPopupOpen(str_id, flags); }

// --- Widgets: Tables ---

bool IGSharp_BeginTable(const char* str_id, int columns, int flags, IGSharp_Vec2 outer_size, float inner_width)
{ return ImGui::BeginTable(str_id, columns, flags, ToImVec2(outer_size), inner_width); }

void IGSharp_EndTable(void)                     { ImGui::EndTable(); }
void IGSharp_TableNextRow(int row_flags, float min_row_height) { ImGui::TableNextRow(row_flags, min_row_height); }
bool IGSharp_TableNextColumn(void)              { return ImGui::TableNextColumn(); }
bool IGSharp_TableSetColumnIndex(int column_n)  { return ImGui::TableSetColumnIndex(column_n); }

void IGSharp_TableSetupColumn(const char* label, int flags, float init_width_or_weight, unsigned int user_id)
{ ImGui::TableSetupColumn(label, flags, init_width_or_weight, user_id); }

void IGSharp_TableSetupScrollFreeze(int cols, int rows) { ImGui::TableSetupScrollFreeze(cols, rows); }
void IGSharp_TableHeadersRow(void)              { ImGui::TableHeadersRow(); }
void IGSharp_TableHeader(const char* label)     { ImGui::TableHeader(label); }

// --- Widgets: Tabs ---

bool IGSharp_BeginTabBar(const char* str_id, int flags) { return ImGui::BeginTabBar(str_id, flags); }
void IGSharp_EndTabBar(void)                    { ImGui::EndTabBar(); }
bool IGSharp_BeginTabItem(const char* label, bool* p_open, int flags) { return ImGui::BeginTabItem(label, p_open, flags); }
void IGSharp_EndTabItem(void)                   { ImGui::EndTabItem(); }
bool IGSharp_TabItemButton(const char* label, int flags) { return ImGui::TabItemButton(label, flags); }
void IGSharp_SetTabItemClosed(const char* label){ ImGui::SetTabItemClosed(label); }

// --- Disabling ---

void IGSharp_BeginDisabled(bool disabled)       { ImGui::BeginDisabled(disabled); }
void IGSharp_EndDisabled(void)                  { ImGui::EndDisabled(); }

// --- Item Utilities ---

bool IGSharp_IsItemHovered(int flags)           { return ImGui::IsItemHovered(flags); }
bool IGSharp_IsItemActive(void)                 { return ImGui::IsItemActive(); }
bool IGSharp_IsItemFocused(void)                { return ImGui::IsItemFocused(); }
bool IGSharp_IsItemClicked(int mouse_button)    { return ImGui::IsItemClicked(mouse_button); }
bool IGSharp_IsItemVisible(void)                { return ImGui::IsItemVisible(); }
bool IGSharp_IsItemEdited(void)                 { return ImGui::IsItemEdited(); }
bool IGSharp_IsItemActivated(void)              { return ImGui::IsItemActivated(); }
bool IGSharp_IsItemDeactivated(void)            { return ImGui::IsItemDeactivated(); }
bool IGSharp_IsItemDeactivatedAfterEdit(void)   { return ImGui::IsItemDeactivatedAfterEdit(); }
bool IGSharp_IsItemToggledOpen(void)            { return ImGui::IsItemToggledOpen(); }
IGSharp_Vec2 IGSharp_GetItemRectMin(void)       { return FromImVec2(ImGui::GetItemRectMin()); }
IGSharp_Vec2 IGSharp_GetItemRectMax(void)       { return FromImVec2(ImGui::GetItemRectMax()); }
IGSharp_Vec2 IGSharp_GetItemRectSize(void)      { return FromImVec2(ImGui::GetItemRectSize()); }
void IGSharp_SetItemDefaultFocus(void)          { ImGui::SetItemDefaultFocus(); }

// --- Misc Utilities ---

IGSharp_Vec2 IGSharp_CalcTextSize(const char* text, const char* text_end, bool hide_text_after_double_hash, float wrap_width)
{ return FromImVec2(ImGui::CalcTextSize(text, text_end, hide_text_after_double_hash, wrap_width)); }

unsigned int IGSharp_GetColorU32(int idx, float alpha_mul)        { return ImGui::GetColorU32((ImGuiCol)idx, alpha_mul); }
unsigned int IGSharp_GetColorU32Vec4(IGSharp_Vec4 col)            { return ImGui::GetColorU32(ToImVec4(col)); }
unsigned int IGSharp_GetColorU32Packed(unsigned int col, float a) { return ImGui::GetColorU32((ImU32)col, a); }

IGSharp_Vec4 IGSharp_ColorConvertU32ToFloat4(unsigned int in)
{
    ImVec4 v = ImGui::ColorConvertU32ToFloat4((ImU32)in);
    return { v.x, v.y, v.z, v.w };
}
unsigned int IGSharp_ColorConvertFloat4ToU32(IGSharp_Vec4 in)
{ return ImGui::ColorConvertFloat4ToU32(ToImVec4(in)); }

void IGSharp_ColorConvertRGBtoHSV(float r, float g, float b, float* out_h, float* out_s, float* out_v)
{ ImGui::ColorConvertRGBtoHSV(r, g, b, *out_h, *out_s, *out_v); }

void IGSharp_ColorConvertHSVtoRGB(float h, float s, float v, float* out_r, float* out_g, float* out_b)
{ ImGui::ColorConvertHSVtoRGB(h, s, v, *out_r, *out_g, *out_b); }

// --- Keyboard / Mouse Input ---

bool IGSharp_IsKeyDown(int key)                          { return ImGui::IsKeyDown((ImGuiKey)key); }
bool IGSharp_IsKeyPressed(int key, bool repeat)          { return ImGui::IsKeyPressed((ImGuiKey)key, repeat); }
bool IGSharp_IsKeyReleased(int key)                      { return ImGui::IsKeyReleased((ImGuiKey)key); }
bool IGSharp_IsKeyChordPressed(int key_chord)            { return ImGui::IsKeyChordPressed((ImGuiKeyChord)key_chord); }
bool IGSharp_IsMouseDown(int button)                     { return ImGui::IsMouseDown(button); }
bool IGSharp_IsMouseClicked(int button, bool repeat)     { return ImGui::IsMouseClicked(button, repeat); }
bool IGSharp_IsMouseReleased(int button)                 { return ImGui::IsMouseReleased(button); }
bool IGSharp_IsMouseDoubleClicked(int button)            { return ImGui::IsMouseDoubleClicked(button); }

bool IGSharp_IsMouseHoveringRect(IGSharp_Vec2 r_min, IGSharp_Vec2 r_max, bool clip)
{ return ImGui::IsMouseHoveringRect(ToImVec2(r_min), ToImVec2(r_max), clip); }

bool IGSharp_IsMousePosValid(const IGSharp_Vec2* mouse_pos)
{
    if (mouse_pos == nullptr) return ImGui::IsMousePosValid();
    ImVec2 tmp = ToImVec2(*mouse_pos);
    return ImGui::IsMousePosValid(&tmp);
}

IGSharp_Vec2 IGSharp_GetMousePos(void)                   { return FromImVec2(ImGui::GetMousePos()); }
bool IGSharp_IsMouseDragging(int button, float lock_threshold)
{ return ImGui::IsMouseDragging(button, lock_threshold); }
IGSharp_Vec2 IGSharp_GetMouseDragDelta(int button, float lock_threshold)
{ return FromImVec2(ImGui::GetMouseDragDelta(button, lock_threshold)); }

// --- Viewport ---

void* IGSharp_GetMainViewport(void)                      { return ImGui::GetMainViewport(); }
IGSharp_Vec2 IGSharp_Viewport_GetPos(void* viewport)     { return FromImVec2(((ImGuiViewport*)viewport)->Pos); }
IGSharp_Vec2 IGSharp_Viewport_GetSize(void* viewport)    { return FromImVec2(((ImGuiViewport*)viewport)->Size); }
IGSharp_Vec2 IGSharp_Viewport_GetWorkPos(void* viewport) { return FromImVec2(((ImGuiViewport*)viewport)->WorkPos); }
IGSharp_Vec2 IGSharp_Viewport_GetWorkSize(void* viewport){ return FromImVec2(((ImGuiViewport*)viewport)->WorkSize); }

// --- DrawList: Accessors ---

void* IGSharp_GetWindowDrawList(void)                    { return ImGui::GetWindowDrawList(); }
void* IGSharp_GetBackgroundDrawList(void)                { return ImGui::GetBackgroundDrawList(); }
void* IGSharp_GetForegroundDrawList(void)                { return ImGui::GetForegroundDrawList(); }

// --- DrawList: Clipping ---

static inline ImDrawList* DL(void* p) { return (ImDrawList*)p; }

void IGSharp_DrawList_PushClipRect(void* dl, IGSharp_Vec2 r_min, IGSharp_Vec2 r_max, bool intersect_with_current)
{ DL(dl)->PushClipRect(ToImVec2(r_min), ToImVec2(r_max), intersect_with_current); }
void IGSharp_DrawList_PushClipRectFullScreen(void* dl)   { DL(dl)->PushClipRectFullScreen(); }
void IGSharp_DrawList_PopClipRect(void* dl)              { DL(dl)->PopClipRect(); }

// --- DrawList: Primitives ---

void IGSharp_DrawList_AddLine(void* dl, IGSharp_Vec2 p1, IGSharp_Vec2 p2, unsigned int col, float thickness)
{ DL(dl)->AddLine(ToImVec2(p1), ToImVec2(p2), col, thickness); }

void IGSharp_DrawList_AddRect(void* dl, IGSharp_Vec2 p_min, IGSharp_Vec2 p_max, unsigned int col, float rounding, int flags, float thickness)
{ DL(dl)->AddRect(ToImVec2(p_min), ToImVec2(p_max), col, rounding, flags, thickness); }

void IGSharp_DrawList_AddRectFilled(void* dl, IGSharp_Vec2 p_min, IGSharp_Vec2 p_max, unsigned int col, float rounding, int flags)
{ DL(dl)->AddRectFilled(ToImVec2(p_min), ToImVec2(p_max), col, rounding, flags); }

void IGSharp_DrawList_AddRectFilledMultiColor(void* dl, IGSharp_Vec2 p_min, IGSharp_Vec2 p_max, unsigned int col_ul, unsigned int col_ur, unsigned int col_br, unsigned int col_bl)
{ DL(dl)->AddRectFilledMultiColor(ToImVec2(p_min), ToImVec2(p_max), col_ul, col_ur, col_br, col_bl); }

void IGSharp_DrawList_AddQuad(void* dl, IGSharp_Vec2 p1, IGSharp_Vec2 p2, IGSharp_Vec2 p3, IGSharp_Vec2 p4, unsigned int col, float thickness)
{ DL(dl)->AddQuad(ToImVec2(p1), ToImVec2(p2), ToImVec2(p3), ToImVec2(p4), col, thickness); }

void IGSharp_DrawList_AddQuadFilled(void* dl, IGSharp_Vec2 p1, IGSharp_Vec2 p2, IGSharp_Vec2 p3, IGSharp_Vec2 p4, unsigned int col)
{ DL(dl)->AddQuadFilled(ToImVec2(p1), ToImVec2(p2), ToImVec2(p3), ToImVec2(p4), col); }

void IGSharp_DrawList_AddTriangle(void* dl, IGSharp_Vec2 p1, IGSharp_Vec2 p2, IGSharp_Vec2 p3, unsigned int col, float thickness)
{ DL(dl)->AddTriangle(ToImVec2(p1), ToImVec2(p2), ToImVec2(p3), col, thickness); }

void IGSharp_DrawList_AddTriangleFilled(void* dl, IGSharp_Vec2 p1, IGSharp_Vec2 p2, IGSharp_Vec2 p3, unsigned int col)
{ DL(dl)->AddTriangleFilled(ToImVec2(p1), ToImVec2(p2), ToImVec2(p3), col); }

void IGSharp_DrawList_AddCircle(void* dl, IGSharp_Vec2 center, float radius, unsigned int col, int num_segments, float thickness)
{ DL(dl)->AddCircle(ToImVec2(center), radius, col, num_segments, thickness); }

void IGSharp_DrawList_AddCircleFilled(void* dl, IGSharp_Vec2 center, float radius, unsigned int col, int num_segments)
{ DL(dl)->AddCircleFilled(ToImVec2(center), radius, col, num_segments); }

void IGSharp_DrawList_AddNgon(void* dl, IGSharp_Vec2 center, float radius, unsigned int col, int num_segments, float thickness)
{ DL(dl)->AddNgon(ToImVec2(center), radius, col, num_segments, thickness); }

void IGSharp_DrawList_AddNgonFilled(void* dl, IGSharp_Vec2 center, float radius, unsigned int col, int num_segments)
{ DL(dl)->AddNgonFilled(ToImVec2(center), radius, col, num_segments); }

void IGSharp_DrawList_AddEllipse(void* dl, IGSharp_Vec2 center, IGSharp_Vec2 radius, unsigned int col, float rot, int num_segments, float thickness)
{ DL(dl)->AddEllipse(ToImVec2(center), ToImVec2(radius), col, rot, num_segments, thickness); }

void IGSharp_DrawList_AddEllipseFilled(void* dl, IGSharp_Vec2 center, IGSharp_Vec2 radius, unsigned int col, float rot, int num_segments)
{ DL(dl)->AddEllipseFilled(ToImVec2(center), ToImVec2(radius), col, rot, num_segments); }

void IGSharp_DrawList_AddText(void* dl, IGSharp_Vec2 pos, unsigned int col, const char* text_begin, const char* text_end)
{ DL(dl)->AddText(ToImVec2(pos), col, text_begin, text_end); }

void IGSharp_DrawList_AddBezierCubic(void* dl, IGSharp_Vec2 p1, IGSharp_Vec2 p2, IGSharp_Vec2 p3, IGSharp_Vec2 p4, unsigned int col, float thickness, int num_segments)
{ DL(dl)->AddBezierCubic(ToImVec2(p1), ToImVec2(p2), ToImVec2(p3), ToImVec2(p4), col, thickness, num_segments); }

void IGSharp_DrawList_AddBezierQuadratic(void* dl, IGSharp_Vec2 p1, IGSharp_Vec2 p2, IGSharp_Vec2 p3, unsigned int col, float thickness, int num_segments)
{ DL(dl)->AddBezierQuadratic(ToImVec2(p1), ToImVec2(p2), ToImVec2(p3), col, thickness, num_segments); }

void IGSharp_DrawList_AddPolyline(void* dl, const IGSharp_Vec2* points, int num_points, unsigned int col, int flags, float thickness)
{ DL(dl)->AddPolyline((const ImVec2*)points, num_points, col, flags, thickness); }

void IGSharp_DrawList_AddConvexPolyFilled(void* dl, const IGSharp_Vec2* points, int num_points, unsigned int col)
{ DL(dl)->AddConvexPolyFilled((const ImVec2*)points, num_points, col); }

void IGSharp_DrawList_AddConcavePolyFilled(void* dl, const IGSharp_Vec2* points, int num_points, unsigned int col)
{ DL(dl)->AddConcavePolyFilled((const ImVec2*)points, num_points, col); }

// --- DrawList: Images ---

void IGSharp_DrawList_AddImage(void* dl, unsigned long long tex_id, IGSharp_Vec2 p_min, IGSharp_Vec2 p_max, IGSharp_Vec2 uv_min, IGSharp_Vec2 uv_max, unsigned int col)
{ DL(dl)->AddImage((ImTextureID)tex_id, ToImVec2(p_min), ToImVec2(p_max), ToImVec2(uv_min), ToImVec2(uv_max), col); }

void IGSharp_DrawList_AddImageQuad(void* dl, unsigned long long tex_id, IGSharp_Vec2 p1, IGSharp_Vec2 p2, IGSharp_Vec2 p3, IGSharp_Vec2 p4, IGSharp_Vec2 uv1, IGSharp_Vec2 uv2, IGSharp_Vec2 uv3, IGSharp_Vec2 uv4, unsigned int col)
{ DL(dl)->AddImageQuad((ImTextureID)tex_id, ToImVec2(p1), ToImVec2(p2), ToImVec2(p3), ToImVec2(p4), ToImVec2(uv1), ToImVec2(uv2), ToImVec2(uv3), ToImVec2(uv4), col); }

void IGSharp_DrawList_AddImageRounded(void* dl, unsigned long long tex_id, IGSharp_Vec2 p_min, IGSharp_Vec2 p_max, IGSharp_Vec2 uv_min, IGSharp_Vec2 uv_max, unsigned int col, float rounding, int flags)
{ DL(dl)->AddImageRounded((ImTextureID)tex_id, ToImVec2(p_min), ToImVec2(p_max), ToImVec2(uv_min), ToImVec2(uv_max), col, rounding, flags); }

// --- DrawList: Path API ---

void IGSharp_DrawList_PathClear(void* dl)                          { DL(dl)->PathClear(); }
void IGSharp_DrawList_PathLineTo(void* dl, IGSharp_Vec2 pos)       { DL(dl)->PathLineTo(ToImVec2(pos)); }
void IGSharp_DrawList_PathLineToMergeDuplicate(void* dl, IGSharp_Vec2 pos)
{ DL(dl)->PathLineToMergeDuplicate(ToImVec2(pos)); }
void IGSharp_DrawList_PathFillConvex(void* dl, unsigned int col)   { DL(dl)->PathFillConvex(col); }
void IGSharp_DrawList_PathStroke(void* dl, unsigned int col, int flags, float thickness)
{ DL(dl)->PathStroke(col, flags, thickness); }

void IGSharp_DrawList_PathArcTo(void* dl, IGSharp_Vec2 center, float radius, float a_min, float a_max, int num_segments)
{ DL(dl)->PathArcTo(ToImVec2(center), radius, a_min, a_max, num_segments); }

void IGSharp_DrawList_PathArcToFast(void* dl, IGSharp_Vec2 center, float radius, int a_min_of_12, int a_max_of_12)
{ DL(dl)->PathArcToFast(ToImVec2(center), radius, a_min_of_12, a_max_of_12); }

void IGSharp_DrawList_PathBezierCubicCurveTo(void* dl, IGSharp_Vec2 p2, IGSharp_Vec2 p3, IGSharp_Vec2 p4, int num_segments)
{ DL(dl)->PathBezierCubicCurveTo(ToImVec2(p2), ToImVec2(p3), ToImVec2(p4), num_segments); }

void IGSharp_DrawList_PathBezierQuadraticCurveTo(void* dl, IGSharp_Vec2 p2, IGSharp_Vec2 p3, int num_segments)
{ DL(dl)->PathBezierQuadraticCurveTo(ToImVec2(p2), ToImVec2(p3), num_segments); }

void IGSharp_DrawList_PathRect(void* dl, IGSharp_Vec2 rect_min, IGSharp_Vec2 rect_max, float rounding, int flags)
{ DL(dl)->PathRect(ToImVec2(rect_min), ToImVec2(rect_max), rounding, flags); }

// --- InputText with callback ---

bool IGSharp_InputTextEx(const char* label, char* buf, size_t buf_size, int flags, IGSharp_InputTextCallback callback, void* user_data)
{ return ImGui::InputText(label, buf, buf_size, flags, (ImGuiInputTextCallback)callback, user_data); }

bool IGSharp_InputTextMultilineEx(const char* label, char* buf, size_t buf_size, IGSharp_Vec2 size, int flags, IGSharp_InputTextCallback callback, void* user_data)
{ return ImGui::InputTextMultiline(label, buf, buf_size, ToImVec2(size), flags, (ImGuiInputTextCallback)callback, user_data); }

bool IGSharp_InputTextWithHintEx(const char* label, const char* hint, char* buf, size_t buf_size, int flags, IGSharp_InputTextCallback callback, void* user_data)
{ return ImGui::InputTextWithHint(label, hint, buf, buf_size, flags, (ImGuiInputTextCallback)callback, user_data); }

// --- InputTextCallbackData: Field Accessors ---

#define CBD(p) ((ImGuiInputTextCallbackData*)(p))

int            IGSharp_InputTextCallbackData_GetEventFlag(void* d)         { return CBD(d)->EventFlag; }
int            IGSharp_InputTextCallbackData_GetFlags(void* d)             { return CBD(d)->Flags; }
void*          IGSharp_InputTextCallbackData_GetUserData(void* d)          { return CBD(d)->UserData; }
int            IGSharp_InputTextCallbackData_GetEventKey(void* d)          { return CBD(d)->EventKey; }
unsigned short IGSharp_InputTextCallbackData_GetEventChar(void* d)         { return (unsigned short)CBD(d)->EventChar; }
void           IGSharp_InputTextCallbackData_SetEventChar(void* d, unsigned short c) { CBD(d)->EventChar = (ImWchar)c; }
bool           IGSharp_InputTextCallbackData_GetEventActivated(void* d)    { return CBD(d)->EventActivated; }
char*          IGSharp_InputTextCallbackData_GetBuf(void* d)               { return CBD(d)->Buf; }
int            IGSharp_InputTextCallbackData_GetBufTextLen(void* d)        { return CBD(d)->BufTextLen; }
void           IGSharp_InputTextCallbackData_SetBufTextLen(void* d, int v) { CBD(d)->BufTextLen = v; }
int            IGSharp_InputTextCallbackData_GetBufSize(void* d)           { return CBD(d)->BufSize; }
bool           IGSharp_InputTextCallbackData_GetBufDirty(void* d)          { return CBD(d)->BufDirty; }
void           IGSharp_InputTextCallbackData_SetBufDirty(void* d, bool v)  { CBD(d)->BufDirty = v; }
int            IGSharp_InputTextCallbackData_GetCursorPos(void* d)         { return CBD(d)->CursorPos; }
void           IGSharp_InputTextCallbackData_SetCursorPos(void* d, int v)  { CBD(d)->CursorPos = v; }
int            IGSharp_InputTextCallbackData_GetSelectionStart(void* d)    { return CBD(d)->SelectionStart; }
void           IGSharp_InputTextCallbackData_SetSelectionStart(void* d, int v) { CBD(d)->SelectionStart = v; }
int            IGSharp_InputTextCallbackData_GetSelectionEnd(void* d)      { return CBD(d)->SelectionEnd; }
void           IGSharp_InputTextCallbackData_SetSelectionEnd(void* d, int v)   { CBD(d)->SelectionEnd = v; }

// --- InputTextCallbackData: Helper Methods ---

void IGSharp_InputTextCallbackData_DeleteChars(void* d, int pos, int bytes_count) { CBD(d)->DeleteChars(pos, bytes_count); }
void IGSharp_InputTextCallbackData_InsertChars(void* d, int pos, const char* text, const char* text_end) { CBD(d)->InsertChars(pos, text, text_end); }
void IGSharp_InputTextCallbackData_SelectAll(void* d)        { CBD(d)->SelectAll(); }
void IGSharp_InputTextCallbackData_ClearSelection(void* d)   { CBD(d)->ClearSelection(); }
bool IGSharp_InputTextCallbackData_HasSelection(void* d)     { return CBD(d)->HasSelection(); }

#undef CBD

// --- Plot Widgets ---

void IGSharp_PlotLines(const char* label, const float* values, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, IGSharp_Vec2 graph_size, int stride)
{ ImGui::PlotLines(label, values, values_count, values_offset, overlay_text, scale_min, scale_max, ToImVec2(graph_size), stride); }

void IGSharp_PlotLinesCallback(const char* label, IGSharp_PlotValuesGetter values_getter, void* data, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, IGSharp_Vec2 graph_size)
{ ImGui::PlotLines(label, values_getter, data, values_count, values_offset, overlay_text, scale_min, scale_max, ToImVec2(graph_size)); }

void IGSharp_PlotHistogram(const char* label, const float* values, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, IGSharp_Vec2 graph_size, int stride)
{ ImGui::PlotHistogram(label, values, values_count, values_offset, overlay_text, scale_min, scale_max, ToImVec2(graph_size), stride); }

void IGSharp_PlotHistogramCallback(const char* label, IGSharp_PlotValuesGetter values_getter, void* data, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, IGSharp_Vec2 graph_size)
{ ImGui::PlotHistogram(label, values_getter, data, values_count, values_offset, overlay_text, scale_min, scale_max, ToImVec2(graph_size)); }

// --- Fonts: Atlas Loading ---

void* IGSharp_IO_GetFonts(void)                 { return ImGui::GetIO().Fonts; }

void* IGSharp_FontAtlas_AddFontDefault(void* atlas)
{ return ((ImFontAtlas*)atlas)->AddFontDefault(); }

void* IGSharp_FontAtlas_AddFontFromFileTTF(void* atlas, const char* filename, float size_pixels)
{ return ((ImFontAtlas*)atlas)->AddFontFromFileTTF(filename, size_pixels); }

void* IGSharp_FontAtlas_AddFontFromMemoryTTF(void* atlas, void* font_data, int font_data_size, float size_pixels, bool transfer_ownership)
{
    ImFontConfig cfg;
    cfg.FontDataOwnedByAtlas = transfer_ownership;
    return ((ImFontAtlas*)atlas)->AddFontFromMemoryTTF(font_data, font_data_size, size_pixels, &cfg);
}

void* IGSharp_FontAtlas_AddFontFromMemoryCompressedTTF(void* atlas, const void* compressed_data, int compressed_size, float size_pixels)
{ return ((ImFontAtlas*)atlas)->AddFontFromMemoryCompressedTTF(compressed_data, compressed_size, size_pixels); }

bool IGSharp_FontAtlas_Build(void* atlas)       { return ((ImFontAtlas*)atlas)->Build(); }
void IGSharp_FontAtlas_Clear(void* atlas)       { ((ImFontAtlas*)atlas)->Clear(); }
void IGSharp_FontAtlas_ClearFonts(void* atlas)  { ((ImFontAtlas*)atlas)->ClearFonts(); }
int  IGSharp_FontAtlas_GetFontCount(void* atlas){ return ((ImFontAtlas*)atlas)->Fonts.Size; }
void* IGSharp_FontAtlas_GetFont(void* atlas, int index)
{
    ImFontAtlas* a = (ImFontAtlas*)atlas;
    if (index < 0 || index >= a->Fonts.Size) return nullptr;
    return a->Fonts[index];
}

void IGSharp_IO_SetFontDefault(void* font)      { ImGui::GetIO().FontDefault = (ImFont*)font; }
void* IGSharp_IO_GetFontDefault(void)           { return ImGui::GetIO().FontDefault; }

// --- Fonts: Push/Pop/Query ---

void IGSharp_PushFont(void* font, float font_size_base_unscaled)
{ ImGui::PushFont((ImFont*)font, font_size_base_unscaled); }
void IGSharp_PopFont(void)                      { ImGui::PopFont(); }
void* IGSharp_GetFont(void)                     { return ImGui::GetFont(); }
float IGSharp_GetFontSize(void)                 { return ImGui::GetFontSize(); }

// --- ListClipper ---

void* IGSharp_ListClipper_New(void)             { return new ImGuiListClipper(); }
void IGSharp_ListClipper_Delete(void* clipper)  { delete (ImGuiListClipper*)clipper; }

void IGSharp_ListClipper_Begin(void* clipper, int items_count, float items_height)
{ ((ImGuiListClipper*)clipper)->Begin(items_count, items_height); }

void IGSharp_ListClipper_End(void* clipper)     { ((ImGuiListClipper*)clipper)->End(); }
bool IGSharp_ListClipper_Step(void* clipper)    { return ((ImGuiListClipper*)clipper)->Step(); }

void IGSharp_ListClipper_IncludeItemsByIndex(void* clipper, int item_begin, int item_end)
{ ((ImGuiListClipper*)clipper)->IncludeItemsByIndex(item_begin, item_end); }

void IGSharp_ListClipper_SeekCursorForItem(void* clipper, int item_index)
{ ((ImGuiListClipper*)clipper)->SeekCursorForItem(item_index); }

int IGSharp_ListClipper_GetDisplayStart(void* clipper) { return ((ImGuiListClipper*)clipper)->DisplayStart; }
int IGSharp_ListClipper_GetDisplayEnd(void* clipper)   { return ((ImGuiListClipper*)clipper)->DisplayEnd; }

// --- IO: Field Accessors ---

#define IO() ImGui::GetIO()

IGSharp_Vec2 IGSharp_IO_GetDisplaySize(void)                    { return FromImVec2(IO().DisplaySize); }
void         IGSharp_IO_SetDisplaySize(IGSharp_Vec2 v)          { IO().DisplaySize = ToImVec2(v); }
IGSharp_Vec2 IGSharp_IO_GetDisplayFramebufferScale(void)        { return FromImVec2(IO().DisplayFramebufferScale); }
void         IGSharp_IO_SetDisplayFramebufferScale(IGSharp_Vec2 v) { IO().DisplayFramebufferScale = ToImVec2(v); }
float        IGSharp_IO_GetDeltaTime(void)                      { return IO().DeltaTime; }
void         IGSharp_IO_SetDeltaTime(float v)                   { IO().DeltaTime = v; }
IGSharp_Vec2 IGSharp_IO_GetMousePos(void)                       { return FromImVec2(IO().MousePos); }
IGSharp_Vec2 IGSharp_IO_GetMouseDelta(void)                     { return FromImVec2(IO().MouseDelta); }
float        IGSharp_IO_GetMouseWheel(void)                     { return IO().MouseWheel; }
float        IGSharp_IO_GetMouseWheelH(void)                    { return IO().MouseWheelH; }
bool         IGSharp_IO_GetKeyCtrl(void)                        { return IO().KeyCtrl; }
bool         IGSharp_IO_GetKeyShift(void)                       { return IO().KeyShift; }
bool         IGSharp_IO_GetKeyAlt(void)                         { return IO().KeyAlt; }
bool         IGSharp_IO_GetKeySuper(void)                       { return IO().KeySuper; }
bool         IGSharp_IO_GetWantTextInput(void)                  { return IO().WantTextInput; }
bool         IGSharp_IO_GetWantSetMousePos(void)                { return IO().WantSetMousePos; }
bool         IGSharp_IO_GetWantSaveIniSettings(void)            { return IO().WantSaveIniSettings; }
void         IGSharp_IO_SetWantSaveIniSettings(bool v)          { IO().WantSaveIniSettings = v; }
bool         IGSharp_IO_GetNavActive(void)                      { return IO().NavActive; }
bool         IGSharp_IO_GetNavVisible(void)                     { return IO().NavVisible; }
int          IGSharp_IO_GetMetricsRenderVertices(void)          { return IO().MetricsRenderVertices; }
int          IGSharp_IO_GetMetricsRenderIndices(void)           { return IO().MetricsRenderIndices; }
int          IGSharp_IO_GetMetricsRenderWindows(void)           { return IO().MetricsRenderWindows; }
int          IGSharp_IO_GetMetricsActiveWindows(void)           { return IO().MetricsActiveWindows; }
int          IGSharp_IO_GetBackendFlags(void)                   { return IO().BackendFlags; }
void         IGSharp_IO_SetBackendFlags(int v)                  { IO().BackendFlags = v; }
float        IGSharp_IO_GetMouseDoubleClickTime(void)           { return IO().MouseDoubleClickTime; }
void         IGSharp_IO_SetMouseDoubleClickTime(float v)        { IO().MouseDoubleClickTime = v; }
float        IGSharp_IO_GetMouseDoubleClickMaxDist(void)        { return IO().MouseDoubleClickMaxDist; }
void         IGSharp_IO_SetMouseDoubleClickMaxDist(float v)     { IO().MouseDoubleClickMaxDist = v; }
float        IGSharp_IO_GetMouseDragThreshold(void)             { return IO().MouseDragThreshold; }
void         IGSharp_IO_SetMouseDragThreshold(float v)          { IO().MouseDragThreshold = v; }
float        IGSharp_IO_GetKeyRepeatDelay(void)                 { return IO().KeyRepeatDelay; }
void         IGSharp_IO_SetKeyRepeatDelay(float v)              { IO().KeyRepeatDelay = v; }
float        IGSharp_IO_GetKeyRepeatRate(void)                  { return IO().KeyRepeatRate; }
void         IGSharp_IO_SetKeyRepeatRate(float v)               { IO().KeyRepeatRate = v; }

// --- IO: Event Queue ---

void IGSharp_IO_AddKeyEvent(int key, bool down)                 { IO().AddKeyEvent((ImGuiKey)key, down); }
void IGSharp_IO_AddKeyAnalogEvent(int key, bool down, float v)  { IO().AddKeyAnalogEvent((ImGuiKey)key, down, v); }
void IGSharp_IO_AddMousePosEvent(float x, float y)              { IO().AddMousePosEvent(x, y); }
void IGSharp_IO_AddMouseButtonEvent(int button, bool down)      { IO().AddMouseButtonEvent(button, down); }
void IGSharp_IO_AddMouseWheelEvent(float wx, float wy)          { IO().AddMouseWheelEvent(wx, wy); }
void IGSharp_IO_AddMouseSourceEvent(int source)                 { IO().AddMouseSourceEvent((ImGuiMouseSource)source); }
void IGSharp_IO_AddFocusEvent(bool focused)                     { IO().AddFocusEvent(focused); }
void IGSharp_IO_AddInputCharacter(unsigned int c)               { IO().AddInputCharacter(c); }
void IGSharp_IO_AddInputCharacterUTF16(unsigned short c)        { IO().AddInputCharacterUTF16((ImWchar16)c); }
void IGSharp_IO_AddInputCharactersUTF8(const char* str)         { IO().AddInputCharactersUTF8(str); }
void IGSharp_IO_SetAppAcceptingEvents(bool accepting)           { IO().SetAppAcceptingEvents(accepting); }
void IGSharp_IO_ClearEventsQueue(void)                          { IO().ClearEventsQueue(); }
void IGSharp_IO_ClearInputKeys(void)                            { IO().ClearInputKeys(); }
void IGSharp_IO_ClearInputMouse(void)                           { IO().ClearInputMouse(); }

#undef IO

// --- Style: Scalar Fields ---

#define S() ImGui::GetStyle()

float IGSharp_Style_GetFontSizeBase(void)            { return S().FontSizeBase; }
void  IGSharp_Style_SetFontSizeBase(float v)         { S().FontSizeBase = v; }
float IGSharp_Style_GetFontScaleMain(void)           { return S().FontScaleMain; }
void  IGSharp_Style_SetFontScaleMain(float v)        { S().FontScaleMain = v; }
float IGSharp_Style_GetFontScaleDpi(void)            { return S().FontScaleDpi; }
float IGSharp_Style_GetAlpha(void)                   { return S().Alpha; }
void  IGSharp_Style_SetAlpha(float v)                { S().Alpha = v; }
float IGSharp_Style_GetDisabledAlpha(void)           { return S().DisabledAlpha; }
void  IGSharp_Style_SetDisabledAlpha(float v)        { S().DisabledAlpha = v; }
float IGSharp_Style_GetWindowRounding(void)          { return S().WindowRounding; }
void  IGSharp_Style_SetWindowRounding(float v)       { S().WindowRounding = v; }
float IGSharp_Style_GetWindowBorderSize(void)        { return S().WindowBorderSize; }
void  IGSharp_Style_SetWindowBorderSize(float v)     { S().WindowBorderSize = v; }
float IGSharp_Style_GetChildRounding(void)           { return S().ChildRounding; }
void  IGSharp_Style_SetChildRounding(float v)        { S().ChildRounding = v; }
float IGSharp_Style_GetChildBorderSize(void)         { return S().ChildBorderSize; }
void  IGSharp_Style_SetChildBorderSize(float v)      { S().ChildBorderSize = v; }
float IGSharp_Style_GetPopupRounding(void)           { return S().PopupRounding; }
void  IGSharp_Style_SetPopupRounding(float v)        { S().PopupRounding = v; }
float IGSharp_Style_GetPopupBorderSize(void)         { return S().PopupBorderSize; }
void  IGSharp_Style_SetPopupBorderSize(float v)      { S().PopupBorderSize = v; }
float IGSharp_Style_GetFrameRounding(void)           { return S().FrameRounding; }
void  IGSharp_Style_SetFrameRounding(float v)        { S().FrameRounding = v; }
float IGSharp_Style_GetFrameBorderSize(void)         { return S().FrameBorderSize; }
void  IGSharp_Style_SetFrameBorderSize(float v)      { S().FrameBorderSize = v; }
float IGSharp_Style_GetIndentSpacing(void)           { return S().IndentSpacing; }
void  IGSharp_Style_SetIndentSpacing(float v)        { S().IndentSpacing = v; }
float IGSharp_Style_GetColumnsMinSpacing(void)       { return S().ColumnsMinSpacing; }
void  IGSharp_Style_SetColumnsMinSpacing(float v)    { S().ColumnsMinSpacing = v; }
float IGSharp_Style_GetScrollbarSize(void)           { return S().ScrollbarSize; }
void  IGSharp_Style_SetScrollbarSize(float v)        { S().ScrollbarSize = v; }
float IGSharp_Style_GetScrollbarRounding(void)       { return S().ScrollbarRounding; }
void  IGSharp_Style_SetScrollbarRounding(float v)    { S().ScrollbarRounding = v; }
float IGSharp_Style_GetGrabMinSize(void)             { return S().GrabMinSize; }
void  IGSharp_Style_SetGrabMinSize(float v)          { S().GrabMinSize = v; }
float IGSharp_Style_GetGrabRounding(void)            { return S().GrabRounding; }
void  IGSharp_Style_SetGrabRounding(float v)         { S().GrabRounding = v; }
float IGSharp_Style_GetImageRounding(void)           { return S().ImageRounding; }
void  IGSharp_Style_SetImageRounding(float v)        { S().ImageRounding = v; }
float IGSharp_Style_GetImageBorderSize(void)         { return S().ImageBorderSize; }
void  IGSharp_Style_SetImageBorderSize(float v)      { S().ImageBorderSize = v; }
float IGSharp_Style_GetTabRounding(void)             { return S().TabRounding; }
void  IGSharp_Style_SetTabRounding(float v)          { S().TabRounding = v; }
float IGSharp_Style_GetTabBorderSize(void)           { return S().TabBorderSize; }
void  IGSharp_Style_SetTabBorderSize(float v)        { S().TabBorderSize = v; }
float IGSharp_Style_GetMouseCursorScale(void)        { return S().MouseCursorScale; }
void  IGSharp_Style_SetMouseCursorScale(float v)     { S().MouseCursorScale = v; }
bool  IGSharp_Style_GetAntiAliasedLines(void)        { return S().AntiAliasedLines; }
void  IGSharp_Style_SetAntiAliasedLines(bool v)      { S().AntiAliasedLines = v; }
bool  IGSharp_Style_GetAntiAliasedFill(void)         { return S().AntiAliasedFill; }
void  IGSharp_Style_SetAntiAliasedFill(bool v)       { S().AntiAliasedFill = v; }
float IGSharp_Style_GetCurveTessellationTol(void)    { return S().CurveTessellationTol; }
void  IGSharp_Style_SetCurveTessellationTol(float v) { S().CurveTessellationTol = v; }
float IGSharp_Style_GetCircleTessellationMaxError(void)    { return S().CircleTessellationMaxError; }
void  IGSharp_Style_SetCircleTessellationMaxError(float v) { S().CircleTessellationMaxError = v; }

// --- Style: Vec2 Fields ---

IGSharp_Vec2 IGSharp_Style_GetWindowPadding(void)             { return FromImVec2(S().WindowPadding); }
void         IGSharp_Style_SetWindowPadding(IGSharp_Vec2 v)   { S().WindowPadding = ToImVec2(v); }
IGSharp_Vec2 IGSharp_Style_GetWindowMinSize(void)             { return FromImVec2(S().WindowMinSize); }
void         IGSharp_Style_SetWindowMinSize(IGSharp_Vec2 v)   { S().WindowMinSize = ToImVec2(v); }
IGSharp_Vec2 IGSharp_Style_GetWindowTitleAlign(void)          { return FromImVec2(S().WindowTitleAlign); }
void         IGSharp_Style_SetWindowTitleAlign(IGSharp_Vec2 v){ S().WindowTitleAlign = ToImVec2(v); }
IGSharp_Vec2 IGSharp_Style_GetFramePadding(void)              { return FromImVec2(S().FramePadding); }
void         IGSharp_Style_SetFramePadding(IGSharp_Vec2 v)    { S().FramePadding = ToImVec2(v); }
IGSharp_Vec2 IGSharp_Style_GetItemSpacing(void)               { return FromImVec2(S().ItemSpacing); }
void         IGSharp_Style_SetItemSpacing(IGSharp_Vec2 v)     { S().ItemSpacing = ToImVec2(v); }
IGSharp_Vec2 IGSharp_Style_GetItemInnerSpacing(void)          { return FromImVec2(S().ItemInnerSpacing); }
void         IGSharp_Style_SetItemInnerSpacing(IGSharp_Vec2 v){ S().ItemInnerSpacing = ToImVec2(v); }
IGSharp_Vec2 IGSharp_Style_GetCellPadding(void)               { return FromImVec2(S().CellPadding); }
void         IGSharp_Style_SetCellPadding(IGSharp_Vec2 v)     { S().CellPadding = ToImVec2(v); }
IGSharp_Vec2 IGSharp_Style_GetTouchExtraPadding(void)         { return FromImVec2(S().TouchExtraPadding); }
void         IGSharp_Style_SetTouchExtraPadding(IGSharp_Vec2 v)   { S().TouchExtraPadding = ToImVec2(v); }
IGSharp_Vec2 IGSharp_Style_GetButtonTextAlign(void)           { return FromImVec2(S().ButtonTextAlign); }
void         IGSharp_Style_SetButtonTextAlign(IGSharp_Vec2 v) { S().ButtonTextAlign = ToImVec2(v); }
IGSharp_Vec2 IGSharp_Style_GetSelectableTextAlign(void)       { return FromImVec2(S().SelectableTextAlign); }
void         IGSharp_Style_SetSelectableTextAlign(IGSharp_Vec2 v) { S().SelectableTextAlign = ToImVec2(v); }
IGSharp_Vec2 IGSharp_Style_GetSeparatorTextAlign(void)        { return FromImVec2(S().SeparatorTextAlign); }
void         IGSharp_Style_SetSeparatorTextAlign(IGSharp_Vec2 v)  { S().SeparatorTextAlign = ToImVec2(v); }
IGSharp_Vec2 IGSharp_Style_GetSeparatorTextPadding(void)      { return FromImVec2(S().SeparatorTextPadding); }
void         IGSharp_Style_SetSeparatorTextPadding(IGSharp_Vec2 v){ S().SeparatorTextPadding = ToImVec2(v); }
IGSharp_Vec2 IGSharp_Style_GetDisplayWindowPadding(void)      { return FromImVec2(S().DisplayWindowPadding); }
void         IGSharp_Style_SetDisplayWindowPadding(IGSharp_Vec2 v){ S().DisplayWindowPadding = ToImVec2(v); }
IGSharp_Vec2 IGSharp_Style_GetDisplaySafeAreaPadding(void)    { return FromImVec2(S().DisplaySafeAreaPadding); }
void         IGSharp_Style_SetDisplaySafeAreaPadding(IGSharp_Vec2 v) { S().DisplaySafeAreaPadding = ToImVec2(v); }

// --- Style: Colors ---

IGSharp_Vec4 IGSharp_Style_GetColor(int idx)
{
    if (idx < 0 || idx >= ImGuiCol_COUNT) return { 0, 0, 0, 0 };
    ImVec4 c = S().Colors[idx];
    return { c.x, c.y, c.z, c.w };
}

void IGSharp_Style_SetColor(int idx, IGSharp_Vec4 col)
{
    if (idx < 0 || idx >= ImGuiCol_COUNT) return;
    S().Colors[idx] = ToImVec4(col);
}

#undef S
