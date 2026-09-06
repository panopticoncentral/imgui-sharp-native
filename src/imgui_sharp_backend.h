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

typedef struct SDL_Window SDL_Window;
typedef union SDL_Event SDL_Event;

IGSHARP_API bool IGSharp_ImplSDL3_InitForSDLGPU(SDL_Window* window);
IGSHARP_API void IGSharp_ImplSDL3_Shutdown(void);
IGSHARP_API void IGSharp_ImplSDL3_NewFrame(void);
IGSHARP_API bool IGSharp_ImplSDL3_ProcessEvent(const SDL_Event* event);

//-----------------------------------------------------------------------------
// [SECTION] SDL_GPU Renderer
//-----------------------------------------------------------------------------

typedef struct SDL_GPUDevice SDL_GPUDevice;
typedef struct SDL_GPUCommandBuffer SDL_GPUCommandBuffer;
typedef struct SDL_GPURenderPass SDL_GPURenderPass;
typedef struct SDL_GPUGraphicsPipeline SDL_GPUGraphicsPipeline;

IGSHARP_API bool IGSharp_ImplSDLGPU3_Init(SDL_GPUDevice* device, int color_target_format, int msaa_samples);
IGSHARP_API void IGSharp_ImplSDLGPU3_Shutdown(void);
IGSHARP_API void IGSharp_ImplSDLGPU3_NewFrame(void);
IGSHARP_API void IGSharp_ImplSDLGPU3_PrepareDrawData(void* draw_data, SDL_GPUCommandBuffer* command_buffer);
IGSHARP_API void IGSharp_ImplSDLGPU3_RenderDrawData(void* draw_data, SDL_GPUCommandBuffer* command_buffer, SDL_GPURenderPass* render_pass);

// Uses a caller-provided pipeline; NULL selects the backend default, as above.
// The pipeline must be compatible with the render pass and ImGui vertex/shader inputs.
IGSHARP_API void IGSharp_ImplSDLGPU3_RenderDrawDataWithPipeline(void* draw_data, SDL_GPUCommandBuffer* command_buffer, SDL_GPURenderPass* render_pass, SDL_GPUGraphicsPipeline* pipeline);
