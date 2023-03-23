#include "render.h"

int MENUSIZE = 64;

// Pixel size of Window
int HEIGHT = 480 + MENUSIZE;
int WIDTH = 640; 


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

void RenderWindow::render(ImGuiIO& io, Lines& l) {

    // Rendering
    ImGui::Render();
    SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    SDL_SetRenderDrawColor(renderer,44, 44, 44, 255);
    SDL_RenderClear(renderer);
    drawLines(l);
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(renderer);
}

void RenderWindow::render(ImGuiIO& io, Lines& l, 
               unsigned int red, unsigned int blue) {

    // Rendering
    ImGui::Render();
    SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    SDL_SetRenderDrawColor(renderer,44, 44, 44, 255);
    SDL_RenderClear(renderer);
    drawState(l, red, blue);
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(renderer);
}



void RenderWindow::destroySDL() {

    // Remove SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

//////////~~~~~~~~~IMGUI~~~~~~~~~~~/////////////
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

//////~~~~~~Sort~~~~~~~///////
void RenderWindow::drawState(Lines& l, unsigned int red, unsigned int blue) {

    int size = l.val.size();
    int index = 16; // Center of screen
    for (int i = 0; i < size; i++) {
        if (i == red) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        } 
        else if (i == blue) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        l.rect[i].x = index;
        l.rect[i].h = l.val[i] + (4*16);
        SDL_RenderFillRect(renderer, &l.rect[i]);
        index+=6;
    }
}

// void RenderWindow::drawState(Lines& l, unsigned int red, unsigned int blue) {

//     unsigned int index = 0;
//     int size = l.val.size();
//     for (int i = 0; i < size; i++) {
//         if (index == red) {
//             SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
//         } 
//         else if (index == blue) {
//             SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
//         } else {
//             SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
//         }
//         SDL_RenderDrawLine(renderer, index, 4*16, index, l.val[i]);
//         index++;
//     }
// }

void RenderWindow::drawLines(Lines& l) {

    int size = l.val.size();
    for (int i = 0; i < size; i++) {
        SDL_SetRenderDrawColor(renderer, l.col[i].r, l.col[i].g, l.col[i].b, l.col[i].a);
        SDL_RenderFillRect(renderer, &l.rect[i]);
    }
}