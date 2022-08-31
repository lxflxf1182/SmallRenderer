#pragma once
#ifndef DRAW2D_H
#define DRAW2D_H

#include "image.h"
#include "math.h"

void draw_line_v1(int x0, int y0, int x1, int y1, Image& image, const uint8_t* color);

void draw_line_v2(int x0, int y0, int x1, int y1, Image& image, const uint8_t* color);

void draw_line_v3(int x0, int y0, int x1, int y1, Image& image, const uint8_t* color);

void draw_line_v4(int x0, int y0, int x1, int y1, Image& image, const uint8_t* color);

void draw_triangle_v1(Vector2i v1, Vector2i v2, Vector2i v3,Image& image, const uint8_t* color);

void draw_triangle_v2(Vector2i v1, Vector2i v2, Vector2i v3, Image& image, const uint8_t* color);

void draw_triangle_v3(Vector2i* pts, Image& image, const uint8_t* color);

#endif
