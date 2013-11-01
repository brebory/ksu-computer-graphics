/*
 * CGAssignment2.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: broberto
 */

#include <GL/glut.h>
#include "CGMouseInput.h"
#include "CGNode.h"
#include "CGNodeManager.h"
#include "CGCelestialBody.h"
#include <iostream>
#include <math.h>

using namespace TinyCGLib;

int GL_WINDOW_X = 500;
int GL_WINDOW_Y = 500;
int windowID;
GLfloat eyeX;
GLfloat eyeY;
GLfloat eyeZ;
float DEFAULT_SIZE = 0.25f;
CGNodeManager sceneManager;
bool continuousUpdate;
bool horizontalView;
const int instructionLines = 10;
char instructions[instructionLines][80];


void leftClickCallback(CGMouseInput::CGMouseX x, CGMouseInput::CGMouseY y) {
	((CGCelestialBody *)sceneManager.getRoot())->increaseSpeed();
	((CGCelestialBody *)sceneManager.getRoot()->getChild(0))->increaseSpeed();
	((CGCelestialBody *)sceneManager.getRoot()->getChild(0)->getChild(0))->increaseSpeed();
}

void rightClickCallback(CGMouseInput::CGMouseX x, CGMouseInput::CGMouseY y) {
	((CGCelestialBody *)sceneManager.getRoot())->decreaseSpeed();
	((CGCelestialBody *)sceneManager.getRoot()->getChild(0))->decreaseSpeed();
	((CGCelestialBody *)sceneManager.getRoot()->getChild(0)->getChild(0))->decreaseSpeed();
}

void glEnable2D()
{
	int vPort[4];

   glGetIntegerv(GL_VIEWPORT, vPort);

   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();

   glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();
}

void glDisable2D()
{
   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   glMatrixMode(GL_MODELVIEW);
   glPopMatrix();
}

void toggleViewport() {
	if (horizontalView) {
		eyeX = 10.0;
		eyeY = 10.0;
	} else {
		eyeX = 0.0;
		eyeY = 0.0;
	}
	horizontalView = !horizontalView;
}

void renderText() {

	glEnable2D();
	glPushMatrix();
	glScalef(0.1, 0.1, 0.1);
	for (int idx = 0; idx < instructionLines; ++idx) {
		int textLength = strlen(instructions[idx]);
		glPushMatrix();
		glTranslatef(200.0, 4700.0 - (150.0*idx), 0.0);
		for (int jdx = 0; jdx < textLength; ++jdx) {
			glColor3d(1.0, 1.0, 1.0);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, instructions[idx][jdx]);
		}
		glPopMatrix();
	}
	glPopMatrix();
	glDisable2D();
}

void glutRenderCallback() {
	// Clear color buffer and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Load the identity matrix to reset transformations
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	if (continuousUpdate) {
		sceneManager.updateNodes();
	}
	sceneManager.drawNodes();

	renderText();
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
	glFrustum(-xy_aspect * 0.08, xy_aspect * 0.08, -0.08, 0.08, 0.1, 30.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

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
	windowID = glutCreateWindow("Assignment 2");

	// Set up display, idle, and reshape callbacks
	glutDisplayFunc(glutRenderCallback);
	glutIdleFunc(glutIdleCallback);
	glutReshapeFunc(glutReshapeCallback);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Set up the view
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

}

void changeObjectsToWireframe() {
	if (!((CGCelestialBody *)sceneManager.getRoot())->isWireframe()) {
		((CGCelestialBody *)sceneManager.getRoot())->toggleWireframe();
		((CGCelestialBody *)sceneManager.getRoot()->getChild(0))->toggleWireframe();
		((CGCelestialBody *)sceneManager.getRoot()->getChild(0)->getChild(0))->toggleWireframe();
	}
}

void changeObjectsToSolid() {
	if (((CGCelestialBody *)sceneManager.getRoot())->isWireframe()) {
		((CGCelestialBody *)sceneManager.getRoot())->toggleWireframe();
		((CGCelestialBody *)sceneManager.getRoot()->getChild(0))->toggleWireframe();
		((CGCelestialBody *)sceneManager.getRoot()->getChild(0)->getChild(0))->toggleWireframe();
	}
}

void glutKeyboardCallback(unsigned char key, int x, int y) {
  switch (key) {
    case 27: // Escape key
      glutDestroyWindow(windowID);
      exit (0);
      break;
    case 's':
    case 'S':
    	changeObjectsToSolid();
    	break;
    case 'w':
    case 'W':
    	changeObjectsToWireframe();
    	break;
    case 'a':
    case 'A':
    	continuousUpdate = !continuousUpdate;
    	break;
    case 'v':
    case 'V':
    	toggleViewport();
    	break;
    case 'd':
    case 'D':
    	sceneManager.getRoot()->update();
    	break;
  }
  glutPostRedisplay();
}

void glutSpecialCallback(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		((CGCelestialBody *)sceneManager.getRoot())->decreaseSpeed();
		((CGCelestialBody *)sceneManager.getRoot()->getChild(0))->decreaseSpeed();
		((CGCelestialBody *)sceneManager.getRoot()->getChild(0)->getChild(0))->decreaseSpeed();
		break;
	case GLUT_KEY_RIGHT:
		((CGCelestialBody *)sceneManager.getRoot())->increaseSpeed();
		((CGCelestialBody *)sceneManager.getRoot()->getChild(0))->increaseSpeed();
		((CGCelestialBody *)sceneManager.getRoot()->getChild(0)->getChild(0))->increaseSpeed();
		break;
	}
}



int main(int argc, char **argv) {
	strcpy(instructions[0], "Controls:");
	strcpy(instructions[1], "=========");
	strcpy(instructions[2], "a/A: toggle automatic update");
	strcpy(instructions[3], "v/V: toggle viewpoint");
	strcpy(instructions[4], "d/D: advance a day");
	strcpy(instructions[5], "s/S: switch to solid rendering");
	strcpy(instructions[6], "w/W: switch to wireframe rendering");
	strcpy(instructions[7], "mouseL/rightArrow: increase speed");
	strcpy(instructions[8], "mouseR/leftArrow: decrease speed");
	strcpy(instructions[9], "esc: exit");

	eyeX = 0.0;
	eyeY = 0.0;
	eyeZ = 10.0;

	glutInitialize(argc, argv);
	GLfloat rotSpeed = 0.035;
	GLfloat moonSpeedMultiplier = 12.125;
	GLfloat planetRotationSpeedMultiplier = 365.0;

	horizontalView = true;
	continuousUpdate = false;

	sceneManager = CGNodeManager();
	sceneManager.setRoot(new CGCelestialBody(0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 5.0, 0.1, 0.0, 0.0));
	sceneManager.getRoot()->addChild(new CGCelestialBody(0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 2.0, rotSpeed * planetRotationSpeedMultiplier, 11.0, rotSpeed));
	sceneManager.getRoot()->getChild(0)->addChild(new CGCelestialBody(0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.75, 0.01, 4.0, rotSpeed * moonSpeedMultiplier));

	glutKeyboardFunc(glutKeyboardCallback);
	glutSpecialFunc(glutSpecialCallback);

	CGMouseInput::initialize();
	CGMouseInput::setMouseLeftClickHandler(leftClickCallback);
	CGMouseInput::setMouseRightClickHandler(rightClickCallback);

	glutMainLoop();

	return EXIT_SUCCESS;
}


