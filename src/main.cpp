#include "render.h"
#include <utility>


#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

#include <iostream>

int main(int, char**) {
    
   

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
    ImVec2 padding = ImVec2(0,0);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, padding);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, padding);

    // Setup Platform/Renderer backends
    rind.setupRenderPlatform();

    // Main Loop
    bool done = false;

    // Menu bools
    static bool show_window = true;
    bool show_algorithms = false;
    bool show_weights = false;
    bool show_speed = false;
    bool menu_clicked = false;
    
    // Visualize button
    bool visualize = false;

    // Animation check
    bool anim = false;

    // Algorithms and Grid interactions
    const char* viz = "Visualize";

    while (!done) {

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(rind.getWindow()))
                done = true;
        }

        // Start the Dear ImGui frame
        rind.startImGuiFrame(); 
        {
            static float f = 0.0f;

            static ImVec2 pos = ImVec2(0,0);
            static ImVec2 windowSize = ImVec2(640,4*16);
            static ImVec2 buttonSize = ImVec2((642/6),4*16);
            
            ImGui::SetNextWindowPos(pos);
            // ImGui::SetNextWindowBgAlpha(0.0f);  // Make Transparent
            ImGui::SetNextWindowSize(windowSize);
            ImGui::Begin("Buttons", &show_window, ImGuiWindowFlags_NoDecoration |  ImGuiWindowFlags_NoMove); // Remove Bar
          
            if (ImGui::Button("Generate New Array", buttonSize))
                std::cout << "quick";
            ImGui::SameLine(0.0f, 0.0f); 
            ImGui::SliderFloat("Change Array Size", &f, 0.0f, 1.0f); 
            ImGui::SameLine(0.0f, 0.0f);           // Edit 1 float using a slider from 0.0f to 1.0f
            if (ImGui::Button("Quick Sort", buttonSize))
                std::cout << "quick";
            ImGui::SameLine(0.0f, 0.0f);
            if (ImGui::Button("Merge Sort", buttonSize))
                std::cout << "merge";
            ImGui::SameLine(0.0f, 0.0f);
            if (ImGui::Button("Heap Sort", buttonSize))
                std::cout << "heap";
            ImGui::SameLine(0.0f, 0.0f);
            if (ImGui::Button("Insertion Sort", buttonSize))
                std::cout << "insertion";
            ImGui::End();
        }

      
        

        rind.render(io);
        SDL_Delay(5);
    }

    // Cleanup
    rind.destroyImGui();
    rind.destroySDL();
    SDL_Quit();

    return 0;
}