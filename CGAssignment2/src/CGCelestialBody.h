/*
 * CGCelestialBody.h
 *
 *  Created on: Oct 29, 2013
 *      Author: broberto
 */

#ifndef CGCELESTIALBODY_H_
#define CGCELESTIALBODY_H_

#include "CGNode.h"

namespace TinyCGLib {

class CGCelestialBody: public TinyCGLib::CGNode {
public:
	CGCelestialBody();
	CGCelestialBody(GLfloat, GLfloat, GLfloat, GLfloat);
	CGCelestialBody(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
	virtual ~CGCelestialBody();

	void drawSelf();

	void updateSelf();

	void toggleWireframe();

	bool isWireframe();

	void increaseSpeed();
	void decreaseSpeed();

private:
	GLfloat _axisRadius;
	GLfloat _axisRotation;
	GLfloat _orbitRotation;
	GLfloat _orbitRadius;
	GLfloat _axisSpeed;
	GLfloat _orbitSpeed;
	bool _wireframe;
};

} /* namespace TinyCGLib */
#endif /* CGCELESTIALBODY_H_ */
