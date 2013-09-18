/*
 * test.cpp
 *
 *  Created on: Aug 29, 2013
 *      Author: broberto
 */

#include <sstream>
#include <string>
#include <GL/glut.h>
#include <math.h>

int main_window;
int segments = 30;
float time_delta;


void glutIdleCallback(void) {
	if (glutGetWindow() != main_window) {
		glutSetWindow(main_window);
	}

	glutPostRedisplay();
}

void glutReshapeCallback(int x, int y) {
	float xy_aspect = (float)x / (float)y;
	glViewport(0, 0, x, y);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-xy_aspect * 0.08, xy_aspect * 0.08, -0.08, 0.08, 0.1, 15.0);
}

void glutDisplayCallback() {
	std::stringstream ss;
	std::string output;
	time_delta += 0.1;
	glViewport(250, 250, 250, 250);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
		glColor3f(fmodf((time_delta + 125.0f), 255.0f) / 255.0f, fmodf((time_delta), 255.0f) / 255.0f, fmodf((time_delta), 255.0f) / 255.0f);
		glVertex2f(-1.5, -1.5);
		glColor3f(fmodf((time_delta), 255.0f) / 255.0f, fmodf((time_delta + 125.0f), 255.0f) / 255.0f, fmodf((time_delta), 255.0f) / 255.0f);
		glVertex2f(-1.5, 1.5);
		glColor3f(fmodf((time_delta), 255.0f) / 255.0f, fmodf((time_delta), 255.0f) / 255.0f, fmodf((time_delta + 125.0f), 255.0f) / 255.0f);
		glVertex2f(1.5, 1.5);
		glColor3f(fmodf((time_delta + 125.0f), 255.0f) / 255.0f, fmodf((time_delta + 125.0f), 255.0f) / 255.0f, fmodf((time_delta), 255.0f) / 255.0f);
		glVertex2f(1.5, -1.5);
		ss << time_delta;
		ss >> output;
		/*for (int idx = 0, len = output.size(); idx < len; ++idx) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, output.at(idx));
		}*/
	glutPostRedisplay();
	glEnd();
	glFlush();

}

void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("simple");
	glutDisplayFunc(glutDisplayCallback);

	init();

	time_delta = 0.1;

	glutMainLoop();
}




