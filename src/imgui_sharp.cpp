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

// --- Fonts (minimal) ---

void* IGSharp_IO_GetFonts(void)                 { return ImGui::GetIO().Fonts; }
void* IGSharp_FontAtlas_AddFontDefault(void* atlas)
{ return ((ImFontAtlas*)atlas)->AddFontDefault(); }
bool IGSharp_FontAtlas_Build(void* atlas)       { return ((ImFontAtlas*)atlas)->Build(); }
