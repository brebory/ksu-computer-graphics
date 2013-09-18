/*
 * GLMouseInput.h
 *
 *  Created on: Sep 17, 2013
 *      Author: broberto
 *
 *      Class GLMouseInput provides an interface for setting various action
 *      handlers for mouse i/o in OpenGL and GLUT.
 */

#ifndef CGMOUSEINPUT_H_
#define CGMOUSEINPUT_H_

#include <GL/glut.h>

namespace TinyCGLib {

class CGMouseInput {
public:
	typedef int CGMouseX;
	typedef int CGMouseY;
	typedef void (*CGMouseFunctionPtr)(CGMouseX, CGMouseY);

	CGMouseInput();
	virtual ~CGMouseInput();

	static void initialize();

	static void setMouseLeftClickHandler(CGMouseFunctionPtr);
	static void setMouseLeftClickReleaseHandler(CGMouseFunctionPtr);
	static void setMouseRightClickHandler(CGMouseFunctionPtr);
	static void setMouseRightClickReleaseHandler(CGMouseFunctionPtr);
	static void setMouseMoveHandler(CGMouseFunctionPtr);
	static void setMouseIdleHandler(CGMouseFunctionPtr);

private:
	static CGMouseFunctionPtr m_onMouseLeftClick;
	static CGMouseFunctionPtr m_onMouseLeftClickRelease;
	static CGMouseFunctionPtr m_onMouseRightCLick;
	static CGMouseFunctionPtr m_onMpuseRightClickRelease;
	static CGMouseFunctionPtr m_onMouseMove;
	static CGMouseFunctionPtr m_onMouseIdle;

	static void _registerGlutMouseFunctions(void);
	static void _processGlutMouse(int, int, int, int);

	static void _defaultMouseLeftClickHandler(CGMouseX, CGMouseY);
	static void _defaultMouseLeftClickReleaseHandler(CGMouseX, CGMouseY);
	static void _defaultMouseRightClickHandler(CGMouseX, CGMouseY);
	static void _defaultMouseRightClickReleaseHandler(CGMouseX, CGMouseY);
	static void _defaultMouseMoveHandler(CGMouseX, CGMouseY);
	static void _defaultMouseIdleHandler(CGMouseX, CGMouseY);

};

} /* namespace TinyGCLib */
#endif /* CGMOUSEINPUT_H_ */
