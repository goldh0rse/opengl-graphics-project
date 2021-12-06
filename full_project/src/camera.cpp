#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 worldUp, glm::vec3 facing){
  this->ViewMatrix = glm::mat4(1.f);

	this->movementSpeed = 3.f;
	this->sensitivity = 5.f;

	this->worldUp = worldUp;
	this->position = position;
  this->facing = facing;
	this->right = glm::vec3(0.f);
	this->up = worldUp;

	this->pitch = 0.f;
	this->yaw = -90.f;
	this->roll = 0.f;

	// this->updateCamera();
}

Camera::~Camera(void){}

void Camera::updateCamera(void){
  this->facing.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->facing.y = sin(glm::radians(this->pitch));
	this->facing.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

	this->facing = glm::normalize(this->facing);
	this->right = glm::normalize(glm::cross(this->facing, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->facing));
}

glm::mat4 Camera::getViewMatrix(void){
	// this->updateCamera();

	this->ViewMatrix = glm::lookAt(this->position, this->position + this->front, this->up);

	return this->ViewMatrix;
}


glm::vec3 Camera::getPosition(void) const {
	return this->position;
}

void Camera::move(const float& dt, const int direction){
	//Update position vector
	switch (direction){
	case FORWARD:
		this->position += this->facing * this->movementSpeed * dt;
		break;
	case BACKWARD:
		this->position -= this->facing * this->movementSpeed * dt;
		break;
	case LEFT:
		this->position -= this->right * this->movementSpeed * dt;
		break;
	case RIGHT:
		this->position += this->right * this->movementSpeed * dt;
		break;
	default:
		break;
	}
}

void Camera::updateMouseInput(const float& dt, const double& offsetX, const double& offsetY){
	//Update pitch yaw and roll
	this->pitch += static_cast<GLfloat>(offsetY) * this->sensitivity * dt;
	this->yaw += static_cast<GLfloat>(offsetX) * this->sensitivity * dt;

	if (this->pitch > 80.f){
    this->pitch = 80.f;

  }	else if (this->pitch < -80.f){
    this->pitch = -80.f;
  }

	if (this->yaw > 360.f || this->yaw < -360.f){
			this->yaw = 0.f;
  }
}

void Camera::updateInput(const float& dt, const int direction, const double& offsetX, const double& offsetY){
	this->updateMouseInput(dt, offsetX, offsetY);
}
