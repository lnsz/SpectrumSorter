#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <vector>
#include <iostream>
#include "Vertex.h"

class List
{
public:
	List();
	~List();

	void draw();
	void init(int y, int width, int height);
	void sort();
	void shuffle();
	void update();

private:
	Vertex* _vertexData;
	int _numVertices;
	int _y;
	int _size;
	int _height;
	std::vector<int> _list;
	GLuint _vboID;
};
