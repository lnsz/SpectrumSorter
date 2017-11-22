#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <vector>
#include <iostream>

enum class State {RUN, EXIT};

class View
{
public:
	View();
	~View();
	void start();

private:
	void run();
	void init();
	void render();
	void processInput();
	SDL_Window* _window;
	State _state;
	int _screenWidth;
	int _screenHeight;
	std::vector< std::vector<int> > _lists;
};

