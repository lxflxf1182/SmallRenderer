#include "file.h"

bool HasExtension(std::string file_name, std::string ext)
{
	return (file_name.substr(file_name.find_last_of('.') + 1) == ext);
}

unsigned char read_byte(FILE* file)
{
	int byte = fgetc(file);
	if (byte == EOF) {
		Throw("file::read_byte():failed to read a character");
	}
	return (unsigned char)byte;
}

void read_bytes(FILE* file, void* buffer, int size)
{
	if ((int)fread(buffer, 1, size, file) != size) {
		Throw("file::read_bytes(): the number of characters read is "
			"not the same as the number of characters to be read");
	}
}

void write_bytes(FILE* file, void* buffer, int size)
{
	if ((int)fwrite(buffer, 1, size, file) != size) {
		Throw("file::write_bytes(): the number of characters write is "
			"not the same as the number of characters to be write");
	}
}

void read_rle_data(FILE* file, uint8_t* buffer, int channels, int size)
{
	int cur_size = 0;
	while (cur_size < size) {
		unsigned char sign = read_byte(file);
		bool is_repeat = sign & 0x80;
		int num_pixels = (sign & 0x7F) + 1;
		unsigned char pixels[4];
		if (is_repeat) {
			for (int i = 0; i < channels; i++) {
				pixels[i] = read_byte(file);
			}
			for (int i = 0; i < num_pixels; i++) {
				for (int j = 0; j < channels; j++) {
					buffer[cur_size++] = pixels[j];
				}
			}
		}
		else {
			int total_num_pixels = num_pixels * channels;
			for (int i = 0; i < total_num_pixels; i++) {
				buffer[cur_size++] = read_byte(file);
			}
		}
	}
	if (cur_size != size) {
		Throw("file::read_rle_data(): size mismatch when reading images");
	}
}


