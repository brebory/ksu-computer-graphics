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
	CGNode(const CGNode&);

	virtual ~CGNode();

	void draw();

private:
	GLfloat _position[3];
	std::vector<ManagedCGNodePtr> _children;
	ManagedCGNodePtr _parent;

	virtual void drawSelf();
	virtual void drawChildren();

};

} /* namespace TinyCGLib */
#endif /* CGNODE_H_ */
