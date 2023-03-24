#include "gui.h"

// Determine which Menu to display
//
void _showSimpleMenu(Menu& menu) {
     if (menu.show_simple) {
        menu.show_simple = false;
    } else {
        menu.show_simple = true;
        menu.show_efficient = false;
        menu.show_bubble = false;
    }
}

void _showEfficientMenu(Menu& menu) {
     if (menu.show_efficient) {
        menu.show_efficient = false;
    } else {
        menu.show_simple = false;
        menu.show_efficient = true;
        menu.show_bubble = false;
    }
}

void _showBubbleMenu(Menu& menu) {
     if (menu.show_bubble) {
        menu.show_bubble = false;
    } else {
        menu.show_simple = false;
        menu.show_efficient = false;
        menu.show_bubble = true;
    }
}


// Goes in Main Loop to determines which menu to display
//
void displayMenu(Menu& menu) {
     if (menu.show_simple) {
            menu.show_efficient = false;
            menu.show_bubble = false;
            simpleMenu(menu);
        } else if (menu.show_efficient) {
            menu.show_simple = false;
            menu.show_bubble = false;
            efficientMenu(menu);
        } else if (menu.show_bubble) {
            menu.show_simple = false;
            menu.show_efficient = false;
            bubbleMenu(menu);
        }
}

/////////////~~~~~~~~~~~~~~~~Menus~~~~~~~~~~~~~~~~///////////////

void mainMenu(Menu& menu, Lines& l) {
    static ImVec2 pos = ImVec2(0,0);
    static ImVec2 windowSize = ImVec2(640,4*16);
    static ImVec2 buttonSize = ImVec2((642/6), 4*16);
    const char* viz;

    if (menu.sort == -1) 
        viz = "Select a Sort";
    else
        viz = "Sort";
    
    ImVec2 spacing = ImVec2(0, 8);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, spacing);
    
    ImGui::SetNextWindowPos(pos);
    ImGui::SetNextWindowSize(windowSize);

    ImGui::Begin("Buttons", &menu.show_window, ImGuiWindowFlags_NoDecoration |  ImGuiWindowFlags_NoMove); // Remove Bar
    if (ImGui::Button("Generate\nNew Array", buttonSize))
        randomizeVector(l, l.arraySize);
    ImGui::SameLine();
    {
        slider(buttonSize.x, l.arraySize);
    }
    ImGui::SameLine(0.0f, 0.0f);
    ImGui::PopStyleVar();
    if (ImGui::Button(viz, buttonSize))
        if (menu.sort == -1)
            viz = "Select a Sort";
        else
            menu.start = true;
    ImGui::SameLine(0.0f, 0.0f);
    if (ImGui::Button("Simple\nSorts", buttonSize))
         _showSimpleMenu(menu);
    ImGui::SameLine(0.0f, 0.0f);
    if (ImGui::Button("Efficient\nSorts", buttonSize))
         _showEfficientMenu(menu);
    ImGui::SameLine(0.0f, 0.0f);
    if (ImGui::Button("Bubble\nSorts", buttonSize))
        _showBubbleMenu(menu);
    ImGui::End();
}

/*
* Simple Sort Menu
*/
void simpleMenu(Menu& menu) {

    static ImVec2 menuPos = ImVec2((642/6)*3, (4*16) + 4);
    static ImVec2 menuSize = ImVec2((642/6), 4*16);
    static ImVec2 dropSize = ImVec2((642/6), 2*16);
    
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0,0));
    ImGui::SetNextWindowPos(menuPos);
    ImGui::SetNextWindowSize(menuSize);

    ImGui::Begin("Menu", &menu.show_simple,  ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove); 
    if (ImGui::Button("Insertion Sort", dropSize))  {
        menu.sort = Sort_Insertion;
        menu.show_simple = false;
    }  
    if (ImGui::Button("Selection Sort", dropSize)) {
        menu.sort = Sort_Selection;
        menu.show_simple = false;
    }    
    ImGui::PopStyleVar();                           
    ImGui::End();
}


/*
* Efficient Sort Menu
*/
void efficientMenu(Menu& menu) {

    static ImVec2 menuPos = ImVec2((642/6)*4, (4*16) + 4);
    static ImVec2 menuSize = ImVec2((642/6), 4*16);
    static ImVec2 dropSize = ImVec2((642/6), 2*16);
    
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0,0));
    ImGui::SetNextWindowPos(menuPos);
    ImGui::SetNextWindowSize(menuSize);

    ImGui::Begin("Menu", &menu.show_efficient,  ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove); 
    if (ImGui::Button("Merge Sort", dropSize))  {
        menu.sort = Sort_Merge;
        menu.show_efficient = false;
    }  
    if (ImGui::Button("Heap Sort", dropSize)) {
        menu.sort = Sort_Heap;
        menu.show_efficient = false;
    }
    if (ImGui::Button("Quick Sort", dropSize)) {
        menu.sort = Sort_Quick;
        menu.show_efficient = false;
    }    
    if (ImGui::Button("Shell Sort", dropSize)) {
        menu.sort = Sort_Shell;
        menu.show_efficient = false;
    }      
    ImGui::PopStyleVar();                           
    ImGui::End();
}


/*
* Bubble Sort Menu
*/
void bubbleMenu(Menu& menu) {

    static ImVec2 menuPos = ImVec2((642/6)*5, (4*16) + 4);
    static ImVec2 menuSize = ImVec2((642/6), 2*16);
    static ImVec2 dropSize = ImVec2((642/6), 2*16);
    
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0,0));
    ImGui::SetNextWindowPos(menuPos);
    ImGui::SetNextWindowSize(menuSize);
    ImGui::Begin("Menu", &menu.show_bubble,  ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove); 
    
    if (ImGui::Button("Bubble Sort", dropSize))  {
        menu.sort = Sort_Bubble;
        menu.show_bubble = false;
    }    
    ImGui::PopStyleVar(); 
                              
    ImGui::End();
}



////////////~~~~~~~~~~Helper Functions~~~~~~~~~~~~//////////
void _textCentered(std::string text) {
    auto windowWidth = 3*(642/6);
    auto textWidth   = ImGui::CalcTextSize(text.c_str()).x;

    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
    ImGui::SetCursorPosY(8);
    ImGui::Text(text.c_str());
}

void slider(int buttonSizeX, int& arraySize) {
    ImGui::BeginGroup();
    _textCentered("Array Size");
    // ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::HSV(0/7.0f, 0.5f, 0.5f));
    // ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, (ImVec4)ImColor::HSV(0 / 7.0f, 0.6f, 0.5f));
    // ImGui::PushStyleColor(ImGuiCol_FrameBgActive, (ImVec4)ImColor::HSV(0 / 7.0f, 0.7f, 0.5f));
    // ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(0 / 7.0f, 0.9f, 0.9f));
    ImGui::PushItemWidth(buttonSizeX);
    ImGui::SliderInt("##", &arraySize, 2, 200);
    // ImGui::PopStyleColor(4);
    ImGui::PopItemWidth(); 
    ImGui::EndGroup();
}

