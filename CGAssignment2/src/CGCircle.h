/*
 * CGCircle.h
 *
 *  Created on: Sep 25, 2013
 *      Author: broberto
 */

#ifndef CGCIRCLE_H_
#define CGCIRCLE_H_

#include "CGNode.h"

namespace TinyCGLib {

class CGCircle: public TinyCGLib::CGNode {
public:
	CGCircle();
	CGCircle(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);

	void setRadius(GLfloat);

	virtual ~CGCircle();

private:
	GLfloat _radius;

	virtual void drawSelf();

};
} /* namespace TinyCGLib */
#endif /* CGCIRCLE_H_ */
