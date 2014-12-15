#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Matrix4.h"
#include "Vector3.h"

class Camera
{
protected:
	Matrix4 world2camera;            // model matrix (transforms model coordinates to world coordinates)
	Matrix4 Inverted;


public:
	Camera();   // Constructor
	Matrix4& getMatrix();	
	Vector3 e;
	Vector3 d;
	Vector3 up;
	Vector3 forward;
	Vector3 backward;
	Vector3 right;
	Vector3 left;
	Vector3 upd;
	Vector3 down;
	Vector3 lookAt;
	void moveLeft(double);
	void moveRight(double);
	void moveUp(double);
	void moveDown(double);
	void moveForward(double);
	void moveBackward(double);
	void set(Vector3&, Vector3&, Vector3&);
	Matrix4& getInverse();
	void makeInverse();
	void setMatrix(Matrix4);
	void rotateY(double);
	void rotateX(double);
	void rotate(Vector3, double);
	void move(Vector3, double);
};

#endif

