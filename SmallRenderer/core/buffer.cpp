#include "buffer.h"

ZBuffer::ZBuffer(int width, int height)
{
	this->width = width;
	this->height = height;
	buffer = new float[width * height];
	for (int i = 0; i < width * height; i++)
		buffer[i] = -std::numeric_limits<float>::max();
}

float& ZBuffer::operator[](int index)
{
	if (index >= width * height) {
		Throw("ZBuffer::operator[]: Out of array range");
	}
	return buffer[index];
}
