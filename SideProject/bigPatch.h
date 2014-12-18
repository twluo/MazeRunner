#ifndef _BIGPATCH_H_
#define _BIGPATCH_H_

#include "bpatch.h"
class bigPatch
{
private:
	Vector4 controlPoints[49];
	Vector4 animatedPoints[49];
	void setPoints();
	void setAnimatedPoints();
	bpatch a;
	bpatch b;
	bpatch c;
	bpatch d;
	double t;
public:
	void definePoints(Vector4[]);
	void draw();
	void animate();
	bigPatch();
	~bigPatch();
};

#endif