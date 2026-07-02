// dear imgui sharp

/*

Index of this file:

// [SECTION] Header mess
// [SECTION] Forward declarations and basic types
// [SECTION] Texture identifiers (ImTextureID, ImTextureRef)
// [SECTION] Dear ImGui end-user API functions
// [SECTION] Flags & Enumerations
// [SECTION] Tables API flags and structures (ImGuiTableFlags, ImGuiTableColumnFlags, ImGuiTableRowFlags, ImGuiTableBgTarget, ImGuiTableSortSpecs, ImGuiTableColumnSortSpecs)
// [SECTION] Helpers: Debug log, memory allocations macros, ImVector<>
// [SECTION] ImGuiStyle
// [SECTION] ImGuiIO
// [SECTION] Misc data structures (ImGuiInputTextCallbackData, ImGuiSizeCallbackData, ImGuiPayload)
// [SECTION] Helpers (ImGuiOnceUponAFrame, ImGuiTextFilter, ImGuiTextBuffer, ImGuiStorage, ImGuiListClipper, Math Operators, ImColor)
// [SECTION] Multi-Select API flags and structures (ImGuiMultiSelectFlags, ImGuiSelectionRequestType, ImGuiSelectionRequest, ImGuiMultiSelectIO, ImGuiSelectionBasicStorage)
// [SECTION] Drawing API (ImDrawCmd, ImDrawIdx, ImDrawVert, ImDrawChannel, ImDrawListSplitter, ImDrawListFlags, ImDrawList, ImDrawData)
// [SECTION] Texture API (ImTextureFormat, ImTextureStatus, ImTextureRect, ImTextureData)
// [SECTION] Font API (ImFontConfig, ImFontGlyph, ImFontAtlasFlags, ImFontAtlas, ImFontGlyphRangesBuilder, ImFont)
// [SECTION] Viewports
// [SECTION] Platform Dependent Interfaces
// [SECTION] Obsolete functions and types

*/

#pragma once

//-----------------------------------------------------------------------------
// [SECTION] Header mess
//-----------------------------------------------------------------------------

#include <stddef.h>
#include <stdint.h>
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
typedef struct IGSharp_Context    IGSharp_Context;
typedef struct IGSharp_IO         IGSharp_IO;
typedef struct IGSharp_Style      IGSharp_Style;
typedef struct IGSharp_PlatformIO IGSharp_PlatformIO;

// Callback typedefs
typedef int   (*IGSharp_InputTextCallback)(void* data); // data = ImGuiInputTextCallbackData*
typedef void  (*IGSharp_SizeCallback)(void* data);      // data = ImGuiSizeCallbackData* (use IGSharp_SizeCallbackData_* accessors)
typedef void* (*IGSharp_MemAllocFunc)(size_t sz, void* user_data);
typedef void  (*IGSharp_MemFreeFunc)(void* ptr, void* user_data);

typedef struct {
    float x, y;
} IGSharp_Vec2;

typedef struct {
    float x, y, z, w;
} IGSharp_Vec4;

//-----------------------------------------------------------------------------
// [SECTION] Texture identifiers (ImTextureID, ImTextureRef)
//-----------------------------------------------------------------------------
// ImTextureID is the backend-specific low-level texture identifier (ImU64 by
// default). It is passed across this API as 'unsigned long long'; the width is
// pinned by a static_assert in imgui_sharp_layout_check.cpp.
//
// ImTextureRef carries EITHER an ImTextureID (user-provided texture) OR an
// ImTextureData* (a backend/atlas texture whose ImTextureID only becomes valid
// after the renderer uploads it). Converting a ref to an id before upload is
// lossy. This API keeps the two paths separate instead of mirroring the union:
//   - user textures: pass the ImTextureID via the 'unsigned long long tex_id'
//     parameters on IGSharp_Image*/IGSharp_DrawList_AddImage*/PushTexture.
//   - atlas/backend textures: obtain the ImTextureData* (e.g.
//     IGSharp_FontAtlas_GetTexData) and pass it to the *TextureData variants,
//     which preserve the indirection into the recorded draw command.

// Sentinel for "no texture" (mirror of ImTextureID_Invalid). Value pinned by a
// static_assert in imgui_sharp_layout_check.cpp.
#define IGSHARP_TEXTUREID_INVALID 0ULL

//-----------------------------------------------------------------------------
// [SECTION] Dear ImGui end-user API functions
// (Note that ImGui:: being a namespace, you can add extra ImGui:: functions in your own separate file. Please don't modify imgui source files!)
//-----------------------------------------------------------------------------

// Context creation and access
IGSHARP_API IGSharp_Context* IGSharp_CreateContext(void* shared_font_atlas); // shared_font_atlas: ImFontAtlas* (NULL = context creates & owns its own)
IGSHARP_API void             IGSharp_DestroyContext(IGSharp_Context* ctx);
IGSHARP_API IGSharp_Context* IGSharp_GetCurrentContext(void);
IGSHARP_API void             IGSharp_SetCurrentContext(IGSharp_Context* ctx);

// Main
IGSHARP_API IGSharp_IO*         IGSharp_GetIO(void);
IGSHARP_API IGSharp_PlatformIO* IGSharp_GetPlatformIO(void);
IGSHARP_API IGSharp_Style*      IGSharp_GetStyle(void);
IGSHARP_API void                IGSharp_NewFrame(void);
IGSHARP_API void                IGSharp_EndFrame(void);
IGSHARP_API void                IGSharp_Render(void);
IGSHARP_API void*               IGSharp_GetDrawData(void);

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
// dst (IGSharp_Style*, may be NULL == current style) selects which style the palette is written into.
IGSHARP_API void IGSharp_StyleColorsDark(IGSharp_Style* dst);
IGSHARP_API void IGSharp_StyleColorsLight(IGSharp_Style* dst);
IGSHARP_API void IGSharp_StyleColorsClassic(IGSharp_Style* dst);

// Windows
IGSHARP_API bool IGSharp_Begin(const char* name, bool* p_open, int flags);
IGSHARP_API void IGSharp_End(void);

// Child Windows
IGSHARP_API bool IGSharp_BeginChild(const char* str_id, IGSharp_Vec2 size, int child_flags, int window_flags);
IGSHARP_API bool IGSharp_BeginChildID(unsigned int id, IGSharp_Vec2 size, int child_flags, int window_flags);
IGSHARP_API void IGSharp_EndChild(void);

// Windows Utilities
IGSHARP_API bool         IGSharp_IsWindowAppearing(void);
IGSHARP_API bool         IGSharp_IsWindowCollapsed(void);
IGSHARP_API bool         IGSharp_IsWindowFocused(int flags);
IGSHARP_API bool         IGSharp_IsWindowHovered(int flags);
IGSHARP_API void* IGSharp_GetWindowDrawList(void);
IGSHARP_API IGSharp_Vec2 IGSharp_GetWindowPos(void);
IGSHARP_API IGSharp_Vec2 IGSharp_GetWindowSize(void);
IGSHARP_API float        IGSharp_GetWindowWidth(void);
IGSHARP_API float        IGSharp_GetWindowHeight(void);

// Window manipulation
IGSHARP_API void IGSharp_SetNextWindowPos(IGSharp_Vec2 pos, int cond, IGSharp_Vec2 pivot);
IGSHARP_API void IGSharp_SetNextWindowSize(IGSharp_Vec2 size, int cond);
IGSHARP_API void IGSharp_SetNextWindowSizeConstraints(IGSharp_Vec2 size_min, IGSharp_Vec2 size_max, IGSharp_SizeCallback custom_callback, void* custom_callback_data);
IGSHARP_API void IGSharp_SetNextWindowContentSize(IGSharp_Vec2 size);
IGSHARP_API void IGSharp_SetNextWindowCollapsed(bool collapsed, int cond);
IGSHARP_API void IGSharp_SetNextWindowFocus(void);
IGSHARP_API void IGSharp_SetNextWindowScroll(IGSharp_Vec2 scroll);
IGSHARP_API void IGSharp_SetNextWindowBgAlpha(float alpha);
IGSHARP_API void IGSharp_SetWindowPos(IGSharp_Vec2 pos, int cond);
IGSHARP_API void IGSharp_SetWindowSize(IGSharp_Vec2 size, int cond);
IGSHARP_API void IGSharp_SetWindowCollapsed(bool collapsed, int cond);
IGSHARP_API void IGSharp_SetWindowFocus(void);
IGSHARP_API void IGSharp_SetWindowPosNamed(const char* name, IGSharp_Vec2 pos, int cond);
IGSHARP_API void IGSharp_SetWindowSizeNamed(const char* name, IGSharp_Vec2 size, int cond);
IGSHARP_API void IGSharp_SetWindowCollapsedNamed(const char* name, bool collapsed, int cond);
IGSHARP_API void IGSharp_SetWindowFocusNamed(const char* name);

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
IGSHARP_API void* IGSharp_GetFontBaked(void);

// Parameters stacks (shared)
IGSHARP_API void IGSharp_PushStyleColorU32(int idx, unsigned int col);
IGSHARP_API void IGSharp_PushStyleColorVec4(int idx, IGSharp_Vec4 col);
IGSHARP_API void IGSharp_PopStyleColor(int count);
IGSHARP_API void IGSharp_PushStyleVarFloat(int idx, float val);
IGSHARP_API void IGSharp_PushStyleVarVec2(int idx, IGSharp_Vec2 val);
IGSHARP_API void IGSharp_PushStyleVarX(int idx, float val_x);
IGSHARP_API void IGSharp_PushStyleVarY(int idx, float val_y);
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
IGSHARP_API IGSharp_Vec2 IGSharp_GetFontTexUvWhitePixel(void);
IGSHARP_API unsigned int IGSharp_GetColorU32(int idx, float alpha_mul);
IGSHARP_API unsigned int IGSharp_GetColorU32Vec4(IGSharp_Vec4 col);
IGSHARP_API unsigned int IGSharp_GetColorU32Packed(unsigned int col, float alpha_mul);
IGSHARP_API IGSharp_Vec4 IGSharp_GetStyleColorVec4(int idx);

// Layout cursor positioning
IGSHARP_API IGSharp_Vec2 IGSharp_GetCursorScreenPos(void);
IGSHARP_API void         IGSharp_SetCursorScreenPos(IGSharp_Vec2 screen_pos);
IGSHARP_API IGSharp_Vec2 IGSharp_GetContentRegionAvail(void);
IGSHARP_API IGSharp_Vec2 IGSharp_GetCursorPos(void);
IGSHARP_API float        IGSharp_GetCursorPosX(void);
IGSHARP_API float        IGSharp_GetCursorPosY(void);
IGSHARP_API void         IGSharp_SetCursorPos(IGSharp_Vec2 local_pos);
IGSHARP_API void         IGSharp_SetCursorPosX(float local_x);
IGSHARP_API void         IGSharp_SetCursorPosY(float local_y);
IGSHARP_API IGSharp_Vec2 IGSharp_GetCursorStartPos(void);

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

// ID stack/scopes
IGSHARP_API void         IGSharp_PushIDStr(const char* str_id);
IGSHARP_API void         IGSharp_PushIDStrRange(const char* str_id_begin, const char* str_id_end);
IGSHARP_API void         IGSharp_PushIDPtr(const void* ptr_id);
IGSHARP_API void         IGSharp_PushIDInt(int int_id);
IGSHARP_API void         IGSharp_PopID(void);
IGSHARP_API unsigned int IGSharp_GetIDStr(const char* str_id);
IGSHARP_API unsigned int IGSharp_GetIDStrRange(const char* str_id_begin, const char* str_id_end);
IGSHARP_API unsigned int IGSharp_GetIDPtr(const void* ptr_id);
IGSHARP_API unsigned int IGSharp_GetIDInt(int int_id);

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
IGSHARP_API bool IGSharp_CheckboxFlags(const char* label, int* flags, int flags_value);
IGSHARP_API bool IGSharp_CheckboxFlagsUInt(const char* label, unsigned int* flags, unsigned int flags_value);
IGSHARP_API bool IGSharp_RadioButton(const char* label, bool active);
IGSHARP_API bool IGSharp_RadioButtonInt(const char* label, int* v, int v_button);
IGSHARP_API void IGSharp_ProgressBar(float fraction, IGSharp_Vec2 size_arg, const char* overlay);
IGSHARP_API void IGSharp_Bullet(void);
IGSHARP_API bool IGSharp_TextLink(const char* label);
IGSHARP_API bool IGSharp_TextLinkOpenURL(const char* label, const char* url);

// Widgets: Images
IGSHARP_API void IGSharp_Image(unsigned long long tex_id, IGSharp_Vec2 image_size, IGSharp_Vec2 uv0, IGSharp_Vec2 uv1);
IGSHARP_API void IGSharp_ImageWithBg(unsigned long long tex_id, IGSharp_Vec2 image_size, IGSharp_Vec2 uv0, IGSharp_Vec2 uv1, IGSharp_Vec4 bg_col, IGSharp_Vec4 tint_col);
IGSHARP_API bool IGSharp_ImageButton(const char* str_id, unsigned long long tex_id, IGSharp_Vec2 image_size, IGSharp_Vec2 uv0, IGSharp_Vec2 uv1, IGSharp_Vec4 bg_col, IGSharp_Vec4 tint_col);
// ImTextureData* variants: bind an atlas/backend texture (e.g. from IGSharp_FontAtlas_GetTexData)
// while preserving the deferred ImTextureID resolution (tex_data may be NULL == no texture).
IGSHARP_API void IGSharp_ImageTextureData(void* tex_data, IGSharp_Vec2 image_size, IGSharp_Vec2 uv0, IGSharp_Vec2 uv1);
IGSHARP_API void IGSharp_ImageWithBgTextureData(void* tex_data, IGSharp_Vec2 image_size, IGSharp_Vec2 uv0, IGSharp_Vec2 uv1, IGSharp_Vec4 bg_col, IGSharp_Vec4 tint_col);
IGSHARP_API bool IGSharp_ImageButtonTextureData(const char* str_id, void* tex_data, IGSharp_Vec2 image_size, IGSharp_Vec2 uv0, IGSharp_Vec2 uv1, IGSharp_Vec4 bg_col, IGSharp_Vec4 tint_col);

// Widgets: Combo Box (Dropdown)
IGSHARP_API bool IGSharp_BeginCombo(const char* label, const char* preview_value, int flags);
IGSHARP_API void IGSharp_EndCombo(void);
IGSHARP_API bool IGSharp_Combo(const char* label, int* current_item, const char* const items[], int items_count, int popup_max_height_in_items);
IGSHARP_API bool IGSharp_ComboStr(const char* label, int* current_item, const char* items_separated_by_zeros, int popup_max_height_in_items);
IGSHARP_API bool IGSharp_ComboCallback(const char* label, int* current_item, const char* (*getter)(void* user_data, int idx), void* user_data, int items_count, int popup_max_height_in_items);

// Widgets: Drag Sliders
IGSHARP_API bool IGSharp_DragFloat(const char* label, float* v, float v_speed, float v_min, float v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_DragFloat2(const char* label, float v[2], float v_speed, float v_min, float v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_DragFloat3(const char* label, float v[3], float v_speed, float v_min, float v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_DragFloat4(const char* label, float v[4], float v_speed, float v_min, float v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_DragFloatRange2(const char* label, float* v_current_min, float* v_current_max, float v_speed, float v_min, float v_max, const char* format, const char* format_max, int flags);
IGSHARP_API bool IGSharp_DragInt(const char* label, int* v, float v_speed, int v_min, int v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_DragInt2(const char* label, int v[2], float v_speed, int v_min, int v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_DragInt3(const char* label, int v[3], float v_speed, int v_min, int v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_DragInt4(const char* label, int v[4], float v_speed, int v_min, int v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_DragIntRange2(const char* label, int* v_current_min, int* v_current_max, float v_speed, int v_min, int v_max, const char* format, const char* format_max, int flags);
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
IGSHARP_API bool IGSharp_VSliderFloat(const char* label, IGSharp_Vec2 size, float* v, float v_min, float v_max, const char* format, int flags);
IGSHARP_API bool IGSharp_VSliderInt(const char* label, IGSharp_Vec2 size, int* v, int v_min, int v_max, const char* format, int flags);
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
IGSHARP_API void IGSharp_SetColorEditOptions(int flags); // flags = ImGuiColorEditFlags

// Widgets: Trees
IGSHARP_API bool  IGSharp_TreeNode(const char* label);
IGSHARP_API bool  IGSharp_TreeNodeStr(const char* str_id, const char* text);              // decorrelate id from displayed text
IGSHARP_API bool  IGSharp_TreeNodePtr(const void* ptr_id, const char* text);
IGSHARP_API bool  IGSharp_TreeNodeEx(const char* label, int flags);
IGSHARP_API bool  IGSharp_TreeNodeExStr(const char* str_id, int flags, const char* text);
IGSHARP_API bool  IGSharp_TreeNodeExPtr(const void* ptr_id, int flags, const char* text);
IGSHARP_API void IGSharp_TreePushStr(const char* str_id);
IGSHARP_API void IGSharp_TreePushPtr(const void* ptr_id);
IGSHARP_API void  IGSharp_TreePop(void);
IGSHARP_API float IGSharp_GetTreeNodeToLabelSpacing(void);
IGSHARP_API bool  IGSharp_CollapsingHeader(const char* label, int flags);
IGSHARP_API bool  IGSharp_CollapsingHeaderClosable(const char* label, bool* p_visible, int flags);
IGSHARP_API void  IGSharp_SetNextItemOpen(bool is_open, int cond);
IGSHARP_API void IGSharp_SetNextItemStorageID(unsigned int storage_id);
IGSHARP_API bool  IGSharp_TreeNodeGetOpen(unsigned int storage_id);

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
IGSHARP_API bool IGSharp_ListBox(const char* label, int* current_item, const char* const items[], int items_count, int height_in_items);
IGSHARP_API bool IGSharp_ListBoxCallback(const char* label, int* current_item, const char* (*getter)(void* user_data, int idx), void* user_data, int items_count, int height_in_items);

// Widgets: Data Plotting
IGSHARP_API void IGSharp_PlotLines(const char* label, const float* values, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, IGSharp_Vec2 graph_size, int stride);
IGSHARP_API void IGSharp_PlotLinesCallback(const char* label, float (*values_getter)(void* data, int idx), void* data, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, IGSharp_Vec2 graph_size);
IGSHARP_API void IGSharp_PlotHistogram(const char* label, const float* values, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, IGSharp_Vec2 graph_size, int stride);
IGSHARP_API void IGSharp_PlotHistogramCallback(const char* label, float (*values_getter)(void* data, int idx), void* data, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, IGSharp_Vec2 graph_size);

// Widgets: Value() Helpers. Output single value in "name: value" format
IGSHARP_API void IGSharp_ValueBool(const char* prefix, bool b);
IGSHARP_API void IGSharp_ValueInt(const char* prefix, int v);
IGSHARP_API void IGSharp_ValueUInt(const char* prefix, unsigned int v);
IGSHARP_API void IGSharp_ValueFloat(const char* prefix, float v, const char* float_format);

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
IGSHARP_API void IGSharp_SetItemTooltip(const char* text);

// Popups, Modals
IGSHARP_API bool IGSharp_BeginPopup(const char* str_id, int flags);
IGSHARP_API bool IGSharp_BeginPopupModal(const char* name, bool* p_open, int flags);
IGSHARP_API void IGSharp_EndPopup(void);

// Popups: open/close functions
IGSHARP_API void IGSharp_OpenPopup(const char* str_id, int popup_flags);
IGSHARP_API void IGSharp_OpenPopupID(unsigned int id, int popup_flags);
IGSHARP_API void IGSharp_OpenPopupOnItemClick(const char* str_id, int popup_flags);
IGSHARP_API void IGSharp_CloseCurrentPopup(void);

// Popups: Open+Begin popup combined functions helpers to create context menus.
IGSHARP_API bool IGSharp_BeginPopupContextItem(const char* str_id, int popup_flags);
IGSHARP_API bool IGSharp_BeginPopupContextWindow(const char* str_id, int popup_flags);
IGSHARP_API bool IGSharp_BeginPopupContextVoid(const char* str_id, int popup_flags);

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
IGSHARP_API void IGSharp_TableHeader(const char* label);
IGSHARP_API void IGSharp_TableHeadersRow(void);
IGSHARP_API void  IGSharp_TableAngledHeadersRow(void);

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

// Legacy Columns API (prefer using Tables!)
IGSHARP_API void  IGSharp_Columns(int count, const char* id, bool borders);
IGSHARP_API void  IGSharp_NextColumn(void);
IGSHARP_API int   IGSharp_GetColumnIndex(void);
IGSHARP_API float IGSharp_GetColumnWidth(int column_index);
IGSHARP_API void  IGSharp_SetColumnWidth(int column_index, float width);
IGSHARP_API float IGSharp_GetColumnOffset(int column_index);
IGSHARP_API void  IGSharp_SetColumnOffset(int column_index, float offset_x);
IGSHARP_API int   IGSharp_GetColumnsCount(void);

// Tab Bars, Tabs
IGSHARP_API bool IGSharp_BeginTabBar(const char* str_id, int flags);
IGSHARP_API void IGSharp_EndTabBar(void);
IGSHARP_API bool IGSharp_BeginTabItem(const char* label, bool* p_open, int flags);
IGSHARP_API void IGSharp_EndTabItem(void);
IGSHARP_API bool IGSharp_TabItemButton(const char* label, int flags);
IGSHARP_API void IGSharp_SetTabItemClosed(const char* tab_or_docked_window_label);

// Logging/Capture
// - All text output from the interface can be captured into tty/file/clipboard. By default, tree nodes are automatically opened during logging.
IGSHARP_API void IGSharp_LogToTTY(int auto_open_depth);
IGSHARP_API void IGSharp_LogToFile(int auto_open_depth, const char* filename);
IGSHARP_API void IGSharp_LogToClipboard(int auto_open_depth);
IGSHARP_API void IGSharp_LogFinish(void);
IGSHARP_API void IGSharp_LogButtons(void);
IGSHARP_API void IGSharp_LogText(const char* text);

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

// Clipping
IGSHARP_API void IGSharp_PushClipRect(IGSharp_Vec2 clip_rect_min, IGSharp_Vec2 clip_rect_max, bool intersect_with_current_clip_rect);
IGSHARP_API void IGSharp_PopClipRect(void);

// Focus, Activation
IGSHARP_API void IGSharp_SetItemDefaultFocus(void);
IGSHARP_API void IGSharp_SetKeyboardFocusHere(int offset);

// Keyboard/Gamepad Navigation
IGSHARP_API void IGSharp_SetNavCursorVisible(bool visible);

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
IGSHARP_API bool         IGSharp_IsAnyItemHovered(void);
IGSHARP_API bool         IGSharp_IsAnyItemActive(void);
IGSHARP_API bool         IGSharp_IsAnyItemFocused(void);
IGSHARP_API unsigned int IGSharp_GetItemID(void);
IGSHARP_API IGSharp_Vec2 IGSharp_GetItemRectMin(void);
IGSHARP_API IGSharp_Vec2 IGSharp_GetItemRectMax(void);
IGSHARP_API IGSharp_Vec2 IGSharp_GetItemRectSize(void);
IGSHARP_API int  IGSharp_GetItemFlags(void); // ImGuiItemFlags

// Viewports
IGSHARP_API void* IGSharp_GetMainViewport(void);

// Background/Foreground Draw Lists
IGSHARP_API void* IGSharp_GetBackgroundDrawList(void);
IGSHARP_API void* IGSharp_GetForegroundDrawList(void);

// Miscellaneous Utilities
IGSHARP_API bool         IGSharp_IsRectVisible(IGSharp_Vec2 size);
IGSHARP_API bool         IGSharp_IsRectVisibleRange(IGSharp_Vec2 rect_min, IGSharp_Vec2 rect_max);
IGSHARP_API double       IGSharp_GetTime(void);
IGSHARP_API int          IGSharp_GetFrameCount(void);
IGSHARP_API void*        IGSharp_GetDrawListSharedData(void);
IGSHARP_API const char*  IGSharp_GetStyleColorName(int idx);
IGSHARP_API void         IGSharp_SetStateStorage(void* storage);
IGSHARP_API void*        IGSharp_GetStateStorage(void);

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
IGSHARP_API int          IGSharp_GetKeyPressedAmount(int key, float repeat_delay, float rate);
IGSHARP_API const char*  IGSharp_GetKeyName(int key);
IGSHARP_API void         IGSharp_SetNextFrameWantCaptureKeyboard(bool want_capture_keyboard);

// Inputs Utilities: Shortcut Testing & Routing
IGSHARP_API bool         IGSharp_Shortcut(int key_chord, int flags);
IGSHARP_API void         IGSharp_SetNextItemShortcut(int key_chord, int flags);

// Inputs Utilities: Key/Input Ownership
IGSHARP_API void         IGSharp_SetItemKeyOwner(int key);

// Inputs Utilities: Mouse
IGSHARP_API bool         IGSharp_IsMouseDown(int button);
IGSHARP_API bool         IGSharp_IsMouseClicked(int button, bool repeat);
IGSHARP_API bool         IGSharp_IsMouseReleased(int button);
IGSHARP_API bool         IGSharp_IsMouseDoubleClicked(int button);
IGSHARP_API bool         IGSharp_IsMouseReleasedWithDelay(int button, float delay);
IGSHARP_API int          IGSharp_GetMouseClickedCount(int button);
IGSHARP_API bool         IGSharp_IsMouseHoveringRect(IGSharp_Vec2 r_min, IGSharp_Vec2 r_max, bool clip);
IGSHARP_API bool         IGSharp_IsMousePosValid(const IGSharp_Vec2* mouse_pos);
IGSHARP_API bool         IGSharp_IsAnyMouseDown(void);
IGSHARP_API IGSharp_Vec2 IGSharp_GetMousePos(void);
IGSHARP_API IGSharp_Vec2 IGSharp_GetMousePosOnOpeningCurrentPopup(void);
IGSHARP_API bool         IGSharp_IsMouseDragging(int button, float lock_threshold);
IGSHARP_API IGSharp_Vec2 IGSharp_GetMouseDragDelta(int button, float lock_threshold);
IGSHARP_API void         IGSharp_ResetMouseDragDelta(int button);
IGSHARP_API int          IGSharp_GetMouseCursor(void);
IGSHARP_API void         IGSharp_SetMouseCursor(int cursor_type);
IGSHARP_API void         IGSharp_SetNextFrameWantCaptureMouse(bool want_capture_mouse);

// Clipboard Utilities
IGSHARP_API const char* IGSharp_GetClipboardText(void);
IGSHARP_API void        IGSharp_SetClipboardText(const char* text);

// Settings/.Ini Utilities
IGSHARP_API void        IGSharp_LoadIniSettingsFromDisk(const char* ini_filename);
IGSHARP_API void        IGSharp_LoadIniSettingsFromMemory(const char* ini_data, size_t ini_size);
IGSHARP_API void        IGSharp_SaveIniSettingsToDisk(const char* ini_filename);
IGSHARP_API const char* IGSharp_SaveIniSettingsToMemory(size_t* out_ini_size);

// Debug Utilities
IGSHARP_API void        IGSharp_DebugTextEncoding(const char* text);
IGSHARP_API void        IGSharp_DebugFlashStyleColor(int idx); // ImGuiCol
IGSHARP_API void        IGSharp_DebugStartItemPicker(void);
IGSHARP_API bool        IGSharp_DebugCheckVersionAndDataLayout(const char* version_str, size_t sz_io, size_t sz_style, size_t sz_vec2, size_t sz_vec4, size_t sz_drawvert, size_t sz_drawidx);
IGSHARP_API void        IGSharp_DebugLog(const char* text);

// Memory Allocators (see IGSharp_MemAllocFunc/IGSharp_MemFreeFunc typedefs in the forward declarations section)
IGSHARP_API void        IGSharp_SetAllocatorFunctions(IGSharp_MemAllocFunc alloc_func, IGSharp_MemFreeFunc free_func, void* user_data);
IGSHARP_API void        IGSharp_GetAllocatorFunctions(IGSharp_MemAllocFunc* p_alloc_func, IGSharp_MemFreeFunc* p_free_func, void** p_user_data);
IGSHARP_API void*       IGSharp_MemAlloc(size_t size);
IGSHARP_API void        IGSharp_MemFree(void* ptr);

//-----------------------------------------------------------------------------
// [SECTION] Flags & Enumerations
//-----------------------------------------------------------------------------

// Mirrored from upstream Dear ImGui. Values must match upstream exactly —
// validated per-value by static_assert in imgui_sharp_layout_check.cpp.
// Used as array sizes in IGSharp_IO.KeysData and IGSharp_Style.Colors below,
// and exposed so consumers don't need to redefine these enums independently.

// IGSharp_WindowFlags
// Mirrored from upstream ImGuiWindowFlags_. Flags for Begin(), BeginChild().
// Values must match upstream exactly — validated per-value by static_assert in
// imgui_sharp_layout_check.cpp. Passed to functions as plain 'int'.
typedef enum {
    IGSharp_WindowFlags_None                      = 0,
    IGSharp_WindowFlags_NoTitleBar                = 1 << 0,   // Disable title-bar
    IGSharp_WindowFlags_NoResize                  = 1 << 1,   // Disable user resizing with the lower-right grip
    IGSharp_WindowFlags_NoMove                    = 1 << 2,   // Disable user moving the window
    IGSharp_WindowFlags_NoScrollbar               = 1 << 3,   // Disable scrollbars (window can still scroll with mouse or programmatically)
    IGSharp_WindowFlags_NoScrollWithMouse         = 1 << 4,   // Disable user vertically scrolling with mouse wheel. On child window, mouse wheel will be forwarded to the parent unless NoScrollbar is also set.
    IGSharp_WindowFlags_NoCollapse                = 1 << 5,   // Disable user collapsing window by double-clicking on it. Also referred to as Window Menu Button (e.g. within a docking node).
    IGSharp_WindowFlags_AlwaysAutoResize          = 1 << 6,   // Resize every window to its content every frame
    IGSharp_WindowFlags_NoBackground              = 1 << 7,   // Disable drawing background color (WindowBg, etc.) and outside border. Similar as using SetNextWindowBgAlpha(0.0f).
    IGSharp_WindowFlags_NoSavedSettings           = 1 << 8,   // Never load/save settings in .ini file
    IGSharp_WindowFlags_NoMouseInputs             = 1 << 9,   // Disable catching mouse, hovering test with pass through.
    IGSharp_WindowFlags_MenuBar                   = 1 << 10,  // Has a menu-bar
    IGSharp_WindowFlags_HorizontalScrollbar       = 1 << 11,  // Allow horizontal scrollbar to appear (off by default).
    IGSharp_WindowFlags_NoFocusOnAppearing        = 1 << 12,  // Disable taking focus when transitioning from hidden to visible state
    IGSharp_WindowFlags_NoBringToFrontOnFocus     = 1 << 13,  // Disable bringing window to front when taking focus (e.g. clicking on it or programmatically giving it focus)
    IGSharp_WindowFlags_AlwaysVerticalScrollbar   = 1 << 14,  // Always show vertical scrollbar (even if ContentSize.y < Size.y)
    IGSharp_WindowFlags_AlwaysHorizontalScrollbar = 1 << 15,  // Always show horizontal scrollbar (even if ContentSize.x < Size.x)
    IGSharp_WindowFlags_NoNavInputs               = 1 << 16,  // No keyboard/gamepad navigation within the window
    IGSharp_WindowFlags_NoNavFocus                = 1 << 17,  // No focusing toward this window with keyboard/gamepad navigation (e.g. skipped by Ctrl+Tab)
    IGSharp_WindowFlags_UnsavedDocument           = 1 << 18,  // Display a dot next to the title.
    IGSharp_WindowFlags_NoNav                     = IGSharp_WindowFlags_NoNavInputs | IGSharp_WindowFlags_NoNavFocus,
    IGSharp_WindowFlags_NoDecoration              = IGSharp_WindowFlags_NoTitleBar | IGSharp_WindowFlags_NoResize | IGSharp_WindowFlags_NoScrollbar | IGSharp_WindowFlags_NoCollapse,
    IGSharp_WindowFlags_NoInputs                  = IGSharp_WindowFlags_NoMouseInputs | IGSharp_WindowFlags_NoNavInputs | IGSharp_WindowFlags_NoNavFocus,

    // [Internal]
    IGSharp_WindowFlags_ChildWindow               = 1 << 24,  // Don't use! For internal use by BeginChild()
    IGSharp_WindowFlags_Tooltip                   = 1 << 25,  // Don't use! For internal use by BeginTooltip()
    IGSharp_WindowFlags_Popup                     = 1 << 26,  // Don't use! For internal use by BeginPopup()
    IGSharp_WindowFlags_Modal                     = 1 << 27,  // Don't use! For internal use by BeginPopupModal()
    IGSharp_WindowFlags_ChildMenu                 = 1 << 28,  // Don't use! For internal use by BeginMenu()
} IGSharp_WindowFlags;

// IGSharp_ChildFlags
// Flags for ImGui::BeginChild() (-> IGSharp_BeginChild()).
// Mirrored from upstream ImGuiChildFlags_; values validated per-value in imgui_sharp_layout_check.cpp.
// (Obsolete alias ImGuiChildFlags_Border is intentionally omitted.)
typedef enum {
    IGSharp_ChildFlags_None                   = 0,
    IGSharp_ChildFlags_Borders                = 1 << 0,   // Show an outer border and enable WindowPadding. (always == 1 == true for legacy reason)
    IGSharp_ChildFlags_AlwaysUseWindowPadding = 1 << 1,   // Pad with style.WindowPadding even if no border are drawn
    IGSharp_ChildFlags_ResizeX                = 1 << 2,   // Allow resize from right border (layout direction)
    IGSharp_ChildFlags_ResizeY                = 1 << 3,   // Allow resize from bottom border (layout direction)
    IGSharp_ChildFlags_AutoResizeX            = 1 << 4,   // Enable auto-resizing width
    IGSharp_ChildFlags_AutoResizeY            = 1 << 5,   // Enable auto-resizing height
    IGSharp_ChildFlags_AlwaysAutoResize       = 1 << 6,   // Combined with AutoResizeX/AutoResizeY, always measure size even when child is hidden
    IGSharp_ChildFlags_FrameStyle             = 1 << 7,   // Style the child window like a framed item
    IGSharp_ChildFlags_NavFlattened           = 1 << 8,   // [BETA] Share focus scope, allow nav to cross over parent border
} IGSharp_ChildFlags;

// IGSharp_ItemFlags
// Mirrored from upstream Dear ImGui (enum ImGuiItemFlags_). Values must match
// upstream exactly — validated per-value by static_assert in imgui_sharp_layout_check.cpp.
// Flags: for PushItemFlag(), shared by all items. Passed to/returned from functions as plain int.
typedef enum {
    IGSharp_ItemFlags_None                 = 0,
    IGSharp_ItemFlags_NoTabStop            = 1 << 0,   // Disable keyboard tabbing.
    IGSharp_ItemFlags_NoNav                = 1 << 1,   // Disable any form of focusing (keyboard/gamepad directional navigation and SetKeyboardFocusHere() calls).
    IGSharp_ItemFlags_NoNavDefaultFocus    = 1 << 2,   // Disable item being a candidate for default focus (e.g. used by title bar items).
    IGSharp_ItemFlags_ButtonRepeat         = 1 << 3,   // Any button-like behavior will have repeat mode enabled.
    IGSharp_ItemFlags_AutoClosePopups      = 1 << 4,   // MenuItem()/Selectable() automatically close their parent popup window.
    IGSharp_ItemFlags_AllowDuplicateId     = 1 << 5,   // Allow submitting an item with the same identifier as an item already submitted this frame without triggering a warning tooltip.
    IGSharp_ItemFlags_Disabled             = 1 << 6,   // Disable interactions. Used by BeginDisabled()/EndDisabled(); read back via GetItemFlags().
} IGSharp_ItemFlags;

// IGSharp_InputTextFlags
// Flags for InputText(), InputTextMultiline(), InputTextWithHint().
// Mirrored from upstream ImGuiInputTextFlags_; values must match exactly —
// validated per-value by static_assert in imgui_sharp_layout_check.cpp.
// Passed to functions as plain int (see ImGuiInputTextFlags alias below).
typedef enum {
    IGSharp_InputTextFlags_None                = 0,
    // Basic filters (also see IGSharp_InputTextFlags_CallbackCharFilter)
    IGSharp_InputTextFlags_CharsDecimal        = 1 << 0,   // Allow 0123456789.+-*/
    IGSharp_InputTextFlags_CharsHexadecimal    = 1 << 1,   // Allow 0123456789ABCDEFabcdef
    IGSharp_InputTextFlags_CharsScientific     = 1 << 2,   // Allow 0123456789.+-*/eE (Scientific notation input)
    IGSharp_InputTextFlags_CharsUppercase      = 1 << 3,   // Turn a..z into A..Z
    IGSharp_InputTextFlags_CharsNoBlank        = 1 << 4,   // Filter out spaces, tabs
    // Inputs
    IGSharp_InputTextFlags_AllowTabInput       = 1 << 5,   // Pressing TAB input a '\t' character into the text field
    IGSharp_InputTextFlags_EnterReturnsTrue    = 1 << 6,   // Return 'true' when Enter is pressed (as opposed to every time the value was modified)
    IGSharp_InputTextFlags_EscapeClearsAll     = 1 << 7,   // Escape key clears content if not empty, and deactivate otherwise
    IGSharp_InputTextFlags_CtrlEnterForNewLine = 1 << 8,   // In multi-line mode: validate with Enter, add new line with Ctrl+Enter
    // Other options
    IGSharp_InputTextFlags_ReadOnly            = 1 << 9,   // Read-only mode
    IGSharp_InputTextFlags_Password            = 1 << 10,  // Password mode, display all characters as '*', disable copy
    IGSharp_InputTextFlags_AlwaysOverwrite     = 1 << 11,  // Overwrite mode
    IGSharp_InputTextFlags_AutoSelectAll       = 1 << 12,  // Select entire text when first taking mouse focus
    IGSharp_InputTextFlags_ParseEmptyRefVal    = 1 << 13,  // InputFloat(), InputInt(), InputScalar() etc. only: parse empty string as zero value
    IGSharp_InputTextFlags_DisplayEmptyRefVal  = 1 << 14,  // InputFloat(), InputInt(), InputScalar() etc. only: when value is zero, do not display it
    IGSharp_InputTextFlags_NoHorizontalScroll  = 1 << 15,  // Disable following the cursor horizontally
    IGSharp_InputTextFlags_NoUndoRedo          = 1 << 16,  // Disable undo/redo
    IGSharp_InputTextFlags_ElideLeft           = 1 << 17,  // When text doesn't fit, elide left side to ensure right side stays visible. Single-line only!
    // Callback features
    IGSharp_InputTextFlags_CallbackCompletion  = 1 << 18,  // Callback on pressing TAB (for completion handling)
    IGSharp_InputTextFlags_CallbackHistory     = 1 << 19,  // Callback on pressing Up/Down arrows (for history handling)
    IGSharp_InputTextFlags_CallbackAlways      = 1 << 20,  // Callback on each iteration
    IGSharp_InputTextFlags_CallbackCharFilter  = 1 << 21,  // Callback on character inputs to replace or discard them
    IGSharp_InputTextFlags_CallbackResize      = 1 << 22,  // Callback on buffer capacity changes request
    IGSharp_InputTextFlags_CallbackEdit        = 1 << 23,  // Callback on any edit
    IGSharp_InputTextFlags_WordWrap            = 1 << 24,  // InputTextMultiline(): word-wrap lines that are too long
} IGSharp_InputTextFlags_;

// IGSharp_TreeNodeFlags
// Flags for ImGui::TreeNodeEx(), ImGui::CollapsingHeader() etc.
// Mirrored from upstream ImGuiTreeNodeFlags_ — values validated per-value by
// static_assert in imgui_sharp_layout_check.cpp.
typedef enum {
    IGSharp_TreeNodeFlags_None                 = 0,
    IGSharp_TreeNodeFlags_Selected             = 1 << 0,   // Draw as selected
    IGSharp_TreeNodeFlags_Framed               = 1 << 1,   // Draw frame with background (e.g. for CollapsingHeader)
    IGSharp_TreeNodeFlags_AllowOverlap         = 1 << 2,   // Hit testing will allow subsequent widgets to overlap this one
    IGSharp_TreeNodeFlags_NoTreePushOnOpen     = 1 << 3,   // Don't do a TreePush() when open (e.g. for CollapsingHeader)
    IGSharp_TreeNodeFlags_NoAutoOpenOnLog      = 1 << 4,   // Don't automatically and temporarily open node when Logging is active
    IGSharp_TreeNodeFlags_DefaultOpen          = 1 << 5,   // Default node to be open
    IGSharp_TreeNodeFlags_OpenOnDoubleClick    = 1 << 6,   // Open on double-click instead of simple click
    IGSharp_TreeNodeFlags_OpenOnArrow          = 1 << 7,   // Open when clicking on the arrow part
    IGSharp_TreeNodeFlags_Leaf                 = 1 << 8,   // No collapsing, no arrow (use as a convenience for leaf nodes)
    IGSharp_TreeNodeFlags_Bullet               = 1 << 9,   // Display a bullet instead of arrow
    IGSharp_TreeNodeFlags_FramePadding         = 1 << 10,  // Use FramePadding to vertically align text baseline to regular widget height
    IGSharp_TreeNodeFlags_SpanAvailWidth       = 1 << 11,  // Extend hit box to the right-most edge, even if not framed
    IGSharp_TreeNodeFlags_SpanFullWidth        = 1 << 12,  // Extend hit box to the left-most and right-most edges
    IGSharp_TreeNodeFlags_SpanLabelWidth       = 1 << 13,  // Narrow hit box + narrow hovering highlight, will only cover the label text
    IGSharp_TreeNodeFlags_SpanAllColumns       = 1 << 14,  // Frame will span all columns of its container table
    IGSharp_TreeNodeFlags_LabelSpanAllColumns  = 1 << 15,  // Label will span all columns of its container table
    IGSharp_TreeNodeFlags_NavLeftJumpsToParent = 1 << 17,  // Nav: left arrow moves back to parent
    IGSharp_TreeNodeFlags_CollapsingHeader     = IGSharp_TreeNodeFlags_Framed | IGSharp_TreeNodeFlags_NoTreePushOnOpen | IGSharp_TreeNodeFlags_NoAutoOpenOnLog,
    IGSharp_TreeNodeFlags_DrawLinesNone        = 1 << 18,  // No lines drawn
    IGSharp_TreeNodeFlags_DrawLinesFull        = 1 << 19,  // Horizontal lines to child nodes, vertical line covers full contents
    IGSharp_TreeNodeFlags_DrawLinesToNodes     = 1 << 20,  // Horizontal lines to child nodes, vertical line down to bottom-most child node
} IGSharp_TreeNodeFlags;

// IGSharp_PopupFlags
// Flags for OpenPopup*(), BeginPopupContext*(), IsPopupOpen() -> ImGuiPopupFlags_
typedef enum {
    IGSharp_PopupFlags_None                    = 0,
    IGSharp_PopupFlags_MouseButtonLeft         = 1 << 2,   // For BeginPopupContext*(): open on Left Mouse release. Only one button allowed!
    IGSharp_PopupFlags_MouseButtonRight        = 2 << 2,   // For BeginPopupContext*(): open on Right Mouse release. Only one button allowed! (default)
    IGSharp_PopupFlags_MouseButtonMiddle       = 3 << 2,   // For BeginPopupContext*(): open on Middle Mouse release. Only one button allowed!
    IGSharp_PopupFlags_NoReopen                = 1 << 5,   // For OpenPopup*(), BeginPopupContext*(): don't reopen same popup if already open (won't reposition, won't reinitialize navigation)
    IGSharp_PopupFlags_NoOpenOverExistingPopup = 1 << 7,   // For OpenPopup*(), BeginPopupContext*(): don't open if there's already a popup at the same level of the popup stack
    IGSharp_PopupFlags_NoOpenOverItems         = 1 << 8,   // For BeginPopupContextWindow(): don't return true when hovering items, only when hovering empty space
    IGSharp_PopupFlags_AnyPopupId              = 1 << 10,  // For IsPopupOpen(): ignore the ImGuiID parameter and test for any popup.
    IGSharp_PopupFlags_AnyPopupLevel           = 1 << 11,  // For IsPopupOpen(): search/test at any level of the popup stack (default test in the current level)
    IGSharp_PopupFlags_AnyPopup                = IGSharp_PopupFlags_AnyPopupId | IGSharp_PopupFlags_AnyPopupLevel,
    IGSharp_PopupFlags_MouseButtonShift_       = 2,        // [Internal]
    IGSharp_PopupFlags_MouseButtonMask_        = 0x0C,     // [Internal]
    IGSharp_PopupFlags_InvalidMask_            = 0x03,     // [Internal] Reserve legacy bits 0-1 to detect incorrectly passing 1 or 2 to the function.
} IGSharp_PopupFlags;

// IGSharp_SelectableFlags
// Flags for Selectable(). Mirror of ImGuiSelectableFlags_ — passed to functions as plain int.
// Values validated per-value by static_assert in imgui_sharp_layout_check.cpp.
typedef enum {
    IGSharp_SelectableFlags_None              = 0,
    IGSharp_SelectableFlags_NoAutoClosePopups = 1 << 0,   // Clicking this doesn't close parent popup window (overrides ImGuiItemFlags_AutoClosePopups)
    IGSharp_SelectableFlags_SpanAllColumns    = 1 << 1,   // Frame will span all columns of its container table (text will still fit in current column)
    IGSharp_SelectableFlags_AllowDoubleClick  = 1 << 2,   // Generate press events on double clicks too
    IGSharp_SelectableFlags_Disabled          = 1 << 3,   // Cannot be selected, display grayed out text
    IGSharp_SelectableFlags_AllowOverlap      = 1 << 4,   // Hit testing will allow subsequent widgets to overlap this one
    IGSharp_SelectableFlags_Highlight         = 1 << 5,   // Make the item be displayed as if it is hovered
    IGSharp_SelectableFlags_SelectOnNav       = 1 << 6,   // Auto-select when moved into, unless Ctrl is held
} IGSharp_SelectableFlags;

// IGSharp_ComboFlags
typedef enum {
    IGSharp_ComboFlags_None                    = 0,
    IGSharp_ComboFlags_PopupAlignLeft          = 1 << 0,   // Align the popup toward the left by default
    IGSharp_ComboFlags_HeightSmall             = 1 << 1,   // Max ~4 items visible. Tip: If you want your combo popup to be a specific size you can use SetNextWindowSizeConstraints() prior to calling BeginCombo()
    IGSharp_ComboFlags_HeightRegular           = 1 << 2,   // Max ~8 items visible (default)
    IGSharp_ComboFlags_HeightLarge             = 1 << 3,   // Max ~20 items visible
    IGSharp_ComboFlags_HeightLargest           = 1 << 4,   // As many fitting items as possible
    IGSharp_ComboFlags_NoArrowButton           = 1 << 5,   // Display on the preview box without the square arrow button
    IGSharp_ComboFlags_NoPreview               = 1 << 6,   // Display only a square arrow button
    IGSharp_ComboFlags_WidthFitPreview         = 1 << 7,   // Width dynamically calculated from preview contents
    IGSharp_ComboFlags_HeightMask_             = IGSharp_ComboFlags_HeightSmall | IGSharp_ComboFlags_HeightRegular | IGSharp_ComboFlags_HeightLarge | IGSharp_ComboFlags_HeightLargest,
} IGSharp_ComboFlags;

// IGSharp_TabBarFlags
// Flags for IGSharp_BeginTabBar(). Mirrors upstream ImGuiTabBarFlags_.
// Validated per-value by static_assert in imgui_sharp_layout_check.cpp.
typedef enum {
    IGSharp_TabBarFlags_None                          = 0,
    IGSharp_TabBarFlags_Reorderable                   = 1 << 0,   // Allow manually dragging tabs to re-order them + New tabs are appended at the end of list
    IGSharp_TabBarFlags_AutoSelectNewTabs             = 1 << 1,   // Automatically select new tabs when they appear
    IGSharp_TabBarFlags_TabListPopupButton            = 1 << 2,   // Disable buttons to open the tab list popup
    IGSharp_TabBarFlags_NoCloseWithMiddleMouseButton  = 1 << 3,   // Disable behavior of closing tabs (that are submitted with p_open != NULL) with middle mouse button.
    IGSharp_TabBarFlags_NoTabListScrollingButtons     = 1 << 4,   // Disable scrolling buttons (apply when fitting policy is IGSharp_TabBarFlags_FittingPolicyScroll)
    IGSharp_TabBarFlags_NoTooltip                     = 1 << 5,   // Disable tooltips when hovering a tab
    IGSharp_TabBarFlags_DrawSelectedOverline          = 1 << 6,   // Draw selected overline markers over selected tab
    IGSharp_TabBarFlags_FittingPolicyMixed            = 1 << 7,   // Shrink down tabs when they don't fit, until width is style.TabMinWidthShrink, then enable scrolling buttons.
    IGSharp_TabBarFlags_FittingPolicyShrink           = 1 << 8,   // Shrink down tabs when they don't fit
    IGSharp_TabBarFlags_FittingPolicyScroll           = 1 << 9,   // Enable scrolling buttons when tabs don't fit
    IGSharp_TabBarFlags_FittingPolicyMask_            = IGSharp_TabBarFlags_FittingPolicyMixed | IGSharp_TabBarFlags_FittingPolicyShrink | IGSharp_TabBarFlags_FittingPolicyScroll,
    IGSharp_TabBarFlags_FittingPolicyDefault_         = IGSharp_TabBarFlags_FittingPolicyMixed,
} IGSharp_TabBarFlags;

// IGSharp_TabItemFlags
// Flags for IGSharp_BeginTabItem() / IGSharp_TabItemButton().
// Mirrored from upstream ImGuiTabItemFlags_ — values validated per-value by
// static_assert in imgui_sharp_layout_check.cpp.
typedef enum {
    IGSharp_TabItemFlags_None                         = 0,
    IGSharp_TabItemFlags_UnsavedDocument              = 1 << 0,
    IGSharp_TabItemFlags_SetSelected                  = 1 << 1,
    IGSharp_TabItemFlags_NoCloseWithMiddleMouseButton = 1 << 2,
    IGSharp_TabItemFlags_NoPushId                     = 1 << 3,
    IGSharp_TabItemFlags_NoTooltip                    = 1 << 4,
    IGSharp_TabItemFlags_NoReorder                    = 1 << 5,
    IGSharp_TabItemFlags_Leading                      = 1 << 6,
    IGSharp_TabItemFlags_Trailing                     = 1 << 7,
    IGSharp_TabItemFlags_NoAssumedClosure             = 1 << 8,
} IGSharp_TabItemFlags;

// IGSharp_FocusedFlags
// Flags for IsWindowFocused(). Mirrored from upstream ImGuiFocusedFlags_.
// (Docking-only ImGuiFocusedFlags_DockHierarchy intentionally omitted — not on this branch.)
typedef enum {
    IGSharp_FocusedFlags_None                  = 0,
    IGSharp_FocusedFlags_ChildWindows          = 1 << 0,   // Return true if any children of the window is focused
    IGSharp_FocusedFlags_RootWindow            = 1 << 1,   // Test from root window (top most parent of the current hierarchy)
    IGSharp_FocusedFlags_AnyWindow             = 1 << 2,   // Return true if any window is focused. Important: If you are trying to tell how to dispatch your low-level inputs, do NOT use this. Use 'io.WantCaptureMouse' instead! Please read the FAQ!
    IGSharp_FocusedFlags_NoPopupHierarchy      = 1 << 3,   // Do not consider popup hierarchy (do not treat popup emitter as parent of popup) (when used with _ChildWindows or _RootWindow)
    IGSharp_FocusedFlags_RootAndChildWindows   = IGSharp_FocusedFlags_RootWindow | IGSharp_FocusedFlags_ChildWindows,
} IGSharp_FocusedFlags;

// IGSharp_HoveredFlags
typedef enum {
    IGSharp_HoveredFlags_None                          = 0,        // Return true if directly over the item/window, not obstructed by another window, not obstructed by an active popup or modal blocking inputs under them.
    IGSharp_HoveredFlags_ChildWindows                  = 1 << 0,   // IsWindowHovered() only: Return true if any children of the window is hovered
    IGSharp_HoveredFlags_RootWindow                    = 1 << 1,   // IsWindowHovered() only: Test from root window (top most parent of the current hierarchy)
    IGSharp_HoveredFlags_AnyWindow                     = 1 << 2,   // IsWindowHovered() only: Return true if any window is hovered
    IGSharp_HoveredFlags_NoPopupHierarchy              = 1 << 3,   // IsWindowHovered() only: Do not consider popup hierarchy (do not treat popup emitter as parent of popup) (when used with _ChildWindows or _RootWindow)
    IGSharp_HoveredFlags_AllowWhenBlockedByPopup       = 1 << 5,   // Return true even if a popup window is normally blocking access to this item/window
    IGSharp_HoveredFlags_AllowWhenBlockedByActiveItem  = 1 << 7,   // Return true even if an active item is blocking access to this item/window. Useful for Drag and Drop patterns.
    IGSharp_HoveredFlags_AllowWhenOverlappedByItem     = 1 << 8,   // IsItemHovered() only: Return true even if the item uses AllowOverlap mode and is overlapped by another hoverable item.
    IGSharp_HoveredFlags_AllowWhenOverlappedByWindow   = 1 << 9,   // IsItemHovered() only: Return true even if the position is obstructed or overlapped by another window.
    IGSharp_HoveredFlags_AllowWhenDisabled             = 1 << 10,  // IsItemHovered() only: Return true even if the item is disabled
    IGSharp_HoveredFlags_NoNavOverride                 = 1 << 11,  // IsItemHovered() only: Disable using keyboard/gamepad navigation state when active, always query mouse
    IGSharp_HoveredFlags_AllowWhenOverlapped           = IGSharp_HoveredFlags_AllowWhenOverlappedByItem | IGSharp_HoveredFlags_AllowWhenOverlappedByWindow,
    IGSharp_HoveredFlags_RectOnly                      = IGSharp_HoveredFlags_AllowWhenBlockedByPopup | IGSharp_HoveredFlags_AllowWhenBlockedByActiveItem | IGSharp_HoveredFlags_AllowWhenOverlapped,
    IGSharp_HoveredFlags_RootAndChildWindows           = IGSharp_HoveredFlags_RootWindow | IGSharp_HoveredFlags_ChildWindows,
    IGSharp_HoveredFlags_ForTooltip                    = 1 << 12,  // Shortcut for standard flags when using IsItemHovered() + SetTooltip() sequence.
    IGSharp_HoveredFlags_Stationary                    = 1 << 13,  // Require mouse to be stationary for style.HoverStationaryDelay (~0.15 sec) _at least one time_. After this, can move on same item/window. Using the stationary test tends to reduces the need for a long delay.
    IGSharp_HoveredFlags_DelayNone                     = 1 << 14,  // IsItemHovered() only: Return true immediately (default). As this is the default you generally ignore this.
    IGSharp_HoveredFlags_DelayShort                    = 1 << 15,  // IsItemHovered() only: Return true after style.HoverDelayShort elapsed (~0.15 sec) (shared between items) + requires mouse to be stationary for style.HoverStationaryDelay (once per item).
    IGSharp_HoveredFlags_DelayNormal                   = 1 << 16,  // IsItemHovered() only: Return true after style.HoverDelayNormal elapsed (~0.40 sec) (shared between items) + requires mouse to be stationary for style.HoverStationaryDelay (once per item).
    IGSharp_HoveredFlags_NoSharedDelay                 = 1 << 17,  // IsItemHovered() only: Disable shared delay system where moving from one item to the next keeps the previous timer for a short time (standard for tooltips with long delays)
} IGSharp_HoveredFlags;

// IGSharp_DragDropFlags
// Flags for BeginDragDropSource(), AcceptDragDropPayload() (mirrors ImGuiDragDropFlags_)
typedef enum {
    IGSharp_DragDropFlags_None                     = 0,
    // BeginDragDropSource() flags
    IGSharp_DragDropFlags_SourceNoPreviewTooltip   = 1 << 0,   // Disable preview tooltip. By default, a successful call to BeginDragDropSource opens a tooltip so you can display a preview or description of the source contents. This flag disables this behavior.
    IGSharp_DragDropFlags_SourceNoDisableHover     = 1 << 1,   // By default, when dragging we clear data so that IsItemHovered() will return false, to avoid subsequent user code submitting tooltips. This flag disables this behavior so you can still call IsItemHovered() on the source item.
    IGSharp_DragDropFlags_SourceNoHoldToOpenOthers = 1 << 2,   // Disable the behavior that allows to open tree nodes and collapsing header by holding over them while dragging a source item.
    IGSharp_DragDropFlags_SourceAllowNullID        = 1 << 3,   // Allow items such as Text(), Image() that have no unique identifier to be used as drag source, by manufacturing a temporary identifier based on their window-relative position. This is extremely unusual within the dear imgui ecosystem and so we made it explicit.
    IGSharp_DragDropFlags_SourceExtern             = 1 << 4,   // External source (from outside of dear imgui), won't attempt to read current item/window info. Will always return true. Only one Extern source can be active simultaneously.
    IGSharp_DragDropFlags_PayloadAutoExpire        = 1 << 5,   // Automatically expire the payload if the source cease to be submitted (otherwise payloads are persisting while being dragged)
    IGSharp_DragDropFlags_PayloadNoCrossContext    = 1 << 6,   // Hint to specify that the payload may not be copied outside current dear imgui context.
    IGSharp_DragDropFlags_PayloadNoCrossProcess    = 1 << 7,   // Hint to specify that the payload may not be copied outside current process.
    // AcceptDragDropPayload() flags
    IGSharp_DragDropFlags_AcceptBeforeDelivery     = 1 << 10,  // AcceptDragDropPayload() will returns true even before the mouse button is released. You can then call IsDelivery() to test if the payload needs to be delivered.
    IGSharp_DragDropFlags_AcceptNoDrawDefaultRect  = 1 << 11,  // Do not draw the default highlight rectangle when hovering over target.
    IGSharp_DragDropFlags_AcceptNoPreviewTooltip   = 1 << 12,  // Request hiding the BeginDragDropSource tooltip from the BeginDragDropTarget site.
    IGSharp_DragDropFlags_AcceptDrawAsHovered      = 1 << 13,  // Accepting item will render as if hovered. Useful for e.g. a Button() used as a drop target.
    IGSharp_DragDropFlags_AcceptPeekOnly           = IGSharp_DragDropFlags_AcceptBeforeDelivery | IGSharp_DragDropFlags_AcceptNoDrawDefaultRect, // For peeking ahead and inspecting the payload before delivery.
} IGSharp_DragDropFlags;

// Standard drag-drop payload type strings emitted by the ColorEdit*/ColorPicker* widgets
// (mirror of IMGUI_PAYLOAD_TYPE_COLOR_3F / _4F). Pass to IGSharp_AcceptDragDropPayload.
#define IGSHARP_PAYLOAD_TYPE_COLOR_3F "_COL3F"   // float[3]: Standard type for colors, without alpha. User code may use this type.
#define IGSHARP_PAYLOAD_TYPE_COLOR_4F "_COL4F"   // float[4]: Standard type for colors. User code may use this type.

// IGSharp_DataType
typedef enum {
    IGSharp_DataType_S8,        // signed char / char (with sensible compilers)
    IGSharp_DataType_U8,        // unsigned char
    IGSharp_DataType_S16,       // short
    IGSharp_DataType_U16,       // unsigned short
    IGSharp_DataType_S32,       // int
    IGSharp_DataType_U32,       // unsigned int
    IGSharp_DataType_S64,       // long long / __int64
    IGSharp_DataType_U64,       // unsigned long long / unsigned __int64
    IGSharp_DataType_Float,     // float
    IGSharp_DataType_Double,    // double
    IGSharp_DataType_Bool,      // bool (provided for user convenience, not supported by scalar widgets)
    IGSharp_DataType_String,    // char* (provided for user convenience, not supported by scalar widgets)
    IGSharp_DataType_COUNT,
} IGSharp_DataType;

// IGSharp_Dir
// A cardinal direction (mirror of ImGuiDir)
typedef enum {
    IGSharp_Dir_None  = -1,
    IGSharp_Dir_Left  = 0,
    IGSharp_Dir_Right  = 1,
    IGSharp_Dir_Up    = 2,
    IGSharp_Dir_Down  = 3,
    IGSharp_Dir_COUNT,
} IGSharp_Dir;

// IGSharp_SortDirection
// A sorting direction (ascending or descending) -> ImGuiSortDirection (upstream backing type ImU8)
typedef enum {
    IGSharp_SortDirection_None        = 0,
    IGSharp_SortDirection_Ascending   = 1,    // Ascending = 0->9, A->Z etc.
    IGSharp_SortDirection_Descending  = 2,    // Descending = 9->0, Z->A etc.
} IGSharp_SortDirection;

// IGSharp_Key
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

// IGSharp_InputFlags
// Flags for Shortcut(), SetNextItemShortcut().
// Mirrored from upstream ImGuiInputFlags_ — values validated per-value in imgui_sharp_layout_check.cpp.
typedef enum {
    IGSharp_InputFlags_None                 = 0,
    IGSharp_InputFlags_Repeat               = 1 << 0,   // Enable repeat. Return true on successive repeats.

    // Flags for Shortcut(), SetNextItemShortcut()
    // - Default policy is RouteFocused. Can select only 1 policy among all available.
    IGSharp_InputFlags_RouteActive          = 1 << 10,  // Route to active item only.
    IGSharp_InputFlags_RouteFocused         = 1 << 11,  // Route to windows in the focus stack (DEFAULT).
    IGSharp_InputFlags_RouteGlobal          = 1 << 12,  // Global route (unless a focused window or active item registered the route).
    IGSharp_InputFlags_RouteAlways          = 1 << 13,  // Do not register route, poll keys directly.
    // - Routing options
    IGSharp_InputFlags_RouteOverFocused     = 1 << 14,  // Option: global route: higher priority than focused route.
    IGSharp_InputFlags_RouteOverActive      = 1 << 15,  // Option: global route: higher priority than active item.
    IGSharp_InputFlags_RouteUnlessBgFocused = 1 << 16,  // Option: global route: not applied if underlying background/void is focused.
    IGSharp_InputFlags_RouteFromRootWindow  = 1 << 17,  // Option: route evaluated from the point of view of root window rather than current window.

    // Flags for SetNextItemShortcut()
    IGSharp_InputFlags_Tooltip              = 1 << 18,  // Automatically display a tooltip when hovering item [BETA]
} IGSharp_InputFlags;

// IGSharp_ConfigFlags
// Flags for io.ConfigFlags (-> enum ImGuiConfigFlags_)
typedef enum {
    IGSharp_ConfigFlags_None                 = 0,
    IGSharp_ConfigFlags_NavEnableKeyboard    = 1 << 0,   // Master keyboard navigation enable flag.
    IGSharp_ConfigFlags_NavEnableGamepad     = 1 << 1,   // Master gamepad navigation enable flag. Backend also needs to set ImGuiBackendFlags_HasGamepad.
    IGSharp_ConfigFlags_NoMouse              = 1 << 4,   // Instruct dear imgui to disable mouse inputs and interactions.
    IGSharp_ConfigFlags_NoMouseCursorChange  = 1 << 5,   // Instruct backend to not alter mouse cursor shape and visibility.
    IGSharp_ConfigFlags_NoKeyboard           = 1 << 6,   // Instruct dear imgui to disable keyboard inputs and interactions.
    IGSharp_ConfigFlags_IsSRGB               = 1 << 20,  // Application is SRGB-aware.
    IGSharp_ConfigFlags_IsTouchScreen        = 1 << 21,  // Application is using a touch screen instead of a mouse.
} IGSharp_ConfigFlags;

// IGSharp_BackendFlags
// Mirrored from ImGuiBackendFlags_. Values must match upstream exactly —
// validated per-value by static_assert in imgui_sharp_layout_check.cpp.
typedef enum {
    IGSharp_BackendFlags_None                 = 0,
    IGSharp_BackendFlags_HasGamepad           = 1 << 0,   // Backend Platform supports gamepad and currently has one connected.
    IGSharp_BackendFlags_HasMouseCursors      = 1 << 1,   // Backend Platform supports honoring GetMouseCursor() value to change the OS cursor shape.
    IGSharp_BackendFlags_HasSetMousePos       = 1 << 2,   // Backend Platform supports io.WantSetMousePos requests to reposition the OS mouse position.
    IGSharp_BackendFlags_RendererHasVtxOffset = 1 << 3,   // Backend Renderer supports ImDrawCmd::VtxOffset. Enables output of large meshes (64K+ vertices) while still using 16-bit indices.
    IGSharp_BackendFlags_RendererHasTextures  = 1 << 4,   // Backend Renderer supports ImTextureData requests to create/update/destroy textures.
} IGSharp_BackendFlags;

// IGSharp_Col
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

// IGSharp_StyleVar
// Enum: A variable identifier for styling (mirror of ImGuiStyleVar_)
typedef enum {
    IGSharp_StyleVar_Alpha,                       // float     Alpha
    IGSharp_StyleVar_DisabledAlpha,               // float     DisabledAlpha
    IGSharp_StyleVar_WindowPadding,               // ImVec2    WindowPadding
    IGSharp_StyleVar_WindowRounding,              // float     WindowRounding
    IGSharp_StyleVar_WindowBorderSize,            // float     WindowBorderSize
    IGSharp_StyleVar_WindowMinSize,               // ImVec2    WindowMinSize
    IGSharp_StyleVar_WindowTitleAlign,            // ImVec2    WindowTitleAlign
    IGSharp_StyleVar_ChildRounding,               // float     ChildRounding
    IGSharp_StyleVar_ChildBorderSize,             // float     ChildBorderSize
    IGSharp_StyleVar_PopupRounding,               // float     PopupRounding
    IGSharp_StyleVar_PopupBorderSize,             // float     PopupBorderSize
    IGSharp_StyleVar_FramePadding,                // ImVec2    FramePadding
    IGSharp_StyleVar_FrameRounding,               // float     FrameRounding
    IGSharp_StyleVar_FrameBorderSize,             // float     FrameBorderSize
    IGSharp_StyleVar_ItemSpacing,                 // ImVec2    ItemSpacing
    IGSharp_StyleVar_ItemInnerSpacing,            // ImVec2    ItemInnerSpacing
    IGSharp_StyleVar_IndentSpacing,               // float     IndentSpacing
    IGSharp_StyleVar_CellPadding,                 // ImVec2    CellPadding
    IGSharp_StyleVar_ScrollbarSize,               // float     ScrollbarSize
    IGSharp_StyleVar_ScrollbarRounding,           // float     ScrollbarRounding
    IGSharp_StyleVar_ScrollbarPadding,            // float     ScrollbarPadding
    IGSharp_StyleVar_GrabMinSize,                 // float     GrabMinSize
    IGSharp_StyleVar_GrabRounding,                // float     GrabRounding
    IGSharp_StyleVar_ImageRounding,               // float     ImageRounding
    IGSharp_StyleVar_ImageBorderSize,             // float     ImageBorderSize
    IGSharp_StyleVar_TabRounding,                 // float     TabRounding
    IGSharp_StyleVar_TabBorderSize,               // float     TabBorderSize
    IGSharp_StyleVar_TabMinWidthBase,             // float     TabMinWidthBase
    IGSharp_StyleVar_TabMinWidthShrink,           // float     TabMinWidthShrink
    IGSharp_StyleVar_TabBarBorderSize,            // float     TabBarBorderSize
    IGSharp_StyleVar_TabBarOverlineSize,          // float     TabBarOverlineSize
    IGSharp_StyleVar_TableAngledHeadersAngle,     // float     TableAngledHeadersAngle
    IGSharp_StyleVar_TableAngledHeadersTextAlign, // ImVec2    TableAngledHeadersTextAlign
    IGSharp_StyleVar_TreeLinesSize,               // float     TreeLinesSize
    IGSharp_StyleVar_TreeLinesRounding,           // float     TreeLinesRounding
    IGSharp_StyleVar_ButtonTextAlign,             // ImVec2    ButtonTextAlign
    IGSharp_StyleVar_SelectableTextAlign,         // ImVec2    SelectableTextAlign
    IGSharp_StyleVar_SeparatorSize,               // float     SeparatorSize
    IGSharp_StyleVar_SeparatorTextBorderSize,     // float     SeparatorTextBorderSize
    IGSharp_StyleVar_SeparatorTextAlign,          // ImVec2    SeparatorTextAlign
    IGSharp_StyleVar_SeparatorTextPadding,        // ImVec2    SeparatorTextPadding
    IGSharp_StyleVar_COUNT,
} IGSharp_StyleVar;

// IGSharp_ButtonFlags
// Flags for InvisibleButton() [public subset; extended in imgui_internal.h].
// Passed to functions as plain int. Values validated in imgui_sharp_layout_check.cpp.
typedef enum {
    IGSharp_ButtonFlags_None             = 0,
    IGSharp_ButtonFlags_MouseButtonLeft  = 1 << 0,  // React on left mouse button (default)
    IGSharp_ButtonFlags_MouseButtonRight = 1 << 1,  // React on right mouse button
    IGSharp_ButtonFlags_MouseButtonMiddle= 1 << 2,  // React on center mouse button
    IGSharp_ButtonFlags_MouseButtonMask_ = IGSharp_ButtonFlags_MouseButtonLeft | IGSharp_ButtonFlags_MouseButtonRight | IGSharp_ButtonFlags_MouseButtonMiddle, // [Internal]
    IGSharp_ButtonFlags_EnableNav        = 1 << 3,  // InvisibleButton(): do not disable navigation/tabbing. Otherwise disabled by default.
    IGSharp_ButtonFlags_AllowOverlap     = 1 << 12, // Hit testing will allow subsequent widgets to overlap this one.
} IGSharp_ButtonFlags;

// IGSharp_ColorEditFlags
// Flags for ColorEdit3/4(), ColorPicker3/4(), ColorButton(). ImGuiColorEditFlags.
// Mirrored from upstream Dear ImGui — validated per-value by static_assert in
// imgui_sharp_layout_check.cpp. Includes [Internal] mask values.
typedef enum {
    IGSharp_ColorEditFlags_None             = 0,
    IGSharp_ColorEditFlags_NoAlpha          = 1 << 1,   // ColorEdit, ColorPicker, ColorButton: ignore Alpha component (will only read 3 components from the input pointer).
    IGSharp_ColorEditFlags_NoPicker         = 1 << 2,   // ColorEdit: disable picker when clicking on color square.
    IGSharp_ColorEditFlags_NoOptions        = 1 << 3,   // ColorEdit: disable toggling options menu when right-clicking on inputs/small preview.
    IGSharp_ColorEditFlags_NoSmallPreview   = 1 << 4,   // ColorEdit, ColorPicker: disable color square preview next to the inputs. (e.g. to show only the inputs)
    IGSharp_ColorEditFlags_NoInputs         = 1 << 5,   // ColorEdit, ColorPicker: disable inputs sliders/text widgets (e.g. to show only the small preview color square).
    IGSharp_ColorEditFlags_NoTooltip        = 1 << 6,   // ColorEdit, ColorPicker, ColorButton: disable tooltip when hovering the preview.
    IGSharp_ColorEditFlags_NoLabel          = 1 << 7,   // ColorEdit, ColorPicker: disable display of inline text label (the label is still forwarded to the tooltip and picker).
    IGSharp_ColorEditFlags_NoSidePreview    = 1 << 8,   // ColorPicker: disable bigger color preview on right side of the picker, use small color square preview instead.
    IGSharp_ColorEditFlags_NoDragDrop       = 1 << 9,   // ColorEdit: disable drag and drop target/source. ColorButton: disable drag and drop source.
    IGSharp_ColorEditFlags_NoBorder         = 1 << 10,  // ColorButton: disable border (which is enforced by default)
    IGSharp_ColorEditFlags_NoColorMarkers   = 1 << 11,  // ColorEdit: disable rendering R/G/B/A color marker.

    // User Options (right-click on widget to change some of them).
    IGSharp_ColorEditFlags_AlphaOpaque      = 1 << 12,  // ColorEdit, ColorPicker, ColorButton: disable alpha in the preview.
    IGSharp_ColorEditFlags_AlphaNoBg        = 1 << 13,  // ColorEdit, ColorPicker, ColorButton: disable rendering a checkerboard background behind transparent color.
    IGSharp_ColorEditFlags_AlphaPreviewHalf = 1 << 14,  // ColorEdit, ColorPicker, ColorButton: display half opaque / half transparent preview.
    IGSharp_ColorEditFlags_AlphaBar         = 1 << 18,  // ColorEdit, ColorPicker: show vertical alpha bar/gradient in picker.
    IGSharp_ColorEditFlags_HDR              = 1 << 19,  // (WIP) ColorEdit: Currently only disable 0.0f..1.0f limits in RGBA edition.
    IGSharp_ColorEditFlags_DisplayRGB       = 1 << 20,  // [Display] ColorEdit: override _display_ type among RGB/HSV/Hex.
    IGSharp_ColorEditFlags_DisplayHSV       = 1 << 21,  // [Display]
    IGSharp_ColorEditFlags_DisplayHex       = 1 << 22,  // [Display]
    IGSharp_ColorEditFlags_Uint8            = 1 << 23,  // [DataType] ColorEdit, ColorPicker, ColorButton: _display_ values formatted as 0..255.
    IGSharp_ColorEditFlags_Float            = 1 << 24,  // [DataType] ColorEdit, ColorPicker, ColorButton: _display_ values formatted as 0.0f..1.0f floats instead of 0..255 integers.
    IGSharp_ColorEditFlags_PickerHueBar     = 1 << 25,  // [Picker] ColorPicker: bar for Hue, rectangle for Sat/Value.
    IGSharp_ColorEditFlags_PickerHueWheel   = 1 << 26,  // [Picker] ColorPicker: wheel for Hue, triangle for Sat/Value.
    IGSharp_ColorEditFlags_InputRGB         = 1 << 27,  // [Input] ColorEdit, ColorPicker: input and output data in RGB format.
    IGSharp_ColorEditFlags_InputHSV         = 1 << 28,  // [Input] ColorEdit, ColorPicker: input and output data in HSV format.

    // Defaults Options. You can set application defaults using SetColorEditOptions().
    IGSharp_ColorEditFlags_DefaultOptions_  = IGSharp_ColorEditFlags_Uint8 | IGSharp_ColorEditFlags_DisplayRGB | IGSharp_ColorEditFlags_InputRGB | IGSharp_ColorEditFlags_PickerHueBar,

    // [Internal] Masks
    IGSharp_ColorEditFlags_AlphaMask_       = IGSharp_ColorEditFlags_NoAlpha | IGSharp_ColorEditFlags_AlphaOpaque | IGSharp_ColorEditFlags_AlphaNoBg | IGSharp_ColorEditFlags_AlphaPreviewHalf,
    IGSharp_ColorEditFlags_DisplayMask_     = IGSharp_ColorEditFlags_DisplayRGB | IGSharp_ColorEditFlags_DisplayHSV | IGSharp_ColorEditFlags_DisplayHex,
    IGSharp_ColorEditFlags_DataTypeMask_    = IGSharp_ColorEditFlags_Uint8 | IGSharp_ColorEditFlags_Float,
    IGSharp_ColorEditFlags_PickerMask_      = IGSharp_ColorEditFlags_PickerHueWheel | IGSharp_ColorEditFlags_PickerHueBar,
    IGSharp_ColorEditFlags_InputMask_       = IGSharp_ColorEditFlags_InputRGB | IGSharp_ColorEditFlags_InputHSV,
} IGSharp_ColorEditFlags;

// IGSharp_SliderFlags
// Flags for DragFloat(), DragInt(), SliderFloat(), SliderInt() etc.
// Used as 'int' flags in those functions' wrappers. Mirrored from upstream;
// validated per-value by static_assert in imgui_sharp_layout_check.cpp.
typedef enum {
    IGSharp_SliderFlags_None            = 0,
    IGSharp_SliderFlags_Logarithmic     = 1 << 5,   // Make the widget logarithmic (linear otherwise).
    IGSharp_SliderFlags_NoRoundToFormat = 1 << 6,   // Disable rounding underlying value to match precision of the display format string.
    IGSharp_SliderFlags_NoInput         = 1 << 7,   // Disable Ctrl+Click or Enter key allowing to input text directly into the widget.
    IGSharp_SliderFlags_WrapAround      = 1 << 8,   // Enable wrapping around from max to min and from min to max (DragXXX() only for now).
    IGSharp_SliderFlags_ClampOnInput    = 1 << 9,   // Clamp value to min/max bounds when input manually with Ctrl+Click.
    IGSharp_SliderFlags_ClampZeroRange  = 1 << 10,  // Clamp even if min==max==0.0f.
    IGSharp_SliderFlags_NoSpeedTweaks   = 1 << 11,  // Disable keyboard modifiers altering tweak speed.
    IGSharp_SliderFlags_ColorMarkers    = 1 << 12,  // DragScalarN(), SliderScalarN(): Draw R/G/B/A color markers on each component.
    IGSharp_SliderFlags_AlwaysClamp     = IGSharp_SliderFlags_ClampOnInput | IGSharp_SliderFlags_ClampZeroRange,
    IGSharp_SliderFlags_InvalidMask_    = 0x7000000F,   // [Internal] Bits used to detect a miscast 'float power' legacy argument.
} IGSharp_SliderFlags;

// IGSharp_MouseButton
typedef enum {
    IGSharp_MouseButton_Left = 0,
    IGSharp_MouseButton_Right = 1,
    IGSharp_MouseButton_Middle = 2,
    IGSharp_MouseButton_COUNT = 5,
} IGSharp_MouseButton;

// IGSharp_MouseCursor
typedef enum {
    IGSharp_MouseCursor_None = -1,
    IGSharp_MouseCursor_Arrow = 0,
    IGSharp_MouseCursor_TextInput,         // When hovering over InputText, etc.
    IGSharp_MouseCursor_ResizeAll,         // (Unused by Dear ImGui functions)
    IGSharp_MouseCursor_ResizeNS,          // When hovering over a horizontal border
    IGSharp_MouseCursor_ResizeEW,          // When hovering over a vertical border or a column
    IGSharp_MouseCursor_ResizeNESW,        // When hovering over the bottom-left corner of a window
    IGSharp_MouseCursor_ResizeNWSE,        // When hovering over the bottom-right corner of a window
    IGSharp_MouseCursor_Hand,              // (Unused by Dear ImGui functions. Use for e.g. hyperlinks)
    IGSharp_MouseCursor_Wait,              // When waiting for something to process/load.
    IGSharp_MouseCursor_Progress,          // When waiting for something to process/load, but application is still interactive.
    IGSharp_MouseCursor_NotAllowed,        // When hovering something with disallowed interaction. Usually a crossed circle.
    IGSharp_MouseCursor_COUNT
} IGSharp_MouseCursor;

// IGSharp_MouseSource
// Enumeration for AddMouseSourceEvent() actual mouse input source (mirror of ImGuiMouseSource).
typedef enum {
    IGSharp_MouseSource_Mouse = 0,      // Input is coming from an actual mouse.
    IGSharp_MouseSource_TouchScreen,    // Input is coming from a touch screen (no hovering prior to initial press, less precise initial press aiming, dual-axis wheeling possible).
    IGSharp_MouseSource_Pen,            // Input is coming from a pressure/magnetic pen (often used in conjunction with high-sampling rates).
    IGSharp_MouseSource_COUNT,
} IGSharp_MouseSource;

// IGSharp_Cond
// Mirrored from upstream ImGuiCond_. A condition for many Set*() functions.
// Treat as a regular enum: do NOT combine values with binary operators.
// Values validated per-value by static_assert in imgui_sharp_layout_check.cpp.
typedef enum {
    IGSharp_Cond_None         = 0,        // No condition (always set the variable), same as _Always
    IGSharp_Cond_Always       = 1 << 0,   // No condition (always set the variable), same as _None
    IGSharp_Cond_Once         = 1 << 1,   // Set the variable once per runtime session (only the first call will succeed)
    IGSharp_Cond_FirstUseEver = 1 << 2,   // Set the variable if the object/window has no persistently saved data (no entry in .ini file)
    IGSharp_Cond_Appearing    = 1 << 3,   // Set the variable if the object/window is appearing after being hidden/inactive (or the first time)
} IGSharp_Cond;

//-----------------------------------------------------------------------------
// [SECTION] Tables API flags and structures (ImGuiTableFlags, ImGuiTableColumnFlags, ImGuiTableRowFlags, ImGuiTableBgTarget, ImGuiTableSortSpecs, ImGuiTableColumnSortSpecs)
//-----------------------------------------------------------------------------

// IGSharp_TableFlags
// Flags for IGSharp_BeginTable(). Mirrored from ImGuiTableFlags_.
// Values must match upstream exactly — validated per-value by static_assert
// in imgui_sharp_layout_check.cpp. Passed to functions as plain int.
typedef enum {
    // Features
    IGSharp_TableFlags_None                       = 0,
    IGSharp_TableFlags_Resizable                  = 1 << 0,   // Enable resizing columns.
    IGSharp_TableFlags_Reorderable                = 1 << 1,   // Enable reordering columns in header row.
    IGSharp_TableFlags_Hideable                   = 1 << 2,   // Enable hiding/disabling columns in context menu.
    IGSharp_TableFlags_Sortable                   = 1 << 3,   // Enable sorting. Call TableGetSortSpecs() to obtain sort specs.
    IGSharp_TableFlags_NoSavedSettings            = 1 << 4,   // Disable persisting columns order, width, visibility and sort settings in the .ini file.
    IGSharp_TableFlags_ContextMenuInBody          = 1 << 5,   // Right-click on columns body/contents will also display table context menu.
    // Decorations
    IGSharp_TableFlags_RowBg                      = 1 << 6,   // Set each RowBg color with ImGuiCol_TableRowBg or ImGuiCol_TableRowBgAlt.
    IGSharp_TableFlags_BordersInnerH              = 1 << 7,   // Draw horizontal borders between rows.
    IGSharp_TableFlags_BordersOuterH              = 1 << 8,   // Draw horizontal borders at the top and bottom.
    IGSharp_TableFlags_BordersInnerV              = 1 << 9,   // Draw vertical borders between columns.
    IGSharp_TableFlags_BordersOuterV              = 1 << 10,  // Draw vertical borders on the left and right sides.
    IGSharp_TableFlags_BordersH                   = IGSharp_TableFlags_BordersInnerH | IGSharp_TableFlags_BordersOuterH, // Draw horizontal borders.
    IGSharp_TableFlags_BordersV                   = IGSharp_TableFlags_BordersInnerV | IGSharp_TableFlags_BordersOuterV, // Draw vertical borders.
    IGSharp_TableFlags_BordersInner               = IGSharp_TableFlags_BordersInnerV | IGSharp_TableFlags_BordersInnerH, // Draw inner borders.
    IGSharp_TableFlags_BordersOuter               = IGSharp_TableFlags_BordersOuterV | IGSharp_TableFlags_BordersOuterH, // Draw outer borders.
    IGSharp_TableFlags_Borders                    = IGSharp_TableFlags_BordersInner | IGSharp_TableFlags_BordersOuter,   // Draw all borders.
    IGSharp_TableFlags_NoBordersInBody            = 1 << 11,  // [ALPHA] Disable vertical borders in columns Body (borders will always appear in Headers).
    IGSharp_TableFlags_NoBordersInBodyUntilResize = 1 << 12,  // [ALPHA] Disable vertical borders in columns Body until hovered for resize.
    // Sizing Policy (read above for defaults)
    IGSharp_TableFlags_SizingFixedFit             = 1 << 13,  // Columns default to _WidthFixed or _WidthAuto, matching contents width.
    IGSharp_TableFlags_SizingFixedSame            = 2 << 13,  // Columns default to _WidthFixed or _WidthAuto, matching the maximum contents width of all columns.
    IGSharp_TableFlags_SizingStretchProp          = 3 << 13,  // Columns default to _WidthStretch with default weights proportional to each columns contents widths.
    IGSharp_TableFlags_SizingStretchSame          = 4 << 13,  // Columns default to _WidthStretch with default weights all equal.
    // Sizing Extra Options
    IGSharp_TableFlags_NoHostExtendX              = 1 << 16,  // Make outer width auto-fit to columns, overriding outer_size.x value.
    IGSharp_TableFlags_NoHostExtendY              = 1 << 17,  // Make outer height stop exactly at outer_size.y.
    IGSharp_TableFlags_NoKeepColumnsVisible       = 1 << 18,  // Disable keeping column always minimally visible when ScrollX is off.
    IGSharp_TableFlags_PreciseWidths              = 1 << 19,  // Disable distributing remainder width to stretched columns.
    // Clipping
    IGSharp_TableFlags_NoClip                     = 1 << 20,  // Disable clipping rectangle for every individual columns.
    // Padding
    IGSharp_TableFlags_PadOuterX                  = 1 << 21,  // Default if BordersOuterV is on. Enable outermost padding.
    IGSharp_TableFlags_NoPadOuterX                = 1 << 22,  // Default if BordersOuterV is off. Disable outermost padding.
    IGSharp_TableFlags_NoPadInnerX                = 1 << 23,  // Disable inner padding between columns.
    // Scrolling
    IGSharp_TableFlags_ScrollX                    = 1 << 24,  // Enable horizontal scrolling. Require 'outer_size' parameter of BeginTable() to specify the container size.
    IGSharp_TableFlags_ScrollY                    = 1 << 25,  // Enable vertical scrolling.
    // Sorting
    IGSharp_TableFlags_SortMulti                  = 1 << 26,  // Hold shift when clicking headers to sort on multiple column.
    IGSharp_TableFlags_SortTristate               = 1 << 27,  // Allow no sorting, disable default sorting.
    // Miscellaneous
    IGSharp_TableFlags_HighlightHoveredColumn     = 1 << 28,  // Highlight column headers when hovered.
} IGSharp_TableFlags;

// IGSharp_TableColumnFlags
// Flags for IGSharp_TableSetupColumn(). Mirror of enum ImGuiTableColumnFlags_.
// Internal masks (WidthMask_/IndentMask_/StatusMask_/NoDirectResize_) are omitted.
typedef enum {
    // Input configuration flags
    IGSharp_TableColumnFlags_None                  = 0,
    IGSharp_TableColumnFlags_Disabled              = 1 << 0,   // Overriding/master disable flag: hide column, won't show in context menu (unlike calling TableSetColumnEnabled() which manipulates the user accessible state)
    IGSharp_TableColumnFlags_DefaultHide           = 1 << 1,   // Default as a hidden/disabled column.
    IGSharp_TableColumnFlags_DefaultSort           = 1 << 2,   // Default as a sorting column.
    IGSharp_TableColumnFlags_WidthStretch          = 1 << 3,   // Column will stretch. Preferable with horizontal scrolling disabled (default if table sizing policy is _SizingStretchSame or _SizingStretchProp).
    IGSharp_TableColumnFlags_WidthFixed            = 1 << 4,   // Column will not stretch. Preferable with horizontal scrolling enabled (default if table sizing policy is _SizingFixedFit and table is resizable).
    IGSharp_TableColumnFlags_NoResize              = 1 << 5,   // Disable manual resizing.
    IGSharp_TableColumnFlags_NoReorder             = 1 << 6,   // Disable manual reordering this column, this will also prevent other columns from crossing over this column.
    IGSharp_TableColumnFlags_NoHide                = 1 << 7,   // Disable ability to hide/disable this column.
    IGSharp_TableColumnFlags_NoClip                = 1 << 8,   // Disable clipping for this column (all NoClip columns will render in a same draw command).
    IGSharp_TableColumnFlags_NoSort                = 1 << 9,   // Disable ability to sort on this field (even if ImGuiTableFlags_Sortable is set on the table).
    IGSharp_TableColumnFlags_NoSortAscending       = 1 << 10,  // Disable ability to sort in the ascending direction.
    IGSharp_TableColumnFlags_NoSortDescending      = 1 << 11,  // Disable ability to sort in the descending direction.
    IGSharp_TableColumnFlags_NoHeaderLabel         = 1 << 12,  // TableHeadersRow() will submit an empty label for this column. Convenient for some small columns. Name will still appear in context menu or in angled headers. You may append into this cell by calling TableSetColumnIndex() right after the TableHeadersRow() call.
    IGSharp_TableColumnFlags_NoHeaderWidth         = 1 << 13,  // Disable header text width contribution to automatic column width.
    IGSharp_TableColumnFlags_PreferSortAscending   = 1 << 14,  // Make the initial sort direction Ascending when first sorting on this column (default).
    IGSharp_TableColumnFlags_PreferSortDescending  = 1 << 15,  // Make the initial sort direction Descending when first sorting on this column.
    IGSharp_TableColumnFlags_IndentEnable          = 1 << 16,  // Use current Indent value when entering cell (default for column 0).
    IGSharp_TableColumnFlags_IndentDisable         = 1 << 17,  // Ignore current Indent value when entering cell (default for columns > 0). Indentation changes _within_ the cell will still be honored.
    IGSharp_TableColumnFlags_AngledHeader          = 1 << 18,  // TableHeadersRow() will submit an angled header row for this column. Note this will add an extra row.

    // Output status flags, read-only via IGSharp_TableGetColumnFlags()
    IGSharp_TableColumnFlags_IsEnabled             = 1 << 24,  // Status: is enabled == not hidden by user/api (referred to as "Hide" in _DefaultHide and _NoHide) flags.
    IGSharp_TableColumnFlags_IsVisible             = 1 << 25,  // Status: is visible == is enabled AND not clipped by scrolling.
    IGSharp_TableColumnFlags_IsSorted              = 1 << 26,  // Status: is currently part of the sort specs
    IGSharp_TableColumnFlags_IsHovered             = 1 << 27,  // Status: is hovered by mouse
} IGSharp_TableColumnFlags;

// IGSharp_TableRowFlags
// Flags for IGSharp_TableNextRow(). Mirrored from upstream ImGuiTableRowFlags_.
// Validated per-value by static_assert in imgui_sharp_layout_check.cpp.
typedef enum {
    IGSharp_TableRowFlags_None    = 0,
    IGSharp_TableRowFlags_Headers = 1 << 0,  // Identify header row
} IGSharp_TableRowFlags;

// IGSharp_TableBgTarget
// Enum for IGSharp_TableSetBgColor()
typedef enum {
    IGSharp_TableBgTarget_None  = 0,
    IGSharp_TableBgTarget_RowBg0 = 1, // Set row background color 0 (generally used for background, automatically set when ImGuiTableFlags_RowBg is used)
    IGSharp_TableBgTarget_RowBg1 = 2, // Set row background color 1 (generally used for selection marking)
    IGSharp_TableBgTarget_CellBg = 3, // Set cell background color (top-most color)
} IGSharp_TableBgTarget;

// ImGuiTableSortSpecs (opaque; obtain via IGSharp_TableGetSortSpecs())
IGSHARP_API int   IGSharp_TableSortSpecs_GetSpecsCount(void* specs);
IGSHARP_API void* IGSharp_TableSortSpecs_GetSpec(void* specs, int index);
IGSHARP_API bool  IGSharp_TableSortSpecs_GetSpecsDirty(void* specs);
IGSHARP_API void  IGSharp_TableSortSpecs_SetSpecsDirty(void* specs, bool v);

// ImGuiTableColumnSortSpecs (opaque; obtain via IGSharp_TableSortSpecs_GetSpec())
IGSHARP_API unsigned int IGSharp_TableColumnSortSpecs_GetColumnUserID(void* spec);
IGSHARP_API int          IGSharp_TableColumnSortSpecs_GetColumnIndex(void* spec);
IGSHARP_API int          IGSharp_TableColumnSortSpecs_GetSortOrder(void* spec);
IGSHARP_API int          IGSharp_TableColumnSortSpecs_GetSortDirection(void* spec);

//-----------------------------------------------------------------------------
// [SECTION] Helpers: Debug log, memory allocations macros, ImVector<>
//-----------------------------------------------------------------------------
// (no C wrappers: IMGUI_DEBUG_LOG/IM_ALLOC macros and ImVector<> are C++-side utilities.
//  ImVector<T> members are expanded inline as _Size/_Capacity/_Data field triplets in
//  mirror structs, or exposed via accessor functions.)
//-----------------------------------------------------------------------------
// [SECTION] ImGuiStyle
//-----------------------------------------------------------------------------
// Layout-compatible C mirror of Dear ImGui's ImGuiStyle. Verified at compile
// time in src/imgui_sharp_layout_check.cpp.
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
// Obtain a pointer with IGSharp_GetIO() and read/write fields directly. The
// few member functions that ImGuiIO exposes (event queue, ClearInputKeys,
// etc.) are exported as IGSharp_IO_* free functions taking IGSharp_IO* as the
// first argument.
//-----------------------------------------------------------------------------

// IGSharp_KeyData: mirror of upstream ImGuiKeyData (key/analog state, stored in IGSharp_IO.KeysData[]).
typedef struct {
    bool  Down;
    float DownDuration;
    float DownDurationPrev;
    float AnalogValue;
} IGSharp_KeyData;

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
IGSHARP_API void IGSharp_IO_SetKeyEventNativeData(IGSharp_IO* io, int key, int native_keycode, int native_scancode, int native_legacy_index);
IGSHARP_API void IGSharp_IO_SetAppAcceptingEvents(IGSharp_IO* io, bool accepting);
IGSHARP_API void IGSharp_IO_ClearEventsQueue(IGSharp_IO* io);
IGSHARP_API void IGSharp_IO_ClearInputKeys(IGSharp_IO* io);
IGSHARP_API void IGSharp_IO_ClearInputMouse(IGSharp_IO* io);

//-----------------------------------------------------------------------------
// [SECTION] Misc data structures (ImGuiInputTextCallbackData, ImGuiSizeCallbackData, ImGuiPayload)
//-----------------------------------------------------------------------------

// ImGuiInputTextCallbackData: Field Accessors
IGSHARP_API void*          IGSharp_InputTextCallbackData_GetCtx(void* data);    // ImGuiContext* (-> IGSharp_Context*; for IGSharp_SetCurrentContext in multi-context apps)
IGSHARP_API int            IGSharp_InputTextCallbackData_GetEventFlag(void* data);
IGSHARP_API int            IGSharp_InputTextCallbackData_GetFlags(void* data);
IGSHARP_API void*          IGSharp_InputTextCallbackData_GetUserData(void* data);
IGSHARP_API unsigned int   IGSharp_InputTextCallbackData_GetID(void* data);
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
IGSHARP_API void IGSharp_InputTextCallbackData_SetSelection(void* data, int s, int e);
IGSHARP_API void IGSharp_InputTextCallbackData_ClearSelection(void* data);
IGSHARP_API bool IGSharp_InputTextCallbackData_HasSelection(void* data);

// ImGuiInputTextCallbackData: Resize Helpers
IGSHARP_API void IGSharp_InputTextCallbackData_SetBuf(void* data, char* buf);
IGSHARP_API void IGSharp_InputTextCallbackData_SetBufSize(void* data, int size);
IGSHARP_API void IGSharp_InputTextCallbackData_ResizeBuf(void* data, char* new_buf, int new_buf_size);

// ImGuiSizeCallbackData accessors
// --- ImGuiSizeCallbackData: Field Accessors ---
// Delivered as a pointer to the SetNextWindowSizeConstraints() callback (accessed via opaque void*).
IGSHARP_API void*        IGSharp_SizeCallbackData_GetUserData(void* data);      // Read-only.
IGSHARP_API IGSharp_Vec2 IGSharp_SizeCallbackData_GetPos(void* data);          // Read-only.
IGSHARP_API IGSharp_Vec2 IGSharp_SizeCallbackData_GetCurrentSize(void* data);  // Read-only.
IGSHARP_API IGSharp_Vec2 IGSharp_SizeCallbackData_GetDesiredSize(void* data);  // Read-write.
IGSHARP_API void         IGSharp_SizeCallbackData_SetDesiredSize(void* data, IGSharp_Vec2 v);

// ImGuiPayload accessors
IGSHARP_API void*       IGSharp_Payload_GetData(void* payload);
IGSHARP_API int         IGSharp_Payload_GetDataSize(void* payload);
IGSHARP_API const char* IGSharp_Payload_GetDataType(void* payload);
IGSHARP_API bool        IGSharp_Payload_IsDataType(void* payload, const char* type);
IGSHARP_API bool        IGSharp_Payload_IsPreview(void* payload);
IGSHARP_API bool        IGSharp_Payload_IsDelivery(void* payload);

//-----------------------------------------------------------------------------
// [SECTION] Helpers (ImGuiOnceUponAFrame, ImGuiTextFilter, ImGuiTextBuffer, ImGuiStorage, ImGuiListClipper, Math Operators, ImColor)
//-----------------------------------------------------------------------------

// ImGuiOnceUponAFrame
IGSHARP_API void* IGSharp_OnceUponAFrame_New(void);
IGSHARP_API void  IGSharp_OnceUponAFrame_Delete(void* oaf);
IGSHARP_API bool  IGSharp_OnceUponAFrame_Check(void* oaf);   // invokes operator bool(): true at most once per frame
IGSHARP_API int   IGSharp_OnceUponAFrame_GetRefFrame(void* oaf);

// ImGuiTextFilter
// Helpers: ImGuiTextFilter (opaque handle; internals not mirrored)
typedef struct IGSharp_TextFilter IGSharp_TextFilter;
IGSHARP_API IGSharp_TextFilter* IGSharp_TextFilter_New(const char* default_filter);
IGSHARP_API void                IGSharp_TextFilter_Delete(IGSharp_TextFilter* filter);
IGSHARP_API bool                IGSharp_TextFilter_Draw(IGSharp_TextFilter* filter, const char* label, float width);
IGSHARP_API bool                IGSharp_TextFilter_PassFilter(IGSharp_TextFilter* filter, const char* text, const char* text_end);
IGSHARP_API void                IGSharp_TextFilter_Build(IGSharp_TextFilter* filter);
IGSHARP_API void                IGSharp_TextFilter_Clear(IGSharp_TextFilter* filter);
IGSHARP_API bool                IGSharp_TextFilter_IsActive(IGSharp_TextFilter* filter);

// ImGuiTextBuffer (~string builder over ImVector<char>). Opaque handle.
// appendf/appendfv are variadic and dropped; C# formats at the call site and uses Append.
IGSHARP_API void*       IGSharp_TextBuffer_New(void);
IGSHARP_API void        IGSharp_TextBuffer_Delete(void* buf);
IGSHARP_API const char* IGSharp_TextBuffer_CStr(void* buf);
IGSHARP_API int         IGSharp_TextBuffer_Size(void* buf);
IGSHARP_API bool        IGSharp_TextBuffer_Empty(void* buf);
IGSHARP_API void        IGSharp_TextBuffer_Clear(void* buf);
IGSHARP_API void        IGSharp_TextBuffer_Resize(void* buf, int size);
IGSHARP_API void        IGSharp_TextBuffer_Reserve(void* buf, int capacity);
IGSHARP_API void        IGSharp_TextBuffer_Append(void* buf, const char* str, const char* str_end);

// ImGuiStorage (opaque handle; sorted key->value container, ref-returning methods)
IGSHARP_API void*  IGSharp_Storage_New(void);
IGSHARP_API void   IGSharp_Storage_Delete(void* storage);
IGSHARP_API void   IGSharp_Storage_Clear(void* storage);
IGSHARP_API int    IGSharp_Storage_GetInt(void* storage, unsigned int key, int default_val);
IGSHARP_API void   IGSharp_Storage_SetInt(void* storage, unsigned int key, int val);
IGSHARP_API bool   IGSharp_Storage_GetBool(void* storage, unsigned int key, bool default_val);
IGSHARP_API void   IGSharp_Storage_SetBool(void* storage, unsigned int key, bool val);
IGSHARP_API float  IGSharp_Storage_GetFloat(void* storage, unsigned int key, float default_val);
IGSHARP_API void   IGSharp_Storage_SetFloat(void* storage, unsigned int key, float val);
IGSHARP_API void*  IGSharp_Storage_GetVoidPtr(void* storage, unsigned int key);
IGSHARP_API void   IGSharp_Storage_SetVoidPtr(void* storage, unsigned int key, void* val);
IGSHARP_API int*   IGSharp_Storage_GetIntRef(void* storage, unsigned int key, int default_val);
IGSHARP_API bool*  IGSharp_Storage_GetBoolRef(void* storage, unsigned int key, bool default_val);
IGSHARP_API float* IGSharp_Storage_GetFloatRef(void* storage, unsigned int key, float default_val);
IGSHARP_API void** IGSharp_Storage_GetVoidPtrRef(void* storage, unsigned int key, void* default_val);
IGSHARP_API void   IGSharp_Storage_BuildSortByKey(void* storage);
IGSHARP_API void   IGSharp_Storage_SetAllInt(void* storage, int val);

// ImGuiListClipperFlags: flags for IGSharp_ListClipper_Begin / Flags member.
// Mirrored from upstream; values validated per-value in imgui_sharp_layout_check.cpp.
typedef enum {
    IGSharp_ListClipperFlags_None                  = 0,
    IGSharp_ListClipperFlags_NoSetTableRowCounters = 1 << 0,   // [Internal] Disabled modifying table row counters.
} IGSharp_ListClipperFlags;

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
IGSHARP_API int   IGSharp_ListClipper_GetUserIndex(void* clipper);
IGSHARP_API void  IGSharp_ListClipper_SetUserIndex(void* clipper, int user_index);

// (Math operators and ImColor are C++ conveniences; no C wrappers needed —
//  pack colors with IGSharp_ColorConvertFloat4ToU32().)

//-----------------------------------------------------------------------------
// [SECTION] Multi-Select API flags and structures (ImGuiMultiSelectFlags, ImGuiSelectionRequestType, ImGuiSelectionRequest, ImGuiMultiSelectIO, ImGuiSelectionBasicStorage)
//-----------------------------------------------------------------------------

// ImGuiMultiSelectFlags
// Flags for BeginMultiSelect() -> mirror of enum ImGuiMultiSelectFlags_ (passed as int)
typedef enum {
    IGSharp_MultiSelectFlags_None                  = 0,
    IGSharp_MultiSelectFlags_SingleSelect          = 1 << 0,   // Disable selecting more than one item.
    IGSharp_MultiSelectFlags_NoSelectAll           = 1 << 1,   // Disable Ctrl+A shortcut to select all.
    IGSharp_MultiSelectFlags_NoRangeSelect         = 1 << 2,   // Disable Shift+selection mouse/keyboard support.
    IGSharp_MultiSelectFlags_NoAutoSelect          = 1 << 3,   // Disable selecting items when navigating.
    IGSharp_MultiSelectFlags_NoAutoClear           = 1 << 4,   // Disable clearing selection when navigating or selecting another one.
    IGSharp_MultiSelectFlags_NoAutoClearOnReselect = 1 << 5,   // Disable clearing selection when clicking/selecting an already selected item.
    IGSharp_MultiSelectFlags_BoxSelect1d           = 1 << 6,   // Enable box-selection with same width and same x pos items.
    IGSharp_MultiSelectFlags_BoxSelect2d           = 1 << 7,   // Enable box-selection with varying width or varying x pos items support.
    IGSharp_MultiSelectFlags_BoxSelectNoScroll     = 1 << 8,   // Disable scrolling when box-selecting and moving mouse near edges of scope.
    IGSharp_MultiSelectFlags_ClearOnEscape         = 1 << 9,   // Clear selection when pressing Escape while scope is focused.
    IGSharp_MultiSelectFlags_ClearOnClickVoid      = 1 << 10,  // Clear selection when clicking on empty location within scope.
    IGSharp_MultiSelectFlags_ScopeWindow           = 1 << 11,  // Scope for _BoxSelect and _ClearOnClickVoid is whole window (Default).
    IGSharp_MultiSelectFlags_ScopeRect             = 1 << 12,  // Scope for _BoxSelect and _ClearOnClickVoid is rectangle encompassing BeginMultiSelect()/EndMultiSelect().
    IGSharp_MultiSelectFlags_SelectOnAuto          = 1 << 13,  // Apply selection on mouse down when clicking on unselected item, on mouse up when clicking on selected item. (Default)
    IGSharp_MultiSelectFlags_SelectOnClickAlways   = 1 << 14,  // Apply selection on mouse down when clicking on any items.
    IGSharp_MultiSelectFlags_SelectOnClickRelease  = 1 << 15,  // Apply selection on mouse release when clicking an unselected item.
    IGSharp_MultiSelectFlags_NavWrapX              = 1 << 16,  // [Temporary] Enable navigation wrapping on X axis.
    IGSharp_MultiSelectFlags_NoSelectOnRightClick  = 1 << 17,  // Disable default right-click processing.
    IGSharp_MultiSelectFlags_SelectOnMask_         = IGSharp_MultiSelectFlags_SelectOnAuto | IGSharp_MultiSelectFlags_SelectOnClickAlways | IGSharp_MultiSelectFlags_SelectOnClickRelease,
} IGSharp_MultiSelectFlags;

// ImGuiMultiSelectIO accessors
IGSHARP_API int       IGSharp_MultiSelectIO_GetRequestsCount(void* io);
IGSHARP_API void*     IGSharp_MultiSelectIO_GetRequest(void* io, int index);
IGSHARP_API long long IGSharp_MultiSelectIO_GetRangeSrcItem(void* io);
IGSHARP_API long long IGSharp_MultiSelectIO_GetNavIdItem(void* io);
IGSHARP_API bool      IGSharp_MultiSelectIO_GetNavIdSelected(void* io);
IGSHARP_API bool      IGSharp_MultiSelectIO_GetRangeSrcReset(void* io);
IGSHARP_API void      IGSharp_MultiSelectIO_SetRangeSrcReset(void* io, bool v);
IGSHARP_API int       IGSharp_MultiSelectIO_GetItemsCount(void* io);

// ImGuiSelectionRequestType: mirror of ImGuiSelectionRequestType (returned by IGSharp_SelectionRequest_GetType)
typedef enum {
    IGSharp_SelectionRequestType_None = 0,
    IGSharp_SelectionRequestType_SetAll,        // Request app to clear selection (if Selected==false) or select all items (if Selected==true).
    IGSharp_SelectionRequestType_SetRange,      // Request app to select/unselect [RangeFirstItem..RangeLastItem] items (inclusive) based on value of Selected.
} IGSharp_SelectionRequestType;

// ImGuiSelectionRequest accessors
IGSHARP_API int       IGSharp_SelectionRequest_GetType(void* request);
IGSHARP_API bool      IGSharp_SelectionRequest_GetSelected(void* request);
IGSHARP_API int       IGSharp_SelectionRequest_GetRangeDirection(void* request);
IGSHARP_API long long IGSharp_SelectionRequest_GetRangeFirstItem(void* request);
IGSHARP_API long long IGSharp_SelectionRequest_GetRangeLastItem(void* request);

// ImGuiSelectionBasicStorage (opaque handle + accessors)
// NOTE: not mirrored (interleaves ctor/methods, a function-pointer adapter, and internal
// ImGuiStorage). Swap() and the AdapterIndexToStorageId setter are intentionally omitted
// (no C# callback story); the default index->id adapter is kept so GetStorageIdFromIndex works.
IGSHARP_API void*        IGSharp_SelectionBasicStorage_Create(void);
IGSHARP_API void         IGSharp_SelectionBasicStorage_Destroy(void* storage);
IGSHARP_API void         IGSharp_SelectionBasicStorage_ApplyRequests(void* storage, void* ms_io);
IGSHARP_API bool         IGSharp_SelectionBasicStorage_Contains(void* storage, unsigned int id);
IGSHARP_API void         IGSharp_SelectionBasicStorage_Clear(void* storage);
IGSHARP_API void         IGSharp_SelectionBasicStorage_SetItemSelected(void* storage, unsigned int id, bool selected);
IGSHARP_API bool         IGSharp_SelectionBasicStorage_GetNextSelectedItem(void* storage, void** opaque_it, unsigned int* out_id);
IGSHARP_API unsigned int IGSharp_SelectionBasicStorage_GetStorageIdFromIndex(void* storage, int idx);
IGSHARP_API int          IGSharp_SelectionBasicStorage_GetSize(void* storage);
IGSHARP_API bool         IGSharp_SelectionBasicStorage_GetPreserveOrder(void* storage);
IGSHARP_API void         IGSharp_SelectionBasicStorage_SetPreserveOrder(void* storage, bool v);
IGSHARP_API void*        IGSharp_SelectionBasicStorage_GetUserData(void* storage);
IGSHARP_API void         IGSharp_SelectionBasicStorage_SetUserData(void* storage, void* v);

// ImGuiSelectionExternalStorage (opaque; helper to apply selection requests to your own storage)
// Adapter callback: self is an opaque IGSharp_SelectionExternalStorage*; read UserData via IGSharp_SelectionExternalStorage_GetUserData(self).
typedef void (*IGSharp_SelectionExternalStorageAdapter)(void* self, int idx, bool selected);
IGSHARP_API void* IGSharp_SelectionExternalStorage_Create(void);
IGSHARP_API void  IGSharp_SelectionExternalStorage_Destroy(void* storage);
IGSHARP_API void* IGSharp_SelectionExternalStorage_GetUserData(void* storage);
IGSHARP_API void  IGSharp_SelectionExternalStorage_SetUserData(void* storage, void* user_data);
IGSHARP_API void  IGSharp_SelectionExternalStorage_SetAdapterSetItemSelected(void* storage, IGSharp_SelectionExternalStorageAdapter adapter);
IGSHARP_API void  IGSharp_SelectionExternalStorage_ApplyRequests(void* storage, void* ms_io); // ms_io = ImGuiMultiSelectIO*

//-----------------------------------------------------------------------------
// [SECTION] Drawing API (ImDrawCmd, ImDrawIdx, ImDrawVert, ImDrawChannel, ImDrawListSplitter, ImDrawListFlags, ImDrawList, ImDrawData)
//-----------------------------------------------------------------------------

// ImDrawCallback: a draw command can carry a user callback instead of geometry.
// parent_list is an ImDrawList*, cmd is an ImDrawCmd* (use IGSharp_DrawCmd_* accessors).
typedef void (*IGSharp_DrawCallback)(void* parent_list, void* cmd);
// Sentinel UserCallback value asking the backend to reset its render state. Compare
// IGSharp_DrawCmd_GetUserCallback against this before dereferencing it as a function.
// Mirrors upstream ImDrawCallback_ResetRenderState (== (ImDrawCallback)-8).
#define IGSHARP_DRAWCALLBACK_RESETRENDERSTATE ((void*)(intptr_t)(-8))

// ImDrawIdx is the index type used by ImDrawList index buffers. The wrapper bakes in
// the default 16-bit width (unsigned short); pinned by a static_assert in imgui_sharp_layout_check.cpp.

// ImDrawCmd: accessors (not mirrored: contains ImTextureRef and requires the GetTexID() getter)
IGSHARP_API IGSharp_Vec4 IGSharp_DrawCmd_GetClipRect(void* draw_cmd);
IGSHARP_API unsigned long long IGSharp_DrawCmd_GetTexID(void* draw_cmd);
IGSHARP_API unsigned int IGSharp_DrawCmd_GetVtxOffset(void* draw_cmd);
IGSHARP_API unsigned int IGSharp_DrawCmd_GetIdxOffset(void* draw_cmd);
IGSHARP_API unsigned int IGSharp_DrawCmd_GetElemCount(void* draw_cmd);
IGSHARP_API void* IGSharp_DrawCmd_GetUserCallback(void* draw_cmd);
IGSHARP_API void* IGSharp_DrawCmd_GetUserCallbackData(void* draw_cmd);
IGSHARP_API int IGSharp_DrawCmd_GetUserCallbackDataSize(void* draw_cmd);

// ImDrawVert: layout-compatible mirror of the default ImDrawVert (20 bytes).
// Only valid when IMGUI_OVERRIDE_DRAWVERT_STRUCT_LAYOUT is NOT defined (the default).
// Lets .NET read ImDrawList vertex buffers (VtxBuffer) for custom rendering.
typedef struct IGSharp_DrawVert {
    IGSharp_Vec2 pos;
    IGSharp_Vec2 uv;
    unsigned int col; // ImU32
} IGSharp_DrawVert;

// ImDrawListSplitter (accessors)
// ImDrawListSplitter (helper to split a draw list into layers; opaque handle)
IGSHARP_API void* IGSharp_DrawListSplitter_Create(void);
IGSHARP_API void  IGSharp_DrawListSplitter_Destroy(void* splitter);
IGSHARP_API void  IGSharp_DrawListSplitter_Clear(void* splitter);
IGSHARP_API void  IGSharp_DrawListSplitter_ClearFreeMemory(void* splitter);
IGSHARP_API void  IGSharp_DrawListSplitter_Split(void* splitter, void* draw_list, int count);
IGSHARP_API void  IGSharp_DrawListSplitter_Merge(void* splitter, void* draw_list);
IGSHARP_API void  IGSharp_DrawListSplitter_SetCurrentChannel(void* splitter, void* draw_list, int channel_idx);

// ImDrawFlags_
// Flags for ImDrawList functions (AddRect, AddRectFilled, PathStroke, PathRect, ...).
// Mirrored from upstream Dear ImGui ImDrawFlags_ — values must match upstream
// exactly, validated per-value by static_assert in imgui_sharp_layout_check.cpp.
// Passed to the DrawList wrapper functions as plain int.
typedef enum {
    IGSharp_DrawFlags_None                    = 0,
    IGSharp_DrawFlags_Closed                  = 1 << 0,  // PathStroke(), AddPolyline(): specify that shape should be closed (Important: this is always == 1 for legacy reason)
    IGSharp_DrawFlags_RoundCornersTopLeft     = 1 << 4,  // AddRect(), AddRectFilled(), PathRect(): enable rounding top-left corner only (when rounding > 0.0f, we default to all corners).
    IGSharp_DrawFlags_RoundCornersTopRight    = 1 << 5,  // AddRect(), AddRectFilled(), PathRect(): enable rounding top-right corner only (when rounding > 0.0f, we default to all corners).
    IGSharp_DrawFlags_RoundCornersBottomLeft  = 1 << 6,  // AddRect(), AddRectFilled(), PathRect(): enable rounding bottom-left corner only (when rounding > 0.0f, we default to all corners).
    IGSharp_DrawFlags_RoundCornersBottomRight = 1 << 7,  // AddRect(), AddRectFilled(), PathRect(): enable rounding bottom-right corner only (when rounding > 0.0f, we default to all corners).
    IGSharp_DrawFlags_RoundCornersNone        = 1 << 8,  // AddRect(), AddRectFilled(), PathRect(): disable rounding on all corners (when rounding > 0.0f). This is NOT zero, NOT an implicit flag!
    IGSharp_DrawFlags_RoundCornersTop         = IGSharp_DrawFlags_RoundCornersTopLeft | IGSharp_DrawFlags_RoundCornersTopRight,
    IGSharp_DrawFlags_RoundCornersBottom      = IGSharp_DrawFlags_RoundCornersBottomLeft | IGSharp_DrawFlags_RoundCornersBottomRight,
    IGSharp_DrawFlags_RoundCornersLeft        = IGSharp_DrawFlags_RoundCornersBottomLeft | IGSharp_DrawFlags_RoundCornersTopLeft,
    IGSharp_DrawFlags_RoundCornersRight       = IGSharp_DrawFlags_RoundCornersBottomRight | IGSharp_DrawFlags_RoundCornersTopRight,
    IGSharp_DrawFlags_RoundCornersAll         = IGSharp_DrawFlags_RoundCornersTopLeft | IGSharp_DrawFlags_RoundCornersTopRight | IGSharp_DrawFlags_RoundCornersBottomLeft | IGSharp_DrawFlags_RoundCornersBottomRight,
    IGSharp_DrawFlags_RoundCornersDefault_    = IGSharp_DrawFlags_RoundCornersAll, // Default to ALL corners if none of the _RoundCornersXX flags are specified.
    IGSharp_DrawFlags_RoundCornersMask_       = IGSharp_DrawFlags_RoundCornersAll | IGSharp_DrawFlags_RoundCornersNone,
} IGSharp_DrawFlags;

// ImDrawListFlags_
// Flags for ImDrawList instance. Used as ImDrawList::Flags. Passed to functions as plain int.
typedef enum {
    IGSharp_DrawListFlags_None                   = 0,
    IGSharp_DrawListFlags_AntiAliasedLines       = 1 << 0,  // Enable anti-aliased lines/borders
    IGSharp_DrawListFlags_AntiAliasedLinesUseTex = 1 << 1,  // Enable anti-aliased lines/borders using textures when possible
    IGSharp_DrawListFlags_AntiAliasedFill        = 1 << 2,  // Enable anti-aliased edge around filled shapes
    IGSharp_DrawListFlags_AllowVtxOffset         = 1 << 3,  // Can emit 'VtxOffset > 0' to allow large meshes
} IGSharp_DrawListFlags;

// ImDrawList: Clipping
IGSHARP_API void IGSharp_DrawList_PushClipRect(void* draw_list, IGSharp_Vec2 clip_rect_min, IGSharp_Vec2 clip_rect_max, bool intersect_with_current);
IGSHARP_API void IGSharp_DrawList_PushClipRectFullScreen(void* draw_list);
IGSHARP_API void IGSharp_DrawList_PopClipRect(void* draw_list);

// ImDrawList: Texture state
IGSHARP_API void IGSharp_DrawList_PushTexture(void* draw_list, unsigned long long tex_id);
IGSHARP_API void IGSharp_DrawList_PushTextureData(void* draw_list, void* tex_data); // ImTextureData* (preserves deferred resolution; NULL == no texture)
IGSHARP_API void IGSharp_DrawList_PopTexture(void* draw_list);

// ImDrawList: Clip rect query
IGSHARP_API IGSharp_Vec2 IGSharp_DrawList_GetClipRectMin(void* draw_list);
IGSHARP_API IGSharp_Vec2 IGSharp_DrawList_GetClipRectMax(void* draw_list);

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
// ImDrawList: Text with explicit font
IGSHARP_API void IGSharp_DrawList_AddTextFont(void* draw_list, void* font, float font_size, IGSharp_Vec2 pos, unsigned int col, const char* text_begin, const char* text_end, float wrap_width, const IGSharp_Vec4* cpu_fine_clip_rect);

// ImDrawList: Images
IGSHARP_API void IGSharp_DrawList_AddImage(void* draw_list, unsigned long long tex_id, IGSharp_Vec2 p_min, IGSharp_Vec2 p_max, IGSharp_Vec2 uv_min, IGSharp_Vec2 uv_max, unsigned int col);
IGSHARP_API void IGSharp_DrawList_AddImageQuad(void* draw_list, unsigned long long tex_id, IGSharp_Vec2 p1, IGSharp_Vec2 p2, IGSharp_Vec2 p3, IGSharp_Vec2 p4, IGSharp_Vec2 uv1, IGSharp_Vec2 uv2, IGSharp_Vec2 uv3, IGSharp_Vec2 uv4, unsigned int col);
IGSHARP_API void IGSharp_DrawList_AddImageRounded(void* draw_list, unsigned long long tex_id, IGSharp_Vec2 p_min, IGSharp_Vec2 p_max, IGSharp_Vec2 uv_min, IGSharp_Vec2 uv_max, unsigned int col, float rounding, int flags);
// ImTextureData* variants (preserve deferred ImTextureID resolution for atlas/backend textures; tex_data may be NULL).
IGSHARP_API void IGSharp_DrawList_AddImageTextureData(void* draw_list, void* tex_data, IGSharp_Vec2 p_min, IGSharp_Vec2 p_max, IGSharp_Vec2 uv_min, IGSharp_Vec2 uv_max, unsigned int col);
IGSHARP_API void IGSharp_DrawList_AddImageQuadTextureData(void* draw_list, void* tex_data, IGSharp_Vec2 p1, IGSharp_Vec2 p2, IGSharp_Vec2 p3, IGSharp_Vec2 p4, IGSharp_Vec2 uv1, IGSharp_Vec2 uv2, IGSharp_Vec2 uv3, IGSharp_Vec2 uv4, unsigned int col);
IGSHARP_API void IGSharp_DrawList_AddImageRoundedTextureData(void* draw_list, void* tex_data, IGSharp_Vec2 p_min, IGSharp_Vec2 p_max, IGSharp_Vec2 uv_min, IGSharp_Vec2 uv_max, unsigned int col, float rounding, int flags);

// ImDrawList: Path API
IGSHARP_API void IGSharp_DrawList_PathClear(void* draw_list);
IGSHARP_API void IGSharp_DrawList_PathLineTo(void* draw_list, IGSharp_Vec2 pos);
IGSHARP_API void IGSharp_DrawList_PathLineToMergeDuplicate(void* draw_list, IGSharp_Vec2 pos);
IGSHARP_API void IGSharp_DrawList_PathFillConvex(void* draw_list, unsigned int col);
IGSHARP_API void IGSharp_DrawList_PathFillConcave(void* draw_list, unsigned int col);
IGSHARP_API void IGSharp_DrawList_PathStroke(void* draw_list, unsigned int col, int flags, float thickness);
IGSHARP_API void IGSharp_DrawList_PathArcTo(void* draw_list, IGSharp_Vec2 center, float radius, float a_min, float a_max, int num_segments);
IGSHARP_API void IGSharp_DrawList_PathArcToFast(void* draw_list, IGSharp_Vec2 center, float radius, int a_min_of_12, int a_max_of_12);
IGSHARP_API void IGSharp_DrawList_PathEllipticalArcTo(void* draw_list, IGSharp_Vec2 center, IGSharp_Vec2 radius, float rot, float a_min, float a_max, int num_segments);
IGSHARP_API void IGSharp_DrawList_PathBezierCubicCurveTo(void* draw_list, IGSharp_Vec2 p2, IGSharp_Vec2 p3, IGSharp_Vec2 p4, int num_segments);
IGSHARP_API void IGSharp_DrawList_PathBezierQuadraticCurveTo(void* draw_list, IGSharp_Vec2 p2, IGSharp_Vec2 p3, int num_segments);
IGSHARP_API void IGSharp_DrawList_PathRect(void* draw_list, IGSharp_Vec2 rect_min, IGSharp_Vec2 rect_max, float rounding, int flags);

// ImDrawList: Advanced (callbacks, draw commands, cloning)
IGSHARP_API void IGSharp_DrawList_AddCallback(void* draw_list, void* callback, void* userdata, size_t userdata_size);
IGSHARP_API void IGSharp_DrawList_AddDrawCmd(void* draw_list);
IGSHARP_API void* IGSharp_DrawList_CloneOutput(void* draw_list);   // returns a heap ImDrawList*; free with IGSharp_DrawList_Destroy
// Create/destroy a standalone ImDrawList (e.g. to own a CloneOutput result or build a custom list).
// shared_data: pass IGSharp_GetDrawListSharedData(), or NULL.
IGSHARP_API void* IGSharp_DrawList_Create(void* shared_data);      // ImDrawListSharedData*
IGSHARP_API void  IGSharp_DrawList_Destroy(void* draw_list);

// ImDrawList: Channels splitting/merging
IGSHARP_API void IGSharp_DrawList_ChannelsSplit(void* draw_list, int count);
IGSHARP_API void IGSharp_DrawList_ChannelsMerge(void* draw_list);
IGSHARP_API void IGSharp_DrawList_ChannelsSetCurrent(void* draw_list, int n);

// ImDrawList: Advanced - Primitives allocations (for custom mesh generation)
IGSHARP_API void IGSharp_DrawList_PrimReserve(void* draw_list, int idx_count, int vtx_count);
IGSHARP_API void IGSharp_DrawList_PrimUnreserve(void* draw_list, int idx_count, int vtx_count);
IGSHARP_API void IGSharp_DrawList_PrimRect(void* draw_list, IGSharp_Vec2 a, IGSharp_Vec2 b, unsigned int col);
IGSHARP_API void IGSharp_DrawList_PrimRectUV(void* draw_list, IGSharp_Vec2 a, IGSharp_Vec2 b, IGSharp_Vec2 uv_a, IGSharp_Vec2 uv_b, unsigned int col);
IGSHARP_API void IGSharp_DrawList_PrimQuadUV(void* draw_list, IGSharp_Vec2 a, IGSharp_Vec2 b, IGSharp_Vec2 c, IGSharp_Vec2 d, IGSharp_Vec2 uv_a, IGSharp_Vec2 uv_b, IGSharp_Vec2 uv_c, IGSharp_Vec2 uv_d, unsigned int col);
IGSHARP_API void IGSharp_DrawList_PrimWriteVtx(void* draw_list, IGSharp_Vec2 pos, IGSharp_Vec2 uv, unsigned int col);
IGSHARP_API void IGSharp_DrawList_PrimWriteIdx(void* draw_list, unsigned short idx);
IGSHARP_API void IGSharp_DrawList_PrimVtx(void* draw_list, IGSharp_Vec2 pos, IGSharp_Vec2 uv, unsigned int col);

// ImDrawList: Buffer / flag access (ImDrawList is not mirrored; required for a .NET renderer)
IGSHARP_API int   IGSharp_DrawList_GetFlags(void* draw_list);                 // ImDrawListFlags
IGSHARP_API void  IGSharp_DrawList_SetFlags(void* draw_list, int flags);      // ImDrawListFlags
IGSHARP_API int   IGSharp_DrawList_GetCmdBufferSize(void* draw_list);
IGSHARP_API void* IGSharp_DrawList_GetCmdBufferData(void* draw_list);         // ImDrawCmd* (base; element stride is opaque — use IGSharp_DrawList_GetCmd to index)
IGSHARP_API void* IGSharp_DrawList_GetCmd(void* draw_list, int index);        // ImDrawCmd* at index (feed to IGSharp_DrawCmd_* accessors)
IGSHARP_API int   IGSharp_DrawList_GetIdxBufferSize(void* draw_list);
IGSHARP_API void* IGSharp_DrawList_GetIdxBufferData(void* draw_list);         // ImDrawIdx* (unsigned short)
IGSHARP_API int   IGSharp_DrawList_GetVtxBufferSize(void* draw_list);
IGSHARP_API void* IGSharp_DrawList_GetVtxBufferData(void* draw_list);         // ImDrawVert*

// ImDrawData (accessors; obtain via IGSharp_GetDrawData())
IGSHARP_API bool         IGSharp_DrawData_GetValid(void* draw_data);
IGSHARP_API int          IGSharp_DrawData_GetCmdListsCount(void* draw_data);
IGSHARP_API int          IGSharp_DrawData_GetTotalIdxCount(void* draw_data);
IGSHARP_API int          IGSharp_DrawData_GetTotalVtxCount(void* draw_data);
IGSHARP_API void*        IGSharp_DrawData_GetCmdList(void* draw_data, int index); // -> ImDrawList*
IGSHARP_API IGSharp_Vec2 IGSharp_DrawData_GetDisplayPos(void* draw_data);
IGSHARP_API IGSharp_Vec2 IGSharp_DrawData_GetDisplaySize(void* draw_data);
IGSHARP_API IGSharp_Vec2 IGSharp_DrawData_GetFramebufferScale(void* draw_data);
IGSHARP_API void*        IGSharp_DrawData_GetOwnerViewport(void* draw_data); // -> ImGuiViewport*
IGSHARP_API void         IGSharp_DrawData_Clear(void* draw_data);
IGSHARP_API void         IGSharp_DrawData_AddDrawList(void* draw_data, void* draw_list);
IGSHARP_API void         IGSharp_DrawData_DeIndexAllBuffers(void* draw_data);
IGSHARP_API void         IGSharp_DrawData_ScaleClipRects(void* draw_data, IGSharp_Vec2 fb_scale);
// ImDrawData: Textures list (ImVector<ImTextureData*>* — the pointer itself may be NULL)
IGSHARP_API int   IGSharp_DrawData_GetTexturesCount(void* draw_data);
IGSHARP_API void* IGSharp_DrawData_GetTexturesData(void* draw_data);  // -> ImTextureData**
IGSHARP_API void* IGSharp_DrawData_GetTextures(void* draw_data);                 // -> ImVector<ImTextureData*>* (may be NULL)
IGSHARP_API void  IGSharp_DrawData_SetTextures(void* draw_data, void* textures); // override or set NULL to manage textures yourself

//-----------------------------------------------------------------------------
// [SECTION] Texture API (ImTextureFormat, ImTextureStatus, ImTextureRect, ImTextureData)
//-----------------------------------------------------------------------------

// ImTextureFormat
typedef enum {
    IGSharp_TextureFormat_RGBA32,   // 4 components per pixel, each is unsigned 8-bit. Total size = TexWidth * TexHeight * 4
    IGSharp_TextureFormat_Alpha8,   // 1 component per pixel, each is unsigned 8-bit. Total size = TexWidth * TexHeight
} IGSharp_TextureFormat;

// ImTextureStatus
// Status of a texture to communicate with Renderer Backend.
// Mirrored from upstream Dear ImGui. Values must match upstream exactly —
// validated per-value by static_assert in imgui_sharp_layout_check.cpp.
typedef enum {
    IGSharp_TextureStatus_OK,
    IGSharp_TextureStatus_Destroyed,
    IGSharp_TextureStatus_WantCreate,
    IGSharp_TextureStatus_WantUpdates,
    IGSharp_TextureStatus_WantDestroy,
} IGSharp_TextureStatus;

// ImTextureRect: coordinates of a rectangle within a texture. Pure POD mirror.
typedef struct {
    unsigned short x;
    unsigned short y;
    unsigned short w;
    unsigned short h;
} IGSharp_TextureRect;

// ImTextureData accessors
// ImTextureData (accessors; not mirrored — backend-facing struct with behavioral members)
// tex_data is an opaque ImTextureData* (e.g. from a renderer backend or ImFontAtlas).
IGSHARP_API int                IGSharp_TextureData_GetUniqueID(void* tex_data);
IGSHARP_API int                IGSharp_TextureData_GetStatus(void* tex_data);          // ImTextureStatus
IGSHARP_API void*              IGSharp_TextureData_GetBackendUserData(void* tex_data);
IGSHARP_API void               IGSharp_TextureData_SetBackendUserData(void* tex_data, void* backend_user_data);
IGSHARP_API unsigned long long IGSharp_TextureData_GetTexID(void* tex_data);           // ImTextureID
IGSHARP_API int                IGSharp_TextureData_GetFormat(void* tex_data);          // ImTextureFormat
IGSHARP_API int                IGSharp_TextureData_GetWidth(void* tex_data);
IGSHARP_API int                IGSharp_TextureData_GetHeight(void* tex_data);
IGSHARP_API int                IGSharp_TextureData_GetBytesPerPixel(void* tex_data);
IGSHARP_API unsigned char*     IGSharp_TextureData_GetPixels(void* tex_data);
IGSHARP_API void               IGSharp_TextureData_GetUsedRect(void* tex_data, unsigned short* x, unsigned short* y, unsigned short* w, unsigned short* h);
IGSHARP_API void               IGSharp_TextureData_GetUpdateRect(void* tex_data, unsigned short* x, unsigned short* y, unsigned short* w, unsigned short* h);
// Individual update rectangles a backend must apply when Status == WantUpdates (the GetUpdateRect above is their bounding box).
IGSHARP_API int                IGSharp_TextureData_GetUpdatesCount(void* tex_data);
IGSHARP_API void               IGSharp_TextureData_GetUpdate(void* tex_data, int index, unsigned short* x, unsigned short* y, unsigned short* w, unsigned short* h);
IGSHARP_API int                IGSharp_TextureData_GetUnusedFrames(void* tex_data);
IGSHARP_API unsigned short     IGSharp_TextureData_GetRefCount(void* tex_data);
IGSHARP_API bool               IGSharp_TextureData_GetUseColors(void* tex_data);
// Methods
IGSHARP_API void               IGSharp_TextureData_Create(void* tex_data, int format, int w, int h); // format = ImTextureFormat
IGSHARP_API void               IGSharp_TextureData_DestroyPixels(void* tex_data);
IGSHARP_API void*              IGSharp_TextureData_GetPixelsPtr(void* tex_data);
IGSHARP_API void*              IGSharp_TextureData_GetPixelsAt(void* tex_data, int x, int y);
IGSHARP_API int                IGSharp_TextureData_GetSizeInBytes(void* tex_data);
IGSHARP_API int                IGSharp_TextureData_GetPitch(void* tex_data);
IGSHARP_API void               IGSharp_TextureData_SetTexID(void* tex_data, unsigned long long tex_id); // tex_id = ImTextureID
IGSHARP_API void               IGSharp_TextureData_SetStatus(void* tex_data, int status);               // status = ImTextureStatus

//-----------------------------------------------------------------------------
// [SECTION] Font API (ImFontConfig, ImFontGlyph, ImFontAtlasFlags, ImFontAtlas, ImFontGlyphRangesBuilder, ImFont)
//-----------------------------------------------------------------------------

// ImFontConfig (accessors)
// ImFontConfig (accessors; not mirrored — interleaves [Internal] members and has a non-trivial ctor)
IGSHARP_API void* IGSharp_FontConfig_Create(void);
IGSHARP_API void  IGSharp_FontConfig_Destroy(void* cfg);

IGSHARP_API const char* IGSharp_FontConfig_GetName(void* cfg);
IGSHARP_API void        IGSharp_FontConfig_SetName(void* cfg, const char* name);
IGSHARP_API void*       IGSharp_FontConfig_GetFontData(void* cfg);
IGSHARP_API void        IGSharp_FontConfig_SetFontData(void* cfg, void* font_data);
IGSHARP_API int         IGSharp_FontConfig_GetFontDataSize(void* cfg);
IGSHARP_API void        IGSharp_FontConfig_SetFontDataSize(void* cfg, int font_data_size);
IGSHARP_API bool        IGSharp_FontConfig_GetFontDataOwnedByAtlas(void* cfg);
IGSHARP_API void        IGSharp_FontConfig_SetFontDataOwnedByAtlas(void* cfg, bool value);
IGSHARP_API bool        IGSharp_FontConfig_GetMergeMode(void* cfg);
IGSHARP_API void        IGSharp_FontConfig_SetMergeMode(void* cfg, bool value);
IGSHARP_API bool        IGSharp_FontConfig_GetPixelSnapH(void* cfg);
IGSHARP_API void        IGSharp_FontConfig_SetPixelSnapH(void* cfg, bool value);
IGSHARP_API int         IGSharp_FontConfig_GetOversampleH(void* cfg);
IGSHARP_API void        IGSharp_FontConfig_SetOversampleH(void* cfg, int value);
IGSHARP_API int         IGSharp_FontConfig_GetOversampleV(void* cfg);
IGSHARP_API void        IGSharp_FontConfig_SetOversampleV(void* cfg, int value);
IGSHARP_API unsigned short IGSharp_FontConfig_GetEllipsisChar(void* cfg);
IGSHARP_API void           IGSharp_FontConfig_SetEllipsisChar(void* cfg, unsigned short value);
IGSHARP_API float       IGSharp_FontConfig_GetSizePixels(void* cfg);
IGSHARP_API void        IGSharp_FontConfig_SetSizePixels(void* cfg, float value);
IGSHARP_API const unsigned short* IGSharp_FontConfig_GetGlyphRanges(void* cfg);
IGSHARP_API void                  IGSharp_FontConfig_SetGlyphRanges(void* cfg, const unsigned short* ranges);
IGSHARP_API const unsigned short* IGSharp_FontConfig_GetGlyphExcludeRanges(void* cfg);
IGSHARP_API void                  IGSharp_FontConfig_SetGlyphExcludeRanges(void* cfg, const unsigned short* ranges);
IGSHARP_API IGSharp_Vec2 IGSharp_FontConfig_GetGlyphOffset(void* cfg);
IGSHARP_API void         IGSharp_FontConfig_SetGlyphOffset(void* cfg, IGSharp_Vec2 value);
IGSHARP_API float       IGSharp_FontConfig_GetGlyphMinAdvanceX(void* cfg);
IGSHARP_API void        IGSharp_FontConfig_SetGlyphMinAdvanceX(void* cfg, float value);
IGSHARP_API float       IGSharp_FontConfig_GetGlyphMaxAdvanceX(void* cfg);
IGSHARP_API void        IGSharp_FontConfig_SetGlyphMaxAdvanceX(void* cfg, float value);
IGSHARP_API float       IGSharp_FontConfig_GetGlyphExtraAdvanceX(void* cfg);
IGSHARP_API void        IGSharp_FontConfig_SetGlyphExtraAdvanceX(void* cfg, float value);
IGSHARP_API unsigned int IGSharp_FontConfig_GetFontNo(void* cfg);
IGSHARP_API void         IGSharp_FontConfig_SetFontNo(void* cfg, unsigned int value);
IGSHARP_API unsigned int IGSharp_FontConfig_GetFontLoaderFlags(void* cfg);
IGSHARP_API void         IGSharp_FontConfig_SetFontLoaderFlags(void* cfg, unsigned int value);
IGSHARP_API float       IGSharp_FontConfig_GetRasterizerMultiply(void* cfg);
IGSHARP_API void        IGSharp_FontConfig_SetRasterizerMultiply(void* cfg, float value);
IGSHARP_API float       IGSharp_FontConfig_GetRasterizerDensity(void* cfg);
IGSHARP_API void        IGSharp_FontConfig_SetRasterizerDensity(void* cfg, float value);
IGSHARP_API float       IGSharp_FontConfig_GetExtraSizeScale(void* cfg);
IGSHARP_API void        IGSharp_FontConfig_SetExtraSizeScale(void* cfg, float value);

// ImFontGlyph (accessors)
// ImFontGlyph (accessors; leading members are bitfields so not mirrored)
IGSHARP_API bool  IGSharp_FontGlyph_GetColored(void* glyph);
IGSHARP_API bool  IGSharp_FontGlyph_GetVisible(void* glyph);
IGSHARP_API int   IGSharp_FontGlyph_GetSourceIdx(void* glyph);
IGSHARP_API unsigned int IGSharp_FontGlyph_GetCodepoint(void* glyph);
IGSHARP_API float IGSharp_FontGlyph_GetAdvanceX(void* glyph);
IGSHARP_API float IGSharp_FontGlyph_GetX0(void* glyph);
IGSHARP_API float IGSharp_FontGlyph_GetY0(void* glyph);
IGSHARP_API float IGSharp_FontGlyph_GetX1(void* glyph);
IGSHARP_API float IGSharp_FontGlyph_GetY1(void* glyph);
IGSHARP_API float IGSharp_FontGlyph_GetU0(void* glyph);
IGSHARP_API float IGSharp_FontGlyph_GetV0(void* glyph);
IGSHARP_API float IGSharp_FontGlyph_GetU1(void* glyph);
IGSHARP_API float IGSharp_FontGlyph_GetV1(void* glyph);
IGSHARP_API int   IGSharp_FontGlyph_GetPackId(void* glyph);   // ImFontAtlasRectId (-1 if none); pass to IGSharp_FontAtlas_GetCustomRect to refresh UVs

// ImFontGlyphRangesBuilder
// --- ImFontGlyphRangesBuilder (opaque helper; ImWchar passed as unsigned short) ---
IGSHARP_API void* IGSharp_FontGlyphRangesBuilder_New(void);
IGSHARP_API void  IGSharp_FontGlyphRangesBuilder_Delete(void* builder);
IGSHARP_API void  IGSharp_FontGlyphRangesBuilder_Clear(void* builder);
IGSHARP_API bool  IGSharp_FontGlyphRangesBuilder_GetBit(void* builder, size_t n);
IGSHARP_API void  IGSharp_FontGlyphRangesBuilder_SetBit(void* builder, size_t n);
IGSHARP_API void  IGSharp_FontGlyphRangesBuilder_AddChar(void* builder, unsigned short c);
IGSHARP_API void  IGSharp_FontGlyphRangesBuilder_AddText(void* builder, const char* text, const char* text_end);
IGSHARP_API void  IGSharp_FontGlyphRangesBuilder_AddRanges(void* builder, const unsigned short* ranges);
// Builds the glyph ranges and copies up to out_ranges_capacity entries (terminated by a trailing 0)
// into out_ranges. Returns the total number of entries the built ranges require (which may exceed
// out_ranges_capacity); call once with out_ranges=NULL/capacity=0 to query the needed size.
IGSHARP_API int   IGSharp_FontGlyphRangesBuilder_BuildRanges(void* builder, unsigned short* out_ranges, int out_ranges_capacity);

// ImFontAtlas custom rectangles
// ImFontAtlasRect: layout-compatible mirror of upstream ImFontAtlasRect.
// Output of GetCustomRect()/AddCustomRect(). Do not cache (only valid for current texture).
// Note: ImFontAtlasRectId is just a typedef for int; pass/return it as plain int.
typedef struct IGSharp_FontAtlasRect {
    unsigned short x, y;        // Position (in current texture)
    unsigned short w, h;        // Size
    IGSharp_Vec2   uv0, uv1;    // UV coordinates (in current texture)
} IGSharp_FontAtlasRect;

// ImFontAtlasFlags_
// Flags for ImFontAtlas build (passed to functions as plain int).
typedef enum {
    IGSharp_FontAtlasFlags_None               = 0,
    IGSharp_FontAtlasFlags_NoPowerOfTwoHeight = 1 << 0,   // Don't round the height to next power of two
    IGSharp_FontAtlasFlags_NoMouseCursors     = 1 << 1,   // Don't build software mouse cursors into the atlas (save a little texture memory)
    IGSharp_FontAtlasFlags_NoBakedLines       = 1 << 2,   // Don't build thick line textures into the atlas (save a little texture memory, allow support for point/nearest filtering)
} IGSharp_FontAtlasFlags;

// ImFontAtlas
// Construct a standalone atlas (contexts normally create & own their own — reach that one via
// the IGSharp_IO.Fonts field). Create one here only to share it across contexts by passing it to
// IGSharp_CreateContext(); you then own it and must call IGSharp_FontAtlas_Destroy after the
// sharing contexts are destroyed.
IGSHARP_API void* IGSharp_FontAtlas_Create(void);
IGSHARP_API void  IGSharp_FontAtlas_Destroy(void* atlas);
// font_cfg (const ImFontConfig*, may be NULL) and glyph_ranges (const ImWchar*/unsigned short*, may be
// NULL) mirror the upstream optional parameters: pass them to merge fonts, set oversampling, restrict
// glyph ranges, etc. Build a config with IGSharp_FontConfig_Create()/IGSharp_FontConfig_Set*().
IGSHARP_API void* IGSharp_FontAtlas_AddFontDefault(void* atlas, const void* font_cfg);
IGSHARP_API void* IGSharp_FontAtlas_AddFontFromFileTTF(void* atlas, const char* filename, float size_pixels, const void* font_cfg, const unsigned short* glyph_ranges);
IGSHARP_API void* IGSharp_FontAtlas_AddFontFromMemoryTTF(void* atlas, void* font_data, int font_data_size, float size_pixels, bool transfer_ownership);
IGSHARP_API void* IGSharp_FontAtlas_AddFontFromMemoryCompressedTTF(void* atlas, const void* compressed_data, int compressed_size, float size_pixels, const void* font_cfg, const unsigned short* glyph_ranges);
IGSHARP_API void  IGSharp_FontAtlas_Clear(void* atlas);
IGSHARP_API void  IGSharp_FontAtlas_ClearFonts(void* atlas);
IGSHARP_API int   IGSharp_FontAtlas_GetFontCount(void* atlas);
IGSHARP_API void* IGSharp_FontAtlas_GetFont(void* atlas, int index);

// ImFontAtlas font construction & lifecycle
IGSHARP_API void* IGSharp_FontAtlas_AddFont(void* atlas, const void* font_cfg); // font_cfg: const ImFontConfig*
IGSHARP_API void* IGSharp_FontAtlas_AddFontDefaultVector(void* atlas, const void* font_cfg);
IGSHARP_API void* IGSharp_FontAtlas_AddFontDefaultBitmap(void* atlas, const void* font_cfg);
IGSHARP_API void* IGSharp_FontAtlas_AddFontFromMemoryCompressedBase85TTF(void* atlas, const char* compressed_data_base85, float size_pixels, const void* font_cfg, const unsigned short* glyph_ranges);
IGSHARP_API void  IGSharp_FontAtlas_RemoveFont(void* atlas, void* font);
IGSHARP_API void  IGSharp_FontAtlas_CompactCache(void* atlas);
IGSHARP_API void  IGSharp_FontAtlas_SetFontLoader(void* atlas, const void* font_loader); // font_loader: const ImFontLoader*
IGSHARP_API void  IGSharp_FontAtlas_ClearInputData(void* atlas);
IGSHARP_API void  IGSharp_FontAtlas_ClearTexData(void* atlas);
IGSHARP_API const unsigned short* IGSharp_FontAtlas_GetGlyphRangesDefault(void* atlas); // const ImWchar*

// --- Fonts: Custom rectangles (ImFontAtlasRectId is int; -1 == invalid) ---
IGSHARP_API int  IGSharp_FontAtlas_AddCustomRect(void* atlas, int width, int height, IGSharp_FontAtlasRect* out_r);
IGSHARP_API void IGSharp_FontAtlas_RemoveCustomRect(void* atlas, int id);
IGSHARP_API bool IGSharp_FontAtlas_GetCustomRect(void* atlas, int id, IGSharp_FontAtlasRect* out_r);

// ImFontAtlas member field accessors
// ImFontAtlas field accessors (ImFontAtlas is a behavioral struct, not mirrored)
// Input
IGSHARP_API int          IGSharp_FontAtlas_GetFlags(void* atlas);                 // ImFontAtlasFlags
IGSHARP_API void         IGSharp_FontAtlas_SetFlags(void* atlas, int flags);      // ImFontAtlasFlags
IGSHARP_API int          IGSharp_FontAtlas_GetTexDesiredFormat(void* atlas);      // ImTextureFormat
IGSHARP_API void         IGSharp_FontAtlas_SetTexDesiredFormat(void* atlas, int format); // ImTextureFormat
IGSHARP_API int          IGSharp_FontAtlas_GetTexGlyphPadding(void* atlas);
IGSHARP_API void         IGSharp_FontAtlas_SetTexGlyphPadding(void* atlas, int padding);
IGSHARP_API int          IGSharp_FontAtlas_GetTexMinWidth(void* atlas);
IGSHARP_API void         IGSharp_FontAtlas_SetTexMinWidth(void* atlas, int width);
IGSHARP_API int          IGSharp_FontAtlas_GetTexMinHeight(void* atlas);
IGSHARP_API void         IGSharp_FontAtlas_SetTexMinHeight(void* atlas, int height);
IGSHARP_API int          IGSharp_FontAtlas_GetTexMaxWidth(void* atlas);
IGSHARP_API void         IGSharp_FontAtlas_SetTexMaxWidth(void* atlas, int width);
IGSHARP_API int          IGSharp_FontAtlas_GetTexMaxHeight(void* atlas);
IGSHARP_API void         IGSharp_FontAtlas_SetTexMaxHeight(void* atlas, int height);
IGSHARP_API void*        IGSharp_FontAtlas_GetUserData(void* atlas);
IGSHARP_API void         IGSharp_FontAtlas_SetUserData(void* atlas, void* user_data);
// Output
// Resolved low-level ImTextureID. Lossy: returns IGSHARP_TEXTUREID_INVALID until the
// renderer backend has uploaded the atlas texture. To bind the atlas into draw commands
// before/across uploads, use GetTexData below with the *TextureData image variants.
IGSHARP_API unsigned long long IGSharp_FontAtlas_GetTexID(void* atlas);
IGSHARP_API void*        IGSharp_FontAtlas_GetTexData(void* atlas);               // ImTextureData* (preserves deferred resolution)
IGSHARP_API bool         IGSharp_FontAtlas_GetTexPixelsUseColors(void* atlas);
IGSHARP_API void         IGSharp_FontAtlas_SetTexPixelsUseColors(void* atlas, bool v); // set true when rendering colored output into custom rects
IGSHARP_API IGSharp_Vec2 IGSharp_FontAtlas_GetTexUvScale(void* atlas);
IGSHARP_API IGSharp_Vec2 IGSharp_FontAtlas_GetTexUvWhitePixel(void* atlas);
IGSHARP_API bool         IGSharp_FontAtlas_GetTexIsBuilt(void* atlas);
IGSHARP_API bool         IGSharp_FontAtlas_GetLocked(void* atlas);
IGSHARP_API bool         IGSharp_FontAtlas_GetRendererHasTextures(void* atlas);
IGSHARP_API const char*  IGSharp_FontAtlas_GetFontLoaderName(void* atlas);     // == FontLoader->Name
IGSHARP_API unsigned int IGSharp_FontAtlas_GetFontLoaderFlags(void* atlas);            // shared font-loader flags (e.g. FreeType) for all fonts
IGSHARP_API void         IGSharp_FontAtlas_SetFontLoaderFlags(void* atlas, unsigned int flags);

// ImFontBaked accessors & methods
// ImFontBaked (runtime per-size data; pointers valid only for the current frame).
// Most members are [Internal]; exposed as accessor functions rather than a mirror struct.
IGSHARP_API void* IGSharp_FontBaked_FindGlyph(void* baked, unsigned short c);            // ImWchar; returns ImFontGlyph* (U+FFFD fallback glyph if missing)
IGSHARP_API void* IGSharp_FontBaked_FindGlyphNoFallback(void* baked, unsigned short c);  // ImWchar; returns ImFontGlyph*, NULL if glyph doesn't exist
IGSHARP_API float IGSharp_FontBaked_GetCharAdvance(void* baked, unsigned short c);        // ImWchar
IGSHARP_API bool  IGSharp_FontBaked_IsGlyphLoaded(void* baked, unsigned short c);         // ImWchar
IGSHARP_API float IGSharp_FontBaked_GetSize(void* baked);
IGSHARP_API float IGSharp_FontBaked_GetAscent(void* baked);
IGSHARP_API float IGSharp_FontBaked_GetDescent(void* baked);
IGSHARP_API float IGSharp_FontBaked_GetFallbackAdvanceX(void* baked);
IGSHARP_API float IGSharp_FontBaked_GetRasterizerDensity(void* baked);   // density this baked size is baked at
IGSHARP_API int   IGSharp_FontBaked_GetGlyphsCount(void* baked);                  // enumerate all baked glyphs (Glyphs[])
IGSHARP_API void* IGSharp_FontBaked_GetGlyph(void* baked, int index);             // ImFontGlyph* at index
IGSHARP_API void  IGSharp_FontBaked_ClearOutputData(void* baked);                 // [Internal] Don't use unless you know what you're doing

// ImFontFlags_
typedef enum {
    IGSharp_FontFlags_None           = 0,
    IGSharp_FontFlags_NoLoadError    = 1 << 1,  // Disable throwing an error/assert when calling AddFontXXX() with missing file/data. Calling code is expected to check AddFontXXX() return value.
    IGSharp_FontFlags_NoLoadGlyphs   = 1 << 2,  // [Internal] Disable loading new glyphs.
    IGSharp_FontFlags_LockBakedSizes = 1 << 3,  // [Internal] Disable loading new baked sizes, disable garbage collecting current ones.
} IGSharp_FontFlags;

// ImFont accessors & methods
// ImFont (behavioral struct: 'font' is ImFont*)
IGSHARP_API bool         IGSharp_Font_IsGlyphInFont(void* font, unsigned short c);
IGSHARP_API bool         IGSharp_Font_IsLoaded(void* font);
IGSHARP_API const char*  IGSharp_Font_GetDebugName(void* font);
IGSHARP_API void*        IGSharp_Font_GetFontBaked(void* font, float font_size, float density); // returns ImFontBaked*
IGSHARP_API IGSharp_Vec2 IGSharp_Font_CalcTextSizeA(void* font, float size, float max_width, float wrap_width, const char* text_begin, const char* text_end, const char** out_remaining);
IGSHARP_API const char*  IGSharp_Font_CalcWordWrapPosition(void* font, float size, const char* text, const char* text_end, float wrap_width);
IGSHARP_API void         IGSharp_Font_RenderChar(void* font, void* draw_list, float size, IGSharp_Vec2 pos, unsigned int col, unsigned short c, const IGSharp_Vec4* cpu_fine_clip);
IGSHARP_API void         IGSharp_Font_RenderText(void* font, void* draw_list, float size, IGSharp_Vec2 pos, unsigned int col, IGSharp_Vec4 clip_rect, const char* text_begin, const char* text_end, float wrap_width, int flags); // flags: ImDrawTextFlags
IGSHARP_API void         IGSharp_Font_AddRemapChar(void* font, unsigned short from_codepoint, unsigned short to_codepoint);
IGSHARP_API bool         IGSharp_Font_IsGlyphRangeUnused(void* font, unsigned int c_begin, unsigned int c_last);
IGSHARP_API void         IGSharp_Font_ClearOutputData(void* font);               // [Internal] Don't use unless you know what you're doing
// ImFont field accessors
IGSHARP_API void*          IGSharp_Font_GetOwnerAtlas(void* font);   // ImFontAtlas* this font was loaded into
IGSHARP_API int            IGSharp_Font_GetFlags(void* font); // ImFontFlags
IGSHARP_API void           IGSharp_Font_SetFlags(void* font, int flags); // ImFontFlags
IGSHARP_API unsigned short IGSharp_Font_GetFallbackChar(void* font);
IGSHARP_API void           IGSharp_Font_SetFallbackChar(void* font, unsigned short c);
IGSHARP_API unsigned short IGSharp_Font_GetEllipsisChar(void* font);
IGSHARP_API void           IGSharp_Font_SetEllipsisChar(void* font, unsigned short c);
// When swapping EllipsisChar to a custom char, clear EllipsisAutoBake so the "..." glyph isn't re-baked over it.
IGSHARP_API bool           IGSharp_Font_GetEllipsisAutoBake(void* font);
IGSHARP_API void           IGSharp_Font_SetEllipsisAutoBake(void* font, bool v);
IGSHARP_API float          IGSharp_Font_GetLegacySize(void* font);
IGSHARP_API void           IGSharp_Font_SetLegacySize(void* font, float size);

//-----------------------------------------------------------------------------
// [SECTION] Viewports
//-----------------------------------------------------------------------------

// ImGuiViewportFlags_
// Flags stored in ImGuiViewport::Flags
typedef enum IGSharp_ViewportFlags_
{
    IGSharp_ViewportFlags_None              = 0,
    IGSharp_ViewportFlags_IsPlatformWindow  = 1 << 0,   // Represent a Platform Window
    IGSharp_ViewportFlags_IsPlatformMonitor = 1 << 1,   // Represent a Platform Monitor (unused yet)
    IGSharp_ViewportFlags_OwnedByApp        = 1 << 2,   // Platform Window: Is created/managed by the application (rather than a dear imgui backend)
} IGSharp_ViewportFlags_;

// ImGuiViewport
// Core fields (ID/Flags/Pos/Size/FramebufferScale/WorkPos/WorkSize) are intentionally read-only:
// Dear ImGui rewrites them every frame from io.DisplaySize etc., so a setter would have no lasting
// effect. Only the backend-owned PlatformHandle/PlatformHandleRaw fields below have setters.
IGSHARP_API unsigned int IGSharp_Viewport_GetID(void* viewport);
IGSHARP_API int IGSharp_Viewport_GetFlags(void* viewport); // ImGuiViewportFlags
IGSHARP_API IGSharp_Vec2 IGSharp_Viewport_GetPos(void* viewport);
IGSHARP_API IGSharp_Vec2 IGSharp_Viewport_GetSize(void* viewport);
IGSHARP_API IGSharp_Vec2 IGSharp_Viewport_GetFramebufferScale(void* viewport);
IGSHARP_API IGSharp_Vec2 IGSharp_Viewport_GetWorkPos(void* viewport);
IGSHARP_API IGSharp_Vec2 IGSharp_Viewport_GetWorkSize(void* viewport);
IGSHARP_API void* IGSharp_Viewport_GetPlatformHandle(void* viewport);
IGSHARP_API void IGSharp_Viewport_SetPlatformHandle(void* viewport, void* handle);
IGSHARP_API void* IGSharp_Viewport_GetPlatformHandleRaw(void* viewport);
IGSHARP_API void IGSharp_Viewport_SetPlatformHandleRaw(void* viewport, void* handle);
IGSHARP_API IGSharp_Vec2 IGSharp_Viewport_GetCenter(void* viewport);
IGSHARP_API IGSharp_Vec2 IGSharp_Viewport_GetWorkCenter(void* viewport);

//-----------------------------------------------------------------------------
// [SECTION] Platform Dependent Interfaces
//-----------------------------------------------------------------------------

// ImGuiPlatformIO (accessors)
// ImGuiPlatformIO is downgraded to accessors: it interleaves raw C function pointers
// (Platform_GetClipboardTextFn/Platform_SetClipboardTextFn/Platform_OpenInShellFn/
// Platform_SetImeDataFn) taking ImGuiContext*/ImGuiViewport*/ImGuiPlatformImeData* and an
// ImVector<ImTextureData*> Textures (backend-internal), so it is NOT a faithful POD mirror.
// The struct is opaque; obtain a pointer via IGSharp_GetPlatformIO() (declared above).

// Function-pointer typedefs for the clipboard/open-in-shell/IME override setters.
// viewport/ime_data are opaque (ImGuiViewport* / ImGuiPlatformImeData*).
typedef const char* (*IGSharp_Platform_GetClipboardTextFn)(IGSharp_Context* ctx);
typedef void        (*IGSharp_Platform_SetClipboardTextFn)(IGSharp_Context* ctx, const char* text);
typedef bool        (*IGSharp_Platform_OpenInShellFn)(IGSharp_Context* ctx, const char* path);
typedef void        (*IGSharp_Platform_SetImeDataFn)(IGSharp_Context* ctx, void* viewport, void* ime_data);

// Override setters for the platform handler function pointers.
IGSHARP_API void IGSharp_PlatformIO_SetPlatformGetClipboardTextFn(IGSharp_PlatformIO* pio, IGSharp_Platform_GetClipboardTextFn fn);
IGSHARP_API void IGSharp_PlatformIO_SetPlatformSetClipboardTextFn(IGSharp_PlatformIO* pio, IGSharp_Platform_SetClipboardTextFn fn);
IGSHARP_API void IGSharp_PlatformIO_SetPlatformOpenInShellFn(IGSharp_PlatformIO* pio, IGSharp_Platform_OpenInShellFn fn);
IGSHARP_API void IGSharp_PlatformIO_SetPlatformSetImeDataFn(IGSharp_PlatformIO* pio, IGSharp_Platform_SetImeDataFn fn);

// User-data and scalar field accessors.
IGSHARP_API void*          IGSharp_PlatformIO_GetPlatformClipboardUserData(IGSharp_PlatformIO* pio);
IGSHARP_API void           IGSharp_PlatformIO_SetPlatformClipboardUserData(IGSharp_PlatformIO* pio, void* user_data);
IGSHARP_API void*          IGSharp_PlatformIO_GetPlatformOpenInShellUserData(IGSharp_PlatformIO* pio);
IGSHARP_API void           IGSharp_PlatformIO_SetPlatformOpenInShellUserData(IGSharp_PlatformIO* pio, void* user_data);
IGSHARP_API void*          IGSharp_PlatformIO_GetPlatformImeUserData(IGSharp_PlatformIO* pio);
IGSHARP_API void           IGSharp_PlatformIO_SetPlatformImeUserData(IGSharp_PlatformIO* pio, void* user_data);
IGSHARP_API unsigned short IGSharp_PlatformIO_GetPlatformLocaleDecimalPoint(IGSharp_PlatformIO* pio); // ImWchar
IGSHARP_API void           IGSharp_PlatformIO_SetPlatformLocaleDecimalPoint(IGSharp_PlatformIO* pio, unsigned short c); // ImWchar
IGSHARP_API int            IGSharp_PlatformIO_GetRendererTextureMaxWidth(IGSharp_PlatformIO* pio);
IGSHARP_API void           IGSharp_PlatformIO_SetRendererTextureMaxWidth(IGSharp_PlatformIO* pio, int v);
IGSHARP_API int            IGSharp_PlatformIO_GetRendererTextureMaxHeight(IGSharp_PlatformIO* pio);
IGSHARP_API void           IGSharp_PlatformIO_SetRendererTextureMaxHeight(IGSharp_PlatformIO* pio, int v);
IGSHARP_API void*          IGSharp_PlatformIO_GetRendererRenderState(IGSharp_PlatformIO* pio);
IGSHARP_API void           IGSharp_PlatformIO_SetRendererRenderState(IGSharp_PlatformIO* pio, void* render_state);
// Textures list (ImVector<ImTextureData*>). Needed by a renderer backend to destroy textures at shutdown,
// when no ImDrawData is available. GetTexture returns the ImTextureData* at index.
IGSHARP_API int            IGSharp_PlatformIO_GetTexturesCount(IGSharp_PlatformIO* pio);
IGSHARP_API void*          IGSharp_PlatformIO_GetTexture(IGSharp_PlatformIO* pio, int index);

// Member functions.
IGSHARP_API void IGSharp_PlatformIO_ClearPlatformHandlers(IGSharp_PlatformIO* pio);
IGSHARP_API void IGSharp_PlatformIO_ClearRendererHandlers(IGSharp_PlatformIO* pio);

// ImGuiPlatformImeData
// Platform IME data for the platform_io.Platform_SetImeDataFn() callback.
// Pure POD — layout-compatible MIRROR of ImGuiPlatformImeData. The C# side
// reads this via the ImGuiPlatformImeData* pointer passed into that callback.
typedef struct IGSharp_PlatformImeData {
    bool          WantVisible;       // A widget wants the IME to be visible.
    bool          WantTextInput;     // A widget wants text input, not necessarily IME to be visible.
    IGSharp_Vec2  InputPos;          // Position of input cursor (for IME).
    float         InputLineHeight;   // Line height (for IME).
    unsigned int  ViewportId;        // ImGuiID — ID of platform window/viewport.
} IGSharp_PlatformImeData;

//-----------------------------------------------------------------------------
// [SECTION] Obsolete functions and types
//-----------------------------------------------------------------------------
// (none — built with IMGUI_DISABLE_OBSOLETE_FUNCTIONS; obsolete upstream APIs are not exposed)
