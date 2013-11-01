/*
 *  CGNodeManager.h
 *
 *  Created on: Sep 17, 2013
 *      Author: broberto
 */

#ifndef CGNODEMANAGER_H_
#define CGNODEMANAGER_H_

#include <vector>
#include "CGNode.h"

namespace TinyCGLib {

class CGNodeManager {

	// Class CGNodeManager serves as the entry point for the scene graph
public:
	CGNodeManager();
	CGNodeManager(CGNode*);
	virtual ~CGNodeManager();

	void setRoot(CGNode*);
	CGNode* getRoot();
	void clear();
	void drawNodes();
	void updateNodes();

private:
	CGNode* _rootNode;
};

} /* namespace TinyCGLib */
#endif /* CGNODEMANAGER_H_ */
