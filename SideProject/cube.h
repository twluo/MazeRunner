#ifndef _CUBE_H_
#define _CUBE_H_

#include "geode.h"

class Cube : public Geode {
public:
	Cube();
	Cube(double);
	void render();
	void setMatrix(Matrix4);
};

#endif