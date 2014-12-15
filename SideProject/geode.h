#ifndef _GEODE_H_
#define _GEODE_H_

#include "node.h"

class Geode : public Node {
protected:
	double size;
	double R, G, B;
	Matrix4 m;
	GLuint texture[6];
public:
	Geode();
	void draw(Matrix4 C);
	virtual void render() = 0;
	void setColor(double, double, double);
	void setTexture(GLuint tex[6]);
	virtual void setMatrix(Matrix4) = 0;
	Matrix4 getMatrix();
};

#endif