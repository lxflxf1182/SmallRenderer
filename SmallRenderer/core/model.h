#pragma once
#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "file.h"
#include "vector.h"

#define LINE_SIZE 256

class Model {
public:
	Model(){}

	void load(const std::string file_name);
	
	int get_num_vertices();
	int get_num_faces();

	void load_obj(const std::string file_name);

	int get_face_index(const int index);

	Vector3f get_vertex(const int face_index, const int ver_index);

private:

	std::string name;
	int num_vertexs;
	int num_faces;
	std::vector<Vector3f> position_buffer;
	std::vector<Vector3f> normal_buffer;
	std::vector<Vector2f> texcoord_buffer;
	std::vector<uint32_t> face_buffer;
};

#endif
