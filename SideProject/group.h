#ifndef _GROUP_H_
#define _GROUP_H_

#include "node.h"

class Group : public Node {
protected:
	std::list <Node*> children;
	Matrix4 M;
public:
	Group();
	Group(std::string);
	Group(std::string, Node*);
	void addChild(Node*);
	void deleteChild(Node*);
	void setMatrix(Matrix4 m);
	virtual void draw(Matrix4 C, bool);
};

#endif