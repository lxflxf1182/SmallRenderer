#pragma once

#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <memory>
#include "file.h"


#define TGA_HEADER_SIZE 18

enum class PixelFormat {
	Y,
	RGB,
	RGBA
};

enum class FileFormat{
	TGA
};

enum class	PrecisionFormat {
	UInt8,
	Float
};

class Image {
public:
	Image() = default;

	Image(int width, int height, int channels);

	void write(const std::string file_name);

	void read(const std::string file_name);

	void set(int row, int col, const uint8_t* color);

	int get_width();

	int get_height();

protected:
	void write_tga(const std::string file_name);

	void read_tga(const std::string file_name);

	void flip_horizontally();

	void flip_vertically();

	int get_index(const int row, const int col);
	 
protected:
	std::unique_ptr<uint8_t[]> ldr_data;
	std::unique_ptr<float[]> hdr_data;
	int width, height, channels;
	PixelFormat format;
};

#endif // !IMAGE_H

