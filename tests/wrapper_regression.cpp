#include "imgui_sharp.h"
#include <cstdio>
#include <cstdlib>

static void Check(bool ok, const char* message)
{
    if (!ok) { std::fprintf(stderr, "%s\n", message); std::exit(1); }
}

static void DrawLine(IGSharp_DrawList* list)
{
    IGSharp_DrawList_PushClipRectFullScreen(list);
    IGSharp_DrawList_PushTexture(list, 1);
    IGSharp_DrawList_AddLine(list, {0, 0}, {100, 100}, 0xffffffffu, 1);
    Check(IGSharp_DrawList_GetVtxBufferSize(list) > 0, "Line generated no vertices");
    Check(IGSharp_DrawList_GetIdxBufferSize(list) > 0, "Line generated no indices");
}

int main()
{
    IGSharp_Context* context = IGSharp_CreateContext(nullptr);
    IGSharp_IO* io = IGSharp_GetIO();
    io->DisplaySize = {640, 480};
    io->IniFilename = nullptr;
    io->BackendFlags |= IGSharp_BackendFlags_RendererHasTextures;
    IGSharp_NewFrame();
    IGSharp_DrawList* list = IGSharp_DrawList_Create(IGSharp_GetDrawListSharedData());
    Check(IGSharp_DrawList_GetCmdBufferSize(list) == 1, "New list has no initial command");
    Check((IGSharp_DrawList_GetFlags(list) & IGSharp_DrawListFlags_AntiAliasedLines) != 0,
        "New list did not inherit anti-aliasing settings");
    DrawLine(list);
    const int vertices = IGSharp_DrawList_GetVtxBufferSize(list);
    const int indices = IGSharp_DrawList_GetIdxBufferSize(list);
    IGSharp_DrawList* clone = IGSharp_DrawList_CloneOutput(list);
    Check(IGSharp_DrawList_GetVtxBufferSize(clone) == vertices, "Clone lost geometry");
    IGSharp_DrawList_Destroy(clone);
    IGSharp_EndFrame();

    IGSharp_NewFrame();
    IGSharp_DrawList_ResetForNewFrame(list);
    Check(IGSharp_DrawList_GetCmdBufferSize(list) == 1, "Reset lost initial command");
    Check(IGSharp_DrawList_GetVtxBufferSize(list) == 0, "Reset kept old vertices");
    Check(IGSharp_DrawList_GetIdxBufferSize(list) == 0, "Reset kept old indices");
    DrawLine(list);
    Check(IGSharp_DrawList_GetVtxBufferSize(list) == vertices, "Geometry changed after reset");
    Check(IGSharp_DrawList_GetIdxBufferSize(list) == indices, "Indices changed after reset");
    IGSharp_DrawList_Destroy(list);
    // Preserve support for an empty storage-only list without shared data.
    IGSharp_DrawList_Destroy(IGSharp_DrawList_Create(nullptr));
    IGSharp_EndFrame();
    IGSharp_DestroyContext(context);

    IGSharp_FontGlyphRangesBuilder* builder = IGSharp_FontGlyphRangesBuilder_New();
    IGSharp_FontGlyphRangesBuilder_AddText(builder, "AC", nullptr);
    const int count = IGSharp_FontGlyphRangesBuilder_BuildRanges(builder, nullptr, 0);
    Check(count == 5, "Wrong required glyph-range size");
    unsigned short short_buffer[4] = {0, 0, 0, 0xbeef};
    Check(IGSharp_FontGlyphRangesBuilder_BuildRanges(builder, short_buffer, 3) == count,
        "Truncation did not return required capacity");
    Check(short_buffer[3] == 0xbeef, "Range copy exceeded capacity");
    unsigned short ranges[5] = {};
    Check(IGSharp_FontGlyphRangesBuilder_BuildRanges(builder, ranges, count) == count,
        "Full range copy returned wrong size");
    Check(ranges[0] == 'A' && ranges[1] == 'A' && ranges[2] == 'C' &&
        ranges[3] == 'C' && ranges[4] == 0, "Full copy is not complete terminated ranges");
    IGSharp_FontGlyphRangesBuilder_Clear(builder);
    IGSharp_FontGlyphRangesBuilder_AddRanges(builder, ranges);
    Check(IGSharp_FontGlyphRangesBuilder_GetBit(builder, 'A') &&
        !IGSharp_FontGlyphRangesBuilder_GetBit(builder, 'B') &&
        IGSharp_FontGlyphRangesBuilder_GetBit(builder, 'C'), "Range roundtrip failed");
    IGSharp_FontGlyphRangesBuilder_Delete(builder);
}
