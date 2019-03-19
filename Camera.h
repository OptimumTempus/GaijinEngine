//#ifndef CAMERA_H
//#define CAMERA_H
//#pragma once
//
//#include<iostream>
//
//#include<gl/glew.h>
//#include<GLFW/glfw3.h>
//
//#include<glm.hpp>
//#include<vec3.hpp>
//#include<mat4x4.hpp>
//#include<gtc/matrix_transform.hpp>
//#include<gtc/type_ptr.hpp>
//#include<gtx/string_cast.hpp>
//#include<vector>
//
//class Object;
//
////extern std::vector<Object> vectorObject;
//
//enum direction { FORWARD = 0, BACKWARD, LEFT, RIGHT, UP, DOWN };
//
//static const float GH_GRAVITY = -9.8f;
//static const float GH_WALK_SPEED = 2.9f;
//static const float GH_WALK_ACCEL = 50.0f;
//
//class Camera
//{
//
//
//private:
//	bool jump;
//	glm::mat4 ViewMatrix;
//
//	GLfloat movementSpeed;
//	GLfloat sensitivity;
//
//	glm::vec3 worldUp;
//	glm::vec3 position;
//	glm::vec3 front;
//	glm::vec3 right;
//	glm::vec3 up;
//
//	GLfloat pitch;
//	GLfloat yaw;
//	GLfloat roll;
//
//	void updateCameraVectors();
//	
//	glm::vec2 collisionElipse = glm::vec2(.75, .5);
//
//
//public:
//	Camera(glm::vec3 position,glm::vec3 direction, glm::vec3 worldUp);
//
//	~Camera();
//
//
//	bool getJump();
//	void changeJump();
//	void setX(double num);
//	void setY(double num);
//	void setZ(double num);
//	const glm::mat4 getViewMatrix();
//	const glm::vec3 getPosition() const;
//	void set(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp);
//	void move(const float& dt, const int direction);
//	void updateMouseInput(const float& dt, const double& offsetX, const double& offsetY,bool inverted);
//	void updateInput(const float& dt, const int direction, const double& offsetX, const double& offsetY);
//	const float getPitch() const;
//	const float getYaw() const;
//	const float getRoll() const;
//	glm::vec3 getFront();
//};
//
//#endif