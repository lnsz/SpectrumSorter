#include <iostream>
#include "View.h"

int main(int argc, char** argv) {
	View view;
	view.run();

	std::cout << "Enter any key to quit...";
	int a;
	std::cin >> a;
	return 0;
}