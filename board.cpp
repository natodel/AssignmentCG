#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "board.h"

GLuint _displayListId_blackArea; //The OpenGL id of the display list
GLuint _displayListId_whiteArea; //The OpenGL id of the display list

void draw_BlackArea(void)
{
	glBegin(GL_QUADS);
	glColor3f(0.05f, 0.05f, 0.05f);
	glTranslatef(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.50f, 0.0f, 0.0f);
	glVertex3f(1.5f, 0.3f, 0.0f);
	glVertex3f(0.0f, 0.3f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.05f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -1.5f);
	glVertex3f(0.0f, 0.3f, -1.5f);
	glVertex3f(0.0f, 0.3f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.05f, 0.05f, 0.05f);
	glVertex3f(1.5f, 0.0f, 0.0f);
	glVertex3f(1.5f, 0.0f, -1.5f);
	glVertex3f(1.5f, 0.3f, -1.5f);
	glVertex3f(1.5f, 0.3f, 0.0f);
	glEnd();
	
	glBegin(GL_QUADS);
	glColor3f(0.05f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.0f, -1.5f);
	glVertex3f(1.50f, 0.0f, -1.5f);
	glVertex3f(1.5f, 0.3f, -1.5f);
	glVertex3f(0.0f, 0.3f, -1.5f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.05f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.50f, 0.0f, 0.0f);
	glVertex3f(1.5f, 0.0f, -1.5f);
	glVertex3f(0.0f, 0.0f, -1.5f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.1f, 0.1f, 0.1f);
	glVertex3f(0.0f, 0.3f, 0.0f);
	glVertex3f(1.50f, 0.3f, 0.0f);
	glVertex3f(1.5f, 0.3f, -1.5f);
	glVertex3f(0.0f, 0.3f, -1.5f);
	glEnd();
}

void draw_whiteArea(void)
{
	glBegin(GL_QUADS);
	glColor3f(0.05f, 0.05f, 0.05f);
	glTranslatef(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.50f, 0.0f, 0.0f);
	glVertex3f(1.5f, 0.3f, 0.0f);
	glVertex3f(0.0f, 0.3f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.05f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -1.5f);
	glVertex3f(0.0f, 0.3f, -1.5f);
	glVertex3f(0.0f, 0.3f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.05f, 0.05f, 0.05f);
	glVertex3f(1.5f, 0.0f, 0.0f);
	glVertex3f(1.5f, 0.0f, -1.5f);
	glVertex3f(1.5f, 0.3f, -1.5f);
	glVertex3f(1.5f, 0.3f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.05f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.0f, -1.5f);
	glVertex3f(1.50f, 0.0f, -1.5f);
	glVertex3f(1.5f, 0.3f, -1.5f);
	glVertex3f(0.0f, 0.3f, -1.5f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.05f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.50f, 0.0f, 0.0f);
	glVertex3f(1.5f, 0.0f, -1.5f);
	glVertex3f(0.0f, 0.0f, -1.5f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.3f, 0.0f);
	glVertex3f(1.50f, 0.3f, 0.0f);
	glVertex3f(1.5f, 0.3f, -1.5f);
	glVertex3f(0.0f, 0.3f, -1.5f);
	glEnd();
}

void initRendering(void)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
	//Set up a display list for drawing a cube
	_displayListId_blackArea = glGenLists(1); //Make room for the display list
	glNewList(_displayListId_blackArea, GL_COMPILE); //Begin the display list
	draw_BlackArea(); //Add commands for drawing a black area to the display list
	glEndList(); //End the display list
	//Set up a display list for drawing a cube
	_displayListId_whiteArea = glGenLists(2); //Make room for the display list
	glNewList(_displayListId_whiteArea, GL_COMPILE); //Begin the display list
	draw_whiteArea(); //Add commands for drawing a black to the display list
	glEndList(); //End the display list
}
