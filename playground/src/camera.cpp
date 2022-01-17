/* Camera.cpp
 *
 * @description - Definitions for the camera class methods.
 * @author      - Klas Holmberg
 * @email       - hed16khg@cs.umu.se
 * @date        - 2022-01-13
 */
#include "camera.h"

Camera::Camera(glm::vec3 startPos, glm::vec3 worldUp, glm::vec3 startFace)
  :  startPos(startPos), worldUp(worldUp), startFace(startFace){

  this->camPosition = this->startPos;
  this->camFace = this->startFace;
  this->camRight = glm::vec3(0.f);
  this->camRight = glm::normalize(glm::cross(this->camFace, this->worldUp));
  this->camUp = glm::normalize(glm::cross(this->camRight, this->camFace));

  this->pitch = 0.f;
  this->yaw = -90.f;
}


void Camera::moveCamera(const int direction){
  //Update position coordinate
	switch (direction){
  	case FORWARD:
  		this->camPosition += this->camFace * this->camSpeed;
  		break;
  	case BACKWARD:
  		this->camPosition -= this->camFace * this->camSpeed;
  		break;
  	case LEFT:
  		this->camPosition -= this->camRight * this->camSpeed;
  		break;
  	case RIGHT:
  		this->camPosition += this->camRight * this->camSpeed;
  		break;
    case UP:
      this->camPosition += this->camUp * this->camSpeed;
      break;
    case DOWN:
      this->camPosition -= this->camUp * this->camSpeed;
      break;
  	default:
      // Well this is dumb, throw error maybe?
  		break;
	}
}

void Camera::updateCameraFacing(GLfloat offsetX, GLfloat offsetY){
  this->pitch += static_cast<GLfloat>(offsetY) * this->camSens;
  this->yaw += static_cast<GLfloat>(offsetX) * this->camSens;

  /* Prevent Gimbal lock */
  if (this->pitch > 80.f){
    this->pitch = 80.f;
  }	else if (this->pitch < -80.f){
    this->pitch = -80.f;
  }

  if (this->yaw > 360.f || this->yaw < -360.f){
      this->yaw = 0.f;
  }

  this->camFace.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
  this->camFace.y = sin(glm::radians(this->pitch));
  this->camFace.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

  this->camFace = glm::normalize(this->camFace);
  this->camRight = glm::normalize(glm::cross(this->camFace, this->worldUp));
  this->camUp = glm::normalize(glm::cross(this->camRight, this->camFace));

  this->updateViewMatrix();
}

void Camera::updateViewMatrix(void){
  this->ViewMatrix = glm::lookAt(
    this->camPosition,
    this->camPosition + this->camFace,
    this->camUp
  );
}
