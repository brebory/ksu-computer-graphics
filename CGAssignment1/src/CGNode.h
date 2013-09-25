/*
 * CGNode.h
 *
 *  Created on: Sep 17, 2013
 *      Author: broberto
 */

#ifndef CGNODE_H_
#define CGNODE_H_

#include <GL/glut.h>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace TinyCGLib {

class CGNode {
public:
	typedef boost::shared_ptr<CGNode> ManagedCGNodePtr;
	friend class CGNodeManager;

	CGNode();
	CGNode(GLfloat, GLfloat, GLfloat);
	CGNode(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
	CGNode(const CGNode&);

	virtual ~CGNode();

	void draw();

	void update();

	void addChild(ManagedCGNodePtr);

	void setColor(GLfloat, GLfloat, GLfloat);
	void setPosition(GLfloat, GLfloat, GLfloat);
	void setVelocity(GLfloat, GLfloat, GLfloat);


protected:
	GLfloat _position[3];
	GLfloat _velocity[3];
	GLfloat _color[3];
	std::vector<ManagedCGNodePtr> _children;
	CGNode *_parent;

private:
	// Must be implemented by derived class
	virtual void drawSelf() = 0;
	virtual void drawChildren();

	virtual void updateSelf();
	virtual void updateChildren();

};

} /* namespace TinyCGLib */
#endif /* CGNODE_H_ */
