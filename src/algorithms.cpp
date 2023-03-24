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

    // Determine Size and Location of Rects
    //
    int rectWidth = WIDTH/size;
    int index = (WIDTH - rectWidth*size)*0.5; 

    for (int i = 0; i < size; i++) {
        v[i] = d(rd);
        r[i] = {index, 4*16, rectWidth-1, v[i]+(4*16)};
        c[i] = {255, 255, 255, 255};
        index += rectWidth;
    }
    l.rect = r;
    l.val = v;
    l.col = c;
}

// ****************************************************************************
// ******************************* SIMPLE SORTS *******************************
// ****************************************************************************
//

//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Insertion Sort ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
void insertionSort(RenderWindow& rind, ImGuiIO& io, Lines& l)
{    
    for (int i = 1; i < l.val.size(); i++) {
        int key = l.val[i];
        SDL_Rect keyr = l.rect[i];
        int j = i-1;
        
        while (j >= 0 && l.val[j] > key) {
            l.val[j+1] = l.val[j];
            l.rect[j+1] = l.rect[j];
            j--;
        }
        l.val[j+1] = key;
        l.rect[j+1] = keyr;

        // Render
        //
        rind.render(io,l,i,j+1);
        SDL_Delay(30);
    }
}

//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Selection Sort ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
void selectionSort(RenderWindow rind, ImGuiIO &io, Lines &l)
{
    for (int i = 0; i < l.val.size(); i++) {
        int min_index = i;
        int j = i + 1;

        for (j; j < l.val.size(); j++) {
            if (l.val[j] < l.val[min_index])
                min_index = j;
        }
        l.swap(min_index, i);

        // Render
        //
        rind.render(io,l,i,min_index);
        SDL_Delay(30);
    }

    for (auto i : l.val) {
        std::cout<< i << " ";
    }
    if(std::is_sorted(l.val.begin(), l.val.end()))
        std::cout << "sorted\n"; 
}


// ****************************************************************************
// ****************************** EFFICIENT SORTS *****************************
// ****************************************************************************
//

//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Merge Sort ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//




// ****************************************************************************
// ******************************* BUBBLE SORTS *******************************
// ****************************************************************************
//

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Bubble Sort ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
            // SDL_Delay(5);
        }
    }
}
