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
	_velocity[0] = 0.0f;
	_velocity[1] = 0.0f;
	_velocity[2] = 0.0f;
	_color[0] = 0.0f;
	_color[1] = 0.0f;
	_color[2] = 0.0f;
	std::vector<CGNode::ManagedCGNodePtr> _children;
	_children.reserve(3);
	_parent = 0;
	_moving = false;
}

CGNode::CGNode(GLfloat x, GLfloat y, GLfloat z) {
	_position[0] = x;
	_position[1] = y;
	_position[2] = z;
	_velocity[0] = 0.0f;
	_velocity[1] = 0.0f;
	_velocity[2] = 0.0f;
	_color[0] = 0.0f;
	_color[1] = 0.0f;
	_color[2] = 0.0f;
	std::vector<CGNode::ManagedCGNodePtr> _children;
	_children.reserve(3);
	_parent = 0;
	_moving = false;
}

CGNode::CGNode(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b) {
	_position[0] = x;
	_position[1] = y;
	_position[2] = z;
	_velocity[0] = 0.0f;
	_velocity[1] = 0.0f;
	_velocity[2] = 0.0f;
	_color[0] = r;
	_color[1] = g;
	_color[2] = b;
	std::vector<CGNode::ManagedCGNodePtr> _children;
	_children.reserve(3);
	_parent = 0;
	_moving = false;
}

CGNode::~CGNode() { }

void CGNode::draw() {
	// A CGNode is only drawn in full when it itself is drawn as well as it's children
	drawChildren();
	drawSelf();
}

void CGNode::update() {
	updateSelf();
	updateChildren();
}

void CGNode::updateSelf() {
	if (_moving) {
		_position[0] += _velocity[0];
		_position[1] += _velocity[1];
		_position[2] += _velocity[2];
	}

}

void CGNode::addChild(ManagedCGNodePtr child) {
	_children.push_back(child);
	child->_parent = this;
}

void CGNode::drawChildren() {
	for (std::vector<CGNode::ManagedCGNodePtr>::size_type idx = 0, len = _children.size(); idx < len; ++idx) {
		_children.at(idx)->draw();
	}
}

void CGNode::updateChildren() {
	for (std::vector<CGNode::ManagedCGNodePtr>::size_type idx = 0, len = _children.size(); idx < len; ++idx) {
		_children.at(idx)->update();
	}
}

void CGNode::setColor(GLfloat r, GLfloat g, GLfloat b) {
	_color[0] = r;
	_color[1] = g;
	_color[2] = b;
}

void CGNode::setPosition(GLfloat x, GLfloat y, GLfloat z) {
	_position[0] = x;
	_position[1] = y;
	_position[2] = z;
}

void CGNode::setVelocity(GLfloat x, GLfloat y, GLfloat z) {
	_velocity[0] = x;
	_velocity[1] = y;
	_velocity[2] = z;
	_moving = true;
}

} /* namespace TinyCGLib */
