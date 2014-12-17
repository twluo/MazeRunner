#include "camera.h"
#include "Matrix4.h"
#include "Vector3.h"

Camera::Camera() {
	e = Vector3(0.0, 0.0, 0.0);
	up =  Vector3(0.0, 0.0, 0.0);
	d = Vector3(0.0, 0.0, 0.0);
	world2camera.identity();
}

void Camera::set(Vector3& a, Vector3& b, Vector3& c) {
	e = a;
	d = b;
	up = c;
	movement = Vector3(0, 0, 0);
	Vector3 temp;
	lookAt = d - e;
	forward = d - e;
	forward.normalize();
	temp = forward;
	temp.scale(-1);
	backward = temp;
	right = forward.cross(forward, up);
	right.normalize();
	temp = right;
	temp.scale(-1);
	left = temp;
	upd = right.cross(right, forward);
	upd.normalize();
	temp = upd;
	temp.scale(-1);
	down = temp;
	Vector3 x;
	Vector3 y;
	Vector3 z;
	z = e - d;
	z.normalize();
	x = x.cross(up, z);
	x.normalize();
	y = y.cross(z, x);
	y.normalize();
	for (int i = 0; i < 3; i++) {
		world2camera.set(i, 0, x.get(i));
		world2camera.set(i, 1, y.get(i));
		world2camera.set(i, 2, z.get(i));
	}
	makeInverse();
}

void Camera::update(Vector3& a, Vector3& b, Vector3& c) {
	e = a;
	d = b;
	up = c;
	Vector3 temp;
	lookAt = d - e;
	forward = d - e;
	forward.normalize();
	temp = forward;
	temp.scale(-1);
	backward = temp;
	right = forward.cross(forward, up);
	right.normalize();
	temp = right;
	temp.scale(-1);
	left = temp;
	upd = right.cross(right, forward);
	upd.normalize();
	temp = upd;
	temp.scale(-1);
	down = temp;
	Vector3 x;
	Vector3 y;
	Vector3 z;
	z = e - d;
	z.normalize();
	x = x.cross(up, z);
	x.normalize();
	y = y.cross(z, x);
	y.normalize();
	for (int i = 0; i < 3; i++) {
		world2camera.set(i, 0, x.get(i));
		world2camera.set(i, 1, y.get(i));
		world2camera.set(i, 2, z.get(i));
	}
	makeInverse();
}
void Camera::setMatrix(Matrix4 temp) {
	world2camera = temp;
}
void Camera::makeInverse() {
	Vector3 temp = e;
	temp.negate();
	Matrix4 translation;
	Matrix4 rotation;
	translation.identity();
	rotation.identity();
	translation.makeTranslate(temp.getX(), temp.getY(), temp.getZ());
	for (int i = 0; i < 3; i++) {
		rotation.set(i, 0, world2camera.get(i, 0));
		rotation.set(i, 1, world2camera.get(i, 1));
		rotation.set(i, 2, world2camera.get(i, 2));
	}
	rotation.transpose();
	Inverted = rotation * translation;
}
Matrix4& Camera::getMatrix() {
	return world2camera;
}

Matrix4& Camera::getInverse() {
	return Inverted;
}
void Camera::moveLeft(double c){
	Vector3 temp;
	temp = left;
	temp.scale(c);
	e = e + temp;
	d = d + temp;
	update(e, d, upd);
}
void Camera::moveRight(double c){
	Vector3 temp;
	temp = right;
	temp.scale(c);
	e = e + temp;
	d = d + temp;
	update(e, d, upd);
}
void Camera::moveUp(double c){
	Vector3 temp;
	temp = upd;
	temp.scale(c);
	e = e + temp;
	d = d + temp;
	update(e, d, upd);
}
void Camera::moveDown(double c){
	Vector3 temp;
	temp = down;
	temp.scale(c);
	e = e + temp;
	d = d + temp;
	update(e, d, upd);
}
void Camera::moveForward(double c){
	Vector3 temp;
	temp = forward;
	temp.scale(c);
	e = e + temp;
	d = d + temp;
	update(e, d, upd);
}
void Camera::moveBackward(double c){
	Vector3 temp;
	temp = backward;
	temp.scale(c);
	e = e + temp;
	d = d + temp;
	update(e, d, upd);
}

void Camera::rotateY(double c) {
	Matrix4 m;
	Vector4 s;
	s.set(lookAt.getX(), lookAt.getY(), lookAt.getZ(), 0);
	m.makeRotate(c,upd);
	s = m * s;
	lookAt.set(s.get(0), s.get(1), s.get(2));
	d = e + lookAt;
	update(e, d, upd);
}
void Camera::rotateX(double c){
	Matrix4 m;
	Vector4 s;
	s.set(lookAt.getX(), lookAt.getY(), lookAt.getZ(), 0);
	m.makeRotate(c,right);
	s = m * s;
	lookAt.set(s.get(0), s.get(1), s.get(2));
	d = e + lookAt;
	update(e, d, upd);
}

void Camera::rotateDirectionY(double c) {
	Matrix4 m;
	Matrix4 rot;
	Vector4 s;
	s.set(d.getX(), d.getY(), d.getZ(), 1);
	rot.makeRotate(c, upd);
	movement.print("ASD");
	m.makeTranslate(-movement.getX(), -movement.getY(), -movement.getZ());
	rot = rot * m;
	m.makeTranslate(movement.getX(), movement.getY(), movement.getZ());
	rot = m * rot;
	s = rot * s;
	d.set(s.get(0), s.get(1), s.get(2));
	s.set(e.getX(), e.getY(), e.getZ(), 1);
	s = rot * s;
	e.set(s.get(0), s.get(1), s.get(2));
	update(e, d, upd);
}

void Camera::rotate(Vector3 direction, double c) {
	Matrix4 m;
	Vector4 s;
	s.set(lookAt.getX(), lookAt.getY(), lookAt.getZ(), 0);
	m.makeRotate(c, direction);
	s = m * s;
	lookAt.set(s.get(0), s.get(1), s.get(2));
	d = e + lookAt;
	update(e, d, upd);
}

void Camera::move(Vector3 direction, double c) {
	Vector3 temp;
	temp = direction;
	temp.scale(c);
	e = e + temp;
	d = d + temp;
	movement = movement + temp;
	update(e, d, upd);
}