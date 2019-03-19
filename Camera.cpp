//#include "Camera.h"
//
//
//void Camera::updateCameraVectors()
//{
//	this->front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
//	this->front.y = sin(glm::radians(this->pitch));
//	this->front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
//
//	this->front = glm::normalize(this->front);
//	this->right = glm::normalize(glm::cross(this->front, this->worldUp));
//	this->up = glm::normalize(glm::cross(this->right, this->front));
//}
//
//Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp)
//{
//	jump = false;
//	this->ViewMatrix = glm::mat4(1.f);
//
//	this->movementSpeed = 3.f;
//	this->sensitivity = 40.f;
//
//	this->worldUp = worldUp;
//	this->position = position;
//	this->right = glm::vec3(0.f);
//	this->up = worldUp;
//
//	this->pitch = 0.f;
//	this->yaw = -90.f;
//	this->roll = 0.f;
//
//	this->updateCameraVectors();
//}
//
//void Camera::set(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp)
//{
//	
//	this->worldUp = worldUp;
//	this->position = position;
//	this->right = glm::vec3(0.f);
//	this->up = worldUp;
//
//	this->pitch = 0.f;
//	this->yaw = -90.f;
//	this->roll = 0.f;
//
//	this->updateCameraVectors();
//}
//
//Camera::~Camera()
//{
//}
//
//bool Camera::getJump()
//{
//	return jump;
//}
//
//void Camera::changeJump()
//{
//	if (jump == true)
//		jump = false;
//	else
//		jump = true;
//}
//
//void Camera::setX(double num)
//{
//	this->position.x = num;
//}
//
//void Camera::setY(double num)
//{
//	this->position.y = num;
//}
//
//void Camera::setZ(double num)
//{
//	this->position.z = num;
//}
//
//const glm::mat4 Camera::getViewMatrix()
//{
//	this->updateCameraVectors();
//
//	this->ViewMatrix = glm::lookAt(this->position, this->position + this->front, this->up);
//
//	return this->ViewMatrix;
//}
//
//const glm::vec3 Camera::getPosition() const
//{
//	return this->position;
//}
//
//void Camera::move(const float & dt, const int direction)
//{
//
//	//Update position vector
//	switch (direction)
//	{
//	case FORWARD:
//		this->position += this->front * this->movementSpeed * dt;
//		break;
//	case BACKWARD:
//		this->position -= this->front * this->movementSpeed * dt;
//		break;
//	case LEFT:
//		this->position -= this->right * this->movementSpeed * dt;
//		break;
//	case RIGHT:
//		this->position += this->right * this->movementSpeed * dt;
//		break;
//	case UP:
//		this->position.y +=  this->movementSpeed * dt;
//		break;
//	case DOWN:
//		this->position.y -= this->movementSpeed * dt;
//		break;
//	default:
//		break;
//	}
//}
//
//void Camera::updateMouseInput(const float & dt, const double & offsetX, const double & offsetY,bool inverted)
//{
//	if (inverted != true)
//	{
//		this->pitch += static_cast<GLfloat>(offsetY) * this->sensitivity * dt;
//		this->yaw += static_cast<GLfloat>(offsetX) * this->sensitivity * dt;
//	}
//	else
//	{
//		this->pitch -= static_cast<GLfloat>(offsetY) * this->sensitivity * dt;
//		this->yaw += static_cast<GLfloat>(offsetX) * this->sensitivity * dt;
//	}
//
//
//	if (this->pitch > 80.f)
//		this->pitch = 80.f;
//	else if (this->pitch < -80.f)
//		this->pitch = -80.f;
//
//	if (this->yaw > 360.f || this->yaw < -360.f)
//		this->yaw = 0.f;
//}
//
//void Camera::updateInput(const float & dt, const int direction, const double & offsetX, const double & offsetY)
//{
//	this->updateMouseInput(dt, offsetX, offsetY, false);
//}
//
//const float Camera::getPitch() const
//{
//	return pitch;
//}
//
//const float Camera::getYaw() const
//{
//	return yaw;
//}
//
//const float Camera::getRoll() const
//{
//	return roll;
//}
//
//glm::vec3 Camera::getFront()
//{
//	return front;
//}
