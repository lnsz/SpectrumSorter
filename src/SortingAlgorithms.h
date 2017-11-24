#pragma once
#include <iostream>
#include <SDL/SDL.h>
#include <cstdlib>
#include "View.h"
#include "List.h"

void swap(List &list, int i, int j);
extern void bubbleSort(std::vector<List> &lists, View* view);
extern void insertionSort(std::vector<List> &lists, View* view);
extern void selectionSort(std::vector<List> &lists, View* view);
std::vector<int> partition(std::vector<List> &lists, View* view, std::vector<int> low, std::vector<int> high);
std::vector<int> copyAndAdd(std::vector<int> v, int change);
extern void quickSort(std::vector<List> &lists, View* view, std::vector<int> low, std::vector<int> high);
