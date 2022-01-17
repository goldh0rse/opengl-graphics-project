/* Camera.h - Header file for the Camera class.
 *
 * @author      - Klas Holmberg
 * @email       - hed16khg@cs.umu.se
 * @date        - 2022-01-13
 */

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
  /* CONSTRUCTORS & DECONSTRUCTORS */

  /**
   * Camera [The main constructor of the class]
   * @param startPos   [the starting position in world coordinates]
   * @param worldUp    [the starting world up vector]
   * @param startFace  [the starting faceing vector of the camera]
   */
  Camera(glm::vec3 startPos, glm::vec3 worldUp, glm::vec3 startFace);

  /**
   * ~Camera [Deconstructor of the class]
   */
  ~Camera(void){}; // Not necessary in current version

  /* METHODS */
  /**
   * Camera::updateCameraFacing [updates the camFace attribute]
   * @param offsetX  [The offset value that should be applied to the yaw]
   * @param offsetY  [The offset value that should be applied to the pitch]
   */
  void updateCameraFacing(GLfloat offsetX, GLfloat offsetY);

  /**
   * Camera::moveCamera [Moves the camera in a direction]
   * @param direction  [Defines the direction to move the camera]
   */
  void moveCamera(const int direction);

  /**
   * Camera::updateViewMatrix [recomputes the ViewMatrix from the internal
   *                           camera attributes]
   */
  void updateViewMatrix(void);

  /* INLINE METHODS */
  /**
   * getViewMatrix [getter method for the ViewMatrix]
   * @return  [ViewMatrix attribute]
   */
  inline glm::mat4 getViewMatrix(void) { return this->ViewMatrix; }
  /**
   * getCamPosition [getter method for the camera position]
   * @return  [camPosition attribute]
   */
  inline glm::vec3 getCamPosition(void) { return this->camPosition; }

private:
  /* ATTRIBUTES */
  glm::mat4 ViewMatrix;           // The viewmatrix
  const glm::vec3 startPos;       // The starting position world coord
  const glm::vec3 worldUp;        // The starting world up vector (look at)
  const glm::vec3 startFace;      // The starting facing vector
  glm::vec3 camPosition;          // The current camera position world coord
  glm::vec3 camFace;              // The current camera facing vector (look at)
  glm::vec3 camUp;                // The current camera world up vector
  glm::vec3 camRight;             // The current camera right vector
  GLfloat pitch;                  // The current camera pitch angle
  GLfloat yaw;                    // The current camera yaw angle
  const GLfloat camSens = 0.1f;   // The camera facing multiplier
  const GLfloat camSpeed = 0.05f; // The camera movement multiplier
  float fov;                      // The field of view
  float nearPlane;                // The frustrum nearplane distance
  float farPlane;                 // The frustrum farplane distance
  float top;                      // The frustrum top value
  float obliqueScale;             // The oblique scaler for parallel projection
  float obliqueAngleRad;          // The oblique angle for parallel projection
};

#endif
