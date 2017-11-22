#include "View.h"
#include "Helpers.h"
#include <string>
#include <iostream>
#include <vector>

void fatalError(std::string errorString) {
	std::cout << errorString << std::endl;
	std::cout << "Enter any key to quit...";
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
}

View::View() {
	_window = nullptr;
	_screenWidth = 765;
	_screenHeight = 300;
	_state = State::RUN;
}

View::~View()
{
}

void View::start() {
	init();
	run();
}

void View::init() {
	SDL_Init(SDL_INIT_EVERYTHING);

	_window = SDL_CreateWindow("Sorting Visualizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);

	if (_window == nullptr) {
		fatalError("SDL Window could not be created");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr) {
		fatalError("SDL_GL context could not be created");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatalError("Could not initialize glew");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0, 0, 255, 1.0);

	glOrtho(0, _screenWidth, 0, _screenHeight, -1, 1);

	for (int y = 0; y < _screenHeight; y++) {
		std::vector<int> temp;
		for (int x = 0; x < _screenWidth; x++) {
			temp.push_back(x);
			//std::vector<int> colour = int2colour(x);
			//std::cout << colour[0] << ", " << colour[1] << ", " << colour[2] << std::endl;
		}
		_lists.push_back(temp);
	}
}

void View::run() {
	while (_state != State::EXIT) {
		processInput();
		render();
	}
}

void View::processInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type) {
			case SDL_QUIT:
				_state = State::EXIT;
				break;
			case SDL_MOUSEMOTION:
				// std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			default:
				break;
		}
	}
}

void View::render() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableClientState(GL_COLOR_ARRAY);

	for (int y = 0; y < _lists.size(); y++) {
		for (int x = 0; x < _lists[y].size(); x++) {
			glBegin(GL_POINTS);
			std::vector<int> colour = int2colour(_lists[y][x]);
			glColor3ub(colour[0], colour[1], colour[2]);
			glVertex2f(x, y);
			glEnd();
		}
	}
	SDL_GL_SwapWindow(_window);
}