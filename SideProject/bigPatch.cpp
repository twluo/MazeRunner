#include "bigPatch.h"


bigPatch::bigPatch()
{
	t = 0;
}


bigPatch::~bigPatch()
{
}
void bigPatch::setPoints(){
	Vector4 temp[16];
	int index = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int k = i * 7 + j;
			temp[index] = controlPoints[k];
			index++;
		}
	}
	a.setPoints(temp);
	a.evalBPatch();
	index = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 3; j < 7; j++) {
			int k = i * 7 + j;
			temp[index] = controlPoints[k];
			index++;
		}
	}
	b.setPoints(temp);
	b.evalBPatch();
	index = 0;
	for (int i = 3; i < 7; i++) {
		for (int j = 0; j < 4; j++) {
			int k = i * 7 + j;
			temp[index] = controlPoints[k];
			index++;
		}
	}
	c.setPoints(temp);
	c.evalBPatch();
	index = 0;
	for (int i = 3; i < 7; i++) {
		for (int j = 3; j < 7; j++) {
			int k = i * 7 + j;
			temp[index] = controlPoints[k];
			index++;
		}
	}
	d.setPoints(temp);
	d.evalBPatch();
}

void bigPatch::setAnimatedPoints() {
	Vector4 temp[16];
	int index = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int k = i * 7 + j;
			temp[index] = animatedPoints[k];
			index++;
		}
	}
	a.setPoints(temp);
	a.evalBPatch();
	index = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 3; j < 7; j++) {
			int k = i * 7 + j;
			temp[index] = animatedPoints[k];
			index++;
		}
	}
	b.setPoints(temp);
	b.evalBPatch();
	index = 0;
	for (int i = 3; i < 7; i++) {
		for (int j = 0; j < 4; j++) {
			int k = i * 7 + j;
			temp[index] = animatedPoints[k];
			index++;
		}
	}
	c.setPoints(temp);
	c.evalBPatch();
	index = 0;
	for (int i = 3; i < 7; i++) {
		for (int j = 3; j < 7; j++) {
			int k = i * 7 + j;
			temp[index] = animatedPoints[k];
			index++;
		}
	}
	d.setPoints(temp);
	d.evalBPatch();
}
void bigPatch::definePoints(Vector4 points[49]){
	for (int i = 0; i < 49; i++) {
		controlPoints[i] = points[i];
	}
	setPoints();
}
void bigPatch::draw() {
	glColor3d(1, 0, 1);
	a.draw();
	glColor3d(0, 1, 0);
	b.draw();
	glColor3d(0, 0, 1);
	c.draw();
	glColor3d(1,1,1);
	d.draw();
}
void bigPatch::animate() {
	Vector4 temp;
	double x;
	double y;
	double z;
	for (int i = 0; i < 49; i++) {
		temp = controlPoints[i];
		x = temp.get(0);
		z = temp.get(2);
		y = temp.get(1);
		y = 1* sin(sqrt((x*x) + (z*z) + t*M_PI / 2)) + y;
		temp.setValue(1, y);
		animatedPoints[i] = temp;
	}
	t++;
	setAnimatedPoints();
}
