#pragma once
#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "file.h"
#include "vector.h"
#include "image.h"

#define LINE_SIZE 256

class Model {
public:
	Model(){}
	~Model() {
		std::vector<Vector3f>().swap(position_buffer);
		std::vector<Vector3f>().swap(normal_buffer);
		std::vector<Vector2f>().swap(texcoord_buffer);
		std::vector<uint32_t>().swap(face_buffer);
	}

	void load(const std::string file_name);
	
	int get_num_vertices();
	int get_num_faces();

	void load_obj(const std::string file_name);

	int get_face_index(const int index);

	Vector3f get_vertex(const int face_index, const int ver_index);

	Vector2f get_uv(const int face_index, const int ver_index);

	void load_diffuse_map(const std::string file_name);

	void load_normal_map(const std::string file_name);

	void load_specular_map(const std::string file_name);

	uint8_t* get_diffuse_color(const Vector2f& texcoord);

private:

	std::string name;
	int num_vertexs;
	int num_faces;
	std::vector<Vector3f> position_buffer;
	std::vector<Vector3f> normal_buffer;
	std::vector<Vector2f> texcoord_buffer;
	std::vector<uint32_t> face_buffer;

	Image diffuse_map;
	Image normal_map;
	Image specular_map;
};

#endif
