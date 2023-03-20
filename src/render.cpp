#include "render.h"

int MENUSIZE = 64;

// Pixel size of Window
int HEIGHT = 480 + MENUSIZE + 1;
int WIDTH = 640 + 1; 


RenderWindow::RenderWindow() :window(NULL), renderer(NULL) {
    // Create window with SDL_Renderer graphics context
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    window = SDL_CreateWindow("Pathfinding Visualizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, window_flags);

    if (window == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
}

SDL_Renderer* RenderWindow::getRenderer() {return renderer;}
SDL_Window* RenderWindow::getWindow() {return window;}

void RenderWindow::render(ImGuiIO& io) {

    // Rendering
    ImGui::Render();
    SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    SDL_SetRenderDrawColor(renderer,44, 44, 44, 255);
    SDL_RenderClear(renderer);
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(renderer);
}

void RenderWindow::destroySDL() {

    // Remove SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

//////////~~~~~~~~~IMGUI~~~~~~~~~~~////////////////////////////////////


void RenderWindow::setupImGuiContext() {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io =  ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
}

void RenderWindow::setupRenderPlatform() {
    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer_Init(renderer);
}

void RenderWindow::startImGuiFrame() {
    // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
}

void RenderWindow::destroyImGui() {
    // Cleanup
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}
