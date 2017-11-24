#include <iostream>
#include <algorithm>
#include <vector> 
#include <SDL/SDL.h>
#include <cstdlib>
#include "View.h"
#include "List.h"
#include <mutex>

void swap(List &list, int i, int j) {
	std::swap(list.elements[i], list.elements[j]);
	list.updateItem(i);
	list.updateItem(j);
}

void bubbleSort(std::vector<List> &lists, View* view)  {
	int n = (int)lists[0].elements.size();
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			for (int l = 0; l < lists.size(); l++) {
				if (lists[l].elements[j] > lists[l].elements[j + 1]) {
					swap(lists[l], j, j + 1);
					view->processInput();
				}
			}
			view->render();
		}
	}	
}

void insertionSort(std::vector<List> &lists, View* view) {
	int n = (int)lists[0].elements.size();
	for (int i = 1; i < n; i++) {
		for (int l = 0; l < lists.size(); l++) {
			int j = i;
			while (j > 0 && lists[l].elements[j - 1] > lists[l].elements[j])
			{
				swap(lists[l], j, j - 1);
				j--;
				view->processInput();
			}
		}
		view->render();
	}
}

void selectionSort(std::vector<List> &lists, View* view) {
	int n = (int)lists[0].elements.size();
	for (int i = 0; i < n - 1; i++) {
		int min = i;
		for (int l = 0; l < lists.size(); l++) {
			for (int j = i + 1; j < n; j++) {
				if (lists[l].elements[j] < lists[l].elements[min]) {
					min = j;
				}
			}
			swap(lists[l], min, i);
			view->processInput();
		}
		view->render();
	}
}

std::vector<int> copyAndAdd(std::vector<int> v, int change) {
	for (int i = 0; i < v.size(); i++) {
		v[i] += change;
	}
	return v;
}


std::vector<int> partition(std::vector<List> &lists, View* view, std::vector<int> low, std::vector<int> high) {
	std::vector<int> pivots;
	std::vector<int> i;
	for (int l = 0; l < lists.size(); l++) {
		i.push_back(low[l] - 1);
		std::cout << l << " " << low[l] << " " << high[l] << std::endl;
		if (low[l] < high[l]) {
			pivots.push_back(lists[l].elements[high[l]]);
			for (int j = low[l]; j < high[l]; j++) {
				if (lists[l].elements[j] < pivots[l]) {
					i[l]++;
					swap(lists[l], i[l], j);
				}
			}
			swap(lists[l], i[l] + 1, high[l]);
		}
		else {
			pivots.push_back(0);
		}
	}
	view->processInput();
	view->render();
	return i;
}

void quickSort(std::vector<List> &lists, View* view, std::vector<int> low, std::vector<int> high) {
	if (low < high) {
		std::vector<int> p = partition(lists, view, low, high);
		quickSort(lists, view,  low, p);
		quickSort(lists, view, copyAndAdd(p, 2), high);
	}
}
