#include "group.h"


Group::Group(){
	M.identity();
}

Group::Group(std::string n) {
	Name = n;
}

Group::Group(std::string n, Node* p) {
	Name = n;
	parent = p;
}
void Group::addChild(Node* temp){
	children.push_back(temp);
}
void Group::deleteChild(Node* temp){
	children.remove(temp);
}
void Group::draw(Matrix4 C, bool shade) {
	Matrix4 tempM = C * M;
	for (std::list<Node*>::iterator it = children.begin(); it != children.end(); ++it) {
		Node* temp = *it;
		temp->draw(tempM, shade);
	}
}

void Group::setMatrix(Matrix4 temp) {
	M = temp;
}