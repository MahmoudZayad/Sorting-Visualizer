#pragma once

#include "algorithms.h"
#include "render.h"

struct Menu {
    int sort;

    // Menu bools
    bool show_window;
    bool show_simple;
    bool show_efficient;
    bool show_bubble;


    // To start sort
    bool start;

    Menu(bool b) : show_window(!b), show_simple(b), show_efficient(b), show_bubble(b), start(b) {}
};

// Centers Text for Slider
//
void _textCentered(std::string text);

// Slider Setup
//
void slider(int buttonSizeX, int& arraySize);


/////~~~~~~Menu Display Logic~~~~~~~~////////
void displayMenu(Menu& menu);
void _showSimpleMenu(Menu& menu);
void _showEfficientMenu(Menu& menu);
void _showBubbleMenu(Menu& menu);

/////~~~~~~Menus~~~~~~/////
// Main Menu
//
void mainMenu(Menu& menu, Lines& l);

// Sort Menu
//
void simpleMenu(Menu& menu);
void efficientMenu(Menu& menu);
void bubbleMenu(Menu& menu);