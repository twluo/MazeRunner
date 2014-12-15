#ifndef _MATRIXTRANSFORM_H_
#define _MATRIXTRANSFORM_H_

#include "group.h"

class MatrixTransform : public Group {
protected:
	Matrix4 M;
public:
	MatrixTransform();
	MatrixTransform(Matrix4);
	virtual void draw(Matrix4 C);
	void set(Matrix4);
	Matrix4 get();
};

#endif