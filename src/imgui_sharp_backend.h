// dear imgui sharp — backend prototypes
//
// Backend wrappers for SDL3 (platform) and SDL_GPU (renderer). These are not
// part of upstream imgui.h — they wrap the imgui_impl_sdl3.h / imgui_impl_sdlgpu3.h
// backends that ship with Dear ImGui, mirroring upstream's split of imgui.h vs
// imgui_impl_*.h headers.

#pragma once

#include "imgui_sharp.h"   // brings in IGSHARP_API and IGSharp_* basic types

//-----------------------------------------------------------------------------
// [SECTION] SDL3 Platform
//-----------------------------------------------------------------------------

struct SDL_Window;
union  SDL_Event;

IGSHARP_API bool IGSharp_ImplSDL3_InitForSDLGPU(SDL_Window* window);
IGSHARP_API void IGSharp_ImplSDL3_Shutdown(void);
IGSHARP_API void IGSharp_ImplSDL3_NewFrame(void);
IGSHARP_API bool IGSharp_ImplSDL3_ProcessEvent(const SDL_Event* event);

//-----------------------------------------------------------------------------
// [SECTION] SDL_GPU Renderer
//-----------------------------------------------------------------------------

struct SDL_GPUDevice;
struct SDL_GPUCommandBuffer;
struct SDL_GPURenderPass;

IGSHARP_API bool IGSharp_ImplSDLGPU3_Init(SDL_GPUDevice* device, int color_target_format, int msaa_samples);
IGSHARP_API void IGSharp_ImplSDLGPU3_Shutdown(void);
IGSHARP_API void IGSharp_ImplSDLGPU3_NewFrame(void);
IGSHARP_API void IGSharp_ImplSDLGPU3_PrepareDrawData(void* draw_data, SDL_GPUCommandBuffer* command_buffer);
IGSHARP_API void IGSharp_ImplSDLGPU3_RenderDrawData(void* draw_data, SDL_GPUCommandBuffer* command_buffer, SDL_GPURenderPass* render_pass);
