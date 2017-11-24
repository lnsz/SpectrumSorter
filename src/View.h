#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <vector>
#include <iostream>
#include "List.h"
#include "GLSLProgram.h"

class List;

class View
{
public:
	View();
	~View();
	void init(std::string algorithm);
	void render();
	void processInput();

private:
	void run();
	void create();
	SDL_Window* _window;
	int _screenWidth;
	int _screenHeight;
	std::vector< List > _lists;
	GLSLProgram _shaders;
	std::string _algorithm;
};

