/*
 * GLEntityManager.h
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
public:
	CGNodeManager();
	virtual ~CGNodeManager();

	void drawNodes();

private:
	CGNode _rootNode;
};

} /* namespace TinyCGLib */
#endif /* CGNODEMANAGER_H_ */
