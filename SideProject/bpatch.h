#ifndef _BPATCH_H_
#define _BPATCH_H_
#include "Vector4.h"
#include "Matrix4.h"
#include <GL/glut.h>
class bpatch
{
private:
	double bCoef(double n, double i, double t);
	double combo(double n, double i);
	double factorial(double n);
	Vector4 vertices[101][101];
	Vector4 normals[101][101];
	Vector4 points[16];
	Matrix4 setMatrix(int, int, int, int);
	Matrix4 setMatrix(Vector4, Vector4, Vector4, Vector4);
	Vector4 evalBCurve(Matrix4,double);
	GLuint tex;

public:
	void setPoints(Vector4, Vector4, Vector4, Vector4,
		Vector4, Vector4, Vector4, Vector4,
		Vector4, Vector4, Vector4, Vector4,
		Vector4, Vector4, Vector4, Vector4);
	void setPoints(Vector4[16]);
	void draw();
	void evalBPatch();
	bpatch();
	~bpatch();
};

#endif
