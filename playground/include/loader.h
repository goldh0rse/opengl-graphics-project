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
	vector<glm::fvec3> vertex_positions;
	vector<glm::fvec2> vertex_texcoords;
	vector<glm::fvec3> vertex_normals;

	//Face vectors
	vector<GLint> vertex_position_indicies;
	vector<GLint> vertex_texcoord_indicies;
	vector<GLint> vertex_normal_indicies;

	//Vertex array
	vector<Vertex> vertices;

	stringstream ss;
	ifstream in_file(file_name);
	string line = "";
	string prefix = "";
	glm::vec3 temp_vec3;
	glm::vec2 temp_vec2;
	GLint temp_glint = 0;
	float v_max = 0.f;
	bool contains_normals = false;

	//File open error check
	if (!in_file.is_open()) {
		cout << "Error: could not load .objfile: " << file_name << endl;
	}

	//Read one line at a time
	while (getline(in_file, line)){
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
			if (abs(temp_vec3.x) > v_max)
				v_max = abs(temp_vec3.x);

			if (abs(temp_vec3.y) > v_max)
				v_max = abs(temp_vec3.y);

			if (abs(temp_vec3.z) > v_max)
				v_max = abs(temp_vec3.z);

			vertex_positions.push_back(temp_vec3);

		} else if (prefix == "vt") { // Vertex Texcoord
			ss >> temp_vec2.x >> temp_vec2.y;
			vertex_texcoords.push_back(temp_vec2);

		} else if (prefix == "vn") { // Vertex Normal
			contains_normals = true;
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			vertex_normals.push_back(temp_vec3);

		} else if (prefix == "f") {
			string vertex1, vertex2, vertex3;
			GLint vertexIndex[3], texIndex[3], normalIndex[3];

			// 1. f v1 v2 v3
	    int matches = sscanf(line.c_str(), "f %d %d %d\n",
				&vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);

			if (matches == 3){
				// load the values
				cout << "Format: f v1 v2 v3" << endl;

				vertex_position_indicies.push_back(vertexIndex[0]);
				vertex_position_indicies.push_back(vertexIndex[1]);
				vertex_position_indicies.push_back(vertexIndex[2]);

			} else {
				// 2. f v1/vt1 v2/vt2 v3/vt3
				matches = sscanf(line.c_str(), "f %d/%d %d/%d %d/%d\n",
					&vertexIndex[0], &texIndex[0],
					&vertexIndex[1], &texIndex[1],
					&vertexIndex[2], &texIndex[2]);

				if (matches == 6){
					// load the values
					cout << "Format: f v1/vt1 v2/vt2 v3/vt3" << endl;

					vertex_position_indicies.push_back(vertexIndex[0]);
					vertex_position_indicies.push_back(vertexIndex[1]);
					vertex_position_indicies.push_back(vertexIndex[2]);
					vertex_texcoord_indicies.push_back(texIndex[0]);
					vertex_texcoord_indicies.push_back(texIndex[1]);
					vertex_texcoord_indicies.push_back(texIndex[2]);
				} else {
					// 3. f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3
					matches = sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d\n",
						&vertexIndex[0], &texIndex[0], &normalIndex[0],
						&vertexIndex[1], &texIndex[1], &normalIndex[1],
						&vertexIndex[2], &texIndex[2], &normalIndex[2]);

					if (matches == 9){
						// load the values
						cout << "Format: f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3" << endl;

						vertex_position_indicies.push_back(vertexIndex[0]);
						vertex_position_indicies.push_back(vertexIndex[1]);
						vertex_position_indicies.push_back(vertexIndex[2]);
						vertex_texcoord_indicies.push_back(texIndex[0]);
						vertex_texcoord_indicies.push_back(texIndex[1]);
						vertex_texcoord_indicies.push_back(texIndex[2]);
						vertex_normal_indicies.push_back(normalIndex[0]);
						vertex_normal_indicies.push_back(normalIndex[1]);
						vertex_normal_indicies.push_back(normalIndex[2]);
					} else {
						// 4. f v1//vn1 v2//vn2 v3//vn3
						matches = sscanf(line.c_str(), "f %d//%d %d//%d %d//%d\n",
							&vertexIndex[0], &normalIndex[0],
							&vertexIndex[1], &normalIndex[1],
							&vertexIndex[2], &normalIndex[2]);

						if (matches == 6){
							// load the values
							cout << "Format: f v1//vn1 v2//vn2 v3//vn3" << endl;

							vertex_position_indicies.push_back(vertexIndex[0]);
							vertex_position_indicies.push_back(vertexIndex[1]);
							vertex_position_indicies.push_back(vertexIndex[2]);
							vertex_normal_indicies.push_back(normalIndex[0]);
							vertex_normal_indicies.push_back(normalIndex[1]);
							vertex_normal_indicies.push_back(normalIndex[2]);
						} else {
							// Something went wrong! Can't read file
							cout << "Error reading objectfile: " << file_name << endl;
							exit(-1);
						}
					}
				}
			}

			/*
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
			*/
		}
	}

	if(!contains_normals){
		// Compute normals from vertices
		cout << "OBJ-File does not contain any normals: " << file_name << endl;
	}

	//Build final vertex array (mesh)
	vertices.resize(vertex_position_indicies.size(), Vertex());

	//Load in all indices
	for (size_t i = 0; i < vertices.size(); ++i) {
		if(vertex_positions.size() > 0){
			vertices[i].position = vertex_positions[vertex_position_indicies[i] - 1] / (2.f * v_max);
		}

		if(vertex_texcoords.size() > 0){
			vertices[i].texcoord = vertex_texcoords[vertex_texcoord_indicies[i] - 1];
		}

		if(vertex_normals.size() > 0){
			vertices[i].normal = vertex_normals[vertex_normal_indicies[i] - 1];
		}

		// Not added support for color reading.
		vertices[i].color = glm::vec3(1.f, 1.f, 1.f);
	}

	//DEBUG
	cout << "Nr of vertices: " << vertices.size() << endl;

	//Loaded success
	cout << "Loaded OBJ file:" << file_name << endl;
	return vertices;
}

#endif
