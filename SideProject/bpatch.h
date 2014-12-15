#ifndef _BPATCH_H_
#define _BPATCH_H_
#include "window.h"
class bpatch
{
private:
	double bCoef(double n, double i, double t);
	double combo(double n, double i);
	double factorial(double n);
	Vector4 vertices[100][100];
	Vector4 normals[100][100];
	Vector4 points[16];
	Matrix4 setMatrix(int, int, int, int);
	Matrix4 setMatrix(Vector4, Vector4, Vector4, Vector4);
	Vector4 evalBCurve(Matrix4,double);

public:
	void setPoints(Vector4, Vector4, Vector4, Vector4,
		Vector4, Vector4, Vector4, Vector4,
		Vector4, Vector4, Vector4, Vector4,
		Vector4, Vector4, Vector4, Vector4);
	void draw();
	void evalBPatch();
	bpatch();
	~bpatch();
};

#endif
