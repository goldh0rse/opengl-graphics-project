#ifndef LOADER_H_
#define LOADER_H_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "vertex.h"
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

static vector<Vertex> loadObject(string file_name){
    //Vertex portions
	std::vector<glm::fvec3> vertex_positions;
	std::vector<glm::fvec2> vertex_texcoords;
	std::vector<glm::fvec3> vertex_normals;

	//Face vectors
	std::vector<GLint> vertex_position_indicies;
	std::vector<GLint> vertex_texcoord_indicies;
	std::vector<GLint> vertex_normal_indicies;

	//Vertex array
	std::vector<Vertex> vertices;

	std::stringstream ss;
	std::ifstream in_file(file_name);
	std::string line = "";
	std::string prefix = "";
	glm::vec3 temp_vec3;
	glm::vec2 temp_vec2;
	GLint temp_glint = 0;
	float vMax = 0.f;

	//File open error check
	if (!in_file.is_open()) {
		cout << "Error: could not load .objfile: " << file_name << endl;
	}

	//Read one line at a time
	while (std::getline(in_file, line)){
		//Get the prefix of the line
		ss.clear();
		ss.str(line);
		ss >> prefix;

		if (prefix == "#"){
			continue;
		} else if (prefix == "o"){

		} else if (prefix == "s") {

		} else if (prefix == "use_mtl") {

		} else if (prefix == "v") { // Vertex Name
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			if (std::abs(temp_vec3.x) > vMax)
				vMax = std::abs(temp_vec3.x);

			if (std::abs(temp_vec3.y) > vMax)
				vMax = std::abs(temp_vec3.y);

			if (std::abs(temp_vec3.z) > vMax)
				vMax = std::abs(temp_vec3.z);

			vertex_positions.push_back(temp_vec3);

		} else if (prefix == "vt") { // Vertex Texcoord
			ss >> temp_vec2.x >> temp_vec2.y;
			vertex_texcoords.push_back(temp_vec2);

		} else if (prefix == "vn") { // Vertex Normal
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			vertex_normals.push_back(temp_vec3);

		} else if (prefix == "f") {
			int counter = 0;
			while (ss >> temp_glint) {
				//Pushing indices into correct arrays
				if (counter == 0)
					vertex_position_indicies.push_back(temp_glint);
				else if (counter == 1)
					vertex_texcoord_indicies.push_back(temp_glint);
				else if (counter == 2)
					vertex_normal_indicies.push_back(temp_glint);

				//Handling characters
				if (ss.peek() == '/') {
					++counter;
					ss.ignore(1, '/');
				} else if (ss.peek() == ' ') {
					++counter;
					ss.ignore(1, ' ');
				}

				//Reset the counter
				if (counter > 2)
					counter = 0;
			}
		}
	}

	//Build final vertex array (mesh)
	vertices.resize(vertex_position_indicies.size(), Vertex());

	//Load in all indices
	for (size_t i = 0; i < vertices.size(); ++i) {
		vertices[i].position = vertex_positions[vertex_position_indicies[i] - 1] / (2.f * vMax);
		vertices[i].texcoord = vertex_texcoords[vertex_texcoord_indicies[i] - 1];
		vertices[i].normal = vertex_normals[vertex_normal_indicies[i] - 1];
		vertices[i].color = glm::vec3(1.f, 1.f, 1.f);
	}

	//DEBUG
	cout << "Nr of vertices: " << vertices.size() << endl;

	//Loaded success
	cout << "Loaded OBJ file:" << file_name << endl;
	return vertices;
}

#endif
