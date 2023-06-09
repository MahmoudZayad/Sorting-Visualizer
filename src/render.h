#pragma once

#include <SDL2/SDL.h>

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

struct Lines {
    std::vector<SDL_Rect> rect;
    std::vector<int> val;
    std::vector<SDL_Color> col;
	int arraySize;
	int prevSize;
	
	// Swap
	//
	void swap(int min_index, int i);
};


class RenderWindow 
{	
	public:
	
		RenderWindow();
		SDL_Renderer* getRenderer();
		SDL_Window* getWindow();
		
		void render(ImGuiIO& io, Lines& l);
		void render(ImGuiIO& io, Lines& l, unsigned int red, unsigned int blue);	
		// void resize(ImGuiIO& io, Lines& l);
		void drawState(Lines& l, unsigned int red, unsigned int blue);
		void drawLines(Lines& l);

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
