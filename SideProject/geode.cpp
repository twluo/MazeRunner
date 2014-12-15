#include "geode.h"

Geode::Geode() {
}

void Geode::draw(Matrix4 C){
	Matrix4 Ctemp = C * m;
	Vector4 tempcenter = Ctemp * center;
	Vector4 tempscale = Ctemp * scale;
	glMatrixMode(GL_MODELVIEW);
	Matrix4 glmatrix; 
	glColor3d(R, G, B);
	glmatrix = Ctemp;
	glmatrix.transpose();
	glLoadMatrixd(glmatrix.getPointer());
	render();
}

void Geode::setColor(double r, double g, double b) {
	R = r;
	G = g;
	B = b;
}

void Geode::setTexture(GLuint tex[6]) {
	for (int i = 0; i < 6; i++) {
		texture[i] = tex[i];
	}
}
Matrix4 Geode::getMatrix() {
	return m;
}