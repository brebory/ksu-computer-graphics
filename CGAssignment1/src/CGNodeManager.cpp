/*
 * CGNodeManager.cpp
 *
 *  Created on: Sep 17, 2013
 *      Author: broberto
 */

#include "CGNodeManager.h"

namespace TinyCGLib {

CGNodeManager::CGNodeManager()
	:_rootNode() { }

CGNodeManager::CGNodeManager(CGNode *root) {
	_rootNode = root;
}

CGNodeManager::~CGNodeManager() {
}

void CGNodeManager::setRoot(CGNode *newRoot) {
	_rootNode = newRoot;
}

CGNode* CGNodeManager::getRoot() {
	return _rootNode;
}

void CGNodeManager::clear() {

}

void CGNodeManager::drawNodes() {
	_rootNode->draw();
}

void CGNodeManager::updateNodes() {
	_rootNode->update();
}

} /* namespace TinyCGLib */
