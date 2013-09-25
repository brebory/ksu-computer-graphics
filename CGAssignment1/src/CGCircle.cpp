/*
 * CGCircle.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: broberto
 */

#include "CGCircle.h"
#include <math.h>

namespace TinyCGLib {

CGCircle::CGCircle() :_radius(0) {
	// TODO Auto-generated constructor stub

}

CGCircle::CGCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLfloat r, GLfloat g, GLfloat b) {
	_position[0] = x;
	_position[1] = y;
	_position[2] = z;
	_color[0] = r;
	_color[1] = g;
	_color[2] = b;
	_radius = radius;
}

CGCircle::~CGCircle() {
	// TODO Auto-generated destructor stub
}

void CGCircle::setRadius(GLfloat radius) {
	_radius = radius;
}

void CGCircle::drawSelf() {
	const float DEG2RAD = 3.14159/180;

	glBegin(GL_LINE_LOOP);
		glColor3d(_color[0], _color[1], _color[2]);
		for (int i = 0; i < 360; i++) {
			float degInRad = i * DEG2RAD;
			glVertex2f(_position[0] + cos(degInRad) * _radius, _position[1] + sin(degInRad) * _radius);
		}
	glEnd();
}

} /* namespace TinyCGLib */
