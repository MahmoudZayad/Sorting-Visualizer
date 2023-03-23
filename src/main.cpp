#include "render.h"
#include "algorithms.h"
#include <utility>


#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

#include <iostream>

void TextCentered(std::string text) {
    auto windowWidth = 3*(642/6);
    auto textWidth   = ImGui::CalcTextSize(text.c_str()).x;

    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
    ImGui::SetCursorPosY(8);
    ImGui::Text(text.c_str());
}


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
    ImVec2 padding = ImVec2(0, 0);
    ImVec2 spacing = ImVec2(0, 8);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, padding);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, spacing);

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
    int sort = -1;
    

    randomizeVector(l, 100);


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
            static int arraySize = 0;

            static ImVec2 pos = ImVec2(0,0);
            static ImVec2 windowSize = ImVec2(640,4*16);
            static ImVec2 buttonSize = ImVec2((642/6), 4*16);
            
            ImGui::SetNextWindowPos(pos);
            ImGui::SetNextWindowSize(windowSize);

            ImGui::Begin("Buttons", &show_window, ImGuiWindowFlags_NoDecoration |  ImGuiWindowFlags_NoMove); // Remove Bar
            
        
            if (ImGui::Button("Generate\nNew Array", buttonSize))
            std::cout << "quick";
            ImGui::SameLine();

            {
                ImGui::BeginGroup();
                TextCentered("Array Size");
                ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::HSV(0/7.0f, 0.5f, 0.5f));
                ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, (ImVec4)ImColor::HSV(0 / 7.0f, 0.6f, 0.5f));
                ImGui::PushStyleColor(ImGuiCol_FrameBgActive, (ImVec4)ImColor::HSV(0 / 7.0f, 0.7f, 0.5f));
                ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(0 / 7.0f, 0.9f, 0.9f));
                ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0,0));
                ImGui::PushItemWidth(buttonSize.x);
                ImGui::SliderInt("##", &arraySize, 0, 200);
                ImGui::PopStyleVar();
                ImGui::PopStyleColor(4);
                ImGui::PopItemWidth(); 
                ImGui::EndGroup();
            }
            
            ImGui::SameLine(0.0f, 0.0f);
            if (ImGui::Button("Insertion\nSort", buttonSize))
                sort = Sort_Insertion;
            ImGui::SameLine(0.0f, 0.0f);
            if (ImGui::Button("Bubble\nSort", buttonSize))
                sort = Sort_Bubble;
            ImGui::SameLine(0.0f, 0.0f);
            if (ImGui::Button("Heap\nSort", buttonSize))
                std::cout << "heap";
            ImGui::SameLine(0.0f, 0.0f);
            if (ImGui::Button("Insertion\nSort", buttonSize))
                std::cout << "insertion";
           
            ImGui::End();
        }
        // ImGui::ShowStyleEditor();

        switch (sort) {
            case Sort_Insertion: insertionSort(rind, io, l); break;
            case Sort_Bubble: bubbleSort(rind, io, l); break;

            default: break;
        }
        sort = -1; 
            
        
        rind.render(io, l);

        SDL_Delay(5);
    }

    // Cleanup
    rind.destroyImGui();
    rind.destroySDL();
    SDL_Quit();

    return 0;
}