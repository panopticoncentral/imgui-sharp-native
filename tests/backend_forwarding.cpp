#include "imgui_sharp_backend.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlgpu3.h"
#include <cstdio>

static ImDrawData* last_data;
static SDL_GPUCommandBuffer* last_commands;
static SDL_GPURenderPass* last_pass;
static SDL_GPUGraphicsPipeline* last_pipeline;
static int calls;

bool ImGui_ImplSDL3_InitForSDLGPU(SDL_Window*) { return true; }
void ImGui_ImplSDL3_Shutdown() {}
void ImGui_ImplSDL3_NewFrame() {}
bool ImGui_ImplSDL3_ProcessEvent(const SDL_Event*) { return true; }
bool ImGui_ImplSDLGPU3_Init(ImGui_ImplSDLGPU3_InitInfo*) { return true; }
void ImGui_ImplSDLGPU3_Shutdown() {}
void ImGui_ImplSDLGPU3_NewFrame() {}
void ImGui_ImplSDLGPU3_PrepareDrawData(ImDrawData*, SDL_GPUCommandBuffer*) {}
void ImGui_ImplSDLGPU3_RenderDrawData(ImDrawData* data, SDL_GPUCommandBuffer* commands,
    SDL_GPURenderPass* pass, SDL_GPUGraphicsPipeline* pipeline)
{
    last_data = data; last_commands = commands; last_pass = pass;
    last_pipeline = pipeline; ++calls;
}

int main()
{
    // Opaque identity tokens are recorded, never dereferenced.
    int tokens[4] = {};
    auto data = reinterpret_cast<ImDrawData*>(&tokens[0]);
    auto commands = reinterpret_cast<SDL_GPUCommandBuffer*>(&tokens[1]);
    auto pass = reinterpret_cast<SDL_GPURenderPass*>(&tokens[2]);
    auto pipeline = reinterpret_cast<SDL_GPUGraphicsPipeline*>(&tokens[3]);
    IGSharp_ImplSDLGPU3_RenderDrawDataWithPipeline(data, commands, pass, pipeline);
    if (calls != 1 || last_data != data || last_commands != commands ||
        last_pass != pass || last_pipeline != pipeline) return 1;
    IGSharp_ImplSDLGPU3_RenderDrawData(data, commands, pass);
    if (calls != 2 || last_pipeline != nullptr) return 2;
    IGSharp_ImplSDLGPU3_RenderDrawDataWithPipeline(data, commands, pass, nullptr);
    if (calls != 3 || last_pipeline != nullptr) return 3;
    std::puts("Custom and default pipeline forwarding passed");
}
