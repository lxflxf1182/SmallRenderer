#pragma once
#ifndef UTIL_FILE_H
#define UTIL_FILE_H

#include <string>
#include <stdlib.h>
#include "util.h"

bool HasExtension(std::string file_name, std::string ext);

unsigned char read_byte(FILE* file);

void read_bytes(FILE* file, void* buffer, int size);

void write_bytes(FILE* file, void* buffer, int size);

void read_rle_data(FILE* file, uint8_t* buffer, int channels, int size);



#endif // !UTIL_FILE_H
