#ifndef _BEZIERCURVE_H_
#define _BEZIERCURVE_H_
#include "window.h"
class BezierCurve
{
private:
	double bCoef(double n, double i, double t);
	double combo(double n, double i);
	double factorial(double n);
	Vector4 points[4];
	Matrix4 setMatrix(int, int, int, int);
	Matrix4 setMatrix(Vector4, Vector4, Vector4, Vector4);

public:
	void setPoints(Vector4, Vector4, Vector4, Vector4);
	Vector3 evalBCurve(double);
	BezierCurve();
};

#endif
