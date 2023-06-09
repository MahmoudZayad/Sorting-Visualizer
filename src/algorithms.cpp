#include "algorithms.h"

// Create vector with randomized values
//
void randomizeVector(Lines& l, int size)
{
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
    int rectWidth = WIDTH / size;
    int index = (WIDTH - rectWidth * size) * 0.5; 

    for (int i = 0; i < size; i++)
    {
        v[i] = d(rd);
        r[i] = {index, 4 * 16, rectWidth-1, v[i] + (4 * 16)};
        c[i] = {255, 255, 255, 255};
        index += rectWidth;
    }
    l.rect = r;
    l.val = v;
    l.col = c;
}

//
// ****************************************************************************
// ******************************* SIMPLE SORTS *******************************
// ****************************************************************************
//

//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Insertion Sort ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
void insertionSort(RenderWindow& rind, ImGuiIO& io, Lines& l)
{    
    for (int i = 1; i < l.val.size(); i++)
    {
        int key = l.val[i];
        SDL_Rect keyr = l.rect[i];
        int j = i - 1;
        
        while (j >= 0 && l.val[j] > key)
        {
            l.val[j + 1] = l.val[j];
            l.rect[j + 1] = l.rect[j];
            j--;
        }
        l.val[j + 1] = key;
        l.rect[j + 1] = keyr;

        // Render
        //
        rind.render(io, l, j+1, i);
        SDL_Delay(30);
    }
}

//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Selection Sort ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
void selectionSort(RenderWindow rind, ImGuiIO &io, Lines &l)
{
    for (int i = 0; i < l.val.size(); i++)
    {
        int min_index = i;
        int j = i + 1;

        for (j; j < l.val.size(); j++)
        {
            if (l.val[j] < l.val[min_index])
                min_index = j;
        }
        l.swap(min_index, i);

        // Render
        //
        rind.render(io, l, min_index, i);
        SDL_Delay(30);
    }
}

//
// ****************************************************************************
// ****************************** EFFICIENT SORTS *****************************
// ****************************************************************************
//

//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Merge Sort ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
void merge(RenderWindow& rind, ImGuiIO& io, Lines& l, int left, int mid, int right) 
{
    
    // Find size of sub vectors
    int sizeL = mid - left + 1;
    int sizeR = right - mid;
    std::vector<int>  vecLeft(sizeL, 0);
    std::vector<int>  vecRight(sizeR, 0);
    std::vector<SDL_Rect>  vecRecL(sizeL, SDL_Rect());
    std::vector<SDL_Rect>  vecRecR(sizeR, SDL_Rect());

    // Fill sub vectors
    for (int i = 0; i < sizeL; i++)
    {
        vecLeft[i] = l.val[i + left];
        vecRecL[i] = l.rect[i + left];
    }
    for (int i = 0; i < sizeR; i++) 
    {
        vecRight[i] = l.val[i + mid + 1];
        vecRecR[i] = l.rect[i + mid + 1];
    }
    
    int indexL = 0, indexR = 0;
    int indexMerge = left;

    // Merge the arrays
    while(indexL < sizeL && indexR < sizeR) 
    {
        if (vecLeft[indexL] <= vecRight[indexR])
        {
            l.val[indexMerge] = vecLeft[indexL];
            l.rect[indexMerge] = vecRecL[indexL];
            // Render
            rind.render(io, l, indexL + left, indexMerge);
            SDL_Delay(10);
            indexL++;
        }
        else 
        {
            l.val[indexMerge] = vecRight[indexR];
            l.rect[indexMerge] = vecRecR[indexR];
            // Render
            rind.render(io,l, indexR + mid + 1, indexMerge);
            SDL_Delay(10);

            indexR++;
        }
        indexMerge++;
        
    }

    while (indexL < sizeL)
    {
        l.val[indexMerge] = vecLeft[indexL];
        l.rect[indexMerge] = vecRecL[indexL];
        // Render
        rind.render(io,l, indexL + left, indexMerge);
        SDL_Delay(10);
        indexL++;
        indexMerge++;
    }
    
    while (indexR < sizeR)
    {
        l.val[indexMerge] = vecRight[indexR];
        l.rect[indexMerge] = vecRecR[indexR];
        // Render
        rind.render(io,l, indexR + mid + 1, indexMerge);
        SDL_Delay(10);
        indexR++;
        indexMerge++;
    }
}

void mergeSort(RenderWindow& rind, ImGuiIO& io, Lines& l, int left, int right)
{ 
    if (left < right) 
    {
        int mid = left + (right - left) / 2;
        mergeSort(rind, io, l, left, mid);
        mergeSort(rind, io, l, mid + 1, right);

        merge(rind, io, l, left, mid, right);

    }

}

//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Quick Sort ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

int partition(RenderWindow& rind, ImGuiIO& io, Lines& l, int low, int high)
{   
    int pivot = l.val[high];

    int store = low - 1;
    for (int i = low; i <= high; i++) 
    {
        if (l.val[i] < pivot) {
            store++;
            l.swap(store, i);
            // Render
            rind.render(io,l, store, i);
            SDL_Delay(5);
        }
    }
    l.swap(store + 1, high);
    // Render
    rind.render(io,l, store + 1, high);
    SDL_Delay(5);
    return store + 1;
}

void quickSort(RenderWindow& rind, ImGuiIO& io, Lines& l, int low, int high) 
{
    if (low < high)
    {
        int pivot = partition(rind, io, l, low, high);
        quickSort(rind, io, l, low, pivot - 1);
        quickSort(rind, io, l, pivot + 1, high);
    }
}

//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Counting Sort ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

void countingSort(RenderWindow& rind, ImGuiIO &io, Lines &l)
{
    auto maxIndex = distance(std::begin(l.val), max_element(std::begin(l.val), std::end(l.val)));
    auto maxVal = l.val[maxIndex];
    std::vector<int> count(maxVal + 1, 0);
    std::vector<int> output(maxVal + 1, 0);
    std::vector<SDL_Rect> outputRect(maxVal + 1, SDL_Rect());

    int size = l.val.size();

    // Count each instance of a value
    for (int i = 0; i < size; i++)
        count[l.val[i]]++;

    // Find cummulative sum of instances of values up to each index
    for (int i = 1; i <= maxVal; i++) 
        count[i] += count[i-1];

    for (int i = size - 1; i >= 0; i--) 
    {
        output[count[l.val[i]] - 1] = l.val[i];
        outputRect[count[l.val[i]] - 1] = l.rect[i];
        count[l.val[i]]--;
        // Render
        //
        rind.render(io,l, count[l.val[i]] - 1, i);
        SDL_Delay(5);
    }
    
    for (int i= 0; i < size; i++)
    {
        l.val[i] = output[i];
        l.rect[i] = outputRect[i];
        // Render
        //
        rind.render(io,l, 1000, i);
        SDL_Delay(5);
    }
}

//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Radix Sort ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

void _sortDigit(RenderWindow& rind, ImGuiIO &io, Lines &l, int digit)
{
    const int max = 10;
    int size = l.val.size();
    std::vector<int> count(max, 0);
    std::vector<int> output(size, 0);
    std::vector<SDL_Rect> outputRect(size, SDL_Rect());
    
    // Count each instance of a value
    for (int i = 0; i < size; i++)
        count[(l.val[i] / digit) % 10]++;

    // Find cummulative sum of instances of values up to each index
    for (int i = 1; i <= max; i++) 
        count[i] += count[i-1];

    for (int i = size - 1; i >= 0; i--) 
    {
        output[count[(l.val[i] / digit) % 10] - 1] = l.val[i];
        outputRect[count[(l.val[i] / digit) % 10] - 1] = l.rect[i];
        count[(l.val[i] / digit) % 10]--;
        // Render
        //
        rind.render(io,l, count[(l.val[i] / digit) % 10] - 1, i);
        SDL_Delay(5);
    }
    
    for (int i= 0; i < size; i++)
    {
        l.val[i] = output[i];
        l.rect[i] = outputRect[i];
        // Render
        //
        rind.render(io,l, 1000, i);
        SDL_Delay(5);
    }
}

void radixSort(RenderWindow& rind, ImGuiIO &io, Lines &l)
{
    auto maxIndex = distance(std::begin(l.val), max_element(std::begin(l.val), std::end(l.val)));
    auto maxVal = l.val[maxIndex];

    for (int digit = 1; maxVal / digit > 0; digit *= 10)
    {
        _sortDigit(rind, io, l, digit);
    }

    for (auto i : l.val)
        std::cout<< i << " ";
    if(std::is_sorted(l.val.begin(), l.val.end()))
        std::cout << "sorted\n"; 
}


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
