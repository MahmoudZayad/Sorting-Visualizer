
#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer.h"

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

extern int MENUSIZE;

// Pixel size of Window
extern int HEIGHT; 
extern int WIDTH; 


class RenderWindow 
{	
	public:
		RenderWindow();
		SDL_Renderer* getRenderer();
		SDL_Window* getWindow();
		
		void render(ImGuiIO& io);
		void destroySDL();
		void setupImGuiContext();
		void setupRenderPlatform();
		void startImGuiFrame();
		void destroyImGui();
		
	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

};
