#include "imgui_sharp.h"
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlgpu3.h"
#include <SDL3/SDL_gpu.h>

// --- Backend: SDL3 Platform ---

bool IGSharp_ImplSDL3_InitForSDLGPU(SDL_Window* window)
{ return ImGui_ImplSDL3_InitForSDLGPU(window); }

void IGSharp_ImplSDL3_Shutdown(void)
{ ImGui_ImplSDL3_Shutdown(); }

void IGSharp_ImplSDL3_NewFrame(void)
{ ImGui_ImplSDL3_NewFrame(); }

bool IGSharp_ImplSDL3_ProcessEvent(const SDL_Event* event)
{ return ImGui_ImplSDL3_ProcessEvent(event); }

// --- Backend: SDL_GPU Renderer ---

bool IGSharp_ImplSDLGPU3_Init(SDL_GPUDevice* device, int color_target_format, int msaa_samples)
{
    ImGui_ImplSDLGPU3_InitInfo init_info = {};
    init_info.Device = device;
    init_info.ColorTargetFormat = (SDL_GPUTextureFormat)color_target_format;
    init_info.MSAASamples = (SDL_GPUSampleCount)msaa_samples;
    return ImGui_ImplSDLGPU3_Init(&init_info);
}

void IGSharp_ImplSDLGPU3_Shutdown(void)
{ ImGui_ImplSDLGPU3_Shutdown(); }

void IGSharp_ImplSDLGPU3_NewFrame(void)
{ ImGui_ImplSDLGPU3_NewFrame(); }

void IGSharp_ImplSDLGPU3_PrepareDrawData(void* draw_data, SDL_GPUCommandBuffer* command_buffer)
{ ImGui_ImplSDLGPU3_PrepareDrawData((ImDrawData*)draw_data, command_buffer); }

void IGSharp_ImplSDLGPU3_RenderDrawData(void* draw_data, SDL_GPUCommandBuffer* command_buffer, SDL_GPURenderPass* render_pass)
{ ImGui_ImplSDLGPU3_RenderDrawData((ImDrawData*)draw_data, command_buffer, render_pass, nullptr); }
