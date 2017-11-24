#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <vector>
#include <iostream>
#include <functional>
#include "Vertex.h"
#include "View.h"

class View;

class List
{
public:
	List();
	~List();

	void draw();
	void init(int y, int width, int height);
	void shuffle();
	void update();
	void updateItem(int index);
	int _y;
	std::vector<int> elements;

private:
	Vertex* _vertexData;
	std::string _algorithm;
	View* _view;
	int _numVertices;
	
	int _size;
	int _height;
	GLuint _vboID;
};
