/*
 * CGMouseInput.cpp
 *
 *  Created on: Sep 17, 2013
 *      Author: broberto
 */

#include "CGMouseInput.h"
#include <iostream>

namespace TinyCGLib {

CGMouseInput::CGMouseFunctionPtr CGMouseInput::m_onMouseLeftClick = CGMouseInput::_defaultMouseLeftClickHandler;
CGMouseInput::CGMouseFunctionPtr CGMouseInput::m_onMouseLeftClickRelease = CGMouseInput::_defaultMouseLeftClickReleaseHandler;
CGMouseInput::CGMouseFunctionPtr CGMouseInput::m_onMouseLeftClickDrag = CGMouseInput::_defaultMouseLeftClickDragHandler;
CGMouseInput::CGMouseFunctionPtr CGMouseInput::m_onMouseRightClick = CGMouseInput::_defaultMouseRightClickHandler;
CGMouseInput::CGMouseFunctionPtr CGMouseInput::m_onMouseRightClickRelease = CGMouseInput::_defaultMouseRightClickReleaseHandler;
CGMouseInput::CGMouseFunctionPtr CGMouseInput::m_onMouseRightClickDrag = CGMouseInput::_defaultMouseRightClickDragHandler;
CGMouseInput::CGMouseFunctionPtr CGMouseInput::m_onMouseMove = CGMouseInput::_defaultMouseMoveHandler;
CGMouseInput::CGMouseFunctionPtr CGMouseInput::m_onMouseIdle = CGMouseInput::_defaultMouseIdleHandler;
CGMouseInput::CGMouseButtonState CGMouseInput::m_mouseButtonState = CGMouseInput::MouseButtonNone;

CGMouseInput::~CGMouseInput() {
	// TODO Auto-generated destructor stub
}

void CGMouseInput::initialize() {
	_registerGlutMouseFunctions();
}

void CGMouseInput::_registerGlutMouseFunctions() {

	glutMouseFunc(_processGlutMouseClicks);
	glutPassiveMotionFunc(_mouseMoveFunc);
	glutMotionFunc(_processGlutMouseDrags);
}

void CGMouseInput::_processGlutMouseClicks(int button, int state, int x, int y) {

	// Convert the screen x and y to scene x and y
	// Convert the screen x and y to scene x and y
	GLdouble coords[3];

	_convertScreenPointsToScene(x, y, coords);

	// Check which button was pressed and it's current state, and call the
	// appropriate member click handler.
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			m_mouseButtonState = MouseButtonLeft;
			m_onMouseLeftClick(coords[0], coords[1]);
		} else if (state == GLUT_UP) {
			m_mouseButtonState = MouseButtonNone;
			m_onMouseLeftClickRelease(coords[0], coords[1]);
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) {
			m_mouseButtonState = MouseButtonRight;
			m_onMouseRightClick(coords[0], coords[1]);
		} else if (state == GLUT_UP) {
			m_mouseButtonState = MouseButtonNone;
			m_onMouseRightClickRelease(coords[0], coords[1]);
		}
		break;
	}
}

void CGMouseInput::_processGlutMouseDrags(int x, int y) {

	// Convert the screen x and y to scene x and y
	GLdouble coords[3];

	_convertScreenPointsToScene(x, y, coords);

	// Check which button was pressed and it's current state, and call the
	// appropriate member drag handler
	switch (m_mouseButtonState) {
	case MouseButtonLeft:
		m_onMouseLeftClickDrag(coords[0], coords[1]);
		break;
	case MouseButtonRight:
		m_onMouseRightClickDrag(coords[0], coords[1]);
		break;
	case MouseButtonMiddle:
		// stub
		break;
	case MouseButtonNone:
		// stub
		break;
	default:
		// stub
		break;
	}
}

void CGMouseInput::_mouseMoveFunc(int x, int y) {
	GLdouble coords[3];

	_convertScreenPointsToScene(x, y, coords);

	m_onMouseMove(coords[0], coords[1]);
}

void CGMouseInput::_convertScreenPointsToScene(int x, int y, GLdouble out[3]) {
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat windowX, windowY, windowZ;

	// Get the current modelview, projection, and viewport matrices and dimensions
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	windowX = (float)x;
	// Invert the y component to match OpenGL's coordinate system
	windowY = (float)viewport[3] - (float)y;
	// Get the current z value based on the depth buffer and the clicked screen coordinates
	glReadPixels(x, (int)windowY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &windowZ);

	// Reverse the projection back to scene coordinates
	gluUnProject(windowX, windowY, windowZ, modelview, projection, viewport, &out[0], &out[1], &out[2]);
}

void CGMouseInput::setMouseLeftClickHandler(CGMouseInput::CGMouseFunctionPtr onLeftClick) {
	m_onMouseLeftClick = onLeftClick;
}

void CGMouseInput::setMouseLeftClickReleaseHandler(CGMouseInput::CGMouseFunctionPtr onLeftClickRelease) {
	m_onMouseLeftClickRelease = onLeftClickRelease;
}

void CGMouseInput::setMouseLeftClickDragHandler(CGMouseInput::CGMouseFunctionPtr onLeftClickDrag) {
	m_onMouseLeftClickDrag = onLeftClickDrag;
	_registerGlutMouseFunctions();
}

void CGMouseInput::setMouseRightClickHandler(CGMouseInput::CGMouseFunctionPtr onRightClick) {
	m_onMouseRightClick = onRightClick;
}

void CGMouseInput::setMouseRightClickReleaseHandler(CGMouseInput::CGMouseFunctionPtr onRightClickRelease) {
	m_onMouseRightClickRelease = onRightClickRelease;
}

void CGMouseInput::setMouseRightClickDragHandler(CGMouseInput::CGMouseFunctionPtr onRightClickDrag) {
	m_onMouseRightClickDrag = onRightClickDrag;
	_registerGlutMouseFunctions();
}

void CGMouseInput::setMouseMoveHandler(CGMouseInput::CGMouseFunctionPtr onMouseMove) {
	m_onMouseMove = onMouseMove;
	_registerGlutMouseFunctions();
}

void CGMouseInput::setMouseIdleHandler(CGMouseInput::CGMouseFunctionPtr onMouseIdle) {
	m_onMouseIdle = onMouseIdle;
	_registerGlutMouseFunctions();
}

void CGMouseInput::setRightClickMenu(CGMouseInput::CGMenuInitFunctionPtr init, CGMouseInput::CGMenuHandlerFunctionPtr handler) {
	// Use init to set up menu items and enums for handler
	// Use handler to handle menu item clicks
	glutCreateMenu(handler);
	init();
	setMouseRightClickHandler(_defaultMouseRightClickHandler);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void CGMouseInput::_defaultMouseLeftClickHandler(CGMouseX x, CGMouseY y) {
	// stub
}

void CGMouseInput::_defaultMouseLeftClickReleaseHandler(CGMouseX x, CGMouseY y) {
	// stub
}

void CGMouseInput::_defaultMouseLeftClickDragHandler(CGMouseX x, CGMouseY y) {
	// stub
}

void CGMouseInput::_defaultMouseRightClickHandler(CGMouseX x, CGMouseY y) {
	// stub
}

void CGMouseInput::_defaultMouseRightClickReleaseHandler(CGMouseX x, CGMouseY y) {
	// stub
}

void CGMouseInput::_defaultMouseRightClickDragHandler(CGMouseX x, CGMouseY y) {
	// stub
}

void CGMouseInput::_defaultMouseMoveHandler(CGMouseX x, CGMouseY y) {
	// stub
}

void CGMouseInput::_defaultMouseIdleHandler(CGMouseX x, CGMouseY y) {
	// stub
}

} /* namespace TinyCGLib */
