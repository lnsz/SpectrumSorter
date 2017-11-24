#include "View.h"
#include "Helpers.h"
#include "List.h"
#include "Errors.h"
#include "SortingAlgorithms.h"
#include <time.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <functional>
#include <future>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

View::View() {
	_window = nullptr;
	_screenWidth = 0;
	_screenHeight = 0;
	_algorithm = "";
}

View::~View()
{
}

void View::init(std::string algorithm) {
	_algorithm = algorithm;
	create();
	run();
}

void View::create() {
	SDL_Init(SDL_INIT_EVERYTHING);

	_window = SDL_CreateWindow("Sorting Visualizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	SDL_GetWindowSize(_window, &_screenWidth, &_screenHeight);
	_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);

	if (_window == nullptr) {
		fatalError("SDL Window could not be created");
	}

	glewExperimental = true;
	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr) {
		fatalError("SDL_GL context could not be created");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatalError("Could not initialize glew");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0, 0, 0, 1.0);


	_shaders.compileShaders("C:\\Users\\lucas\\Documents\\GitHub\\SortingVisualizer\\src\\Shaders\\colourShader.vert", "C:\\Users\\lucas\\Documents\\GitHub\\SortingVisualizer\\src\\Shaders\\colourShader.frag");
	_shaders.addAttribute("vertexPosition");
	_shaders.addAttribute("vertexColour");
	_shaders.linkShaders();

	for (int i = 0; i < _screenHeight; i++) {
		_lists.push_back(List());
		_lists[i].init(i, _screenWidth, _screenHeight);
		_lists[i].shuffle();
	}
}

void View::run() {
	clock_t t1, t2;
	t1 = clock();
	bubbleSort(_lists, this);
	t2 = clock();
	std::cout << "Finished in " << (t2 - t1) / 1000.0 << " seconds" << std::endl;
	while (true) {
		processInput();
	}
}

void View::processInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type) {
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_MOUSEMOTION:
				// std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			default:
				break;
		}
	}
}

void View::render() {
	clock_t t1, t2;
	t1 = clock();
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	_shaders.use();
	GLint pLocation = _shaders.getUniformLocation("P");

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(_orthoMatrix[0][0]));

	for (int i = 0; i < _lists.size(); i++) {
		_lists[i].draw();
	}
	_shaders.unuse();
	SDL_GL_SwapWindow(_window);
	t2 = clock();
	//std::cout << "draw: " << t2 - t1 << std::endl;
}