/*
 * CGRectangle.cpp
 *
 *  Created on: Sep 17, 2013
 *      Author: broberto
 */

#include <GL/glut.h>
#include "CGRectangle.h"
#include <iostream>

namespace TinyCGLib {

CGRectangle::CGRectangle()
	:_width(0), _height(0) { }

CGRectangle::CGRectangle(GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, GLfloat r, GLfloat g, GLfloat b)
	:CGNode(x, y, z, r, g, b), _width(width), _height(height) { }

CGRectangle::~CGRectangle() {
	// TODO Auto-generated destructor stub
}

void CGRectangle::setDimensions(GLfloat width, GLfloat height) {
	_width = width;
	_height = height;
}

void CGRectangle::drawSelf() {
	glBegin(GL_POLYGON);
		glColor3d(_color[0], _color[1], _color[2]);
		glVertex3f(_position[0] - _width/2, _position[1] - _height/2, _position[2]);
		glVertex3f(_position[0] + _width/2, _position[1] - _height/2, _position[2]);
		glVertex3f(_position[0] + _width/2, _position[1] + _height/2, _position[2]);
		glVertex3f(_position[0] - _width/2, _position[1] + _height/2, _position[2]);
	glEnd();
}

} /* namespace TinyCGLib */
