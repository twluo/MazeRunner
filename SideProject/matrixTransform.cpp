#include "matrixTransform.h"


MatrixTransform::MatrixTransform() {
	M.identity();
}

MatrixTransform::MatrixTransform( Matrix4 temp) {
	M = temp;
}

void MatrixTransform::set(Matrix4 temp) {
	M = temp;
}

Matrix4 MatrixTransform::get() {
	return M;
}

void MatrixTransform::draw(Matrix4 temp) {
	Matrix4 C = temp* M;
	double x = 0;
	double y = 0;
	double z = 0;
	double radius = 0;
	int number = 0;
	for (std::list<Node*>::iterator it = children.begin(); it != children.end(); ++it) {
		Node* tempNode = *it;
		number++;
		tempNode->draw(C);
	}
}
