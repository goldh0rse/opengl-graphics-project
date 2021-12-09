#ifndef CAMERA_H_
#define CAMERA_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

enum direction { FORWARD = 0, BACKWARD, LEFT, RIGHT, UP, DOWN };
const float pi_f = 3.1415926f;

class Camera {
public:
  // Constructors & Destructor
  Camera(glm::vec3 startPos, glm::vec3 worldUp, glm::vec3 startFace);
  ~Camera(void){};

  // Functions
  void updateCameraFacing(GLfloat offsetX, GLfloat offsetY);
  void moveCamera(const int direction);
  inline glm::mat4 getViewMatrix(void) { return this->ViewMatrix; }
  inline glm::vec3 getCamPosition(void) { return this->camPosition; }
  void updateViewMatrix(void);

private:
  // Functions

  // Attributes
  glm::mat4 ViewMatrix;
  const glm::vec3 startPos;
  const glm::vec3 worldUp;
  const glm::vec3 startFace;
  glm::vec3 camPosition;
  glm::vec3 camFace;
  glm::vec3 camUp;
  glm::vec3 camRight;

  GLfloat pitch;
  GLfloat yaw;
  GLfloat camSensitivity;
  GLfloat camSpeed;

  float fov;
  float nearPlane; // Due to where we want clipping to be
  float farPlane; // Test on itchy, if slow dump to 100.f
  float top;
  float obliqueScale;
  float obliqueAngleRad;
};

#endif
