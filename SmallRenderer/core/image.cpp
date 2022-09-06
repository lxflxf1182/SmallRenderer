#include "image.h"

Image::Image(int width, int height, int channels) :width(width), height(height), channels(channels) {
	if (!ldr_data) {
		ldr_data = std::unique_ptr<uint8_t[]>(new uint8_t[width * height * channels]);
	}
	memset(ldr_data.get(), 0, sizeof(uint8_t) * width * height * channels);
}

void Image::write(const std::string file_name)
{
	if (HasExtension(file_name, "tga")) {
		write_tga(file_name);
	}
	else {
		Throw("Image::write(): unsupported image file extension");
	}
}

void Image::read(const std::string file_name)
{
	if (HasExtension(file_name, "tga")) {
		read_tga(file_name);
	}
	else {
		Throw("Image::read(): unsupported image file extension");
	}
}

void Image::set(int row, int col, const uint8_t* color) {

	int index = get_index(row, col) * channels;
	for (int i = 0; i < channels; i++) {
		ldr_data[index + i] = color[i];
	}
}

uint8_t* Image::get(int row, int col)
{
	uint8_t* color = new uint8_t[channels];
	int index = get_index(row, col) * channels;
	memcpy(color, &ldr_data[index], channels);
	return color;
}

int Image::get_width()
{
	return width;
}

int Image::get_height()
{
	return height;
}

void Image::write_tga(const std::string file_name)
{
	if (!ldr_data)
		Throw("Image::write_tga(): unsupported data types");

	unsigned char header[TGA_HEADER_SIZE];

	FILE* file = fopen(file_name.c_str(), "wb");
	if (!file) {
		Throw("Image::write_tga(): can't open file");
	}

	memset(header, 0, TGA_HEADER_SIZE);
	header[2] = (channels == 1) ? 3 : 2;
	header[12] = width & 0xFF;
	header[13] = (width >> 8) & 0xFF;
	header[14] = height & 0xFF;
	header[15] = (height >> 8) & 0xFF;
	header[16] = (channels * 8) & 0xFF;
	write_bytes(file, header, TGA_HEADER_SIZE);

	int size = width * height * channels;
	if (channels >= 3) {
		for (int j = 0; j < height; j++) {
			for (int i = 0; i < width; i++) {
				unsigned char channels_data[4];
				memcpy(channels_data, &ldr_data[(j * width + i) * channels], channels);
				std::swap(channels_data[0], channels_data[2]);
				write_bytes(file, channels_data, channels);
			}
		}
	}
	else {
		write_bytes(file, ldr_data.get(), size);
	}

	fclose(file);
}

void Image::read_tga(const std::string file_name)
{
	FILE* file = fopen(file_name.c_str(), "rb");
	if (!file) {
		Throw("Image::read_tga(): can't open file");
	}

	unsigned char header[TGA_HEADER_SIZE];
	read_bytes(file, header, TGA_HEADER_SIZE);

	width = header[12] | (header[13] << 8);
	height = header[14] | (header[15] << 8);
	if (width <= 0 || height <= 0) {
		Throw("Image::read_tga(): invalid image size");
	}

	if (header[2] != 2 && header[2] != 3 && header[2] != 10 && header[2] != 11) {
		Throw("Image::read_tga(): unsupported image types");
	}
	bool is_rle = header[2] == 10 || header[2] == 11;

	channels = header[16];
	switch (channels)
	{
		case 8:		format = PixelFormat::Y;	break;
		case 24:	format = PixelFormat::RGB;	break;
		case 32:	format = PixelFormat::RGBA;	break;
		default:
			Throw("Image::read_tga(): invalid image depth");
	}
	channels /= 8;

	bool flip_h = header[17] & 0x10;
	bool flip_v = header[17] & 0x20;

	int size = width * height * channels;
	ldr_data = std::unique_ptr<uint8_t[]>(new uint8_t[size]);

	if (!is_rle) {
		read_bytes(file, ldr_data.get(), size);
	}
	else {
		read_rle_data(file, ldr_data.get(), channels, size);
	}
	fclose(file);

	if (flip_h) {
		flip_horizontally();
	}
	if (flip_v) {
		flip_vertically();
	}

	// Convert BGR to RGB
	if (channels >= 3) {
		for (int i = 0; i < size; i+=channels) {
			std::swap(ldr_data[i], ldr_data[i + 2]);
		}
	}
}

void Image::flip_horizontally()
{
	size_t half = width >> 1;
	for (size_t j = 0; j < height; j++) {
		for (size_t i = 0; i < half; i++) {
			for (size_t p = 0; p < channels; p++) {
				std::swap(ldr_data[(j * width + i) * channels + p],
					ldr_data[(j * width + width - i - 1) * channels + p]);
			}
		}
	}
}

void Image::flip_vertically()
{
	size_t half = height >> 1;
	for (size_t j = 0; j < half; j++) {
		for (size_t i = 0; i < width; i++) {
			for (size_t p = 0; p < channels; p++) {
				std::swap(ldr_data[(j * width + i) * channels + p],
					ldr_data[((height - 1 - j) * width + i) * channels + p]);
			}
		}
	}
}

int Image::get_index(const int row, const int col)
{
	return col * width + row;
}
