#include <vector>
#include <iostream>

using namespace std;

std::vector<int> int2colour(int x) {
	int red;
	int green;
	int blue;
	if (x <= 255) {
		red = 255 - x;
		green = x;
		blue = 0;
	}
	else if (x <= 510) {
		red = 0;
		green = 510 - x;
		blue = x - 255;
	}
	else if (x <= 765) {
	//else if (x <= 640) {
		red = x - 510;
		green = 0;
		blue = 765 - x;
	}
	else {
		red = 0;
		green = 0;
		blue = 0;
	}
	//std::cout << red << ", " << green << ", " << blue << std::endl;
	std::vector<int> colours;
	colours.push_back(red);
	colours.push_back(green);
	colours.push_back(blue);
	return colours;
}