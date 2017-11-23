#include "List.h"
#include "Helpers.h"
#include <iostream>
#include <algorithm>
#include <random>
#include "Vertex.h"
#include <cstddef>
auto rng = std::default_random_engine{};

List::List() : _y(0), _size(0), _vboID(0)
{
}

List::~List()
{
	if (_vboID != 0) {
		glDeleteBuffers(1, &_vboID);
	}
}

void List::init(int y, int width, int height) {
	_y = y;
	_size = width;
	_height = height;

	for (int i = 0; i < _size; i++) {
		_list.push_back(i);
	}

	update();
}

void List::update() {
	_vertexData = new Vertex[_size];
	for (int i = 0; i < _size; i++) {
		_vertexData[i].position.x = -1 + (float)i / (float)_size * 2;
		_vertexData[i].position.y = -1 + (float)_y / (float)_height * 2;
		std::vector<int> colour = int2colour(_list[i]);
		_vertexData[i].colour.r = colour[0];
		_vertexData[i].colour.g = colour[1];
		_vertexData[i].colour.b = colour[2];
		_vertexData[i].colour.a = 255;
	}
}

void List::draw() {

	if (_vboID == 0) {
		glGenBuffers(1, &_vboID);
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	glBufferData(GL_ARRAY_BUFFER, sizeof(*_vertexData) * _size, _vertexData, GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, colour));

	glDrawArrays(GL_POINTS, 0, _size);

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void List::sort() {
	std::sort(std::begin(_list), std::end(_list));
}

void List::shuffle() {
	std::shuffle(std::begin(_list), std::end(_list), rng);
	update();
}