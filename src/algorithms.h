#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>
#include <ranges>
#include <random>
#include "render.h"

enum Sort_ {
    Sort_Insertion,
    Sort_Selection,
    Sort_Merge,
    Sort_Heap,
    Sort_Quick,
    Sort_Shell,
    Sort_Bubble
};

// Creates vectors for the struct lines of int size with randomized values to 400
//
void randomizeVector(Lines& l, int size);

// Simple Sorts
//
void insertionSort(RenderWindow& rind, ImGuiIO& io, Lines& l);
void selectionSort(RenderWindow rind, ImGuiIO& io, Lines& l);

// // Efficient Sorts
// //
// void mergeSort(RenderWindow& rind, ImGuiIO& io, Lines& l);
// void heapSort(RenderWindow& rind, ImGuiIO& io, Lines& l);
// void quickSort(RenderWindow& rind, ImGuiIO& io, Lines& l);
// void shellSort(RenderWindow& rind, ImGuiIO& io, Lines& l);

// // Bubble sort and Variants
// //
void bubbleSort(RenderWindow& rind, ImGuiIO& io, Lines& l);
