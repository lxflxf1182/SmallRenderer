#pragma once
#ifndef BUFFER_H
#define BUFFER_H

#include "file.h"

class Buffer {
protected:
	int width, height;
};

class ZBuffer :Buffer {
public:
	ZBuffer(int width, int height);
	~ZBuffer()
	{
		delete[] buffer;
	}

	float& operator [](int index);

	float* buffer;
};


#endif