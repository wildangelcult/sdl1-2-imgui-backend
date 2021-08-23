//my homemade, not so complete imgui backend for assault cube/sdl 1.2
#pragma once
#include "imgui.h"      // IMGUI_IMPL_API

typedef struct SDL_Surface SDL_Surface;
typedef union SDL_Event SDL_Event;

IMGUI_IMPL_API bool     ImGui_ImplSDL_Init();
IMGUI_IMPL_API void     ImGui_ImplSDL_Shutdown();
IMGUI_IMPL_API void     ImGui_ImplSDL_NewFrame(SDL_Surface* framebuffer);
IMGUI_IMPL_API bool     ImGui_ImplSDL_ProcessEvent(const SDL_Event* event);
