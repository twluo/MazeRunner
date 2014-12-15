#include "BezierCurve.h"


BezierCurve::BezierCurve()
{
}
double BezierCurve::bCoef(double n, double i, double t)
{
	//double n: is the degree of our curve, in the case of a cubic curve it is 3
	//double i: the index of the Bernstein coefficient and the control point
	//double t: is the time we are evaluating at

	//Calculate the Bernstein coefficient
	return combo(n, i) * pow(1.0 - t, n - i) * pow(t, i);
}

double BezierCurve::combo(double n, double i)
{
	//C(n, i) = n! / ((n-1)! * i!)
	return factorial(n) / (factorial(n - i) * factorial(i));
}

double BezierCurve::factorial(double n)
{
	double result = 1;

	//If n is 0, by definition 0! is equal to 1
	if (n <= 0)
		return result;

	//Calculate the factorial, n * n-1 * n-2 * ... * 1
	for (double i = n; i > 0; --i)
	{
		result *= i;
	}

	return result;
}


Matrix4 BezierCurve::setMatrix(int a, int b, int c, int d){
	//Setting this matrix
	//p0.x, p1.x, p2.x, p3.x,
	//p0.y, p1.y, p2.y, p3.y,
	//p0.z, p1.z, p2.z, p3.z,
	//0.0, 0.0, 0.0, 0.0);
	Matrix4 bc;
	Vector4 p0 = points[a];
	Vector4 p1 = points[b];
	Vector4 p2 = points[c];
	Vector4 p3 = points[d];
	bc.set(0, 0, p0.get(0));
	bc.set(1, 0, p0.get(1));
	bc.set(2, 0, p0.get(2));
	bc.set(3, 0, 0);

	bc.set(0, 1, p1.get(0));
	bc.set(1, 1, p1.get(1));
	bc.set(2, 1, p1.get(2));
	bc.set(3, 1, 0);

	bc.set(0, 2, p2.get(0));
	bc.set(1, 2, p2.get(1));
	bc.set(2, 2, p2.get(2));
	bc.set(3, 2, 0);

	bc.set(0, 3, p3.get(0));
	bc.set(1, 3, p3.get(1));
	bc.set(2, 3, p3.get(2));
	bc.set(3, 3, 0);

	return bc;
}

Matrix4 BezierCurve::setMatrix(Vector4 p0, Vector4 p1, Vector4 p2, Vector4 p3) {
	//Setting this matrix
	//p0.x, p1.x, p2.x, p3.x,
	//p0.y, p1.y, p2.y, p3.y,
	//p0.z, p1.z, p2.z, p3.z,
	//0.0, 0.0, 0.0, 0.0);
	Matrix4 bc;
	bc.set(0, 0, p0.get(0));
	bc.set(1, 0, p0.get(1));
	bc.set(2, 0, p0.get(2));
	bc.set(3, 0, 0);

	bc.set(0, 1, p1.get(0));
	bc.set(1, 1, p1.get(1));
	bc.set(2, 1, p1.get(2));
	bc.set(3, 1, 0);

	bc.set(0, 2, p2.get(0));
	bc.set(1, 2, p2.get(1));
	bc.set(2, 2, p2.get(2));
	bc.set(3, 2, 0);

	bc.set(0, 3, p3.get(0));
	bc.set(1, 3, p3.get(1));
	bc.set(2, 3, p3.get(2));
	bc.set(3, 3, 0);

	return bc;
}
Vector3 BezierCurve::evalBCurve(double t) {
	//Create a vector with our Bernstein coefficients
	Vector4 C(bCoef(3, 0, t),
		bCoef(3, 1, t),
		bCoef(3, 2, t),
		bCoef(3, 3, t));
	Matrix4 Mp = setMatrix(0, 1, 2, 3);
	//Calculate the final point q
	Vector4 q = Mp * C;
	Vector3 temp;
	temp.set(q.get(0), q.get(1), q.get(2));
	return temp;
}

void BezierCurve::setPoints(Vector4 p0, Vector4 p1, Vector4 p2, Vector4 p3) {
	points[0] = p0;
	points[1] = p1;
	points[2] = p2;
	points[3] = p3;
}
