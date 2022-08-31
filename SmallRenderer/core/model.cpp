#include "model.h"

void Model::load(const std::string file_name) {
	if (HasExtension(file_name, "obj")) {
		load_obj(file_name);
	}
	else {
		Throw("Model::load(): unsupported object file extension");
	}
}

int Model::get_num_vertices()
{
	return face_buffer.size() / 3;
}

int Model::get_num_faces()
{
	return get_num_vertices() / 3;
}

void Model::load_obj(const std::string file_name)
{
	char line[LINE_SIZE];

	FILE* file = fopen(file_name.c_str(), "rb");
	if (!file) {
		Throw("Model::Model(string): can't open file");
	}

	while (true) {
		int items;
		if (fgets(line, LINE_SIZE, file) == NULL) {
			break;
		} else if (strncmp(line, "v ", 2) == 0) {
			Vector3f position;
			items = sscanf(line, "v %f %f %f",
				&position.x, &position.y, &position.z);
			if (items != 3) {
				Throw("Model::Model(string): incorrect vertex read");
			}
			position_buffer.emplace_back(position);
		} else if (strncmp(line, "vt ", 3) == 0) {              /* texcoord */
			Vector2f texcoord;
			items = sscanf(line, "vt %f %f",
				&texcoord.x, &texcoord.y);
			if (items != 2) {
				Throw("Model::Model(string): incorrect texcoord read");
			}
			texcoord_buffer.emplace_back(texcoord);
		} else if (strncmp(line, "vn ", 3) == 0) {              /* normal */
			Vector3f normal;
			items = sscanf(line, "vn %f %f %f",
				&normal.x, &normal.y, &normal.z);
			if (items != 3) {
				Throw("Model::Model(string): incorrect normal read");
			}
			normal_buffer.emplace_back(normal);
		} else if (strncmp(line, "f ", 2) == 0) {               /* face */
			int i;
			uint32_t vertex1[3], vertex2[3], vertex3[3];
			items = sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
				&vertex1[0], &vertex1[1], &vertex1[2],
				&vertex2[0], &vertex2[1], &vertex2[2],
				&vertex3[0], &vertex3[1], &vertex3[2]);
			if (items != 9) {
				Throw("Model::Model(string): incorrect face read");
			}

			face_buffer.insert(face_buffer.end(), vertex1, vertex1 + 3);
			face_buffer.insert(face_buffer.end(), vertex2, vertex2 + 3);
			face_buffer.insert(face_buffer.end(), vertex3, vertex3 + 3);
		}
	}
	fclose(file);
}

int Model::get_face_index(const int index)
{
	return index * 9;
}

Vector3f Model::get_vertex(const int face_index, const int ver_index)
{
	int v_index = face_index + ver_index * 3;
	int index = face_buffer[v_index] - 1;
	return position_buffer[index];
}
