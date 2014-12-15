#include "cube.h"


Cube::Cube() {

}
Cube::Cube(double s) {
	center.set(0, 0, 0, 1);
	scale.set(s*0.5, s*0.5, s*0.5,0);
	size = s;
	m.identity();
}
void Cube::render() {
	double i = size / 2;
	glEnable(GL_TEXTURE_2D);
	// Make sure no bytes are padded:
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Select GL_MODULATE to mix texture with polygon color for shading:
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Use bilinear interpolation:
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3d(1, 1, 1);

	glBindTexture(GL_TEXTURE_2D, texture[2]);

	glBegin(GL_QUADS);
	glNormal3d(0, 0, 1);
	glTexCoord2d(0, 0);
	glVertex3d(-i, -i, i);
	glTexCoord2d(1, 0);
	glVertex3d(i, -i, i);
	glTexCoord2d(1, 1);
	glVertex3d(i, i, i);
	glTexCoord2d(0, 1);
	glVertex3d(-i, i, i);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[3]);

	glBegin(GL_QUADS);
	glNormal3d(1, 0, 0);
	glTexCoord2d(0, 0);
	glVertex3d(-i, -i, -i);
	glTexCoord2d(1, 0);
	glVertex3d(-i, -i, i);
	glTexCoord2d(1, 1);
	glVertex3d(-i, i, i);
	glTexCoord2d(0, 1);
	glVertex3d(-i, i, -i);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glBegin(GL_QUADS);
	glNormal3d(0, 0, -1);
	glTexCoord2d(0, 0);
	glVertex3d(i, -i, -i);
	glTexCoord2d(1, 0);
	glVertex3d(-i, -i, -i);
	glTexCoord2d(1, 1);
	glVertex3d(-i, i, -i);
	glTexCoord2d(0, 1);
	glVertex3d(i, i, -i);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[1]);

	glBegin(GL_QUADS);
	glNormal3d(-1, 0, 0);
	glTexCoord2d(0, 0);
	glVertex3d(i, -i, i);
	glTexCoord2d(1, 0);
	glVertex3d(i, -i, -i);
	glTexCoord2d(1, 1);
	glVertex3d(i, i, -i);
	glTexCoord2d(0, 1);
	glVertex3d(i, i, i);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[4]);

	glBegin(GL_QUADS);
	glNormal3d(0, 1, 0);
	glTexCoord2d(0, 0);
	glVertex3d(-i, i, i);
	glTexCoord2d(1, 0);
	glVertex3d(i, i, i);
	glTexCoord2d(1, 1);
	glVertex3d(i, i, -i);
	glTexCoord2d(0, 1);
	glVertex3d(-i, i, -i);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[5]);

	glBegin(GL_QUADS);
	glNormal3d(0, -1, 0);
	glTexCoord2d(0, 0);
	glVertex3d(-i, -i, i);
	glTexCoord2d(1, 0);
	glVertex3d(i, -i, i);
	glTexCoord2d(1, 1);
	glVertex3d(i, -i, -i);
	glTexCoord2d(0, 1);
	glVertex3d(-i, -i, -i);
	glEnd();

	//glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);
}

void Cube::setMatrix(Matrix4 temp) {
	m = temp;
}
