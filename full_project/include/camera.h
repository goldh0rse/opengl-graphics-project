#ifndef CAMERA_H_
#define CAMERA_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

enum direction {FORWARD = 0, BACKWARD, LEFT, RIGHT, UP, DOWN};

class Camera {
public:
  // Constructors & Destructor
  Camera(void);
  ~Camera(void);

  void updateCamera();
  void moveCamera();

private:
  // Attributes
  glm::mat4 ViewMatrix;
  glm::vec3 camPosition;
  glm::vec3 camFace;
  glm::vec3 camUp;
  glm::vec3 camRight;

  glm::vec3 worldUp;


};

#endif
