//my homemade, not so complete imgui backend for assault cube/sdl 1.2
#include "imgui.h"
#include "imgui_impl_sdl.h"

#include <SDL.h>
#ifdef _WIN32
#include <SDL_syswm.h>
#endif

static bool	g_MousePressed[3] = {false, false, false};
static Uint32	g_Time = 0;
static bool	g_Minimized = false;
static bool	g_InputFocus = true;

bool ImGui_ImplSDL_ProcessEvent(const SDL_Event* event) {
	ImGuiIO& io = ImGui::GetIO();

	switch (event->type) {
		case SDL_MOUSEBUTTONDOWN:
			if (event->button.button == SDL_BUTTON_LEFT) g_MousePressed[0] = true;
			if (event->button.button == SDL_BUTTON_RIGHT) g_MousePressed[1] = true;
			if (event->button.button == SDL_BUTTON_MIDDLE) g_MousePressed[2] = true;
			if (event->button.button == SDL_BUTTON_WHEELUP) io.MouseWheel += 1;
			if (event->button.button == SDL_BUTTON_WHEELDOWN) io.MouseWheel -= 1;
			return true;
		case SDL_MOUSEBUTTONUP:
			if (event->button.button == SDL_BUTTON_LEFT) g_MousePressed[0] = false;
			if (event->button.button == SDL_BUTTON_RIGHT) g_MousePressed[1] = false;
			if (event->button.button == SDL_BUTTON_MIDDLE) g_MousePressed[2] = false;
			return true;
		case SDL_MOUSEMOTION:
			if (g_InputFocus) io.MousePos = ImVec2((float)event->motion.x, (float)event->motion.y);
			return true;
		case SDL_KEYDOWN:
		case SDL_KEYUP:
		{
			SDLKey key = event->key.keysym.sym;
			IM_ASSERT(key >= 0 && key < IM_ARRAYSIZE(io.KeysDown));
			io.KeysDown[key] = (event->type == SDL_KEYDOWN);
			SDLMod mod = SDL_GetModState();
			io.KeyShift = ((mod & KMOD_SHIFT) != 0);
			io.KeyCtrl = ((mod & KMOD_CTRL) != 0);
			io.KeyAlt = ((mod & KMOD_ALT) != 0);
			io.KeySuper = false;
			return true;
		}
		case SDL_ACTIVEEVENT:
			if (event->active.state & SDL_APPACTIVE) g_Minimized = !event->active.gain;
			if (event->active.state & SDL_APPINPUTFOCUS) g_InputFocus = event->active.gain != 0;
			return true;
	}

	return false;
}
bool ImGui_ImplSDL_Init() {
	ImGuiIO& io = ImGui::GetIO();
	io.BackendPlatformName = "imgui_impl_sdl";

	io.KeyMap[ImGuiKey_Tab] = SDLK_TAB;
	io.KeyMap[ImGuiKey_LeftArrow] = SDLK_LEFT;
	io.KeyMap[ImGuiKey_RightArrow] = SDLK_RIGHT;
	io.KeyMap[ImGuiKey_UpArrow] = SDLK_UP;
	io.KeyMap[ImGuiKey_DownArrow] = SDLK_DOWN;
	io.KeyMap[ImGuiKey_PageUp] = SDLK_PAGEUP;
	io.KeyMap[ImGuiKey_PageDown] = SDLK_PAGEDOWN;
	io.KeyMap[ImGuiKey_Home] = SDLK_HOME;
	io.KeyMap[ImGuiKey_End] = SDLK_END;
	io.KeyMap[ImGuiKey_Insert] = SDLK_INSERT;
	io.KeyMap[ImGuiKey_Delete] = SDLK_DELETE;
	io.KeyMap[ImGuiKey_Backspace] = SDLK_BACKSPACE;
	io.KeyMap[ImGuiKey_Space] = SDLK_SPACE;
	io.KeyMap[ImGuiKey_Enter] = SDLK_RETURN;
	io.KeyMap[ImGuiKey_Escape] = SDLK_ESCAPE;
	io.KeyMap[ImGuiKey_KeyPadEnter] = SDLK_KP_ENTER;
	io.KeyMap[ImGuiKey_A] = SDLK_a;
	io.KeyMap[ImGuiKey_C] = SDLK_c;
	io.KeyMap[ImGuiKey_V] = SDLK_v;
	io.KeyMap[ImGuiKey_X] = SDLK_x;
	io.KeyMap[ImGuiKey_Y] = SDLK_y;
	io.KeyMap[ImGuiKey_Z] = SDLK_z;

	io.ClipboardUserData = NULL;

	io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

#ifdef _WIN32
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	if (SDL_GetWMInfo(&wmInfo)) {
		io.ImeWindowHandle = wmInfo.window;
	}
#endif
	return true;
}


void ImGui_ImplSDL_Shutdown() {
}

void ImGui_ImplSDL_NewFrame(SDL_Surface* framebuffer) {
	ImGuiIO& io = ImGui::GetIO();
	IM_ASSERT(io.Fonts->IsBuilt() && "Font atlas not built! It is generally built by the renderer backend. Missing call to renderer _NewFrame() function? e.g. ImGui_ImplOpenGL3_NewFrame().");

	if (g_Minimized) io.DisplaySize = ImVec2(0.0f, 0.0f);
	else io.DisplaySize = ImVec2((float)framebuffer->w, (float)framebuffer->h);

	Uint32 current_time = SDL_GetTicks();
	io.DeltaTime = g_Time > 0 ? (float)((double)(current_time - g_Time) / 1000) : (float)(1.0f / 60.0f);
	g_Time = current_time;
	
	io.MouseDown[0] = g_MousePressed[0];
	io.MouseDown[1] = g_MousePressed[1];
	io.MouseDown[2] = g_MousePressed[2];
	//g_MousePressed[0] = g_MousePressed[1] = g_MousePressed[2] = false;

	if (io.MouseDrawCursor) SDL_ShowCursor(0);
	else SDL_ShowCursor(1);
}
