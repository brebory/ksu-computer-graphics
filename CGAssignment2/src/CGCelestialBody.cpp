/*
 * CGCelestialBody.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: broberto
 */

#include "CGCelestialBody.h"

#include <cmath>
#include <math.h>

namespace TinyCGLib {

CGCelestialBody::CGCelestialBody() : CGNode(), _axisRadius(0), _axisRotation(0), _orbitRadius(0), _orbitRotation(0), _axisSpeed(0), _orbitSpeed(0), _wireframe(true) { }

CGCelestialBody::CGCelestialBody(GLfloat axisRadius, GLfloat axisSpeed, GLfloat orbitRadius, GLfloat orbitSpeed)
	:CGNode(), _axisRadius(axisRadius), _axisRotation(0), _orbitRadius(orbitRadius), _orbitRotation(0),
	 _axisSpeed(axisSpeed), _orbitSpeed(orbitSpeed), _wireframe(true) { }

CGCelestialBody::CGCelestialBody(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat axisRadius, GLfloat axisSpeed, GLfloat orbitRadius, GLfloat orbitSpeed)
	:CGNode(x, y, z, r, g, b), _axisRadius(axisRadius), _axisRotation(0), _orbitRadius(orbitRadius), _orbitRotation(0),
	 _axisSpeed(axisSpeed), _orbitSpeed(orbitSpeed), _wireframe(true) { }

CGCelestialBody::~CGCelestialBody() {
	// TODO Auto-generated destructor stub
}

void CGCelestialBody::drawSelf() {
	// Rotate on orbit axis and translate
	glColor3d(_color[0], _color[1], _color[2]);
	glRotatef(_orbitRotation, 0.0, 1.0, 0.0);
	glTranslatef(_orbitRadius, 0.0, 0.0);
	// Push a matrix so that self rotation on axis doesn't change child positioning
	glPushMatrix();
	glRotatef(_axisRotation, 0.0, 1.0, 0.0);
	if (_wireframe) {
		glutWireSphere(_axisRadius, 12, 12);
	} else {
		glutSolidSphere(_axisRadius, 12, 12);
	}
	glPopMatrix();
}

void CGCelestialBody::updateSelf() {
	_axisRotation = _axisRotation + _axisSpeed;
	_orbitRotation = _orbitRotation + _orbitSpeed;
}

void CGCelestialBody::toggleWireframe() {
	_wireframe = !_wireframe;
}

bool CGCelestialBody::isWireframe() {
	return _wireframe;
}

void CGCelestialBody::increaseSpeed() {
	_orbitSpeed = _orbitSpeed * 2.0;
	_axisSpeed = _axisSpeed * 2.0;
}

void CGCelestialBody::decreaseSpeed() {
	_orbitSpeed = _orbitSpeed * 0.5;
	_axisSpeed = _axisSpeed * 0.5;
}

} /* namespace TinyCGLib */
