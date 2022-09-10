#pragma once
#ifndef BUFFER_H
#define BUFFER_H

#include "file.h"

class Buffer {
public:
	float& operator [](int index);

	~Buffer()
	{
		delete[] buffer;
	}
protected:
	int width, height;
	float* buffer;
};

class ZBuffer : public Buffer {
public:
	ZBuffer(int width, int height);
};


#endif