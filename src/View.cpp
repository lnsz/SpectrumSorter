#include "View.h"

View::View()
{
	_window = nullptr;
	_screenWidth = 600;
	_screenHeight = 400;
}

View::~View()
{
}

void View::run() {
	init();
}

void View::init() {
	SDL_Init(SDL_INIT_EVERYTHING);

	_window = SDL_CreateWindow("Sorting Visualizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
}