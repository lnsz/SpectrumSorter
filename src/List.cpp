#include "List.h"
#include "Helpers.h"
#include <iostream>
#include <algorithm>
#include <random>
#include "Vertex.h"
#include <cstddef>
#include "SortingAlgorithms.h"
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
		elements.push_back(i);
	}
	_vertexData = new Vertex[_size];
	update();

	if (_vboID == 0) {
		glGenBuffers(1, &_vboID);
	}

}

void List::update() {
	for (int i = 0; i < _size; i++) {
		_vertexData[i].position.x = (float)i + 0.5f;
		_vertexData[i].position.y = (float)_y + 0.5f;
		std::vector<float> colour = int2colour((float)elements[i]);
		_vertexData[i].colour.r = (GLubyte)colour[0];
		_vertexData[i].colour.g = (GLubyte)colour[1];
		_vertexData[i].colour.b = (GLubyte)colour[2];
		_vertexData[i].colour.a = 255;
		//std::cout << _vertexData[i].position.y << " " << _vertexData[i].position.x << " " << colour[0] << " " << colour[1] << " " << colour[2] << std::endl;
	}
}

void List::updateItem(int index) {
	_vertexData[index].position.x = (float)index + 0.5f;
	_vertexData[index].position.y = (float)_y + 0.5f;
	std::vector<float> colour = int2colour((float)elements[index]);
	_vertexData[index].colour.r = (GLubyte)colour[0];
	_vertexData[index].colour.g = (GLubyte)colour[1];
	_vertexData[index].colour.b = (GLubyte)colour[2];
	_vertexData[index].colour.a = 255;
}

void List::draw() {

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	glBufferData(GL_ARRAY_BUFFER, sizeof(*_vertexData) * _size, _vertexData, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, colour));

	glDrawArrays(GL_POINTS, 0, _size);

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void List::shuffle() {
	std::shuffle(std::begin(elements), std::end(elements), rng);
	update();
}