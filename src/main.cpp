#include "gui.h"

#include <utility>


#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

#include <iostream>



int main(int, char**) {
    
    Lines l;

    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    // From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

    // Creates window and renderWindow.renderer
    RenderWindow rind = RenderWindow();


    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io =  ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    ImGui::GetStyle();
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

    // Setup Platform/Renderer backends
    rind.setupRenderPlatform();

    // Menu bools
    Menu menu = Menu(false);

    // Algorithms
    menu.sort = -1;

    l.arraySize = 100;
    l.prevSize = l.arraySize;
    
    randomizeVector(l, l.arraySize);

    // Main Loop
    //
    bool done = false;
    while (!done) 
    {

        SDL_Event event;
        while (SDL_PollEvent(&event)) 
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(rind.getWindow()))
                done = true;
        }

        // Start the Dear ImGui frame
        //
        rind.startImGuiFrame(); 
        {
            mainMenu(menu, l);
        }
        
        displayMenu(menu);

        // Check for Array Size Update
        //
        if (l.arraySize != l.prevSize)
        {
            randomizeVector(l, l.arraySize);
            l.prevSize = l.arraySize;
        }

        // Select Algorithm
        //
        if (menu.start) 
        {
            menu.start = false;
            switch (menu.sort) 
            {
                case Sort_Insertion: insertionSort(rind, io, l); break;
                case Sort_Selection: selectionSort(rind, io, l); break;
                case Sort_Bubble: bubbleSort(rind, io, l); break;
            }
            menu.sort = -1; 
        }
       
        // Render
        //
        rind.render(io, l);
        SDL_Delay(5);
    }
    // Cleanup
    //
    rind.destroyImGui();
    rind.destroySDL();
    SDL_Quit();
    return 0;
}