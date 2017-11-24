#include <iostream>
#include <algorithm>
#include <vector> 
#include <SDL/SDL.h>
#include <cstdlib>
#include "View.h"
#include "List.h"
#include <mutex>

void bubbleSort(std::vector<List> &lists, View* view)  {
	int n = lists[0].elements.size();
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			for (int l = 0; l < lists.size(); l++) {
				if (lists[l].elements[j] > lists[l].elements[j + 1]) {
					std::swap(lists[l].elements[j], lists[l].elements[j + 1]);
					lists[l].updateItem(j);
					lists[l].updateItem(j + 1);
					view->processInput();
				}
			}
			view->render();
		}
	}	
}