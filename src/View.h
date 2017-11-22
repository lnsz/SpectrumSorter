#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>

class View
{
public:
	View();
	~View();

	void run();

	void init();

private:
	SDL_Window* _window;
	int _screenWidth;
	int _screenHeight;
};

