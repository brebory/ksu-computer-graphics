/*
 * CGRectangle.h
 *
 *  Created on: Sep 17, 2013
 *      Author: broberto
 */

#ifndef CGRECTANGLE_H_
#define CGRECTANGLE_H_

#include "CGNode.h"
#include <string>
#include <sstream>

namespace TinyCGLib {

class CGRectangle: public TinyCGLib::CGNode {
public:
	CGRectangle();
	CGRectangle(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);

	void setDimensions(GLfloat, GLfloat);
	std::string getColor() {
		std::ostringstream ss;
		ss << "rgb(";
		ss << _color[0];
		ss << ", ";
		ss << _color[1];
		ss << ", ";
		ss << _color[2];
		ss << ")";
		return ss.str();
	}

	std::string getPosition() {
		std::ostringstream ss;
		ss << "(";
		ss << _position[0];
		ss << ", ";
		ss << _position[1];
		ss << ", ";
		ss << _position[2];
		ss << ")";
		return ss.str();
	}

	std::string getDimensions() {
		std::ostringstream ss;
		ss << "[";
		ss << _width;
		ss << "x";
		ss << _height;
		ss << "]";
		return ss.str();
	}

	virtual ~CGRectangle();

private:
	GLfloat _width;
	GLfloat _height;

	virtual void drawSelf();
};

} /* namespace TinyCGLib */
#endif /* CGRECTANGLE_H_ */
