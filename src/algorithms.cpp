#include "algorithms.h"

// Create vector with randomized values
//
void randomizeVector(Lines& l, int size) {
    // Intialize Rectangles and Values
    //
    std::vector<int> v(size, 0);
    std::vector<SDL_Rect> r(size, SDL_Rect());
    std::vector<SDL_Color> c(size, SDL_Color()); 

    // Setup Random Distribution
    //
    std::random_device rd;
    std::uniform_int_distribution<int> d(1,400);

    int index = 16; // Center of screen

    for (int i = 0; i < size; i++) {
        v[i] = d(rd);
        r[i] = {index, 4*16, 5, v[i]+(4*16)};
        c[i] = {255, 255, 255, 255};
        index += 6;
    }
    l.rect = r;
    l.val = v;
    l.col = c;
}

// Simple Sorts
//
void insertionSort(RenderWindow& rind, ImGuiIO& io, Lines& l) {
    
    int j, key;
    int size = l.val.size();
    int center = 640/4; // Center screen
    int tempX;
    int tempH;

    SDL_Rect temp;
    SDL_Rect keyr;

    for (int i = 1; i < size; i++) {
        key = l.val[i];
        keyr = l.rect[i];
        j = i-1;
        
        while (j >= 0 && l.val[j] > key) {
            l.val[j+1] = l.val[j];
            l.rect[j+1] = l.rect[j];
            

            // temp = l.rect[j+1];
            // tempX = l.rect[j+1].x;
            // tempH = l.rect[j+1].h;

            
            // l.rect[j+1].x = l.rect[j].x;
            // l.rect[j+1].h = l.srect[j].h;

            // l.rect[j] = temp;
            // l.rect[j].x = tempX;
            // l.rect[j].h = tempH;
            j--;
        }
        l.val[j+1] = key;
        l.rect[j+1] = keyr;
        // Render
        //
        rind.render(io,l,j+1,j);
        SDL_Delay(5);

    }
    
    for (auto i : l.val) {
        std::cout<< i << " ";
    }
    if(std::is_sorted(l.val.begin(), l.val.end()))
        std::cout << "sorted\n";

    
}

// Bubble Sort
//

void bubbleSort(RenderWindow& rind, ImGuiIO& io, Lines& l) {
    
    int i, j;
    int n = l.val.size();
    for (i = 0; i < n - 1; i++) {
        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++) {
            if (l.val[j] > l.val[j + 1]) {
                std::swap(l.val[j], l.val[j + 1]);
                
            }
            rind.render(io,l,j,j+1);
            SDL_Delay(500);
        }
    }
}
