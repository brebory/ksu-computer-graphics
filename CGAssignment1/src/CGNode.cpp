/*
 * CGNode.cpp
 *
 *  Created on: Sep 17, 2013
 *      Author: broberto
 */

#include "CGNode.h"

namespace TinyCGLib {

CGNode::CGNode() {
	_position[0] = 0.0f;
	_position[1] = 0.0f;
	_position[2] = 0.0f;
	std::vector<CGNode::ManagedNodePtr> _children;
	_children.reserve(3);
}

CGNode::CGNode(GLfloat x, GLfloat y, GLfloat z) {
	_position[0] = x;
	_position[1] = y;
	_position[2] = z;
	std::vector<CGNode::ManagedNodePtr> _children;
	_children.reserve(3);
}

CGNode::~CGNode() { }

void CGNode::draw() {
	drawChildren();
	drawSelf();
}

void CGNode::drawSelf() {

}

void CGNode::drawChildren() {
	for (std::vector<CGNode::ManagedNodePtr>::size_type idx = 0, len = _children.size(); idx < len; ++idx) {
		_children.at(idx)->draw();
	}
}

} /* namespace TinyCGLib */
