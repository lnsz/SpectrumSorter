#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <vector>
#include <iostream>
#include "List.h"
#include "GLSLProgram.h"

enum class State {RUN, EXIT};

class View
{
public:
	View();
	~View();
	void init();

private:
	void run();
	void create();
	void render();
	void processInput();
	SDL_Window* _window;
	State _state;
	int _screenWidth;
	int _screenHeight;
	std::vector< List > _lists;
	GLSLProgram _shaders;
};

