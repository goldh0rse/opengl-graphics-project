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
  Camera(glm::vec3 position, glm::vec3 worldUp, glm::vec3 facing);
  ~Camera(void);

  // Functions
  void moveCamera(glm::vec3 position, glm::vec3 facing);
  glm::mat4 getViewMatrix(void);
  glm::vec3 getPosition(void) const;
  void move(const float& dt, const int direction);
  void updateMouseInput(const float& dt, const double& offsetX, const double& offsetY);
  void updateInput(const float& dt, const int direction, const double& offsetX, const double& offsetY);

private:
  // Attributes
  glm::mat4 ViewMatrix;
  glm::vec3 position;
  glm::vec3 worldUp;
  glm::vec3 facing;
  glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;

  GLfloat movementSpeed;
  GLfloat sensitivity;

	GLfloat pitch;
	GLfloat yaw;
	GLfloat roll;

  // Functions
  void updateCamera(void);

};

#endif
