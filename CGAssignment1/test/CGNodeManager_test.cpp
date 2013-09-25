/*
 * CGNodeManager_test.cpp
 *
 *  Created on: Sep 17, 2013
 *      Author: broberto
 */

#include <GL/glut.h>
#include "../src/CGMouseInput.h"
#include "../src/CGNode.h"
#include "../src/CGNodeManager.h"
#include <iostream>

namespace CGNodeManagerTest {

	using namespace TinyCGLib;

	bool leftMouseDown;
	GLfloat leftMouseLocation[2];
	bool rightMouseDown;
	GLfloat rightMouseLocation[2];
	int GL_WINDOW_X = 320;
	int GL_WINDOW_Y = 320;

	enum MENU_TYPE {
		OPTION_ONE,
		OPTION_TWO,
	};

	void glutRenderCallback() {
		// Clear color buffer
		glClear(GL_COLOR_BUFFER_BIT);
		if (leftMouseDown) {
			glBegin(GL_POLYGON);
				glColor3d(1.0, 0.0, 0.0);
				glVertex3f(leftMouseLocation[0] - 0.5, leftMouseLocation[1] - 0.5, -1);
				glColor3d(1,1,0);
				glVertex3f(leftMouseLocation[0] + 0.5, leftMouseLocation[1] - 0.5, -1);
				glColor3d(1,1,1);
				glVertex3f(leftMouseLocation[0] + 0.5, leftMouseLocation[1] + 0.5, -1);
				glColor3d(0,1,1);
				glVertex3f(leftMouseLocation[0] - 0.5, leftMouseLocation[1] + 0.5, -1);
			glEnd();
		}
		if (rightMouseDown) {
			glBegin(GL_POLYGON);
				glColor3d(0.0, 0.0, 1.0);
				glVertex3f(rightMouseLocation[0] - 0.5, rightMouseLocation[1] - 0.5, -1);
				glVertex3f(rightMouseLocation[0] + 0.5, rightMouseLocation[1] - 0.5, -1);
				glVertex3f(rightMouseLocation[0] + 0.5, rightMouseLocation[1] + 0.5, -1);
				glVertex3f(rightMouseLocation[0] - 0.5, rightMouseLocation[1] + 0.5, -1);
			glEnd();

		}

		// Swap color buffers
		glutSwapBuffers();
	}

	void glutIdleCallback() {
		glutPostRedisplay();
	}

	void glutReshapeCallback(GLint width, GLint height)
	{
		float xy_aspect = (float)width/(float)height;
		glViewport(0, 0, width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-xy_aspect * 0.08, xy_aspect * 0.08, -0.08, 0.08, 0.1, 15.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

	}

	void onLeftClick(CGMouseInput::CGMouseX x, CGMouseInput::CGMouseY y) {
		leftMouseDown = true;

		leftMouseLocation[0] = (x - (GL_WINDOW_X/2)) / (float)GL_WINDOW_X;
		leftMouseLocation[1] = -((y - (GL_WINDOW_Y/2)) / (float)GL_WINDOW_Y);
	}

	void onLeftClickRelease(CGMouseInput::CGMouseX x, CGMouseInput::CGMouseY y) {
		leftMouseDown = false;
	}

	void onRightClick(CGMouseInput::CGMouseX x, CGMouseInput::CGMouseY y) {
		rightMouseDown = true;

		GLint m_viewport[4];

		glGetIntegerv(GL_VIEWPORT, m_viewport);

		rightMouseLocation[0] = (x - (GL_WINDOW_X/2)) / (float)GL_WINDOW_X;
		rightMouseLocation[1] = -((y - (GL_WINDOW_Y/2)) / (float)GL_WINDOW_Y);
	}

	void onRightClickRelease(CGMouseInput::CGMouseX x, CGMouseInput::CGMouseY y) {
		rightMouseDown = false;
	}

	void glutInitialize(int& argc, char **argv) {
		/*
		 * glutInitialize sets up a window for OpenGL rendering and registers
		 * glutDisplayFunc and glutIdleFunc callbacks.
		 *
		 */
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

		glutInitWindowPosition(100, 100);
		glutInitWindowSize(320, 320);
		glutCreateWindow("Test CGMouseInput");

		glutDisplayFunc(glutRenderCallback);
		glutIdleFunc(glutIdleCallback);
		glutReshapeFunc(glutReshapeCallback);

		glClearColor(0.0, 0.0, 0.0, 1.0);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	}

} /* namespace TinyCGLib */

int main(int argc, char **argv) {
	using namespace TinyCGLib;

	CGNodeManagerTest::glutInitialize(argc, argv);

	// Set up GLMouseInput
	CGMouseInput::initialize();
	CGMouseInput::setMouseLeftClickHandler(CGNodeManagerTest::onLeftClick);
	CGMouseInput::setMouseLeftClickReleaseHandler(CGNodeManagerTest::onLeftClickRelease);
	CGMouseInput::setMouseRightClickHandler(CGNodeManagerTest::onRightClick);

	// Start main loop
	glutMainLoop();

	return EXIT_SUCCESS;
}
