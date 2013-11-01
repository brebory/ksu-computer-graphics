/*
 * CGMouseInput.h
 *
 *  Created on: Sep 17, 2013
 *      Author: broberto
 *
 *      Class GLMouseInput provides a singleton interface for setting various
 *      action handlers for mouse i/o in OpenGL and GLUT.
 */

#ifndef CGMOUSEINPUT_H_
#define CGMOUSEINPUT_H_

#include <GL/glut.h>

namespace TinyCGLib {

class CGMouseInput {
public:
	typedef double CGMouseX;
	typedef double CGMouseY;
	typedef void (*CGMouseFunctionPtr)(CGMouseX, CGMouseY);
	typedef void (*CGMenuHandlerFunctionPtr)(int);
	typedef void (*CGMenuInitFunctionPtr)(void);

	enum CGMouseButtonState { MouseButtonLeft, MouseButtonRight, MouseButtonMiddle, MouseButtonNone };

	virtual ~CGMouseInput();

	static void initialize();

	static void setMouseLeftClickHandler(CGMouseFunctionPtr);
	static void setMouseLeftClickReleaseHandler(CGMouseFunctionPtr);
	static void setMouseLeftClickDragHandler(CGMouseFunctionPtr);
	static void setMouseRightClickHandler(CGMouseFunctionPtr);
	static void setMouseRightClickReleaseHandler(CGMouseFunctionPtr);
	static void setMouseRightClickDragHandler(CGMouseFunctionPtr);
	static void setMouseMoveHandler(CGMouseFunctionPtr);
	static void setMouseIdleHandler(CGMouseFunctionPtr);
	static void setRightClickMenu(CGMenuInitFunctionPtr, CGMenuHandlerFunctionPtr);

	static void _defaultMouseLeftClickHandler(CGMouseX, CGMouseY);
	static void _defaultMouseLeftClickReleaseHandler(CGMouseX, CGMouseY);
	static void _defaultMouseLeftClickDragHandler(CGMouseX, CGMouseY);
	static void _defaultMouseRightClickHandler(CGMouseX, CGMouseY);
	static void _defaultMouseRightClickReleaseHandler(CGMouseX, CGMouseY);
	static void _defaultMouseRightClickDragHandler(CGMouseX, CGMouseY);
	static void _defaultMouseMoveHandler(CGMouseX, CGMouseY);
	static void _defaultMouseIdleHandler(CGMouseX, CGMouseY);

	static void _convertScreenPointsToScene(int, int, GLdouble[3]);

private:

	static CGMouseFunctionPtr m_onMouseLeftClick;
	static CGMouseFunctionPtr m_onMouseLeftClickRelease;
	static CGMouseFunctionPtr m_onMouseLeftClickDrag;
	static CGMouseFunctionPtr m_onMouseRightClick;
	static CGMouseFunctionPtr m_onMouseRightClickRelease;
	static CGMouseFunctionPtr m_onMouseRightClickDrag;
	static CGMouseFunctionPtr m_onMouseMove;
	static CGMouseFunctionPtr m_onMouseIdle;
	static CGMouseButtonState m_mouseButtonState;

	static void _registerGlutMouseFunctions(void);
	static void _processGlutMouseClicks(int, int, int, int);
	static void _processGlutMouseDrags(int, int);
	static void _mouseMoveFunc(int, int);

	// Private constructor to prevent instantiation
	CGMouseInput() { };

};

} /* namespace TinyGCLib */
#endif /* CGMOUSEINPUT_H_ */
