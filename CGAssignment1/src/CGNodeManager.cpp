/*
 * CGNodeManager.cpp
 *
 *  Created on: Sep 17, 2013
 *      Author: broberto
 */

#include "CGNodeManager.h"

namespace TinyCGLib {

CGNodeManager::CGNodeManager() {
	// TODO Auto-generated constructor stub

}

CGNodeManager::~CGNodeManager() {
	// TODO Auto-generated destructor stub
}

void CGNodeManager::drawNodes() {
	_rootNode.draw();
}

} /* namespace TinyCGLib */
