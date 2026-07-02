#include "imgui_sharp.h"
#include "imgui.h"

// Helper: cast between our Vec2/Vec4 and ImGui's (layout-compatible)
static inline ImVec2 ToImVec2(IGSharp_Vec2 v) { return ImVec2(v.x, v.y); }
static inline ImVec4 ToImVec4(IGSharp_Vec4 v) { return ImVec4(v.x, v.y, v.z, v.w); }
static inline IGSharp_Vec2 FromImVec2(ImVec2 v) { return { v.x, v.y }; }

// Helper: build an ImTextureRef from an opaque ImTextureData* (preserves the
// deferred ImTextureID resolution). NULL yields an invalid ref.
static inline ImTextureRef ToTexRef(void* tex_data)
{ return tex_data ? reinterpret_cast<ImTextureData*>(tex_data)->GetTexRef() : ImTextureRef(); }


// --- Cast helpers (hoisted so definitions below can be reordered freely) ---
static inline ImDrawList* DL(void* p) { return (ImDrawList*)p; }
static inline ImGuiIO* AsIO(IGSharp_IO* io) { return reinterpret_cast<ImGuiIO*>(io); }
static inline ImDrawData* DD(void* p) { return (ImDrawData*)p; }
static inline ImDrawCmd* DC(void* p) { return (ImDrawCmd*)p; }
static inline ImDrawListSplitter* DLS(void* p) { return (ImDrawListSplitter*)p; }
static inline ImTextureData* TD(void* p) { return (ImTextureData*)p; }
static inline ImFontConfig* FC(void* p) { return (ImFontConfig*)p; }
static inline ImFont* FONT(void* p) { return (ImFont*)p; }
static inline ImGuiPlatformIO* PIO(IGSharp_PlatformIO* p) { return reinterpret_cast<ImGuiPlatformIO*>(p); }
static inline const ImGuiPayload* PL(void* p) { return (const ImGuiPayload*)(p); }
static inline ImGuiMultiSelectIO* MS(void* p) { return (ImGuiMultiSelectIO*)(p); }
static inline ImGuiSelectionRequest* SR(void* p) { return (ImGuiSelectionRequest*)(p); }
static inline ImGuiTableSortSpecs* TSS(void* p) { return (ImGuiTableSortSpecs*)(p); }
static inline const ImGuiTableColumnSortSpecs* TCS(void* p) { return (const ImGuiTableColumnSortSpecs*)(p); }
static inline ImGuiInputTextCallbackData* CBD(void* p) { return (ImGuiInputTextCallbackData*)(p); }
static inline ImGuiSizeCallbackData* SCBD(void* p) { return (ImGuiSizeCallbackData*)(p); }
static inline ImGuiSelectionBasicStorage* SBS(void* p) { return (ImGuiSelectionBasicStorage*)(p); }
static inline ImGuiSelectionExternalStorage* SES(void* p) { return (ImGuiSelectionExternalStorage*)(p); }

//-----------------------------------------------------------------------------
// [SECTION] Header mess
//-----------------------------------------------------------------------------

void IGSharp_CheckVersion(void)
{
    ImGui::DebugCheckVersionAndDataLayout(IMGUI_VERSION, sizeof(ImGuiIO), sizeof(ImGuiStyle),
        sizeof(ImVec2), sizeof(ImVec4), sizeof(ImDrawVert), sizeof(ImDrawIdx));
}

//-----------------------------------------------------------------------------
// [SECTION] Dear ImGui end-user API functions
//-----------------------------------------------------------------------------

// Context creation and access

IGSharp_Context* IGSharp_CreateContext(void* shared_font_atlas) { return reinterpret_cast<IGSharp_Context*>(ImGui::CreateContext((ImFontAtlas*)shared_font_atlas)); }
void             IGSharp_DestroyContext(IGSharp_Context* ctx) { ImGui::DestroyContext(reinterpret_cast<ImGuiContext*>(ctx)); }
IGSharp_Context* IGSharp_GetCurrentContext(void)   { return reinterpret_cast<IGSharp_Context*>(ImGui::GetCurrentContext()); }
void             IGSharp_SetCurrentContext(IGSharp_Context* ctx) { ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx)); }

// Main

IGSharp_IO*    IGSharp_GetIO(void)    { return reinterpret_cast<IGSharp_IO*>(&ImGui::GetIO()); }
IGSharp_Style* IGSharp_GetStyle(void) { return reinterpret_cast<IGSharp_Style*>(&ImGui::GetStyle()); }
IGSharp_PlatformIO* IGSharp_GetPlatformIO(void) { return reinterpret_cast<IGSharp_PlatformIO*>(&ImGui::GetPlatformIO()); }
void          IGSharp_NewFrame(void)            { ImGui::NewFrame(); }
void          IGSharp_EndFrame(void)            { ImGui::EndFrame(); }
void          IGSharp_Render(void)              { ImGui::Render(); }
void*         IGSharp_GetDrawData(void)         { return ImGui::GetDrawData(); }

// Demo, Debug, Information

void IGSharp_ShowDemoWindow(bool* p_open)       { ImGui::ShowDemoWindow(p_open); }
void IGSharp_ShowMetricsWindow(bool* p_open)    { ImGui::ShowMetricsWindow(p_open); }
void IGSharp_ShowDebugLogWindow(bool* p_open)                   { ImGui::ShowDebugLogWindow(p_open); }
void IGSharp_ShowIDStackToolWindow(bool* p_open)                { ImGui::ShowIDStackToolWindow(p_open); }
void IGSharp_ShowAboutWindow(bool* p_open)                      { ImGui::ShowAboutWindow(p_open); }
void IGSharp_ShowStyleEditor(IGSharp_Style* ref)                { ImGui::ShowStyleEditor(reinterpret_cast<ImGuiStyle*>(ref)); }
bool IGSharp_ShowStyleSelector(const char* label)               { return ImGui::ShowStyleSelector(label); }
void IGSharp_ShowFontSelector(const char* label)                { ImGui::ShowFontSelector(label); }
void IGSharp_ShowUserGuide(void)                                { ImGui::ShowUserGuide(); }
const char*   IGSharp_GetVersion(void)          { return ImGui::GetVersion(); }

// Styles

void IGSharp_StyleColorsDark(IGSharp_Style* dst)    { ImGui::StyleColorsDark(reinterpret_cast<ImGuiStyle*>(dst)); }
void IGSharp_StyleColorsLight(IGSharp_Style* dst)   { ImGui::StyleColorsLight(reinterpret_cast<ImGuiStyle*>(dst)); }
void IGSharp_StyleColorsClassic(IGSharp_Style* dst) { ImGui::StyleColorsClassic(reinterpret_cast<ImGuiStyle*>(dst)); }

// Windows

bool IGSharp_Begin(const char* name, bool* p_open, int flags)
{ return ImGui::Begin(name, p_open, flags); }

void IGSharp_End(void) { ImGui::End(); }

// Child Windows

bool IGSharp_BeginChild(const char* str_id, IGSharp_Vec2 size, int child_flags, int window_flags)
{ return ImGui::BeginChild(str_id, ToImVec2(size), child_flags, window_flags); }

bool IGSharp_BeginChildID(unsigned int id, IGSharp_Vec2 size, int child_flags, int window_flags)
{ return ImGui::BeginChild((ImGuiID)id, ToImVec2(size), child_flags, window_flags); }

void IGSharp_EndChild(void) { ImGui::EndChild(); }

// Windows Utilities

bool IGSharp_IsWindowAppearing(void)            { return ImGui::IsWindowAppearing(); }
bool IGSharp_IsWindowCollapsed(void)            { return ImGui::IsWindowCollapsed(); }
bool IGSharp_IsWindowFocused(int flags)         { return ImGui::IsWindowFocused(flags); }
bool IGSharp_IsWindowHovered(int flags)         { return ImGui::IsWindowHovered(flags); }
void* IGSharp_GetWindowDrawList(void)                    { return ImGui::GetWindowDrawList(); }
IGSharp_Vec2 IGSharp_GetWindowPos(void)         { return FromImVec2(ImGui::GetWindowPos()); }
IGSharp_Vec2 IGSharp_GetWindowSize(void)        { return FromImVec2(ImGui::GetWindowSize()); }
float IGSharp_GetWindowWidth(void)              { return ImGui::GetWindowWidth(); }
float IGSharp_GetWindowHeight(void)             { return ImGui::GetWindowHeight(); }

// Window manipulation

void IGSharp_SetNextWindowPos(IGSharp_Vec2 pos, int cond, IGSharp_Vec2 pivot)
{ ImGui::SetNextWindowPos(ToImVec2(pos), cond, ToImVec2(pivot)); }

void IGSharp_SetNextWindowSize(IGSharp_Vec2 size, int cond)
{ ImGui::SetNextWindowSize(ToImVec2(size), cond); }

void IGSharp_SetNextWindowSizeConstraints(IGSharp_Vec2 size_min, IGSharp_Vec2 size_max, IGSharp_SizeCallback custom_callback, void* custom_callback_data)
{ ImGui::SetNextWindowSizeConstraints(ToImVec2(size_min), ToImVec2(size_max), reinterpret_cast<ImGuiSizeCallback>(custom_callback), custom_callback_data); }

void IGSharp_SetNextWindowContentSize(IGSharp_Vec2 size)        { ImGui::SetNextWindowContentSize(ToImVec2(size)); }

void IGSharp_SetNextWindowCollapsed(bool collapsed, int cond)
{ ImGui::SetNextWindowCollapsed(collapsed, cond); }

void  IGSharp_SetNextWindowFocus(void)          { ImGui::SetNextWindowFocus(); }
void IGSharp_SetNextWindowScroll(IGSharp_Vec2 scroll)           { ImGui::SetNextWindowScroll(ToImVec2(scroll)); }
void  IGSharp_SetNextWindowBgAlpha(float alpha)  { ImGui::SetNextWindowBgAlpha(alpha); }
void IGSharp_SetWindowPos(IGSharp_Vec2 pos, int cond)            { ImGui::SetWindowPos(ToImVec2(pos), cond); }
void IGSharp_SetWindowSize(IGSharp_Vec2 size, int cond)          { ImGui::SetWindowSize(ToImVec2(size), cond); }
void IGSharp_SetWindowCollapsed(bool collapsed, int cond)        { ImGui::SetWindowCollapsed(collapsed, cond); }
void IGSharp_SetWindowFocus(void)                                { ImGui::SetWindowFocus(); }
void IGSharp_SetWindowPosNamed(const char* name, IGSharp_Vec2 pos, int cond)   { ImGui::SetWindowPos(name, ToImVec2(pos), cond); }
void IGSharp_SetWindowSizeNamed(const char* name, IGSharp_Vec2 size, int cond) { ImGui::SetWindowSize(name, ToImVec2(size), cond); }
void IGSharp_SetWindowCollapsedNamed(const char* name, bool collapsed, int cond) { ImGui::SetWindowCollapsed(name, collapsed, cond); }
void IGSharp_SetWindowFocusNamed(const char* name)              { ImGui::SetWindowFocus(name); }

// Windows Scrolling

float IGSharp_GetScrollX(void)                                  { return ImGui::GetScrollX(); }
float IGSharp_GetScrollY(void)                                  { return ImGui::GetScrollY(); }
void  IGSharp_SetScrollX(float scroll_x)                        { ImGui::SetScrollX(scroll_x); }
void  IGSharp_SetScrollY(float scroll_y)                        { ImGui::SetScrollY(scroll_y); }
float IGSharp_GetScrollMaxX(void)                               { return ImGui::GetScrollMaxX(); }
float IGSharp_GetScrollMaxY(void)                               { return ImGui::GetScrollMaxY(); }
void  IGSharp_SetScrollHereX(float center_x_ratio)              { ImGui::SetScrollHereX(center_x_ratio); }
void  IGSharp_SetScrollHereY(float center_y_ratio)              { ImGui::SetScrollHereY(center_y_ratio); }
void  IGSharp_SetScrollFromPosX(float local_x, float ratio)     { ImGui::SetScrollFromPosX(local_x, ratio); }
void  IGSharp_SetScrollFromPosY(float local_y, float ratio)     { ImGui::SetScrollFromPosY(local_y, ratio); }

// Parameters stacks (font)

void IGSharp_PushFont(void* font, float font_size_base_unscaled)
{ ImGui::PushFont((ImFont*)font, font_size_base_unscaled); }

void IGSharp_PopFont(void)                      { ImGui::PopFont(); }
void* IGSharp_GetFont(void)                     { return ImGui::GetFont(); }
float IGSharp_GetFontSize(void)                 { return ImGui::GetFontSize(); }
void* IGSharp_GetFontBaked(void)                { return (void*)ImGui::GetFontBaked(); }

// Parameters stacks (shared)

void IGSharp_PushStyleColorU32(int idx, unsigned int col)
{ ImGui::PushStyleColor(idx, (ImU32)col); }

void IGSharp_PushStyleColorVec4(int idx, IGSharp_Vec4 col)
{ ImGui::PushStyleColor(idx, ToImVec4(col)); }

void  IGSharp_PopStyleColor(int count)          { ImGui::PopStyleColor(count); }

void IGSharp_PushStyleVarFloat(int idx, float val)
{ ImGui::PushStyleVar(idx, val); }

void IGSharp_PushStyleVarVec2(int idx, IGSharp_Vec2 val)
{ ImGui::PushStyleVar(idx, ToImVec2(val)); }

void IGSharp_PushStyleVarX(int idx, float val_x) { ImGui::PushStyleVarX(idx, val_x); }
void IGSharp_PushStyleVarY(int idx, float val_y) { ImGui::PushStyleVarY(idx, val_y); }
void  IGSharp_PopStyleVar(int count)            { ImGui::PopStyleVar(count); }
void IGSharp_PushItemFlag(int option, bool enabled)             { ImGui::PushItemFlag((ImGuiItemFlags)option, enabled); }
void IGSharp_PopItemFlag(void)                                  { ImGui::PopItemFlag(); }

// Parameters stacks (current window)

void  IGSharp_PushItemWidth(float w)            { ImGui::PushItemWidth(w); }
void  IGSharp_PopItemWidth(void)                { ImGui::PopItemWidth(); }
void  IGSharp_SetNextItemWidth(float w)         { ImGui::SetNextItemWidth(w); }
float IGSharp_CalcItemWidth(void)               { return ImGui::CalcItemWidth(); }
void  IGSharp_PushTextWrapPos(float pos)        { ImGui::PushTextWrapPos(pos); }
void  IGSharp_PopTextWrapPos(void)              { ImGui::PopTextWrapPos(); }

// Style read access

IGSharp_Vec2 IGSharp_GetFontTexUvWhitePixel(void) { return FromImVec2(ImGui::GetFontTexUvWhitePixel()); }
unsigned int IGSharp_GetColorU32(int idx, float alpha_mul)        { return ImGui::GetColorU32((ImGuiCol)idx, alpha_mul); }
unsigned int IGSharp_GetColorU32Vec4(IGSharp_Vec4 col)            { return ImGui::GetColorU32(ToImVec4(col)); }
unsigned int IGSharp_GetColorU32Packed(unsigned int col, float a) { return ImGui::GetColorU32((ImU32)col, a); }

IGSharp_Vec4 IGSharp_GetStyleColorVec4(int idx)
{
    const ImVec4& v = ImGui::GetStyleColorVec4(idx);
    return { v.x, v.y, v.z, v.w };
}

// Layout cursor positioning

IGSharp_Vec2 IGSharp_GetCursorScreenPos(void)   { return FromImVec2(ImGui::GetCursorScreenPos()); }
void IGSharp_SetCursorScreenPos(IGSharp_Vec2 p) { ImGui::SetCursorScreenPos(ToImVec2(p)); }
IGSharp_Vec2 IGSharp_GetContentRegionAvail(void){ return FromImVec2(ImGui::GetContentRegionAvail()); }
IGSharp_Vec2 IGSharp_GetCursorPos(void)         { return FromImVec2(ImGui::GetCursorPos()); }
float IGSharp_GetCursorPosX(void)               { return ImGui::GetCursorPosX(); }
float IGSharp_GetCursorPosY(void)               { return ImGui::GetCursorPosY(); }
void IGSharp_SetCursorPos(IGSharp_Vec2 p)       { ImGui::SetCursorPos(ToImVec2(p)); }
void  IGSharp_SetCursorPosX(float local_x)      { ImGui::SetCursorPosX(local_x); }
void  IGSharp_SetCursorPosY(float local_y)      { ImGui::SetCursorPosY(local_y); }
IGSharp_Vec2 IGSharp_GetCursorStartPos(void)    { return FromImVec2(ImGui::GetCursorStartPos()); }

// Other layout functions

void IGSharp_Separator(void)                    { ImGui::Separator(); }
void IGSharp_SameLine(float offset, float spacing) { ImGui::SameLine(offset, spacing); }
void IGSharp_NewLine(void)                      { ImGui::NewLine(); }
void IGSharp_Spacing(void)                      { ImGui::Spacing(); }
void IGSharp_Dummy(IGSharp_Vec2 size)           { ImGui::Dummy(ToImVec2(size)); }
void IGSharp_Indent(float indent_w)             { ImGui::Indent(indent_w); }
void IGSharp_Unindent(float indent_w)           { ImGui::Unindent(indent_w); }
void IGSharp_BeginGroup(void)                   { ImGui::BeginGroup(); }
void IGSharp_EndGroup(void)                     { ImGui::EndGroup(); }
void  IGSharp_AlignTextToFramePadding(void)     { ImGui::AlignTextToFramePadding(); }
float IGSharp_GetTextLineHeight(void)           { return ImGui::GetTextLineHeight(); }
float IGSharp_GetTextLineHeightWithSpacing(void){ return ImGui::GetTextLineHeightWithSpacing(); }
float IGSharp_GetFrameHeight(void)              { return ImGui::GetFrameHeight(); }
float IGSharp_GetFrameHeightWithSpacing(void)   { return ImGui::GetFrameHeightWithSpacing(); }

// ID stack/scopes

void IGSharp_PushIDStr(const char* str_id)      { ImGui::PushID(str_id); }
void IGSharp_PushIDStrRange(const char* str_id_begin, const char* str_id_end) { ImGui::PushID(str_id_begin, str_id_end); }
void IGSharp_PushIDPtr(const void* ptr_id)      { ImGui::PushID(ptr_id); }
void IGSharp_PushIDInt(int int_id)              { ImGui::PushID(int_id); }
void IGSharp_PopID(void)                        { ImGui::PopID(); }
unsigned int IGSharp_GetIDStr(const char* str_id){ return ImGui::GetID(str_id); }
unsigned int IGSharp_GetIDStrRange(const char* str_id_begin, const char* str_id_end) { return ImGui::GetID(str_id_begin, str_id_end); }
unsigned int IGSharp_GetIDPtr(const void* ptr_id) { return ImGui::GetID(ptr_id); }
unsigned int IGSharp_GetIDInt(int int_id)       { return ImGui::GetID(int_id); }

// Widgets: Text

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

// Widgets: Main

bool IGSharp_Button(const char* label, IGSharp_Vec2 size)
{ return ImGui::Button(label, ToImVec2(size)); }

bool IGSharp_SmallButton(const char* label)     { return ImGui::SmallButton(label); }

bool IGSharp_InvisibleButton(const char* str_id, IGSharp_Vec2 size, int flags)
{ return ImGui::InvisibleButton(str_id, ToImVec2(size), flags); }

bool IGSharp_ArrowButton(const char* str_id, int dir)
{ return ImGui::ArrowButton(str_id, (ImGuiDir)dir); }

bool IGSharp_Checkbox(const char* label, bool* v)
{ return ImGui::Checkbox(label, v); }

bool IGSharp_CheckboxFlags(const char* label, int* flags, int flags_value)
{ return ImGui::CheckboxFlags(label, flags, flags_value); }

bool IGSharp_CheckboxFlagsUInt(const char* label, unsigned int* flags, unsigned int flags_value)
{ return ImGui::CheckboxFlags(label, flags, flags_value); }

bool IGSharp_RadioButton(const char* label, bool active)
{ return ImGui::RadioButton(label, active); }

bool IGSharp_RadioButtonInt(const char* label, int* v, int v_button)
{ return ImGui::RadioButton(label, v, v_button); }

void IGSharp_ProgressBar(float fraction, IGSharp_Vec2 size_arg, const char* overlay)
{ ImGui::ProgressBar(fraction, ToImVec2(size_arg), overlay); }

void IGSharp_Bullet(void)                       { ImGui::Bullet(); }
bool IGSharp_TextLink(const char* label)        { return ImGui::TextLink(label); }

bool IGSharp_TextLinkOpenURL(const char* label, const char* url)
{ return ImGui::TextLinkOpenURL(label, url); }

// Widgets: Images

void IGSharp_Image(unsigned long long tex_id, IGSharp_Vec2 image_size, IGSharp_Vec2 uv0, IGSharp_Vec2 uv1)
{ ImGui::Image((ImTextureID)tex_id, ToImVec2(image_size), ToImVec2(uv0), ToImVec2(uv1)); }

void IGSharp_ImageWithBg(unsigned long long tex_id, IGSharp_Vec2 image_size, IGSharp_Vec2 uv0, IGSharp_Vec2 uv1, IGSharp_Vec4 bg_col, IGSharp_Vec4 tint_col)
{ ImGui::ImageWithBg((ImTextureID)tex_id, ToImVec2(image_size), ToImVec2(uv0), ToImVec2(uv1), ToImVec4(bg_col), ToImVec4(tint_col)); }

bool IGSharp_ImageButton(const char* str_id, unsigned long long tex_id, IGSharp_Vec2 image_size, IGSharp_Vec2 uv0, IGSharp_Vec2 uv1, IGSharp_Vec4 bg_col, IGSharp_Vec4 tint_col)
{ return ImGui::ImageButton(str_id, (ImTextureID)tex_id, ToImVec2(image_size), ToImVec2(uv0), ToImVec2(uv1), ToImVec4(bg_col), ToImVec4(tint_col)); }

// ImTextureData* variants: bind an atlas/backend texture (e.g. from IGSharp_FontAtlas_GetTexData)

void IGSharp_ImageTextureData(void* tex_data, IGSharp_Vec2 image_size, IGSharp_Vec2 uv0, IGSharp_Vec2 uv1)
{ ImGui::Image(ToTexRef(tex_data), ToImVec2(image_size), ToImVec2(uv0), ToImVec2(uv1)); }

void IGSharp_ImageWithBgTextureData(void* tex_data, IGSharp_Vec2 image_size, IGSharp_Vec2 uv0, IGSharp_Vec2 uv1, IGSharp_Vec4 bg_col, IGSharp_Vec4 tint_col)
{ ImGui::ImageWithBg(ToTexRef(tex_data), ToImVec2(image_size), ToImVec2(uv0), ToImVec2(uv1), ToImVec4(bg_col), ToImVec4(tint_col)); }

bool IGSharp_ImageButtonTextureData(const char* str_id, void* tex_data, IGSharp_Vec2 image_size, IGSharp_Vec2 uv0, IGSharp_Vec2 uv1, IGSharp_Vec4 bg_col, IGSharp_Vec4 tint_col)
{ return ImGui::ImageButton(str_id, ToTexRef(tex_data), ToImVec2(image_size), ToImVec2(uv0), ToImVec2(uv1), ToImVec4(bg_col), ToImVec4(tint_col)); }

// Widgets: Combo Box (Dropdown)

bool IGSharp_BeginCombo(const char* label, const char* preview_value, int flags)
{ return ImGui::BeginCombo(label, preview_value, flags); }

void IGSharp_EndCombo(void) { ImGui::EndCombo(); }

bool IGSharp_Combo(const char* label, int* current_item, const char* const items[], int items_count, int popup_max_height_in_items)
{ return ImGui::Combo(label, current_item, items, items_count, popup_max_height_in_items); }

bool IGSharp_ComboStr(const char* label, int* current_item, const char* items_separated_by_zeros, int popup_max_height_in_items)
{ return ImGui::Combo(label, current_item, items_separated_by_zeros, popup_max_height_in_items); }

bool IGSharp_ComboCallback(const char* label, int* current_item, const char* (*getter)(void* user_data, int idx), void* user_data, int items_count, int popup_max_height_in_items)
{ return ImGui::Combo(label, current_item, getter, user_data, items_count, popup_max_height_in_items); }

// Widgets: Drag Sliders

bool IGSharp_DragFloat(const char* label, float* v, float v_speed, float v_min, float v_max, const char* format, int flags)
{ return ImGui::DragFloat(label, v, v_speed, v_min, v_max, format, flags); }

bool IGSharp_DragFloat2(const char* label, float v[2], float v_speed, float v_min, float v_max, const char* format, int flags)
{ return ImGui::DragFloat2(label, v, v_speed, v_min, v_max, format, flags); }

bool IGSharp_DragFloat3(const char* label, float v[3], float v_speed, float v_min, float v_max, const char* format, int flags)
{ return ImGui::DragFloat3(label, v, v_speed, v_min, v_max, format, flags); }

bool IGSharp_DragFloat4(const char* label, float v[4], float v_speed, float v_min, float v_max, const char* format, int flags)
{ return ImGui::DragFloat4(label, v, v_speed, v_min, v_max, format, flags); }

bool IGSharp_DragFloatRange2(const char* label, float* v_current_min, float* v_current_max, float v_speed, float v_min, float v_max, const char* format, const char* format_max, int flags)
{ return ImGui::DragFloatRange2(label, v_current_min, v_current_max, v_speed, v_min, v_max, format, format_max, flags); }

bool IGSharp_DragInt(const char* label, int* v, float v_speed, int v_min, int v_max, const char* format, int flags)
{ return ImGui::DragInt(label, v, v_speed, v_min, v_max, format, flags); }

bool IGSharp_DragInt2(const char* label, int v[2], float v_speed, int v_min, int v_max, const char* format, int flags)
{ return ImGui::DragInt2(label, v, v_speed, v_min, v_max, format, flags); }

bool IGSharp_DragInt3(const char* label, int v[3], float v_speed, int v_min, int v_max, const char* format, int flags)
{ return ImGui::DragInt3(label, v, v_speed, v_min, v_max, format, flags); }

bool IGSharp_DragInt4(const char* label, int v[4], float v_speed, int v_min, int v_max, const char* format, int flags)
{ return ImGui::DragInt4(label, v, v_speed, v_min, v_max, format, flags); }

bool IGSharp_DragIntRange2(const char* label, int* v_current_min, int* v_current_max, float v_speed, int v_min, int v_max, const char* format, const char* format_max, int flags)
{ return ImGui::DragIntRange2(label, v_current_min, v_current_max, v_speed, v_min, v_max, format, format_max, flags); }

bool IGSharp_DragScalar(const char* label, int data_type, void* p_data, float v_speed, const void* p_min, const void* p_max, const char* format, int flags)
{ return ImGui::DragScalar(label, (ImGuiDataType)data_type, p_data, v_speed, p_min, p_max, format, flags); }

bool IGSharp_DragScalarN(const char* label, int data_type, void* p_data, int components, float v_speed, const void* p_min, const void* p_max, const char* format, int flags)
{ return ImGui::DragScalarN(label, (ImGuiDataType)data_type, p_data, components, v_speed, p_min, p_max, format, flags); }

// Widgets: Regular Sliders

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

bool IGSharp_SliderScalar(const char* label, int data_type, void* p_data, const void* p_min, const void* p_max, const char* format, int flags)
{ return ImGui::SliderScalar(label, (ImGuiDataType)data_type, p_data, p_min, p_max, format, flags); }

bool IGSharp_SliderScalarN(const char* label, int data_type, void* p_data, int components, const void* p_min, const void* p_max, const char* format, int flags)
{ return ImGui::SliderScalarN(label, (ImGuiDataType)data_type, p_data, components, p_min, p_max, format, flags); }

bool IGSharp_VSliderFloat(const char* label, IGSharp_Vec2 size, float* v, float v_min, float v_max, const char* format, int flags)
{ return ImGui::VSliderFloat(label, ToImVec2(size), v, v_min, v_max, format, flags); }

bool IGSharp_VSliderInt(const char* label, IGSharp_Vec2 size, int* v, int v_min, int v_max, const char* format, int flags)
{ return ImGui::VSliderInt(label, ToImVec2(size), v, v_min, v_max, format, flags); }

bool IGSharp_VSliderScalar(const char* label, IGSharp_Vec2 size, int data_type, void* p_data, const void* p_min, const void* p_max, const char* format, int flags)
{ return ImGui::VSliderScalar(label, ToImVec2(size), (ImGuiDataType)data_type, p_data, p_min, p_max, format, flags); }

// Widgets: Input with Keyboard

bool IGSharp_InputText(const char* label, char* buf, size_t buf_size, int flags)
{ return ImGui::InputText(label, buf, buf_size, flags, nullptr, nullptr); }

bool IGSharp_InputTextMultiline(const char* label, char* buf, size_t buf_size, IGSharp_Vec2 size, int flags)
{ return ImGui::InputTextMultiline(label, buf, buf_size, ToImVec2(size), flags, nullptr, nullptr); }

bool IGSharp_InputTextWithHint(const char* label, const char* hint, char* buf, size_t buf_size, int flags)
{ return ImGui::InputTextWithHint(label, hint, buf, buf_size, flags, nullptr, nullptr); }

bool IGSharp_InputTextEx(const char* label, char* buf, size_t buf_size, int flags, IGSharp_InputTextCallback callback, void* user_data)
{ return ImGui::InputText(label, buf, buf_size, flags, (ImGuiInputTextCallback)callback, user_data); }

bool IGSharp_InputTextMultilineEx(const char* label, char* buf, size_t buf_size, IGSharp_Vec2 size, int flags, IGSharp_InputTextCallback callback, void* user_data)
{ return ImGui::InputTextMultiline(label, buf, buf_size, ToImVec2(size), flags, (ImGuiInputTextCallback)callback, user_data); }

bool IGSharp_InputTextWithHintEx(const char* label, const char* hint, char* buf, size_t buf_size, int flags, IGSharp_InputTextCallback callback, void* user_data)
{ return ImGui::InputTextWithHint(label, hint, buf, buf_size, flags, (ImGuiInputTextCallback)callback, user_data); }

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

bool IGSharp_InputScalar(const char* label, int data_type, void* p_data, const void* p_step, const void* p_step_fast, const char* format, int flags)
{ return ImGui::InputScalar(label, (ImGuiDataType)data_type, p_data, p_step, p_step_fast, format, flags); }

bool IGSharp_InputScalarN(const char* label, int data_type, void* p_data, int components, const void* p_step, const void* p_step_fast, const char* format, int flags)
{ return ImGui::InputScalarN(label, (ImGuiDataType)data_type, p_data, components, p_step, p_step_fast, format, flags); }

// Widgets: Color Editor/Picker (tip: the ColorEdit* functions have a little color square that can be left-clicked to open a picker, and right-clicked to open an option menu.)

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

void IGSharp_SetColorEditOptions(int flags)
{ ImGui::SetColorEditOptions(flags); }

// Widgets: Trees

bool  IGSharp_TreeNode(const char* label)       { return ImGui::TreeNode(label); }

bool IGSharp_TreeNodeStr(const char* str_id, const char* text)
{ return ImGui::TreeNode(str_id, "%s", text); }

bool IGSharp_TreeNodePtr(const void* ptr_id, const char* text)
{ return ImGui::TreeNode(ptr_id, "%s", text); }

bool  IGSharp_TreeNodeEx(const char* label, int flags) { return ImGui::TreeNodeEx(label, flags); }

bool IGSharp_TreeNodeExStr(const char* str_id, int flags, const char* text)
{ return ImGui::TreeNodeEx(str_id, flags, "%s", text); }

bool IGSharp_TreeNodeExPtr(const void* ptr_id, int flags, const char* text)
{ return ImGui::TreeNodeEx(ptr_id, flags, "%s", text); }

void IGSharp_TreePushStr(const char* str_id)   { ImGui::TreePush(str_id); }
void IGSharp_TreePushPtr(const void* ptr_id)   { ImGui::TreePush(ptr_id); }
void  IGSharp_TreePop(void)                     { ImGui::TreePop(); }
float IGSharp_GetTreeNodeToLabelSpacing(void)   { return ImGui::GetTreeNodeToLabelSpacing(); }

bool IGSharp_CollapsingHeader(const char* label, int flags)
{ return ImGui::CollapsingHeader(label, flags); }

bool IGSharp_CollapsingHeaderClosable(const char* label, bool* p_visible, int flags)
{ return ImGui::CollapsingHeader(label, p_visible, flags); }

void IGSharp_SetNextItemOpen(bool is_open, int cond)
{ ImGui::SetNextItemOpen(is_open, cond); }

void IGSharp_SetNextItemStorageID(unsigned int storage_id)
{ ImGui::SetNextItemStorageID((ImGuiID)storage_id); }

bool IGSharp_TreeNodeGetOpen(unsigned int storage_id)
{ return ImGui::TreeNodeGetOpen((ImGuiID)storage_id); }

// Widgets: Selectables

bool IGSharp_Selectable(const char* label, bool selected, int flags, IGSharp_Vec2 size)
{ return ImGui::Selectable(label, selected, flags, ToImVec2(size)); }

bool IGSharp_SelectablePtr(const char* label, bool* p_selected, int flags, IGSharp_Vec2 size)
{ return ImGui::Selectable(label, p_selected, flags, ToImVec2(size)); }

// Multi-selection system for Selectable(), Checkbox(), TreeNode() functions [BETA]

void* IGSharp_BeginMultiSelect(int flags, int selection_size, int items_count)
{ return ImGui::BeginMultiSelect(flags, selection_size, items_count); }

void* IGSharp_EndMultiSelect(void)                           { return ImGui::EndMultiSelect(); }
void  IGSharp_SetNextItemSelectionUserData(long long v)      { ImGui::SetNextItemSelectionUserData((ImGuiSelectionUserData)v); }
bool  IGSharp_IsItemToggledSelection(void)                   { return ImGui::IsItemToggledSelection(); }

// Widgets: List Boxes

bool IGSharp_BeginListBox(const char* label, IGSharp_Vec2 size)
{ return ImGui::BeginListBox(label, ToImVec2(size)); }

void IGSharp_EndListBox(void) { ImGui::EndListBox(); }

bool IGSharp_ListBox(const char* label, int* current_item, const char* const items[], int items_count, int height_in_items)
{ return ImGui::ListBox(label, current_item, items, items_count, height_in_items); }

bool IGSharp_ListBoxCallback(const char* label, int* current_item, const char* (*getter)(void* user_data, int idx), void* user_data, int items_count, int height_in_items)
{ return ImGui::ListBox(label, current_item, getter, user_data, items_count, height_in_items); }

// Widgets: Data Plotting

void IGSharp_PlotLines(const char* label, const float* values, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, IGSharp_Vec2 graph_size, int stride)
{ ImGui::PlotLines(label, values, values_count, values_offset, overlay_text, scale_min, scale_max, ToImVec2(graph_size), stride); }

void IGSharp_PlotLinesCallback(const char* label, float (*values_getter)(void* data, int idx), void* data, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, IGSharp_Vec2 graph_size)
{ ImGui::PlotLines(label, values_getter, data, values_count, values_offset, overlay_text, scale_min, scale_max, ToImVec2(graph_size)); }

void IGSharp_PlotHistogram(const char* label, const float* values, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, IGSharp_Vec2 graph_size, int stride)
{ ImGui::PlotHistogram(label, values, values_count, values_offset, overlay_text, scale_min, scale_max, ToImVec2(graph_size), stride); }

void IGSharp_PlotHistogramCallback(const char* label, float (*values_getter)(void* data, int idx), void* data, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, IGSharp_Vec2 graph_size)
{ ImGui::PlotHistogram(label, values_getter, data, values_count, values_offset, overlay_text, scale_min, scale_max, ToImVec2(graph_size)); }

// Widgets: Value() Helpers. Output single value in "name: value" format

void IGSharp_ValueBool(const char* prefix, bool b)          { ImGui::Value(prefix, b); }
void IGSharp_ValueInt(const char* prefix, int v)            { ImGui::Value(prefix, v); }
void IGSharp_ValueUInt(const char* prefix, unsigned int v)  { ImGui::Value(prefix, v); }

void IGSharp_ValueFloat(const char* prefix, float v, const char* float_format)
{ ImGui::Value(prefix, v, float_format); }

// Widgets: Menus

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

// Tooltips

bool IGSharp_BeginTooltip(void)                 { return ImGui::BeginTooltip(); }
void IGSharp_EndTooltip(void)                   { ImGui::EndTooltip(); }
void IGSharp_SetTooltip(const char* text)       { ImGui::SetTooltip("%s", text); }

// Tooltips: helpers for showing a tooltip when hovering an item

bool IGSharp_BeginItemTooltip(void)             { return ImGui::BeginItemTooltip(); }
void IGSharp_SetItemTooltip(const char* text)   { ImGui::SetItemTooltip("%s", text); }

// Popups, Modals

bool IGSharp_BeginPopup(const char* str_id, int flags)
{ return ImGui::BeginPopup(str_id, flags); }

bool IGSharp_BeginPopupModal(const char* name, bool* p_open, int flags)
{ return ImGui::BeginPopupModal(name, p_open, flags); }

void IGSharp_EndPopup(void)                     { ImGui::EndPopup(); }

// Popups: open/close functions

void IGSharp_OpenPopup(const char* str_id, int popup_flags)
{ ImGui::OpenPopup(str_id, popup_flags); }

void IGSharp_OpenPopupID(unsigned int id, int popup_flags)
{ ImGui::OpenPopup((ImGuiID)id, popup_flags); }

void IGSharp_OpenPopupOnItemClick(const char* str_id, int popup_flags)
{ ImGui::OpenPopupOnItemClick(str_id, popup_flags); }

void IGSharp_CloseCurrentPopup(void)            { ImGui::CloseCurrentPopup(); }

// Popups: Open+Begin popup combined functions helpers to create context menus.

bool IGSharp_BeginPopupContextItem(const char* str_id, int popup_flags)
{ return ImGui::BeginPopupContextItem(str_id, popup_flags); }

bool IGSharp_BeginPopupContextWindow(const char* str_id, int popup_flags)
{ return ImGui::BeginPopupContextWindow(str_id, popup_flags); }

bool IGSharp_BeginPopupContextVoid(const char* str_id, int popup_flags)
{ return ImGui::BeginPopupContextVoid(str_id, popup_flags); }

// Popups: query functions

bool IGSharp_IsPopupOpen(const char* str_id, int flags)
{ return ImGui::IsPopupOpen(str_id, flags); }

// Tables

bool IGSharp_BeginTable(const char* str_id, int columns, int flags, IGSharp_Vec2 outer_size, float inner_width)
{ return ImGui::BeginTable(str_id, columns, flags, ToImVec2(outer_size), inner_width); }

void IGSharp_EndTable(void)                     { ImGui::EndTable(); }
void IGSharp_TableNextRow(int row_flags, float min_row_height) { ImGui::TableNextRow(row_flags, min_row_height); }
bool IGSharp_TableNextColumn(void)              { return ImGui::TableNextColumn(); }
bool IGSharp_TableSetColumnIndex(int column_n)  { return ImGui::TableSetColumnIndex(column_n); }

// Tables: Headers & Columns declaration

void IGSharp_TableSetupColumn(const char* label, int flags, float init_width_or_weight, unsigned int user_id)
{ ImGui::TableSetupColumn(label, flags, init_width_or_weight, user_id); }

void IGSharp_TableSetupScrollFreeze(int cols, int rows) { ImGui::TableSetupScrollFreeze(cols, rows); }
void IGSharp_TableHeader(const char* label)     { ImGui::TableHeader(label); }
void IGSharp_TableHeadersRow(void)              { ImGui::TableHeadersRow(); }
void  IGSharp_TableAngledHeadersRow(void)                       { ImGui::TableAngledHeadersRow(); }

// Tables: Sorting & Miscellaneous functions

void* IGSharp_TableGetSortSpecs(void)                        { return ImGui::TableGetSortSpecs(); }
int         IGSharp_TableGetColumnCount(void)                   { return ImGui::TableGetColumnCount(); }
int         IGSharp_TableGetColumnIndex(void)                   { return ImGui::TableGetColumnIndex(); }
int         IGSharp_TableGetRowIndex(void)                      { return ImGui::TableGetRowIndex(); }
const char* IGSharp_TableGetColumnName(int column_n)            { return ImGui::TableGetColumnName(column_n); }
int         IGSharp_TableGetColumnFlags(int column_n)           { return (int)ImGui::TableGetColumnFlags(column_n); }
void        IGSharp_TableSetColumnEnabled(int column_n, bool v) { ImGui::TableSetColumnEnabled(column_n, v); }
int         IGSharp_TableGetHoveredColumn(void)                 { return ImGui::TableGetHoveredColumn(); }

void IGSharp_TableSetBgColor(int target, unsigned int color, int column_n)
{ ImGui::TableSetBgColor((ImGuiTableBgTarget)target, (ImU32)color, column_n); }

// Legacy Columns API (prefer using Tables!)

void  IGSharp_Columns(int count, const char* id, bool borders)  { ImGui::Columns(count, id, borders); }
void  IGSharp_NextColumn(void)                                  { ImGui::NextColumn(); }
int   IGSharp_GetColumnIndex(void)                              { return ImGui::GetColumnIndex(); }
float IGSharp_GetColumnWidth(int column_index)                  { return ImGui::GetColumnWidth(column_index); }
void  IGSharp_SetColumnWidth(int column_index, float width)     { ImGui::SetColumnWidth(column_index, width); }
float IGSharp_GetColumnOffset(int column_index)                 { return ImGui::GetColumnOffset(column_index); }
void  IGSharp_SetColumnOffset(int column_index, float offset_x) { ImGui::SetColumnOffset(column_index, offset_x); }
int   IGSharp_GetColumnsCount(void)                             { return ImGui::GetColumnsCount(); }

// Tab Bars, Tabs

bool IGSharp_BeginTabBar(const char* str_id, int flags) { return ImGui::BeginTabBar(str_id, flags); }
void IGSharp_EndTabBar(void)                    { ImGui::EndTabBar(); }
bool IGSharp_BeginTabItem(const char* label, bool* p_open, int flags) { return ImGui::BeginTabItem(label, p_open, flags); }
void IGSharp_EndTabItem(void)                   { ImGui::EndTabItem(); }
bool IGSharp_TabItemButton(const char* label, int flags) { return ImGui::TabItemButton(label, flags); }
void IGSharp_SetTabItemClosed(const char* label){ ImGui::SetTabItemClosed(label); }

// Logging/Capture

void IGSharp_LogToTTY(int auto_open_depth)              { ImGui::LogToTTY(auto_open_depth); }

void IGSharp_LogToFile(int auto_open_depth, const char* filename)
{ ImGui::LogToFile(auto_open_depth, filename); }

void IGSharp_LogToClipboard(int auto_open_depth)        { ImGui::LogToClipboard(auto_open_depth); }
void IGSharp_LogFinish(void)                            { ImGui::LogFinish(); }
void IGSharp_LogButtons(void)                           { ImGui::LogButtons(); }
void IGSharp_LogText(const char* text)                  { ImGui::LogText("%s", text); }

// Drag and Drop

bool  IGSharp_BeginDragDropSource(int flags)                 { return ImGui::BeginDragDropSource(flags); }

bool  IGSharp_SetDragDropPayload(const char* type, const void* data, size_t sz, int cond)
{ return ImGui::SetDragDropPayload(type, data, sz, cond); }

void  IGSharp_EndDragDropSource(void)                        { ImGui::EndDragDropSource(); }
bool  IGSharp_BeginDragDropTarget(void)                      { return ImGui::BeginDragDropTarget(); }

void* IGSharp_AcceptDragDropPayload(const char* type, int flags)
{ return (void*)ImGui::AcceptDragDropPayload(type, flags); }

void  IGSharp_EndDragDropTarget(void)                        { ImGui::EndDragDropTarget(); }
void* IGSharp_GetDragDropPayload(void)                       { return (void*)ImGui::GetDragDropPayload(); }

// Disabling [BETA API]

void IGSharp_BeginDisabled(bool disabled)       { ImGui::BeginDisabled(disabled); }
void IGSharp_EndDisabled(void)                  { ImGui::EndDisabled(); }

// Clipping

void IGSharp_PushClipRect(IGSharp_Vec2 clip_rect_min, IGSharp_Vec2 clip_rect_max, bool intersect_with_current_clip_rect)
{ ImGui::PushClipRect(ToImVec2(clip_rect_min), ToImVec2(clip_rect_max), intersect_with_current_clip_rect); }

void IGSharp_PopClipRect(void)
{ ImGui::PopClipRect(); }

// Focus, Activation

void IGSharp_SetItemDefaultFocus(void)          { ImGui::SetItemDefaultFocus(); }
void IGSharp_SetKeyboardFocusHere(int offset)                   { ImGui::SetKeyboardFocusHere(offset); }

// Keyboard/Gamepad Navigation

void IGSharp_SetNavCursorVisible(bool visible)
{ ImGui::SetNavCursorVisible(visible); }

// Overlapping mode

void IGSharp_SetNextItemAllowOverlap(void)                      { ImGui::SetNextItemAllowOverlap(); }

// Item/Widgets Utilities and Query Functions

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
bool         IGSharp_IsAnyItemHovered(void)                     { return ImGui::IsAnyItemHovered(); }
bool         IGSharp_IsAnyItemActive(void)                      { return ImGui::IsAnyItemActive(); }
bool         IGSharp_IsAnyItemFocused(void)                     { return ImGui::IsAnyItemFocused(); }
unsigned int IGSharp_GetItemID(void)                            { return ImGui::GetItemID(); }
IGSharp_Vec2 IGSharp_GetItemRectMin(void)       { return FromImVec2(ImGui::GetItemRectMin()); }
IGSharp_Vec2 IGSharp_GetItemRectMax(void)       { return FromImVec2(ImGui::GetItemRectMax()); }
IGSharp_Vec2 IGSharp_GetItemRectSize(void)      { return FromImVec2(ImGui::GetItemRectSize()); }

int IGSharp_GetItemFlags(void)
{ return (int)ImGui::GetItemFlags(); }

// Viewports

void* IGSharp_GetMainViewport(void)                      { return ImGui::GetMainViewport(); }

// Background/Foreground Draw Lists

void* IGSharp_GetBackgroundDrawList(void)                { return ImGui::GetBackgroundDrawList(); }
void* IGSharp_GetForegroundDrawList(void)                { return ImGui::GetForegroundDrawList(); }

// Miscellaneous Utilities

bool IGSharp_IsRectVisible(IGSharp_Vec2 size)                                { return ImGui::IsRectVisible(ToImVec2(size)); }
bool IGSharp_IsRectVisibleRange(IGSharp_Vec2 rect_min, IGSharp_Vec2 rect_max){ return ImGui::IsRectVisible(ToImVec2(rect_min), ToImVec2(rect_max)); }
double IGSharp_GetTime(void)                                                 { return ImGui::GetTime(); }
int IGSharp_GetFrameCount(void)                                              { return ImGui::GetFrameCount(); }
void* IGSharp_GetDrawListSharedData(void)                                    { return ImGui::GetDrawListSharedData(); }
const char* IGSharp_GetStyleColorName(int idx)                              { return ImGui::GetStyleColorName((ImGuiCol)idx); }
void IGSharp_SetStateStorage(void* storage)                                  { ImGui::SetStateStorage((ImGuiStorage*)storage); }
void* IGSharp_GetStateStorage(void)                                          { return ImGui::GetStateStorage(); }

// Text Utilities

IGSharp_Vec2 IGSharp_CalcTextSize(const char* text, const char* text_end, bool hide_text_after_double_hash, float wrap_width)
{ return FromImVec2(ImGui::CalcTextSize(text, text_end, hide_text_after_double_hash, wrap_width)); }

// Color Utilities

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

// Inputs Utilities: Raw Keyboard/Mouse/Gamepad Access

bool IGSharp_IsKeyDown(int key)                          { return ImGui::IsKeyDown((ImGuiKey)key); }
bool IGSharp_IsKeyPressed(int key, bool repeat)          { return ImGui::IsKeyPressed((ImGuiKey)key, repeat); }
bool IGSharp_IsKeyReleased(int key)                      { return ImGui::IsKeyReleased((ImGuiKey)key); }
bool IGSharp_IsKeyChordPressed(int key_chord)            { return ImGui::IsKeyChordPressed((ImGuiKeyChord)key_chord); }
int IGSharp_GetKeyPressedAmount(int key, float repeat_delay, float rate)  { return ImGui::GetKeyPressedAmount((ImGuiKey)key, repeat_delay, rate); }
const char* IGSharp_GetKeyName(int key)                  { return ImGui::GetKeyName((ImGuiKey)key); }
void IGSharp_SetNextFrameWantCaptureKeyboard(bool want_capture_keyboard) { ImGui::SetNextFrameWantCaptureKeyboard(want_capture_keyboard); }

// Inputs Utilities: Shortcut Testing & Routing

bool IGSharp_Shortcut(int key_chord, int flags)          { return ImGui::Shortcut((ImGuiKeyChord)key_chord, (ImGuiInputFlags)flags); }
void IGSharp_SetNextItemShortcut(int key_chord, int flags) { ImGui::SetNextItemShortcut((ImGuiKeyChord)key_chord, (ImGuiInputFlags)flags); }

// Inputs Utilities: Key/Input Ownership

void IGSharp_SetItemKeyOwner(int key)                    { ImGui::SetItemKeyOwner((ImGuiKey)key); }

// Inputs Utilities: Mouse

bool IGSharp_IsMouseDown(int button)                     { return ImGui::IsMouseDown(button); }
bool IGSharp_IsMouseClicked(int button, bool repeat)     { return ImGui::IsMouseClicked(button, repeat); }
bool IGSharp_IsMouseReleased(int button)                 { return ImGui::IsMouseReleased(button); }
bool IGSharp_IsMouseDoubleClicked(int button)            { return ImGui::IsMouseDoubleClicked(button); }

bool IGSharp_IsMouseReleasedWithDelay(int button, float delay)
{ return ImGui::IsMouseReleasedWithDelay(button, delay); }

int IGSharp_GetMouseClickedCount(int button)             { return ImGui::GetMouseClickedCount(button); }

bool IGSharp_IsMouseHoveringRect(IGSharp_Vec2 r_min, IGSharp_Vec2 r_max, bool clip)
{ return ImGui::IsMouseHoveringRect(ToImVec2(r_min), ToImVec2(r_max), clip); }

bool IGSharp_IsMousePosValid(const IGSharp_Vec2* mouse_pos)
{
    if (mouse_pos == nullptr) return ImGui::IsMousePosValid();
    ImVec2 tmp = ToImVec2(*mouse_pos);
    return ImGui::IsMousePosValid(&tmp);
}

bool IGSharp_IsAnyMouseDown(void)                        { return ImGui::IsAnyMouseDown(); }
IGSharp_Vec2 IGSharp_GetMousePos(void)                   { return FromImVec2(ImGui::GetMousePos()); }

IGSharp_Vec2 IGSharp_GetMousePosOnOpeningCurrentPopup(void)
{ return FromImVec2(ImGui::GetMousePosOnOpeningCurrentPopup()); }

bool IGSharp_IsMouseDragging(int button, float lock_threshold)
{ return ImGui::IsMouseDragging(button, lock_threshold); }

IGSharp_Vec2 IGSharp_GetMouseDragDelta(int button, float lock_threshold)
{ return FromImVec2(ImGui::GetMouseDragDelta(button, lock_threshold)); }

void IGSharp_ResetMouseDragDelta(int button)             { ImGui::ResetMouseDragDelta(button); }
int  IGSharp_GetMouseCursor(void)                               { return (int)ImGui::GetMouseCursor(); }
void IGSharp_SetMouseCursor(int cursor_type)                    { ImGui::SetMouseCursor((ImGuiMouseCursor)cursor_type); }

void IGSharp_SetNextFrameWantCaptureMouse(bool want_capture_mouse)
{ ImGui::SetNextFrameWantCaptureMouse(want_capture_mouse); }

// Clipboard Utilities

const char* IGSharp_GetClipboardText(void)              { return ImGui::GetClipboardText(); }
void        IGSharp_SetClipboardText(const char* text)  { ImGui::SetClipboardText(text); }

// Settings/.Ini Utilities

void        IGSharp_LoadIniSettingsFromDisk(const char* ini_filename)               { ImGui::LoadIniSettingsFromDisk(ini_filename); }
void        IGSharp_LoadIniSettingsFromMemory(const char* ini_data, size_t ini_size) { ImGui::LoadIniSettingsFromMemory(ini_data, ini_size); }
void        IGSharp_SaveIniSettingsToDisk(const char* ini_filename)                 { ImGui::SaveIniSettingsToDisk(ini_filename); }
const char* IGSharp_SaveIniSettingsToMemory(size_t* out_ini_size)                   { return ImGui::SaveIniSettingsToMemory(out_ini_size); }

// Debug Utilities

void IGSharp_DebugTextEncoding(const char* text)    { ImGui::DebugTextEncoding(text); }
void IGSharp_DebugFlashStyleColor(int idx)          { ImGui::DebugFlashStyleColor((ImGuiCol)idx); }
void IGSharp_DebugStartItemPicker(void)             { ImGui::DebugStartItemPicker(); }

bool IGSharp_DebugCheckVersionAndDataLayout(const char* version_str, size_t sz_io, size_t sz_style, size_t sz_vec2, size_t sz_vec4, size_t sz_drawvert, size_t sz_drawidx)
{
    return ImGui::DebugCheckVersionAndDataLayout(version_str, sz_io, sz_style, sz_vec2, sz_vec4, sz_drawvert, sz_drawidx);
}

void IGSharp_DebugLog(const char* text)             { ImGui::DebugLog("%s", text); }

// Memory Allocators (see IGSharp_MemAllocFunc/IGSharp_MemFreeFunc typedefs in the forward declarations section)

void IGSharp_SetAllocatorFunctions(IGSharp_MemAllocFunc alloc_func, IGSharp_MemFreeFunc free_func, void* user_data)
{
    ImGui::SetAllocatorFunctions((ImGuiMemAllocFunc)alloc_func, (ImGuiMemFreeFunc)free_func, user_data);
}

void IGSharp_GetAllocatorFunctions(IGSharp_MemAllocFunc* p_alloc_func, IGSharp_MemFreeFunc* p_free_func, void** p_user_data)
{
    ImGui::GetAllocatorFunctions((ImGuiMemAllocFunc*)p_alloc_func, (ImGuiMemFreeFunc*)p_free_func, p_user_data);
}

void*  IGSharp_MemAlloc(size_t size)                { return ImGui::MemAlloc(size); }
void   IGSharp_MemFree(void* ptr)                   { ImGui::MemFree(ptr); }

//-----------------------------------------------------------------------------
// [SECTION] Tables API flags and structures (ImGuiTableFlags, ImGuiTableColumnFlags, ImGuiTableRowFlags, ImGuiTableBgTarget, ImGuiTableSortSpecs, ImGuiTableColumnSortSpecs)
//-----------------------------------------------------------------------------

// ImGuiTableSortSpecs (opaque; obtain via IGSharp_TableGetSortSpecs())

int   IGSharp_TableSortSpecs_GetSpecsCount(void* s)          { return TSS(s)->SpecsCount; }

void* IGSharp_TableSortSpecs_GetSpec(void* s, int i)
{
    if (!s || i < 0 || i >= TSS(s)->SpecsCount) return nullptr;
    return (void*)&TSS(s)->Specs[i];
}

bool  IGSharp_TableSortSpecs_GetSpecsDirty(void* s)          { return TSS(s)->SpecsDirty; }
void  IGSharp_TableSortSpecs_SetSpecsDirty(void* s, bool v)  { TSS(s)->SpecsDirty = v; }

// ImGuiTableColumnSortSpecs (opaque; obtain via IGSharp_TableSortSpecs_GetSpec())

unsigned int IGSharp_TableColumnSortSpecs_GetColumnUserID(void* c)   { return (unsigned int)TCS(c)->ColumnUserID; }
int          IGSharp_TableColumnSortSpecs_GetColumnIndex(void* c)    { return (int)TCS(c)->ColumnIndex; }
int          IGSharp_TableColumnSortSpecs_GetSortOrder(void* c)      { return (int)TCS(c)->SortOrder; }
int          IGSharp_TableColumnSortSpecs_GetSortDirection(void* c)  { return (int)TCS(c)->SortDirection; }

//-----------------------------------------------------------------------------
// [SECTION] ImGuiStyle
//-----------------------------------------------------------------------------

void IGSharp_Style_ScaleAllSizes(IGSharp_Style* style, float scale)
    { reinterpret_cast<ImGuiStyle*>(style)->ScaleAllSizes(scale); }

//-----------------------------------------------------------------------------
// [SECTION] ImGuiIO
//-----------------------------------------------------------------------------

// Wrap ImGuiIO's C++ member functions; pass the IGSharp_IO* you got from IGSharp_GetIO().

void IGSharp_IO_AddKeyEvent(IGSharp_IO* io, int key, bool down)                 { AsIO(io)->AddKeyEvent((ImGuiKey)key, down); }
void IGSharp_IO_AddKeyAnalogEvent(IGSharp_IO* io, int key, bool down, float v)  { AsIO(io)->AddKeyAnalogEvent((ImGuiKey)key, down, v); }
void IGSharp_IO_AddMousePosEvent(IGSharp_IO* io, float x, float y)              { AsIO(io)->AddMousePosEvent(x, y); }
void IGSharp_IO_AddMouseButtonEvent(IGSharp_IO* io, int button, bool down)      { AsIO(io)->AddMouseButtonEvent(button, down); }
void IGSharp_IO_AddMouseWheelEvent(IGSharp_IO* io, float wx, float wy)          { AsIO(io)->AddMouseWheelEvent(wx, wy); }
void IGSharp_IO_AddMouseSourceEvent(IGSharp_IO* io, int source)                 { AsIO(io)->AddMouseSourceEvent((ImGuiMouseSource)source); }
void IGSharp_IO_AddFocusEvent(IGSharp_IO* io, bool focused)                     { AsIO(io)->AddFocusEvent(focused); }
void IGSharp_IO_AddInputCharacter(IGSharp_IO* io, unsigned int c)               { AsIO(io)->AddInputCharacter(c); }
void IGSharp_IO_AddInputCharacterUTF16(IGSharp_IO* io, unsigned short c)        { AsIO(io)->AddInputCharacterUTF16((ImWchar16)c); }
void IGSharp_IO_AddInputCharactersUTF8(IGSharp_IO* io, const char* str)         { AsIO(io)->AddInputCharactersUTF8(str); }
void IGSharp_IO_SetKeyEventNativeData(IGSharp_IO* io, int key, int native_keycode, int native_scancode, int native_legacy_index) { AsIO(io)->SetKeyEventNativeData((ImGuiKey)key, native_keycode, native_scancode, native_legacy_index); }
void IGSharp_IO_SetAppAcceptingEvents(IGSharp_IO* io, bool accepting)           { AsIO(io)->SetAppAcceptingEvents(accepting); }
void IGSharp_IO_ClearEventsQueue(IGSharp_IO* io)                                { AsIO(io)->ClearEventsQueue(); }
void IGSharp_IO_ClearInputKeys(IGSharp_IO* io)                                  { AsIO(io)->ClearInputKeys(); }
void IGSharp_IO_ClearInputMouse(IGSharp_IO* io)                                 { AsIO(io)->ClearInputMouse(); }

//-----------------------------------------------------------------------------
// [SECTION] Misc data structures (ImGuiInputTextCallbackData, ImGuiSizeCallbackData, ImGuiPayload)
//-----------------------------------------------------------------------------

// ImGuiInputTextCallbackData: Field Accessors

void*          IGSharp_InputTextCallbackData_GetCtx(void* d)              { return (void*)CBD(d)->Ctx; }
int            IGSharp_InputTextCallbackData_GetEventFlag(void* d)         { return CBD(d)->EventFlag; }
int            IGSharp_InputTextCallbackData_GetFlags(void* d)             { return CBD(d)->Flags; }
void*          IGSharp_InputTextCallbackData_GetUserData(void* d)          { return CBD(d)->UserData; }
unsigned int   IGSharp_InputTextCallbackData_GetID(void* d)               { return (unsigned int)((ImGuiInputTextCallbackData*)d)->ID; }
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

// ImGuiInputTextCallbackData: Helper Methods

void IGSharp_InputTextCallbackData_DeleteChars(void* d, int pos, int bytes_count) { CBD(d)->DeleteChars(pos, bytes_count); }
void IGSharp_InputTextCallbackData_InsertChars(void* d, int pos, const char* text, const char* text_end) { CBD(d)->InsertChars(pos, text, text_end); }
void IGSharp_InputTextCallbackData_SelectAll(void* d)        { CBD(d)->SelectAll(); }
void IGSharp_InputTextCallbackData_SetSelection(void* d, int s, int e) { ((ImGuiInputTextCallbackData*)d)->SetSelection(s, e); }
void IGSharp_InputTextCallbackData_ClearSelection(void* d)   { CBD(d)->ClearSelection(); }
bool IGSharp_InputTextCallbackData_HasSelection(void* d)     { return CBD(d)->HasSelection(); }

// ImGuiInputTextCallbackData: Resize Helpers

void IGSharp_InputTextCallbackData_SetBuf(void* d, char* buf)
{ ((ImGuiInputTextCallbackData*)d)->Buf = buf; }

void IGSharp_InputTextCallbackData_SetBufSize(void* d, int size)
{ ((ImGuiInputTextCallbackData*)d)->BufSize = size; }

void IGSharp_InputTextCallbackData_ResizeBuf(void* d, char* new_buf, int new_buf_size)
{
    ImGuiInputTextCallbackData* data = (ImGuiInputTextCallbackData*)d;
    data->Buf = new_buf;
    data->BufSize = new_buf_size;
    data->BufDirty = true;
}

// ImGuiSizeCallbackData accessors

void*        IGSharp_SizeCallbackData_GetUserData(void* d)      { return SCBD(d)->UserData; }
IGSharp_Vec2 IGSharp_SizeCallbackData_GetPos(void* d)          { return FromImVec2(SCBD(d)->Pos); }
IGSharp_Vec2 IGSharp_SizeCallbackData_GetCurrentSize(void* d)  { return FromImVec2(SCBD(d)->CurrentSize); }
IGSharp_Vec2 IGSharp_SizeCallbackData_GetDesiredSize(void* d)  { return FromImVec2(SCBD(d)->DesiredSize); }
void         IGSharp_SizeCallbackData_SetDesiredSize(void* d, IGSharp_Vec2 v) { SCBD(d)->DesiredSize = ToImVec2(v); }

// ImGuiPayload accessors

void*       IGSharp_Payload_GetData(void* p)                 { return p ? PL(p)->Data : nullptr; }
int         IGSharp_Payload_GetDataSize(void* p)             { return p ? PL(p)->DataSize : 0; }
const char* IGSharp_Payload_GetDataType(void* p)             { return p ? PL(p)->DataType : nullptr; }
bool        IGSharp_Payload_IsDataType(void* p, const char* type) { return p ? PL(p)->IsDataType(type) : false; }
bool        IGSharp_Payload_IsPreview(void* p)               { return p ? PL(p)->IsPreview() : false; }
bool        IGSharp_Payload_IsDelivery(void* p)              { return p ? PL(p)->IsDelivery() : false; }

//-----------------------------------------------------------------------------
// [SECTION] Helpers (ImGuiOnceUponAFrame, ImGuiTextFilter, ImGuiTextBuffer, ImGuiStorage, ImGuiListClipper, Math Operators, ImColor)
//-----------------------------------------------------------------------------

// ImGuiOnceUponAFrame

void* IGSharp_OnceUponAFrame_New(void)          { return new ImGuiOnceUponAFrame(); }
void IGSharp_OnceUponAFrame_Delete(void* oaf)   { delete (ImGuiOnceUponAFrame*)oaf; }
bool IGSharp_OnceUponAFrame_Check(void* oaf)    { return (bool)*((ImGuiOnceUponAFrame*)oaf); }
int IGSharp_OnceUponAFrame_GetRefFrame(void* oaf) { return ((ImGuiOnceUponAFrame*)oaf)->RefFrame; }

IGSharp_TextFilter* IGSharp_TextFilter_New(const char* default_filter)
{ return reinterpret_cast<IGSharp_TextFilter*>(IM_NEW(ImGuiTextFilter)(default_filter)); }

void IGSharp_TextFilter_Delete(IGSharp_TextFilter* filter)
{ IM_DELETE(reinterpret_cast<ImGuiTextFilter*>(filter)); }

bool IGSharp_TextFilter_Draw(IGSharp_TextFilter* filter, const char* label, float width)
{ return reinterpret_cast<ImGuiTextFilter*>(filter)->Draw(label, width); }

bool IGSharp_TextFilter_PassFilter(IGSharp_TextFilter* filter, const char* text, const char* text_end)
{ return reinterpret_cast<ImGuiTextFilter*>(filter)->PassFilter(text, text_end); }

void IGSharp_TextFilter_Build(IGSharp_TextFilter* filter)
{ reinterpret_cast<ImGuiTextFilter*>(filter)->Build(); }

void IGSharp_TextFilter_Clear(IGSharp_TextFilter* filter)
{ reinterpret_cast<ImGuiTextFilter*>(filter)->Clear(); }

bool IGSharp_TextFilter_IsActive(IGSharp_TextFilter* filter)
{ return reinterpret_cast<ImGuiTextFilter*>(filter)->IsActive(); }

// ImGuiTextBuffer (~string builder over ImVector<char>). Opaque handle.

void* IGSharp_TextBuffer_New(void)              { return new ImGuiTextBuffer(); }
void IGSharp_TextBuffer_Delete(void* buf)       { delete (ImGuiTextBuffer*)buf; }
const char* IGSharp_TextBuffer_CStr(void* buf)  { return ((ImGuiTextBuffer*)buf)->c_str(); }
int IGSharp_TextBuffer_Size(void* buf)          { return ((ImGuiTextBuffer*)buf)->size(); }
bool IGSharp_TextBuffer_Empty(void* buf)        { return ((ImGuiTextBuffer*)buf)->empty(); }
void IGSharp_TextBuffer_Clear(void* buf)        { ((ImGuiTextBuffer*)buf)->clear(); }
void IGSharp_TextBuffer_Resize(void* buf, int size)         { ((ImGuiTextBuffer*)buf)->resize(size); }
void IGSharp_TextBuffer_Reserve(void* buf, int capacity)    { ((ImGuiTextBuffer*)buf)->reserve(capacity); }

void IGSharp_TextBuffer_Append(void* buf, const char* str, const char* str_end)
{ ((ImGuiTextBuffer*)buf)->append(str, str_end); }

// ImGuiStorage (opaque handle; sorted key->value container, ref-returning methods)

void* IGSharp_Storage_New(void)                 { return new ImGuiStorage(); }
void IGSharp_Storage_Delete(void* storage)      { delete (ImGuiStorage*)storage; }
void IGSharp_Storage_Clear(void* storage)       { ((ImGuiStorage*)storage)->Clear(); }

int IGSharp_Storage_GetInt(void* storage, unsigned int key, int default_val)
{ return ((ImGuiStorage*)storage)->GetInt(key, default_val); }

void IGSharp_Storage_SetInt(void* storage, unsigned int key, int val)
{ ((ImGuiStorage*)storage)->SetInt(key, val); }

bool IGSharp_Storage_GetBool(void* storage, unsigned int key, bool default_val)
{ return ((ImGuiStorage*)storage)->GetBool(key, default_val); }

void IGSharp_Storage_SetBool(void* storage, unsigned int key, bool val)
{ ((ImGuiStorage*)storage)->SetBool(key, val); }

float IGSharp_Storage_GetFloat(void* storage, unsigned int key, float default_val)
{ return ((ImGuiStorage*)storage)->GetFloat(key, default_val); }

void IGSharp_Storage_SetFloat(void* storage, unsigned int key, float val)
{ ((ImGuiStorage*)storage)->SetFloat(key, val); }

void* IGSharp_Storage_GetVoidPtr(void* storage, unsigned int key)
{ return ((ImGuiStorage*)storage)->GetVoidPtr(key); }

void IGSharp_Storage_SetVoidPtr(void* storage, unsigned int key, void* val)
{ ((ImGuiStorage*)storage)->SetVoidPtr(key, val); }

int* IGSharp_Storage_GetIntRef(void* storage, unsigned int key, int default_val)
{ return ((ImGuiStorage*)storage)->GetIntRef(key, default_val); }

bool* IGSharp_Storage_GetBoolRef(void* storage, unsigned int key, bool default_val)
{ return ((ImGuiStorage*)storage)->GetBoolRef(key, default_val); }

float* IGSharp_Storage_GetFloatRef(void* storage, unsigned int key, float default_val)
{ return ((ImGuiStorage*)storage)->GetFloatRef(key, default_val); }

void** IGSharp_Storage_GetVoidPtrRef(void* storage, unsigned int key, void* default_val)
{ return ((ImGuiStorage*)storage)->GetVoidPtrRef(key, default_val); }

void IGSharp_Storage_BuildSortByKey(void* storage)  { ((ImGuiStorage*)storage)->BuildSortByKey(); }
void IGSharp_Storage_SetAllInt(void* storage, int val) { ((ImGuiStorage*)storage)->SetAllInt(val); }

// ImGuiListClipper

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
int IGSharp_ListClipper_GetUserIndex(void* clipper) { return ((ImGuiListClipper*)clipper)->UserIndex; }
void IGSharp_ListClipper_SetUserIndex(void* clipper, int user_index) { ((ImGuiListClipper*)clipper)->UserIndex = user_index; }

//-----------------------------------------------------------------------------
// [SECTION] Multi-Select API flags and structures (ImGuiMultiSelectFlags, ImGuiSelectionRequestType, ImGuiSelectionRequest, ImGuiMultiSelectIO, ImGuiSelectionBasicStorage)
//-----------------------------------------------------------------------------

// ImGuiMultiSelectIO accessors

int       IGSharp_MultiSelectIO_GetRequestsCount(void* io)   { return MS(io)->Requests.Size; }

void*     IGSharp_MultiSelectIO_GetRequest(void* io, int i)
{
    if (!io || i < 0 || i >= MS(io)->Requests.Size) return nullptr;
    return &MS(io)->Requests[i];
}

long long IGSharp_MultiSelectIO_GetRangeSrcItem(void* io)    { return (long long)MS(io)->RangeSrcItem; }
long long IGSharp_MultiSelectIO_GetNavIdItem(void* io)       { return (long long)MS(io)->NavIdItem; }
bool      IGSharp_MultiSelectIO_GetNavIdSelected(void* io)   { return MS(io)->NavIdSelected; }
bool      IGSharp_MultiSelectIO_GetRangeSrcReset(void* io)   { return MS(io)->RangeSrcReset; }
void      IGSharp_MultiSelectIO_SetRangeSrcReset(void* io, bool v) { MS(io)->RangeSrcReset = v; }
int       IGSharp_MultiSelectIO_GetItemsCount(void* io)      { return MS(io)->ItemsCount; }

// ImGuiSelectionRequest accessors

int       IGSharp_SelectionRequest_GetType(void* r)              { return SR(r)->Type; }
bool      IGSharp_SelectionRequest_GetSelected(void* r)          { return SR(r)->Selected; }
int       IGSharp_SelectionRequest_GetRangeDirection(void* r)    { return SR(r)->RangeDirection; }
long long IGSharp_SelectionRequest_GetRangeFirstItem(void* r)    { return (long long)SR(r)->RangeFirstItem; }
long long IGSharp_SelectionRequest_GetRangeLastItem(void* r)     { return (long long)SR(r)->RangeLastItem; }

// ImGuiSelectionBasicStorage (opaque handle + accessors)

void*        IGSharp_SelectionBasicStorage_Create(void)                  { return new ImGuiSelectionBasicStorage(); }
void         IGSharp_SelectionBasicStorage_Destroy(void* s)             { delete SBS(s); }
void         IGSharp_SelectionBasicStorage_ApplyRequests(void* s, void* ms_io) { SBS(s)->ApplyRequests((ImGuiMultiSelectIO*)ms_io); }
bool         IGSharp_SelectionBasicStorage_Contains(void* s, unsigned int id)  { return SBS(s)->Contains((ImGuiID)id); }
void         IGSharp_SelectionBasicStorage_Clear(void* s)              { SBS(s)->Clear(); }
void         IGSharp_SelectionBasicStorage_SetItemSelected(void* s, unsigned int id, bool selected) { SBS(s)->SetItemSelected((ImGuiID)id, selected); }

bool         IGSharp_SelectionBasicStorage_GetNextSelectedItem(void* s, void** opaque_it, unsigned int* out_id)
{ return SBS(s)->GetNextSelectedItem(opaque_it, (ImGuiID*)out_id); }

unsigned int IGSharp_SelectionBasicStorage_GetStorageIdFromIndex(void* s, int idx) { return (unsigned int)SBS(s)->GetStorageIdFromIndex(idx); }
int          IGSharp_SelectionBasicStorage_GetSize(void* s)            { return SBS(s)->Size; }
bool         IGSharp_SelectionBasicStorage_GetPreserveOrder(void* s)   { return SBS(s)->PreserveOrder; }
void         IGSharp_SelectionBasicStorage_SetPreserveOrder(void* s, bool v) { SBS(s)->PreserveOrder = v; }
void*        IGSharp_SelectionBasicStorage_GetUserData(void* s)        { return SBS(s)->UserData; }
void         IGSharp_SelectionBasicStorage_SetUserData(void* s, void* v) { SBS(s)->UserData = v; }
void* IGSharp_SelectionExternalStorage_Create(void)                       { return IM_NEW(ImGuiSelectionExternalStorage)(); }
void  IGSharp_SelectionExternalStorage_Destroy(void* storage)             { IM_DELETE(SES(storage)); }
void* IGSharp_SelectionExternalStorage_GetUserData(void* storage)         { return SES(storage)->UserData; }
void  IGSharp_SelectionExternalStorage_SetUserData(void* storage, void* user_data) { SES(storage)->UserData = user_data; }

void  IGSharp_SelectionExternalStorage_SetAdapterSetItemSelected(void* storage, IGSharp_SelectionExternalStorageAdapter adapter)
{ SES(storage)->AdapterSetItemSelected = (void (*)(ImGuiSelectionExternalStorage*, int, bool))adapter; }

void  IGSharp_SelectionExternalStorage_ApplyRequests(void* storage, void* ms_io) { SES(storage)->ApplyRequests((ImGuiMultiSelectIO*)ms_io); }

//-----------------------------------------------------------------------------
// [SECTION] Drawing API (ImDrawCmd, ImDrawIdx, ImDrawVert, ImDrawChannel, ImDrawListSplitter, ImDrawListFlags, ImDrawList, ImDrawData)
//-----------------------------------------------------------------------------

// ImDrawIdx is the index type used by ImDrawList index buffers. The wrapper bakes in

IGSharp_Vec4 IGSharp_DrawCmd_GetClipRect(void* dc)
{ const ImVec4& r = DC(dc)->ClipRect; return { r.x, r.y, r.z, r.w }; }

unsigned long long IGSharp_DrawCmd_GetTexID(void* dc)        { return (unsigned long long)DC(dc)->GetTexID(); }
unsigned int IGSharp_DrawCmd_GetVtxOffset(void* dc)          { return DC(dc)->VtxOffset; }
unsigned int IGSharp_DrawCmd_GetIdxOffset(void* dc)          { return DC(dc)->IdxOffset; }
unsigned int IGSharp_DrawCmd_GetElemCount(void* dc)          { return DC(dc)->ElemCount; }
void* IGSharp_DrawCmd_GetUserCallback(void* dc)              { return (void*)DC(dc)->UserCallback; }
void* IGSharp_DrawCmd_GetUserCallbackData(void* dc)          { return DC(dc)->UserCallbackData; }
int IGSharp_DrawCmd_GetUserCallbackDataSize(void* dc)        { return DC(dc)->UserCallbackDataSize; }

// ImDrawListSplitter (accessors)

void* IGSharp_DrawListSplitter_Create(void)                  { return IM_NEW(ImDrawListSplitter)(); }
void  IGSharp_DrawListSplitter_Destroy(void* splitter)       { IM_DELETE(DLS(splitter)); }
void  IGSharp_DrawListSplitter_Clear(void* splitter)         { DLS(splitter)->Clear(); }
void  IGSharp_DrawListSplitter_ClearFreeMemory(void* splitter){ DLS(splitter)->ClearFreeMemory(); }

void  IGSharp_DrawListSplitter_Split(void* splitter, void* draw_list, int count)
    { DLS(splitter)->Split((ImDrawList*)draw_list, count); }

void  IGSharp_DrawListSplitter_Merge(void* splitter, void* draw_list)
    { DLS(splitter)->Merge((ImDrawList*)draw_list); }

void  IGSharp_DrawListSplitter_SetCurrentChannel(void* splitter, void* draw_list, int channel_idx)
    { DLS(splitter)->SetCurrentChannel((ImDrawList*)draw_list, channel_idx); }

// ImDrawList: Clipping

void IGSharp_DrawList_PushClipRect(void* dl, IGSharp_Vec2 r_min, IGSharp_Vec2 r_max, bool intersect_with_current)
{ DL(dl)->PushClipRect(ToImVec2(r_min), ToImVec2(r_max), intersect_with_current); }

void IGSharp_DrawList_PushClipRectFullScreen(void* dl)   { DL(dl)->PushClipRectFullScreen(); }
void IGSharp_DrawList_PopClipRect(void* dl)              { DL(dl)->PopClipRect(); }

// ImDrawList: Texture state

void IGSharp_DrawList_PushTexture(void* dl, unsigned long long tex_id)
{ DL(dl)->PushTexture(ImTextureRef((ImTextureID)tex_id)); }

void IGSharp_DrawList_PushTextureData(void* dl, void* tex_data)
{ DL(dl)->PushTexture(ToTexRef(tex_data)); }

void IGSharp_DrawList_PopTexture(void* dl)                         { DL(dl)->PopTexture(); }

// ImDrawList: Clip rect query

IGSharp_Vec2 IGSharp_DrawList_GetClipRectMin(void* dl)            { return FromImVec2(DL(dl)->GetClipRectMin()); }
IGSharp_Vec2 IGSharp_DrawList_GetClipRectMax(void* dl)            { return FromImVec2(DL(dl)->GetClipRectMax()); }

// ImDrawList: Primitives

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

// ImDrawList: Text with explicit font

void IGSharp_DrawList_AddTextFont(void* dl, void* font, float font_size, IGSharp_Vec2 pos, unsigned int col, const char* text_begin, const char* text_end, float wrap_width, const IGSharp_Vec4* cpu_fine_clip_rect)
{ DL(dl)->AddText((ImFont*)font, font_size, ToImVec2(pos), col, text_begin, text_end, wrap_width, (const ImVec4*)cpu_fine_clip_rect); }

// ImDrawList: Images

void IGSharp_DrawList_AddImage(void* dl, unsigned long long tex_id, IGSharp_Vec2 p_min, IGSharp_Vec2 p_max, IGSharp_Vec2 uv_min, IGSharp_Vec2 uv_max, unsigned int col)
{ DL(dl)->AddImage((ImTextureID)tex_id, ToImVec2(p_min), ToImVec2(p_max), ToImVec2(uv_min), ToImVec2(uv_max), col); }

void IGSharp_DrawList_AddImageQuad(void* dl, unsigned long long tex_id, IGSharp_Vec2 p1, IGSharp_Vec2 p2, IGSharp_Vec2 p3, IGSharp_Vec2 p4, IGSharp_Vec2 uv1, IGSharp_Vec2 uv2, IGSharp_Vec2 uv3, IGSharp_Vec2 uv4, unsigned int col)
{ DL(dl)->AddImageQuad((ImTextureID)tex_id, ToImVec2(p1), ToImVec2(p2), ToImVec2(p3), ToImVec2(p4), ToImVec2(uv1), ToImVec2(uv2), ToImVec2(uv3), ToImVec2(uv4), col); }

void IGSharp_DrawList_AddImageRounded(void* dl, unsigned long long tex_id, IGSharp_Vec2 p_min, IGSharp_Vec2 p_max, IGSharp_Vec2 uv_min, IGSharp_Vec2 uv_max, unsigned int col, float rounding, int flags)
{ DL(dl)->AddImageRounded((ImTextureID)tex_id, ToImVec2(p_min), ToImVec2(p_max), ToImVec2(uv_min), ToImVec2(uv_max), col, rounding, flags); }

// ImTextureData* variants (preserve deferred ImTextureID resolution for atlas/backend textures; tex_data may be NULL).

void IGSharp_DrawList_AddImageTextureData(void* dl, void* tex_data, IGSharp_Vec2 p_min, IGSharp_Vec2 p_max, IGSharp_Vec2 uv_min, IGSharp_Vec2 uv_max, unsigned int col)
{ DL(dl)->AddImage(ToTexRef(tex_data), ToImVec2(p_min), ToImVec2(p_max), ToImVec2(uv_min), ToImVec2(uv_max), col); }

void IGSharp_DrawList_AddImageQuadTextureData(void* dl, void* tex_data, IGSharp_Vec2 p1, IGSharp_Vec2 p2, IGSharp_Vec2 p3, IGSharp_Vec2 p4, IGSharp_Vec2 uv1, IGSharp_Vec2 uv2, IGSharp_Vec2 uv3, IGSharp_Vec2 uv4, unsigned int col)
{ DL(dl)->AddImageQuad(ToTexRef(tex_data), ToImVec2(p1), ToImVec2(p2), ToImVec2(p3), ToImVec2(p4), ToImVec2(uv1), ToImVec2(uv2), ToImVec2(uv3), ToImVec2(uv4), col); }

void IGSharp_DrawList_AddImageRoundedTextureData(void* dl, void* tex_data, IGSharp_Vec2 p_min, IGSharp_Vec2 p_max, IGSharp_Vec2 uv_min, IGSharp_Vec2 uv_max, unsigned int col, float rounding, int flags)
{ DL(dl)->AddImageRounded(ToTexRef(tex_data), ToImVec2(p_min), ToImVec2(p_max), ToImVec2(uv_min), ToImVec2(uv_max), col, rounding, flags); }

// ImDrawList: Path API

void IGSharp_DrawList_PathClear(void* dl)                          { DL(dl)->PathClear(); }
void IGSharp_DrawList_PathLineTo(void* dl, IGSharp_Vec2 pos)       { DL(dl)->PathLineTo(ToImVec2(pos)); }

void IGSharp_DrawList_PathLineToMergeDuplicate(void* dl, IGSharp_Vec2 pos)
{ DL(dl)->PathLineToMergeDuplicate(ToImVec2(pos)); }

void IGSharp_DrawList_PathFillConvex(void* dl, unsigned int col)   { DL(dl)->PathFillConvex(col); }
void IGSharp_DrawList_PathFillConcave(void* dl, unsigned int col) { DL(dl)->PathFillConcave(col); }

void IGSharp_DrawList_PathStroke(void* dl, unsigned int col, int flags, float thickness)
{ DL(dl)->PathStroke(col, flags, thickness); }

void IGSharp_DrawList_PathArcTo(void* dl, IGSharp_Vec2 center, float radius, float a_min, float a_max, int num_segments)
{ DL(dl)->PathArcTo(ToImVec2(center), radius, a_min, a_max, num_segments); }

void IGSharp_DrawList_PathArcToFast(void* dl, IGSharp_Vec2 center, float radius, int a_min_of_12, int a_max_of_12)
{ DL(dl)->PathArcToFast(ToImVec2(center), radius, a_min_of_12, a_max_of_12); }

void IGSharp_DrawList_PathEllipticalArcTo(void* dl, IGSharp_Vec2 center, IGSharp_Vec2 radius, float rot, float a_min, float a_max, int num_segments)
{ DL(dl)->PathEllipticalArcTo(ToImVec2(center), ToImVec2(radius), rot, a_min, a_max, num_segments); }

void IGSharp_DrawList_PathBezierCubicCurveTo(void* dl, IGSharp_Vec2 p2, IGSharp_Vec2 p3, IGSharp_Vec2 p4, int num_segments)
{ DL(dl)->PathBezierCubicCurveTo(ToImVec2(p2), ToImVec2(p3), ToImVec2(p4), num_segments); }

void IGSharp_DrawList_PathBezierQuadraticCurveTo(void* dl, IGSharp_Vec2 p2, IGSharp_Vec2 p3, int num_segments)
{ DL(dl)->PathBezierQuadraticCurveTo(ToImVec2(p2), ToImVec2(p3), num_segments); }

void IGSharp_DrawList_PathRect(void* dl, IGSharp_Vec2 rect_min, IGSharp_Vec2 rect_max, float rounding, int flags)
{ DL(dl)->PathRect(ToImVec2(rect_min), ToImVec2(rect_max), rounding, flags); }

// ImDrawList: Advanced (callbacks, draw commands, cloning)

void IGSharp_DrawList_AddCallback(void* dl, void* callback, void* userdata, size_t userdata_size)
{ DL(dl)->AddCallback((ImDrawCallback)callback, userdata, userdata_size); }

void IGSharp_DrawList_AddDrawCmd(void* dl)                        { DL(dl)->AddDrawCmd(); }
void* IGSharp_DrawList_CloneOutput(void* dl)                      { return (void*)DL(dl)->CloneOutput(); }

// Create/destroy a standalone ImDrawList (e.g. to own a CloneOutput result or build a custom list).

void* IGSharp_DrawList_Create(void* shared_data)                 { return (void*)IM_NEW(ImDrawList)((ImDrawListSharedData*)shared_data); }
void  IGSharp_DrawList_Destroy(void* dl)                         { IM_DELETE(DL(dl)); }

// ImDrawList: Channels splitting/merging

void IGSharp_DrawList_ChannelsSplit(void* dl, int count)         { DL(dl)->ChannelsSplit(count); }
void IGSharp_DrawList_ChannelsMerge(void* dl)                    { DL(dl)->ChannelsMerge(); }
void IGSharp_DrawList_ChannelsSetCurrent(void* dl, int n)        { DL(dl)->ChannelsSetCurrent(n); }

// ImDrawList: Advanced - Primitives allocations (for custom mesh generation)

void IGSharp_DrawList_PrimReserve(void* dl, int idx_count, int vtx_count)
{ DL(dl)->PrimReserve(idx_count, vtx_count); }

void IGSharp_DrawList_PrimUnreserve(void* dl, int idx_count, int vtx_count)
{ DL(dl)->PrimUnreserve(idx_count, vtx_count); }

void IGSharp_DrawList_PrimRect(void* dl, IGSharp_Vec2 a, IGSharp_Vec2 b, unsigned int col)
{ DL(dl)->PrimRect(ToImVec2(a), ToImVec2(b), col); }

void IGSharp_DrawList_PrimRectUV(void* dl, IGSharp_Vec2 a, IGSharp_Vec2 b, IGSharp_Vec2 uv_a, IGSharp_Vec2 uv_b, unsigned int col)
{ DL(dl)->PrimRectUV(ToImVec2(a), ToImVec2(b), ToImVec2(uv_a), ToImVec2(uv_b), col); }

void IGSharp_DrawList_PrimQuadUV(void* dl, IGSharp_Vec2 a, IGSharp_Vec2 b, IGSharp_Vec2 c, IGSharp_Vec2 d, IGSharp_Vec2 uv_a, IGSharp_Vec2 uv_b, IGSharp_Vec2 uv_c, IGSharp_Vec2 uv_d, unsigned int col)
{ DL(dl)->PrimQuadUV(ToImVec2(a), ToImVec2(b), ToImVec2(c), ToImVec2(d), ToImVec2(uv_a), ToImVec2(uv_b), ToImVec2(uv_c), ToImVec2(uv_d), col); }

void IGSharp_DrawList_PrimWriteVtx(void* dl, IGSharp_Vec2 pos, IGSharp_Vec2 uv, unsigned int col)
{ DL(dl)->PrimWriteVtx(ToImVec2(pos), ToImVec2(uv), col); }

void IGSharp_DrawList_PrimWriteIdx(void* dl, unsigned short idx)
{ DL(dl)->PrimWriteIdx((ImDrawIdx)idx); }

void IGSharp_DrawList_PrimVtx(void* dl, IGSharp_Vec2 pos, IGSharp_Vec2 uv, unsigned int col)
{ DL(dl)->PrimVtx(ToImVec2(pos), ToImVec2(uv), col); }

// ImDrawList: Buffer / flag access (ImDrawList is not mirrored; required for a .NET renderer)

int   IGSharp_DrawList_GetFlags(void* dl)              { return (int)DL(dl)->Flags; }
void  IGSharp_DrawList_SetFlags(void* dl, int flags)   { DL(dl)->Flags = (ImDrawListFlags)flags; }
int   IGSharp_DrawList_GetCmdBufferSize(void* dl)      { return DL(dl)->CmdBuffer.Size; }
void* IGSharp_DrawList_GetCmdBufferData(void* dl)      { return (void*)DL(dl)->CmdBuffer.Data; }
void* IGSharp_DrawList_GetCmd(void* dl, int index)     { return (void*)&DL(dl)->CmdBuffer[index]; }
int   IGSharp_DrawList_GetIdxBufferSize(void* dl)      { return DL(dl)->IdxBuffer.Size; }
void* IGSharp_DrawList_GetIdxBufferData(void* dl)      { return (void*)DL(dl)->IdxBuffer.Data; }
int   IGSharp_DrawList_GetVtxBufferSize(void* dl)      { return DL(dl)->VtxBuffer.Size; }
void* IGSharp_DrawList_GetVtxBufferData(void* dl)      { return (void*)DL(dl)->VtxBuffer.Data; }

// ImDrawData (accessors; obtain via IGSharp_GetDrawData())

bool         IGSharp_DrawData_GetValid(void* draw_data)            { return DD(draw_data)->Valid; }
int          IGSharp_DrawData_GetCmdListsCount(void* draw_data)    { return DD(draw_data)->CmdListsCount; }
int          IGSharp_DrawData_GetTotalIdxCount(void* draw_data)    { return DD(draw_data)->TotalIdxCount; }
int          IGSharp_DrawData_GetTotalVtxCount(void* draw_data)    { return DD(draw_data)->TotalVtxCount; }

void* IGSharp_DrawData_GetCmdList(void* draw_data, int index)
{
    ImDrawData* d = DD(draw_data);
    if (index < 0 || index >= d->CmdLists.Size) return nullptr;
    return d->CmdLists[index];
}

IGSharp_Vec2 IGSharp_DrawData_GetDisplayPos(void* draw_data)       { return FromImVec2(DD(draw_data)->DisplayPos); }
IGSharp_Vec2 IGSharp_DrawData_GetDisplaySize(void* draw_data)      { return FromImVec2(DD(draw_data)->DisplaySize); }
IGSharp_Vec2 IGSharp_DrawData_GetFramebufferScale(void* draw_data) { return FromImVec2(DD(draw_data)->FramebufferScale); }
void*        IGSharp_DrawData_GetOwnerViewport(void* draw_data)    { return DD(draw_data)->OwnerViewport; }
void         IGSharp_DrawData_Clear(void* draw_data)               { DD(draw_data)->Clear(); }
void         IGSharp_DrawData_AddDrawList(void* draw_data, void* draw_list) { DD(draw_data)->AddDrawList(DL(draw_list)); }
void         IGSharp_DrawData_DeIndexAllBuffers(void* draw_data)   { DD(draw_data)->DeIndexAllBuffers(); }
void         IGSharp_DrawData_ScaleClipRects(void* draw_data, IGSharp_Vec2 fb_scale) { DD(draw_data)->ScaleClipRects(ToImVec2(fb_scale)); }

// ImDrawData: Textures list (ImVector<ImTextureData*>* — the pointer itself may be NULL)

int   IGSharp_DrawData_GetTexturesCount(void* draw_data)
{
    ImVector<ImTextureData*>* t = DD(draw_data)->Textures;
    return t ? t->Size : 0;
}

void* IGSharp_DrawData_GetTexturesData(void* draw_data)
{
    ImVector<ImTextureData*>* t = DD(draw_data)->Textures;
    return t ? (void*)t->Data : nullptr;
}

void* IGSharp_DrawData_GetTextures(void* draw_data)              { return (void*)DD(draw_data)->Textures; }
void  IGSharp_DrawData_SetTextures(void* draw_data, void* textures) { DD(draw_data)->Textures = (ImVector<ImTextureData*>*)textures; }

//-----------------------------------------------------------------------------
// [SECTION] Texture API (ImTextureFormat, ImTextureStatus, ImTextureRect, ImTextureData)
//-----------------------------------------------------------------------------

// ImTextureData accessors

int   IGSharp_TextureData_GetUniqueID(void* tex_data)        { return TD(tex_data)->UniqueID; }
int   IGSharp_TextureData_GetStatus(void* tex_data)          { return (int)TD(tex_data)->Status; }
void* IGSharp_TextureData_GetBackendUserData(void* tex_data) { return TD(tex_data)->BackendUserData; }
void  IGSharp_TextureData_SetBackendUserData(void* tex_data, void* backend_user_data) { TD(tex_data)->BackendUserData = backend_user_data; }
unsigned long long IGSharp_TextureData_GetTexID(void* tex_data) { return (unsigned long long)TD(tex_data)->TexID; }
int   IGSharp_TextureData_GetFormat(void* tex_data)          { return (int)TD(tex_data)->Format; }
int   IGSharp_TextureData_GetWidth(void* tex_data)           { return TD(tex_data)->Width; }
int   IGSharp_TextureData_GetHeight(void* tex_data)          { return TD(tex_data)->Height; }
int   IGSharp_TextureData_GetBytesPerPixel(void* tex_data)   { return TD(tex_data)->BytesPerPixel; }
unsigned char* IGSharp_TextureData_GetPixels(void* tex_data) { return TD(tex_data)->Pixels; }

void  IGSharp_TextureData_GetUsedRect(void* tex_data, unsigned short* x, unsigned short* y, unsigned short* w, unsigned short* h)
{
    const ImTextureRect& r = TD(tex_data)->UsedRect;
    if (x) *x = r.x; if (y) *y = r.y; if (w) *w = r.w; if (h) *h = r.h;
}

void  IGSharp_TextureData_GetUpdateRect(void* tex_data, unsigned short* x, unsigned short* y, unsigned short* w, unsigned short* h)
{
    const ImTextureRect& r = TD(tex_data)->UpdateRect;
    if (x) *x = r.x; if (y) *y = r.y; if (w) *w = r.w; if (h) *h = r.h;
}

// Individual update rectangles a backend must apply when Status == WantUpdates (the GetUpdateRect above is their bounding box).

int   IGSharp_TextureData_GetUpdatesCount(void* tex_data) { return TD(tex_data)->Updates.Size; }

void  IGSharp_TextureData_GetUpdate(void* tex_data, int index, unsigned short* x, unsigned short* y, unsigned short* w, unsigned short* h)
{
    const ImTextureRect& r = TD(tex_data)->Updates[index];
    if (x) *x = r.x; if (y) *y = r.y; if (w) *w = r.w; if (h) *h = r.h;
}

int            IGSharp_TextureData_GetUnusedFrames(void* tex_data) { return TD(tex_data)->UnusedFrames; }
unsigned short IGSharp_TextureData_GetRefCount(void* tex_data)     { return TD(tex_data)->RefCount; }
bool           IGSharp_TextureData_GetUseColors(void* tex_data)    { return TD(tex_data)->UseColors; }

// Methods

void  IGSharp_TextureData_Create(void* tex_data, int format, int w, int h) { TD(tex_data)->Create((ImTextureFormat)format, w, h); }
void  IGSharp_TextureData_DestroyPixels(void* tex_data)      { TD(tex_data)->DestroyPixels(); }
void* IGSharp_TextureData_GetPixelsPtr(void* tex_data)       { return TD(tex_data)->GetPixels(); }
void* IGSharp_TextureData_GetPixelsAt(void* tex_data, int x, int y) { return TD(tex_data)->GetPixelsAt(x, y); }
int   IGSharp_TextureData_GetSizeInBytes(void* tex_data)     { return TD(tex_data)->GetSizeInBytes(); }
int   IGSharp_TextureData_GetPitch(void* tex_data)           { return TD(tex_data)->GetPitch(); }
void  IGSharp_TextureData_SetTexID(void* tex_data, unsigned long long tex_id) { TD(tex_data)->SetTexID((ImTextureID)tex_id); }
void  IGSharp_TextureData_SetStatus(void* tex_data, int status) { TD(tex_data)->SetStatus((ImTextureStatus)status); }

//-----------------------------------------------------------------------------
// [SECTION] Font API (ImFontConfig, ImFontGlyph, ImFontAtlasFlags, ImFontAtlas, ImFontGlyphRangesBuilder, ImFont)
//-----------------------------------------------------------------------------

// ImFontConfig (accessors)

void* IGSharp_FontConfig_Create(void)        { return IM_NEW(ImFontConfig)(); }
void  IGSharp_FontConfig_Destroy(void* cfg)  { IM_DELETE(FC(cfg)); }
const char* IGSharp_FontConfig_GetName(void* cfg)              { return FC(cfg)->Name; }

void        IGSharp_FontConfig_SetName(void* cfg, const char* name)
{
    ImFontConfig* c = FC(cfg);
    if (name == nullptr) { c->Name[0] = '\0'; return; }
    const size_t cap = sizeof(c->Name);
    size_t i = 0;
    for (; i + 1 < cap && name[i] != '\0'; i++)
        c->Name[i] = name[i];
    c->Name[i] = '\0';
}

void*       IGSharp_FontConfig_GetFontData(void* cfg)          { return FC(cfg)->FontData; }
void        IGSharp_FontConfig_SetFontData(void* cfg, void* font_data) { FC(cfg)->FontData = font_data; }
int         IGSharp_FontConfig_GetFontDataSize(void* cfg)      { return FC(cfg)->FontDataSize; }
void        IGSharp_FontConfig_SetFontDataSize(void* cfg, int font_data_size) { FC(cfg)->FontDataSize = font_data_size; }
bool        IGSharp_FontConfig_GetFontDataOwnedByAtlas(void* cfg) { return FC(cfg)->FontDataOwnedByAtlas; }
void        IGSharp_FontConfig_SetFontDataOwnedByAtlas(void* cfg, bool value) { FC(cfg)->FontDataOwnedByAtlas = value; }
bool        IGSharp_FontConfig_GetMergeMode(void* cfg)         { return FC(cfg)->MergeMode; }
void        IGSharp_FontConfig_SetMergeMode(void* cfg, bool value) { FC(cfg)->MergeMode = value; }
bool        IGSharp_FontConfig_GetPixelSnapH(void* cfg)        { return FC(cfg)->PixelSnapH; }
void        IGSharp_FontConfig_SetPixelSnapH(void* cfg, bool value) { FC(cfg)->PixelSnapH = value; }
int         IGSharp_FontConfig_GetOversampleH(void* cfg)       { return (int)FC(cfg)->OversampleH; }
void        IGSharp_FontConfig_SetOversampleH(void* cfg, int value) { FC(cfg)->OversampleH = (ImS8)value; }
int         IGSharp_FontConfig_GetOversampleV(void* cfg)       { return (int)FC(cfg)->OversampleV; }
void        IGSharp_FontConfig_SetOversampleV(void* cfg, int value) { FC(cfg)->OversampleV = (ImS8)value; }
unsigned short IGSharp_FontConfig_GetEllipsisChar(void* cfg)   { return (unsigned short)FC(cfg)->EllipsisChar; }
void           IGSharp_FontConfig_SetEllipsisChar(void* cfg, unsigned short value) { FC(cfg)->EllipsisChar = (ImWchar)value; }
float       IGSharp_FontConfig_GetSizePixels(void* cfg)        { return FC(cfg)->SizePixels; }
void        IGSharp_FontConfig_SetSizePixels(void* cfg, float value) { FC(cfg)->SizePixels = value; }
const unsigned short* IGSharp_FontConfig_GetGlyphRanges(void* cfg) { return (const unsigned short*)FC(cfg)->GlyphRanges; }
void                  IGSharp_FontConfig_SetGlyphRanges(void* cfg, const unsigned short* ranges) { FC(cfg)->GlyphRanges = (const ImWchar*)ranges; }
const unsigned short* IGSharp_FontConfig_GetGlyphExcludeRanges(void* cfg) { return (const unsigned short*)FC(cfg)->GlyphExcludeRanges; }
void                  IGSharp_FontConfig_SetGlyphExcludeRanges(void* cfg, const unsigned short* ranges) { FC(cfg)->GlyphExcludeRanges = (const ImWchar*)ranges; }
IGSharp_Vec2 IGSharp_FontConfig_GetGlyphOffset(void* cfg)      { return FromImVec2(FC(cfg)->GlyphOffset); }
void         IGSharp_FontConfig_SetGlyphOffset(void* cfg, IGSharp_Vec2 value) { FC(cfg)->GlyphOffset = ToImVec2(value); }
float       IGSharp_FontConfig_GetGlyphMinAdvanceX(void* cfg)  { return FC(cfg)->GlyphMinAdvanceX; }
void        IGSharp_FontConfig_SetGlyphMinAdvanceX(void* cfg, float value) { FC(cfg)->GlyphMinAdvanceX = value; }
float       IGSharp_FontConfig_GetGlyphMaxAdvanceX(void* cfg)  { return FC(cfg)->GlyphMaxAdvanceX; }
void        IGSharp_FontConfig_SetGlyphMaxAdvanceX(void* cfg, float value) { FC(cfg)->GlyphMaxAdvanceX = value; }
float       IGSharp_FontConfig_GetGlyphExtraAdvanceX(void* cfg) { return FC(cfg)->GlyphExtraAdvanceX; }
void        IGSharp_FontConfig_SetGlyphExtraAdvanceX(void* cfg, float value) { FC(cfg)->GlyphExtraAdvanceX = value; }
unsigned int IGSharp_FontConfig_GetFontNo(void* cfg)           { return (unsigned int)FC(cfg)->FontNo; }
void         IGSharp_FontConfig_SetFontNo(void* cfg, unsigned int value) { FC(cfg)->FontNo = (ImU32)value; }
unsigned int IGSharp_FontConfig_GetFontLoaderFlags(void* cfg)  { return FC(cfg)->FontLoaderFlags; }
void         IGSharp_FontConfig_SetFontLoaderFlags(void* cfg, unsigned int value) { FC(cfg)->FontLoaderFlags = value; }
float       IGSharp_FontConfig_GetRasterizerMultiply(void* cfg) { return FC(cfg)->RasterizerMultiply; }
void        IGSharp_FontConfig_SetRasterizerMultiply(void* cfg, float value) { FC(cfg)->RasterizerMultiply = value; }
float       IGSharp_FontConfig_GetRasterizerDensity(void* cfg) { return FC(cfg)->RasterizerDensity; }
void        IGSharp_FontConfig_SetRasterizerDensity(void* cfg, float value) { FC(cfg)->RasterizerDensity = value; }
float       IGSharp_FontConfig_GetExtraSizeScale(void* cfg)    { return FC(cfg)->ExtraSizeScale; }
void        IGSharp_FontConfig_SetExtraSizeScale(void* cfg, float value) { FC(cfg)->ExtraSizeScale = value; }

// ImFontGlyph (accessors)

bool  IGSharp_FontGlyph_GetColored(void* glyph)      { return ((ImFontGlyph*)glyph)->Colored != 0; }
bool  IGSharp_FontGlyph_GetVisible(void* glyph)      { return ((ImFontGlyph*)glyph)->Visible != 0; }
int   IGSharp_FontGlyph_GetSourceIdx(void* glyph)    { return (int)((ImFontGlyph*)glyph)->SourceIdx; }
unsigned int IGSharp_FontGlyph_GetCodepoint(void* glyph) { return ((ImFontGlyph*)glyph)->Codepoint; }
float IGSharp_FontGlyph_GetAdvanceX(void* glyph)     { return ((ImFontGlyph*)glyph)->AdvanceX; }
float IGSharp_FontGlyph_GetX0(void* glyph)           { return ((ImFontGlyph*)glyph)->X0; }
float IGSharp_FontGlyph_GetY0(void* glyph)           { return ((ImFontGlyph*)glyph)->Y0; }
float IGSharp_FontGlyph_GetX1(void* glyph)           { return ((ImFontGlyph*)glyph)->X1; }
float IGSharp_FontGlyph_GetY1(void* glyph)           { return ((ImFontGlyph*)glyph)->Y1; }
float IGSharp_FontGlyph_GetU0(void* glyph)           { return ((ImFontGlyph*)glyph)->U0; }
float IGSharp_FontGlyph_GetV0(void* glyph)           { return ((ImFontGlyph*)glyph)->V0; }
float IGSharp_FontGlyph_GetU1(void* glyph)           { return ((ImFontGlyph*)glyph)->U1; }
float IGSharp_FontGlyph_GetV1(void* glyph)           { return ((ImFontGlyph*)glyph)->V1; }
int   IGSharp_FontGlyph_GetPackId(void* glyph)       { return ((ImFontGlyph*)glyph)->PackId; }

// ImFontGlyphRangesBuilder

void* IGSharp_FontGlyphRangesBuilder_New(void)        { return new ImFontGlyphRangesBuilder(); }
void  IGSharp_FontGlyphRangesBuilder_Delete(void* builder) { delete (ImFontGlyphRangesBuilder*)builder; }
void  IGSharp_FontGlyphRangesBuilder_Clear(void* builder)  { ((ImFontGlyphRangesBuilder*)builder)->Clear(); }
bool  IGSharp_FontGlyphRangesBuilder_GetBit(void* builder, size_t n) { return ((ImFontGlyphRangesBuilder*)builder)->GetBit(n); }
void  IGSharp_FontGlyphRangesBuilder_SetBit(void* builder, size_t n) { ((ImFontGlyphRangesBuilder*)builder)->SetBit(n); }
void  IGSharp_FontGlyphRangesBuilder_AddChar(void* builder, unsigned short c) { ((ImFontGlyphRangesBuilder*)builder)->AddChar((ImWchar)c); }

void  IGSharp_FontGlyphRangesBuilder_AddText(void* builder, const char* text, const char* text_end)
{ ((ImFontGlyphRangesBuilder*)builder)->AddText(text, text_end); }

void  IGSharp_FontGlyphRangesBuilder_AddRanges(void* builder, const unsigned short* ranges)
{ ((ImFontGlyphRangesBuilder*)builder)->AddRanges((const ImWchar*)ranges); }

// Builds the glyph ranges and copies up to out_ranges_capacity entries (terminated by a trailing 0)

int   IGSharp_FontGlyphRangesBuilder_BuildRanges(void* builder, unsigned short* out_ranges, int out_ranges_capacity)
{
    ImVector<ImWchar> tmp;
    ((ImFontGlyphRangesBuilder*)builder)->BuildRanges(&tmp);
    int count = tmp.Size;
    int copy_count = count < out_ranges_capacity ? count : out_ranges_capacity;
    for (int i = 0; i < copy_count; i++)
        out_ranges[i] = (unsigned short)tmp[i];
    return count;
}

// ImFontAtlas

void* IGSharp_FontAtlas_Create(void)                { return (void*)IM_NEW(ImFontAtlas)(); }
void  IGSharp_FontAtlas_Destroy(void* atlas)        { IM_DELETE((ImFontAtlas*)atlas); }

void* IGSharp_FontAtlas_AddFontDefault(void* atlas, const void* font_cfg)
{ return ((ImFontAtlas*)atlas)->AddFontDefault((const ImFontConfig*)font_cfg); }

void* IGSharp_FontAtlas_AddFontFromFileTTF(void* atlas, const char* filename, float size_pixels, const void* font_cfg, const unsigned short* glyph_ranges)
{ return ((ImFontAtlas*)atlas)->AddFontFromFileTTF(filename, size_pixels, (const ImFontConfig*)font_cfg, (const ImWchar*)glyph_ranges); }

void* IGSharp_FontAtlas_AddFontFromMemoryTTF(void* atlas, void* font_data, int font_data_size, float size_pixels, bool transfer_ownership)
{
    ImFontConfig cfg;
    cfg.FontDataOwnedByAtlas = transfer_ownership;
    return ((ImFontAtlas*)atlas)->AddFontFromMemoryTTF(font_data, font_data_size, size_pixels, &cfg);
}

void* IGSharp_FontAtlas_AddFontFromMemoryCompressedTTF(void* atlas, const void* compressed_data, int compressed_size, float size_pixels, const void* font_cfg, const unsigned short* glyph_ranges)
{ return ((ImFontAtlas*)atlas)->AddFontFromMemoryCompressedTTF(compressed_data, compressed_size, size_pixels, (const ImFontConfig*)font_cfg, (const ImWchar*)glyph_ranges); }

void IGSharp_FontAtlas_Clear(void* atlas)       { ((ImFontAtlas*)atlas)->Clear(); }
void IGSharp_FontAtlas_ClearFonts(void* atlas)  { ((ImFontAtlas*)atlas)->ClearFonts(); }
int  IGSharp_FontAtlas_GetFontCount(void* atlas){ return ((ImFontAtlas*)atlas)->Fonts.Size; }

void* IGSharp_FontAtlas_GetFont(void* atlas, int index)
{
    ImFontAtlas* a = (ImFontAtlas*)atlas;
    if (index < 0 || index >= a->Fonts.Size) return nullptr;
    return a->Fonts[index];
}

// ImFontAtlas font construction & lifecycle

void* IGSharp_FontAtlas_AddFont(void* atlas, const void* font_cfg)
{ return ((ImFontAtlas*)atlas)->AddFont((const ImFontConfig*)font_cfg); }

void* IGSharp_FontAtlas_AddFontDefaultVector(void* atlas, const void* font_cfg)
{ return ((ImFontAtlas*)atlas)->AddFontDefaultVector((const ImFontConfig*)font_cfg); }

void* IGSharp_FontAtlas_AddFontDefaultBitmap(void* atlas, const void* font_cfg)
{ return ((ImFontAtlas*)atlas)->AddFontDefaultBitmap((const ImFontConfig*)font_cfg); }

void* IGSharp_FontAtlas_AddFontFromMemoryCompressedBase85TTF(void* atlas, const char* compressed_data_base85, float size_pixels, const void* font_cfg, const unsigned short* glyph_ranges)
{ return ((ImFontAtlas*)atlas)->AddFontFromMemoryCompressedBase85TTF(compressed_data_base85, size_pixels, (const ImFontConfig*)font_cfg, (const ImWchar*)glyph_ranges); }

void IGSharp_FontAtlas_RemoveFont(void* atlas, void* font)
{ ((ImFontAtlas*)atlas)->RemoveFont((ImFont*)font); }

void IGSharp_FontAtlas_CompactCache(void* atlas)
{ ((ImFontAtlas*)atlas)->CompactCache(); }

void IGSharp_FontAtlas_SetFontLoader(void* atlas, const void* font_loader)
{ ((ImFontAtlas*)atlas)->SetFontLoader((const ImFontLoader*)font_loader); }

void IGSharp_FontAtlas_ClearInputData(void* atlas)
{ ((ImFontAtlas*)atlas)->ClearInputData(); }

void IGSharp_FontAtlas_ClearTexData(void* atlas)
{ ((ImFontAtlas*)atlas)->ClearTexData(); }

const unsigned short* IGSharp_FontAtlas_GetGlyphRangesDefault(void* atlas)
{ return (const unsigned short*)((ImFontAtlas*)atlas)->GetGlyphRangesDefault(); }

int IGSharp_FontAtlas_AddCustomRect(void* atlas, int width, int height, IGSharp_FontAtlasRect* out_r)
{ return ((ImFontAtlas*)atlas)->AddCustomRect(width, height, reinterpret_cast<ImFontAtlasRect*>(out_r)); }

void IGSharp_FontAtlas_RemoveCustomRect(void* atlas, int id)
{ ((ImFontAtlas*)atlas)->RemoveCustomRect(id); }

bool IGSharp_FontAtlas_GetCustomRect(void* atlas, int id, IGSharp_FontAtlasRect* out_r)
{ return ((ImFontAtlas*)atlas)->GetCustomRect(id, reinterpret_cast<ImFontAtlasRect*>(out_r)); }

// ImFontAtlas member field accessors

int  IGSharp_FontAtlas_GetFlags(void* atlas)                 { return (int)((ImFontAtlas*)atlas)->Flags; }
void IGSharp_FontAtlas_SetFlags(void* atlas, int flags)      { ((ImFontAtlas*)atlas)->Flags = (ImFontAtlasFlags)flags; }
int  IGSharp_FontAtlas_GetTexDesiredFormat(void* atlas)      { return (int)((ImFontAtlas*)atlas)->TexDesiredFormat; }
void IGSharp_FontAtlas_SetTexDesiredFormat(void* atlas, int format) { ((ImFontAtlas*)atlas)->TexDesiredFormat = (ImTextureFormat)format; }
int  IGSharp_FontAtlas_GetTexGlyphPadding(void* atlas)       { return ((ImFontAtlas*)atlas)->TexGlyphPadding; }
void IGSharp_FontAtlas_SetTexGlyphPadding(void* atlas, int padding) { ((ImFontAtlas*)atlas)->TexGlyphPadding = padding; }
int  IGSharp_FontAtlas_GetTexMinWidth(void* atlas)           { return ((ImFontAtlas*)atlas)->TexMinWidth; }
void IGSharp_FontAtlas_SetTexMinWidth(void* atlas, int width){ ((ImFontAtlas*)atlas)->TexMinWidth = width; }
int  IGSharp_FontAtlas_GetTexMinHeight(void* atlas)          { return ((ImFontAtlas*)atlas)->TexMinHeight; }
void IGSharp_FontAtlas_SetTexMinHeight(void* atlas, int height) { ((ImFontAtlas*)atlas)->TexMinHeight = height; }
int  IGSharp_FontAtlas_GetTexMaxWidth(void* atlas)           { return ((ImFontAtlas*)atlas)->TexMaxWidth; }
void IGSharp_FontAtlas_SetTexMaxWidth(void* atlas, int width){ ((ImFontAtlas*)atlas)->TexMaxWidth = width; }
int  IGSharp_FontAtlas_GetTexMaxHeight(void* atlas)          { return ((ImFontAtlas*)atlas)->TexMaxHeight; }
void IGSharp_FontAtlas_SetTexMaxHeight(void* atlas, int height) { ((ImFontAtlas*)atlas)->TexMaxHeight = height; }
void* IGSharp_FontAtlas_GetUserData(void* atlas)             { return ((ImFontAtlas*)atlas)->UserData; }
void IGSharp_FontAtlas_SetUserData(void* atlas, void* user_data) { ((ImFontAtlas*)atlas)->UserData = user_data; }

// Output

unsigned long long IGSharp_FontAtlas_GetTexID(void* atlas)   { return (unsigned long long)((ImFontAtlas*)atlas)->TexRef.GetTexID(); }
void* IGSharp_FontAtlas_GetTexData(void* atlas)              { return ((ImFontAtlas*)atlas)->TexData; }
bool IGSharp_FontAtlas_GetTexPixelsUseColors(void* atlas)    { return ((ImFontAtlas*)atlas)->TexPixelsUseColors; }
void IGSharp_FontAtlas_SetTexPixelsUseColors(void* atlas, bool v) { ((ImFontAtlas*)atlas)->TexPixelsUseColors = v; }
IGSharp_Vec2 IGSharp_FontAtlas_GetTexUvScale(void* atlas)    { return FromImVec2(((ImFontAtlas*)atlas)->TexUvScale); }
IGSharp_Vec2 IGSharp_FontAtlas_GetTexUvWhitePixel(void* atlas) { return FromImVec2(((ImFontAtlas*)atlas)->TexUvWhitePixel); }
bool IGSharp_FontAtlas_GetTexIsBuilt(void* atlas)            { return ((ImFontAtlas*)atlas)->TexIsBuilt; }
bool IGSharp_FontAtlas_GetLocked(void* atlas)               { return ((ImFontAtlas*)atlas)->Locked; }
bool IGSharp_FontAtlas_GetRendererHasTextures(void* atlas)  { return ((ImFontAtlas*)atlas)->RendererHasTextures; }
const char* IGSharp_FontAtlas_GetFontLoaderName(void* atlas){ return ((ImFontAtlas*)atlas)->FontLoaderName; }
unsigned int IGSharp_FontAtlas_GetFontLoaderFlags(void* atlas)            { return ((ImFontAtlas*)atlas)->FontLoaderFlags; }
void IGSharp_FontAtlas_SetFontLoaderFlags(void* atlas, unsigned int flags){ ((ImFontAtlas*)atlas)->FontLoaderFlags = flags; }

// ImFontBaked accessors & methods

void* IGSharp_FontBaked_FindGlyph(void* baked, unsigned short c)
{ return ((ImFontBaked*)baked)->FindGlyph((ImWchar)c); }

void* IGSharp_FontBaked_FindGlyphNoFallback(void* baked, unsigned short c)
{ return ((ImFontBaked*)baked)->FindGlyphNoFallback((ImWchar)c); }

float IGSharp_FontBaked_GetCharAdvance(void* baked, unsigned short c)
{ return ((ImFontBaked*)baked)->GetCharAdvance((ImWchar)c); }

bool  IGSharp_FontBaked_IsGlyphLoaded(void* baked, unsigned short c)
{ return ((ImFontBaked*)baked)->IsGlyphLoaded((ImWchar)c); }

float IGSharp_FontBaked_GetSize(void* baked)             { return ((ImFontBaked*)baked)->Size; }
float IGSharp_FontBaked_GetAscent(void* baked)           { return ((ImFontBaked*)baked)->Ascent; }
float IGSharp_FontBaked_GetDescent(void* baked)          { return ((ImFontBaked*)baked)->Descent; }
float IGSharp_FontBaked_GetFallbackAdvanceX(void* baked) { return ((ImFontBaked*)baked)->FallbackAdvanceX; }
float IGSharp_FontBaked_GetRasterizerDensity(void* baked) { return ((ImFontBaked*)baked)->RasterizerDensity; }
int   IGSharp_FontBaked_GetGlyphsCount(void* baked)       { return ((ImFontBaked*)baked)->Glyphs.Size; }
void* IGSharp_FontBaked_GetGlyph(void* baked, int index)  { return (void*)&((ImFontBaked*)baked)->Glyphs[index]; }
void  IGSharp_FontBaked_ClearOutputData(void* baked)      { ((ImFontBaked*)baked)->ClearOutputData(); }

// ImFont accessors & methods

bool IGSharp_Font_IsGlyphInFont(void* font, unsigned short c)
{ return FONT(font)->IsGlyphInFont((ImWchar)c); }

bool IGSharp_Font_IsLoaded(void* font)              { return FONT(font)->IsLoaded(); }
const char* IGSharp_Font_GetDebugName(void* font)   { return FONT(font)->GetDebugName(); }

void* IGSharp_Font_GetFontBaked(void* font, float font_size, float density)
{ return FONT(font)->GetFontBaked(font_size, density); }

IGSharp_Vec2 IGSharp_Font_CalcTextSizeA(void* font, float size, float max_width, float wrap_width, const char* text_begin, const char* text_end, const char** out_remaining)
{ return FromImVec2(FONT(font)->CalcTextSizeA(size, max_width, wrap_width, text_begin, text_end, out_remaining)); }

const char* IGSharp_Font_CalcWordWrapPosition(void* font, float size, const char* text, const char* text_end, float wrap_width)
{ return FONT(font)->CalcWordWrapPosition(size, text, text_end, wrap_width); }

void IGSharp_Font_RenderChar(void* font, void* draw_list, float size, IGSharp_Vec2 pos, unsigned int col, unsigned short c, const IGSharp_Vec4* cpu_fine_clip)
{
    ImVec4 clip;
    const ImVec4* clip_ptr = nullptr;
    if (cpu_fine_clip) { clip = ToImVec4(*cpu_fine_clip); clip_ptr = &clip; }
    FONT(font)->RenderChar((ImDrawList*)draw_list, size, ToImVec2(pos), (ImU32)col, (ImWchar)c, clip_ptr);
}

void IGSharp_Font_RenderText(void* font, void* draw_list, float size, IGSharp_Vec2 pos, unsigned int col, IGSharp_Vec4 clip_rect, const char* text_begin, const char* text_end, float wrap_width, int flags)
{ FONT(font)->RenderText((ImDrawList*)draw_list, size, ToImVec2(pos), (ImU32)col, ToImVec4(clip_rect), text_begin, text_end, wrap_width, (ImDrawTextFlags)flags); }

void IGSharp_Font_AddRemapChar(void* font, unsigned short from_codepoint, unsigned short to_codepoint)
{ FONT(font)->AddRemapChar((ImWchar)from_codepoint, (ImWchar)to_codepoint); }

bool IGSharp_Font_IsGlyphRangeUnused(void* font, unsigned int c_begin, unsigned int c_last)
{ return FONT(font)->IsGlyphRangeUnused(c_begin, c_last); }

void IGSharp_Font_ClearOutputData(void* font)       { FONT(font)->ClearOutputData(); }

// ImFont field accessors

void* IGSharp_Font_GetOwnerAtlas(void* font)        { return (void*)FONT(font)->OwnerAtlas; }
int  IGSharp_Font_GetFlags(void* font)              { return (int)FONT(font)->Flags; }
void IGSharp_Font_SetFlags(void* font, int flags)   { FONT(font)->Flags = (ImFontFlags)flags; }
unsigned short IGSharp_Font_GetFallbackChar(void* font)              { return (unsigned short)FONT(font)->FallbackChar; }
void IGSharp_Font_SetFallbackChar(void* font, unsigned short c)      { FONT(font)->FallbackChar = (ImWchar)c; }
unsigned short IGSharp_Font_GetEllipsisChar(void* font)              { return (unsigned short)FONT(font)->EllipsisChar; }
void IGSharp_Font_SetEllipsisChar(void* font, unsigned short c)      { FONT(font)->EllipsisChar = (ImWchar)c; }

// When swapping EllipsisChar to a custom char, clear EllipsisAutoBake so the "..." glyph isn't re-baked over it.

bool IGSharp_Font_GetEllipsisAutoBake(void* font)                   { return FONT(font)->EllipsisAutoBake; }
void IGSharp_Font_SetEllipsisAutoBake(void* font, bool v)           { FONT(font)->EllipsisAutoBake = v; }
float IGSharp_Font_GetLegacySize(void* font)        { return FONT(font)->LegacySize; }
void  IGSharp_Font_SetLegacySize(void* font, float size) { FONT(font)->LegacySize = size; }

//-----------------------------------------------------------------------------
// [SECTION] Viewports
//-----------------------------------------------------------------------------

// ImGuiViewport

unsigned int IGSharp_Viewport_GetID(void* viewport)                  { return (unsigned int)((ImGuiViewport*)viewport)->ID; }
int IGSharp_Viewport_GetFlags(void* viewport)                        { return (int)((ImGuiViewport*)viewport)->Flags; }
IGSharp_Vec2 IGSharp_Viewport_GetPos(void* viewport)     { return FromImVec2(((ImGuiViewport*)viewport)->Pos); }
IGSharp_Vec2 IGSharp_Viewport_GetSize(void* viewport)    { return FromImVec2(((ImGuiViewport*)viewport)->Size); }
IGSharp_Vec2 IGSharp_Viewport_GetFramebufferScale(void* viewport)    { return FromImVec2(((ImGuiViewport*)viewport)->FramebufferScale); }
IGSharp_Vec2 IGSharp_Viewport_GetWorkPos(void* viewport) { return FromImVec2(((ImGuiViewport*)viewport)->WorkPos); }
IGSharp_Vec2 IGSharp_Viewport_GetWorkSize(void* viewport){ return FromImVec2(((ImGuiViewport*)viewport)->WorkSize); }
void* IGSharp_Viewport_GetPlatformHandle(void* viewport)             { return ((ImGuiViewport*)viewport)->PlatformHandle; }
void IGSharp_Viewport_SetPlatformHandle(void* viewport, void* handle){ ((ImGuiViewport*)viewport)->PlatformHandle = handle; }
void* IGSharp_Viewport_GetPlatformHandleRaw(void* viewport)          { return ((ImGuiViewport*)viewport)->PlatformHandleRaw; }
void IGSharp_Viewport_SetPlatformHandleRaw(void* viewport, void* handle){ ((ImGuiViewport*)viewport)->PlatformHandleRaw = handle; }
IGSharp_Vec2 IGSharp_Viewport_GetCenter(void* viewport)              { return FromImVec2(((ImGuiViewport*)viewport)->GetCenter()); }
IGSharp_Vec2 IGSharp_Viewport_GetWorkCenter(void* viewport)          { return FromImVec2(((ImGuiViewport*)viewport)->GetWorkCenter()); }

//-----------------------------------------------------------------------------
// [SECTION] Platform Dependent Interfaces
//-----------------------------------------------------------------------------

// Override setters for the platform handler function pointers.

void IGSharp_PlatformIO_SetPlatformGetClipboardTextFn(IGSharp_PlatformIO* pio, IGSharp_Platform_GetClipboardTextFn fn)
{ PIO(pio)->Platform_GetClipboardTextFn = reinterpret_cast<const char* (*)(ImGuiContext*)>(fn); }

void IGSharp_PlatformIO_SetPlatformSetClipboardTextFn(IGSharp_PlatformIO* pio, IGSharp_Platform_SetClipboardTextFn fn)
{ PIO(pio)->Platform_SetClipboardTextFn = reinterpret_cast<void (*)(ImGuiContext*, const char*)>(fn); }

void IGSharp_PlatformIO_SetPlatformOpenInShellFn(IGSharp_PlatformIO* pio, IGSharp_Platform_OpenInShellFn fn)
{ PIO(pio)->Platform_OpenInShellFn = reinterpret_cast<bool (*)(ImGuiContext*, const char*)>(fn); }

void IGSharp_PlatformIO_SetPlatformSetImeDataFn(IGSharp_PlatformIO* pio, IGSharp_Platform_SetImeDataFn fn)
{ PIO(pio)->Platform_SetImeDataFn = reinterpret_cast<void (*)(ImGuiContext*, ImGuiViewport*, ImGuiPlatformImeData*)>(fn); }

// User-data and scalar field accessors.

void*          IGSharp_PlatformIO_GetPlatformClipboardUserData(IGSharp_PlatformIO* pio)            { return PIO(pio)->Platform_ClipboardUserData; }
void           IGSharp_PlatformIO_SetPlatformClipboardUserData(IGSharp_PlatformIO* pio, void* ud)  { PIO(pio)->Platform_ClipboardUserData = ud; }
void*          IGSharp_PlatformIO_GetPlatformOpenInShellUserData(IGSharp_PlatformIO* pio)           { return PIO(pio)->Platform_OpenInShellUserData; }
void           IGSharp_PlatformIO_SetPlatformOpenInShellUserData(IGSharp_PlatformIO* pio, void* ud) { PIO(pio)->Platform_OpenInShellUserData = ud; }
void*          IGSharp_PlatformIO_GetPlatformImeUserData(IGSharp_PlatformIO* pio)                   { return PIO(pio)->Platform_ImeUserData; }
void           IGSharp_PlatformIO_SetPlatformImeUserData(IGSharp_PlatformIO* pio, void* ud)         { PIO(pio)->Platform_ImeUserData = ud; }
unsigned short IGSharp_PlatformIO_GetPlatformLocaleDecimalPoint(IGSharp_PlatformIO* pio)            { return (unsigned short)PIO(pio)->Platform_LocaleDecimalPoint; }
void           IGSharp_PlatformIO_SetPlatformLocaleDecimalPoint(IGSharp_PlatformIO* pio, unsigned short c) { PIO(pio)->Platform_LocaleDecimalPoint = (ImWchar)c; }
int            IGSharp_PlatformIO_GetRendererTextureMaxWidth(IGSharp_PlatformIO* pio)               { return PIO(pio)->Renderer_TextureMaxWidth; }
void           IGSharp_PlatformIO_SetRendererTextureMaxWidth(IGSharp_PlatformIO* pio, int v)        { PIO(pio)->Renderer_TextureMaxWidth = v; }
int            IGSharp_PlatformIO_GetRendererTextureMaxHeight(IGSharp_PlatformIO* pio)              { return PIO(pio)->Renderer_TextureMaxHeight; }
void           IGSharp_PlatformIO_SetRendererTextureMaxHeight(IGSharp_PlatformIO* pio, int v)       { PIO(pio)->Renderer_TextureMaxHeight = v; }
void*          IGSharp_PlatformIO_GetRendererRenderState(IGSharp_PlatformIO* pio)                   { return PIO(pio)->Renderer_RenderState; }
void           IGSharp_PlatformIO_SetRendererRenderState(IGSharp_PlatformIO* pio, void* rs)         { PIO(pio)->Renderer_RenderState = rs; }

// Textures list (ImVector<ImTextureData*>). Needed by a renderer backend to destroy textures at shutdown,

int            IGSharp_PlatformIO_GetTexturesCount(IGSharp_PlatformIO* pio)                         { return PIO(pio)->Textures.Size; }
void*          IGSharp_PlatformIO_GetTexture(IGSharp_PlatformIO* pio, int index)                    { return (void*)PIO(pio)->Textures[index]; }

// Member functions.

void IGSharp_PlatformIO_ClearPlatformHandlers(IGSharp_PlatformIO* pio) { PIO(pio)->ClearPlatformHandlers(); }
void IGSharp_PlatformIO_ClearRendererHandlers(IGSharp_PlatformIO* pio) { PIO(pio)->ClearRendererHandlers(); }
