/*
 * CGAssignment1.cpp
 *
 *  Created on: Sep 24, 2013
 *      Author: broberto
 */

#include <GL/glut.h>
#include "CGMouseInput.h"
#include "CGNode.h"
#include "CGNodeManager.h"
#include "CGRectangle.h"
#include "CGCircle.h"
#include <iostream>
#include <math.h>

using namespace TinyCGLib;

int GL_WINDOW_X = 500;
int GL_WINDOW_Y = 500;
int windowID;
float DEFAULT_SIZE = 0.25f;
CGNodeManager sceneManager;

enum GLMenuType {
	OPTION_ONE,
	OPTION_TWO,
	OPTION_THREE,
};

void glutRenderCallback() {
	// Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	// Load the identity matrix to reset transformations
	glLoadIdentity();
	// Move the viewport back -15 units so that it's easier to see
	glTranslatef(0.0f, 0.0f, -1.0f);
	sceneManager.updateNodes();
	sceneManager.drawNodes();
	// Swap color buffers
	glutSwapBuffers();
}

void glutIdleCallback() {
	glutPostRedisplay();
}

void glutReshapeCallback(GLint width, GLint height)
{
	// Get the aspect ratio for the new size
	float xy_aspect = (float)width/(float)height;
	// Set the viewport to the new size
	glViewport(0, 0, width, height);

	// Reset the transformation and projection matrices
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set up the view frustum
	glFrustum(-xy_aspect * 0.08, xy_aspect * 0.08, -0.08, 0.08, 0.1, 15.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void glutKeyboardCallback(unsigned char key, int x, int y) {
  switch (key) {
    case 27: // Escape key
      glutDestroyWindow(windowID);
      exit (0);
      break;
  }
  glutPostRedisplay();
}

void opt1LeftClickCallback(CGMouseInput::CGMouseX x, CGMouseInput::CGMouseY y) {
	CGNode* selectedNode = sceneManager.getRoot();
	if (selectedNode) {
		selectedNode->setColor(1.0, 0.0, 0.0);
	} else {
		sceneManager.setRoot(new CGRectangle(x, y, 0.0, DEFAULT_SIZE, DEFAULT_SIZE, 1.0, 0.0, 0.0));
	}
}

void opt1LeftClickReleaseCallback(CGMouseInput::CGMouseX x, CGMouseInput::CGMouseY y) {
	CGNode* selectedNode = sceneManager.getRoot();
	if (selectedNode) {
		selectedNode->setColor(1.0, 1.0, 0.0);
	} else {
		sceneManager.setRoot(new CGRectangle(x, y, 0.0, DEFAULT_SIZE, DEFAULT_SIZE, 1.0, 1.0, 0.0));
	}
}

void opt1LeftClickDragCallback(CGMouseInput::CGMouseX x, CGMouseInput::CGMouseY y) {
	CGNode *selectedNode = sceneManager.getRoot();
	if (selectedNode) {
		selectedNode->setPosition(x, y, 0.0);
	} else {
		sceneManager.setRoot(new CGRectangle(x, y, 0.0, DEFAULT_SIZE, DEFAULT_SIZE, 1.0, 0.0, 0.0));
	}
}

void opt1MouseMoveCallback(CGMouseInput::CGMouseX x, CGMouseInput::CGMouseY y) {
	CGNode *selectedNode = sceneManager.getRoot();
	if (selectedNode) {
		selectedNode->setPosition(x, y, 0.0);
	} else {
		sceneManager.setRoot(new CGRectangle(x, y, 0.0, DEFAULT_SIZE, DEFAULT_SIZE, 1.0, 1.0, 0.0));
	}
}

void opt3LeftClickCallback(CGMouseInput::CGMouseX x, CGMouseInput::CGMouseY y) {
	sceneManager.setRoot(new CGCircle(x, y, 0.0, 0.0, 1.0, 1.0, 1.0));
}

void opt3LeftClickDragCallback(CGMouseInput::CGMouseX x, CGMouseInput::CGMouseY y) {
	CGCircle *selectedCircle = dynamic_cast<CGCircle*>(sceneManager.getRoot());
	float dist = sqrt(pow((double)(selectedCircle->getPositionX() - x), 2.0) + pow((double)(selectedCircle->getPositionY() - y), 2.0));
	selectedCircle->setRadius(dist);
}

void opt3LeftClickReleaseCallback(CGMouseInput::CGMouseX x, CGMouseInput::CGMouseY y) {
	CGCircle *selectedCircle = dynamic_cast<CGCircle*>(sceneManager.getRoot());
	selectedCircle->setColor(0.0, 1.0, 0.0);
}

void glutInitialize(int& argc, char **argv) {
	/*
	 * glutInitialize sets up a window for OpenGL rendering and registers
	 * glutDisplayFunc and glutIdleFunc callbacks.
	 *
	 */

	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

	// Create the window and save it's ID
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(GL_WINDOW_X, GL_WINDOW_Y);
	windowID = glutCreateWindow("Assignment 1");

	// Set up display, idle, and reshape callbacks
	glutDisplayFunc(glutRenderCallback);
	glutIdleFunc(glutIdleCallback);
	glutReshapeFunc(glutReshapeCallback);

	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Set up the view
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

}

void menuInit() {
	glutAddMenuEntry("Rectangle Moving With Mouse", OPTION_ONE);
	glutAddMenuEntry("Circle Moving Automatically", OPTION_TWO);
	glutAddMenuEntry("Rubberbanding Circle", OPTION_THREE);
}

void menuCallback(int option) {

	switch((GLMenuType)option) {
	case OPTION_ONE:
		// Create the rectangle, set appropriate click handlers
		CGMouseInput::setMouseLeftClickHandler(opt1LeftClickCallback);
		CGMouseInput::setMouseLeftClickDragHandler(opt1LeftClickDragCallback);
		CGMouseInput::setMouseLeftClickReleaseHandler(opt1LeftClickReleaseCallback);
		CGMouseInput::setMouseMoveHandler(opt1MouseMoveCallback);
		sceneManager.setRoot(new CGRectangle(0.0, 0.0, 0.0, DEFAULT_SIZE, DEFAULT_SIZE, 1.0, 1.0, 0.0));
		break;

	case OPTION_TWO:
		// Reset click handlers
		CGMouseInput::setMouseLeftClickHandler(CGMouseInput::_defaultMouseLeftClickHandler);
		CGMouseInput::setMouseLeftClickDragHandler(CGMouseInput::_defaultMouseLeftClickDragHandler);
		CGMouseInput::setMouseLeftClickReleaseHandler(CGMouseInput::_defaultMouseLeftClickReleaseHandler);
		CGMouseInput::setMouseMoveHandler(CGMouseInput::_defaultMouseMoveHandler);
		sceneManager.setRoot(new CGCircle(-0.5, -0.5, 0.0, DEFAULT_SIZE, 0.0, 0.0, 1.0));
		sceneManager.getRoot()->setVelocity(0.0005, 0.0005, 0.0);
		break;

	case OPTION_THREE:
		CGMouseInput::setMouseLeftClickHandler(opt3LeftClickCallback);
		CGMouseInput::setMouseLeftClickDragHandler(opt3LeftClickDragCallback);
		CGMouseInput::setMouseLeftClickReleaseHandler(opt3LeftClickReleaseCallback);
		CGMouseInput::setMouseMoveHandler(CGMouseInput::_defaultMouseMoveHandler);
		break;
	}
}


int main(int argc, char **argv) {
	using namespace TinyCGLib;

	glutInitialize(argc, argv);
	glutKeyboardFunc(glutKeyboardCallback);

	sceneManager = CGNodeManager();
	sceneManager.setRoot(new CGRectangle);

	// Set up GLMouseInput
	CGMouseInput::initialize();
	CGMouseInput::setRightClickMenu(menuInit, menuCallback);

	// Start main loop
	glutMainLoop();

	return EXIT_SUCCESS;
}

