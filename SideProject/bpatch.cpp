#include "bpatch.h"
#include <iostream>
// Based on Rex Tutorial

bpatch::bpatch()
{
}


bpatch::~bpatch()
{
}


double bpatch::bCoef(double n, double i, double t)
{
	//double n: is the degree of our curve, in the case of a cubic curve it is 3
	//double i: the index of the Bernstein coefficient and the control point
	//double t: is the time we are evaluating at

	//Calculate the Bernstein coefficient
	return combo(n, i) * pow(1.0 - t, n - i) * pow(t, i);
}

double bpatch::combo(double n, double i)
{
	//C(n, i) = n! / ((n-1)! * i!)
	return factorial(n) / (factorial(n - i) * factorial(i));
}

double bpatch::factorial(double n)
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


Matrix4 bpatch::setMatrix(int a, int b, int c, int d){
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

Matrix4 bpatch::setMatrix(Vector4 p0, Vector4 p1, Vector4 p2, Vector4 p3) {
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
Vector4 bpatch::evalBCurve(Matrix4 Mp, double t) {
	//Create a vector with our Bernstein coefficients
		Vector4 C(bCoef(3, 0, t),
		bCoef(3, 1, t),
		bCoef(3, 2, t),
		bCoef(3, 3, t));

	//Calculate the final point q
	Vector4 q = Mp * C;

	//And make sure q is a point by setting its w-component to 1
	q.setValue(3, 1.0);
	return q;
}

void bpatch::evalBPatch() {
	double v = 0;
	double w = 0;
	double delta = 0.01;
	double nDelta = 1;
	Vector4 q0;
	Vector4 q1;
	Vector4 q2;
	Vector4 q3;
	Vector4 p0;
	Vector4 p1;
	Vector4 p2;
	Vector4 p3;
	Vector4 tanp;
	Vector4 tanq;
	Matrix4 pm0 = setMatrix(0, 1, 2, 3);
	Matrix4 pm1 = setMatrix(4, 5, 6, 7);
	Matrix4 pm2 = setMatrix(8, 9, 10, 11);
	Matrix4 pm3 = setMatrix(12, 13, 14, 15);
	Matrix4 pm;
	Matrix4 qm;
	for (int i = 0; i < 100; i++) {
		q0 = evalBCurve(pm0, v);
		q1 = evalBCurve(pm1, v);
		q2 = evalBCurve(pm2, v);
		q3 = evalBCurve(pm3, v);
		p0 = evalBCurve(pm0, v+nDelta);
		p1 = evalBCurve(pm1, v+nDelta);
		p2 = evalBCurve(pm2, v+nDelta);
		p3 = evalBCurve(pm3, v+nDelta);
		w = 0;
		for (int j = 0; j < 100; j++) {
			qm = setMatrix(q0, q1, q2, q3);
			pm = setMatrix(p0, p1, p2, p3);
			vertices[i][j] = evalBCurve(qm , w);
			tanp = evalBCurve(qm, w + nDelta);
			//std::cout << w << "AS" << w + nDelta << std::endl;
			//tanp.print("ASD");
			//vertices[i][j].print("HOHO");
			//std::cout << tanp.get(2) << std::endl;
			tanp = tanp - vertices[i][j];
			//tanp.print("RESLTU");
			tanq = evalBCurve(pm, w) - vertices[i][j];
			//tanq.print("AS");
			tanp.normalize();
			tanq.normalize();
			normals[i][j] = tanp.cross(tanq,tanp);
		//	normals[i][j].print("AS");
			w = w + delta;
		}
		v = v + delta;
	}
}
void bpatch::draw(){
	Vector4 q0;
	Vector4 q1;
	Vector4 q2;
	Vector4 q3;
	Vector4 n0;
	Vector4 n1;
	Vector4 n2;
	Vector4 n3;
	glBegin(GL_QUADS);
	for (int i = 0; i < 99; i++) {
		glNormal3d(0, 1, 0);
		for (int j = 0; j < 99; j++) {
			q0 = vertices[i][j];
			q1 = vertices[i][j + 1];
			q2 = vertices[i + 1][j + 1];
			q3 = vertices[i + 1][j]; 
			n0 = normals[i][j];
			n1 = normals[i][j + 1];
			n2 = normals[i + 1][j + 1];
			n3 = normals[i + 1][j];
			glColor3d(n0.get(1), n0.get(0), n0.get(2));
			glNormal3d(n0.get(0), n0.get(1), n0.get(2));
			glVertex3d(q0.get(0), q0.get(1), q0.get(2));
			glColor3d(n1.get(1), n1.get(0), n1.get(2));
			glNormal3d(n1.get(0), n1.get(1), n1.get(2));
			glVertex3d(q1.get(0), q1.get(1), q1.get(2));
			glColor3d(n2.get(1), n2.get(0), n2.get(2));
			glNormal3d(n2.get(0), n2.get(1), n2.get(2));
			glVertex3d(q2.get(0), q2.get(1), q2.get(2));
			glColor3d(n3.get(1), n3.get(0), n3.get(2));
			glNormal3d(n3.get(0), n3.get(1), n3.get(2));
			glVertex3d(q3.get(0), q3.get(1), q3.get(2));
		}
	}
	glEnd();
}

void bpatch::setPoints(Vector4 p0, Vector4 p1, Vector4 p2, Vector4 p3,
	Vector4 p4, Vector4 p5, Vector4 p6, Vector4 p7,
	Vector4 p8, Vector4 p9, Vector4 p10, Vector4 p11,
	Vector4 p12, Vector4 p13, Vector4 p14, Vector4 p15) {
	points[0] = p0;
	points[1] = p1;
	points[2] = p2;
	points[3] = p3;
	points[4] = p4;
	points[5] = p5;
	points[6] = p6;
	points[7] = p7;
	points[8] = p8;
	points[9] = p9;
	points[10] = p10;
	points[11] = p11;
	points[12] = p12;
	points[13] = p13;
	points[14] = p14;
	points[15] = p15;
}

void bpatch::setPoints(Vector4 control[16]) {
	for (int i = 0; i < 16; i++) {
		points[i] = control[i];
	}
}