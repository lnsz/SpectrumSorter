#include <vector>
#include <iostream>
#include <GL/glew.h>

using namespace std;

std::vector<float> int2colour(float x) {
	float red;
	float green;
	float blue;
	float size = 255.0f;
	if (x <= size / 3.0f) {
		red = size / 3.0f - x;
		green = x;
		blue = 0.0f;
	}
	else if (x <= 2.0f * size / 3.0f) {
		red = 0;
		green = 2.0f * size / 3.0f - x;
		blue = x - size / 3.0f;
	}
	else if (x <= size) {
		red = x - 2.0f * size / 3.0f;
		green = 0.0f;
		blue = size - x;
	}
	else {
		red = 0.0f;
		green = 0.0f;
		blue = 0.0f;
	}
	red *= 765.0f / size;
	green *= 765.0f / size;
	blue *= 765.0f / size;

	std::vector<float> colours;
	colours.push_back(red);
	colours.push_back(green);
	colours.push_back(blue);
	//std::cout << x << ": " << colours[0] << ", " << colours[1] << ", " << colours[2] << std::endl;
	return colours;
}