/*
 * CGMouseInput.cpp
 *
 *  Created on: Sep 17, 2013
 *      Author: broberto
 */

#include "CGMouseInput.h"

namespace TinyCGLib {

CGMouseInput::CGMouseFunctionPtr CGMouseInput::m_onMouseLeftClick = CGMouseInput::_defaultMouseLeftClickHandler;
CGMouseInput::CGMouseFunctionPtr CGMouseInput::m_onMouseLeftClickRelease = CGMouseInput::_defaultMouseLeftClickReleaseHandler;
CGMouseInput::CGMouseFunctionPtr CGMouseInput::m_onMouseRightClick = CGMouseInput::_defaultMouseRightClickHandler;
CGMouseInput::CGMouseFunctionPtr CGMouseInput::m_onMouseRightClickRelease = CGMouseInput::_defaultMouseRightClickReleaseHandler;
CGMouseInput::CGMouseFunctionPtr CGMouseInput::m_onMouseMove = CGMouseInput::_defaultMouseMoveHandler;
CGMouseInput::CGMouseFunctionPtr CGMouseInput::m_onMouseIdle = CGMouseInput::_defaultMouseIdleHandler;

CGMouseInput::CGMouseInput() {

}

CGMouseInput::~CGMouseInput() {
	// TODO Auto-generated destructor stub
}

void CGMouseInput::initialize() {
	_registerGlutMouseFunctions();
}

void CGMouseInput::_registerGlutMouseFunctions() {

	glutMouseFunc(_processGlutMouse);
}

void CGMouseInput::_processGlutMouse(int button, int state, int x, int y) {

	// Check which button was pressed and it's current state, and call the
	// appropriate member click handler.
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			m_onMouseLeftClick((CGMouseX)x, (CGMouseY)y);
		} else if (state == GLUT_UP) {
			m_onMouseLeftClickRelease((CGMouseX)x, (CGMouseY)y);
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) {
			m_onMouseRightClick((CGMouseX)x, (CGMouseY)y);
		} else if (state == GLUT_UP) {
			m_onMouseRightClickRelease((CGMouseX)x, (CGMouseY)y);
		}
		break;
	}
}

void CGMouseInput::setMouseLeftClickHandler(CGMouseInput::CGMouseFunctionPtr onLeftClick) {
	m_onMouseLeftClick = onLeftClick;
}

void CGMouseInput::setMouseLeftClickReleaseHandler(CGMouseInput::CGMouseFunctionPtr onLeftClickRelease) {
	m_onMouseLeftClickRelease = onLeftClickRelease;
}

void CGMouseInput::setMouseRightClickHandler(CGMouseInput::CGMouseFunctionPtr onRightClick) {
	m_onMouseRightClick = onRightClick;
}

void CGMouseInput::setMouseRightClickReleaseHandler(CGMouseInput::CGMouseFunctionPtr onRightClickRelease) {
	m_onMouseRightClickRelease = onRightClickRelease;
}

void CGMouseInput::setMouseMoveHandler(CGMouseInput::CGMouseFunctionPtr onMouseMove) {
	m_onMouseMove = onMouseMove;
}

void CGMouseInput::setMouseIdleHandler(CGMouseInput::CGMouseFunctionPtr onMouseIdle) {
	m_onMouseIdle = onMouseIdle;
}

void CGMouseInput::_defaultMouseLeftClickHandler(CGMouseX x, CGMouseY y) {
	// stub
}

void CGMouseInput::_defaultMouseLeftClickReleaseHandler(CGMouseX x, CGMouseY y) {
	// stub
}

void CGMouseInput::_defaultMouseRightClickHandler(CGMouseX x, CGMouseY y) {
	// stub
}

void CGMouseInput::_defaultMouseRightClickReleaseHandler(CGMouseX x, CGMouseY y) {
	// stub
}

void CGMouseInput::_defaultMouseMoveHandler(CGMouseX x, CGMouseY y) {
	// stub
}

void CGMouseInput::_defaultMouseIdleHandler(CGMouseX x, CGMouseY y) {
	// stub
}

} /* namespace TinyCGLib */
