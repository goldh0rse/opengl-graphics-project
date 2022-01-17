/* primitive.h - Header file for the primitive class.
 *
 * @description - In general a helper class used during the development,
 *                mainly used as a class that hold stativ shapes
 *                (cubes, planes & such)
 * @note        - Deprecated!!!
 * @author      - Klas Holmberg
 * @email       - hed16khg@cs.umu.se
 * @date        - 2022-01-13
 */
#ifndef PRIMITIVE_H_
#define PRIMITIVE_H_
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "vertex.h"

using namespace std;

class Primitive {
public:
  Primitive();
  ~Primitive(){}

  void set(
    const Vertex* vertices, const unsigned nrOfVertices,
    const GLuint* indices, const unsigned nrOfIndices
  );

  inline Vertex* getVertices(void){return this->vertices.data();}
  inline GLuint* getIndices(void){return this->indices.data();}
  inline const unsigned getNrOfVertices(void){return this->vertices.size();}
  inline const unsigned getNrOfIndices(void){return this->indices.size();}

private:
  vector<Vertex> vertices;
  vector<GLuint> indices;

};

class Quad : public Primitive {
public:
  Quad() : Primitive() {
    Vertex vertices[] =
    {
      //Position                      //Color                     //Texture coords      // Normals
      glm::vec3(-0.5f, 0.5f, 0.f),    glm::vec3(1.f, 0.f, 0.f),   glm::vec2(0.f, 1.f),  glm::vec3(0.f, 0.f, 1.f),
      glm::vec3(-0.5f, -0.5f, 0.f),   glm::vec3(0.f, 1.f, 0.f),   glm::vec2(0.f, 0.f),  glm::vec3(0.f, 0.f, 1.f),
      glm::vec3(0.5f, -0.5f, 0.f),    glm::vec3(0.f, 0.f, 1.f),   glm::vec2(1.f, 0.f),  glm::vec3(0.f, 0.f, 1.f),
      glm::vec3(0.5f, 0.5f, 0.f),     glm::vec3(1.f, 1.f, 0.f),   glm::vec2(1.f, 1.f),  glm::vec3(0.f, 0.f, 1.f)
    };
    unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

    GLuint indices[] =
    {
      0, 1, 2,  // Triangle 1
      0, 2, 3   // Triangle 2
    };
    unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

    this->set(vertices, nrOfVertices, indices, nrOfIndices);
  }
};

class Pyramid : public Primitive {
public:
	Pyramid() : Primitive() {
		Vertex vertices[] =
		{
			//Position								      //Color							        //Texcoords					    //Normals
			//Triangle front
			glm::vec3(0.f, .5f, 0.f),				glm::vec3(1.f, 0.f, 0.f),		glm::vec2(.5f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-.5f, -.5f, .5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(.5f, -.5f, .5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),

			//Triangle left
			glm::vec3(0.f, .5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),		glm::vec2(.5f, 1.f),		glm::vec3(-1.f, 0.f, 0.f),
			glm::vec3(-.5f, -.5f, -.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f),
			glm::vec3(-.5f, -.5f, .5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f),

			//Triangle back
			glm::vec3(0.f, .5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),		glm::vec2(.5f, 1.f),		glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(.5f, -.5f, -.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(-.5f, -.5f, -.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),

			//Triangles right
			glm::vec3(0.f, .5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),		glm::vec2(.5f, 1.f),		glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(.5f, -.5f, .5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(.5f, -.5f, -.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(1.f, 0.f, 0.f),
		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		this->set(vertices, nrOfVertices, nullptr, 0);
	}
};

#endif
