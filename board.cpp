
#include<windows.h>
#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#include "board.h"

using namespace std;

float i;
int k = 0;

void draw_BlackArea() {
	glEnable(GL_BLEND);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glColor4f(0.1f, 0.1f, 0.2f, 0.5f);
	glColorMaterial(GL_FRONT, GL_SPECULAR);
	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
	
	glBegin(GL_QUADS);
	glTranslatef(0.0f, 0.0f, 0.0f);
	glNormal3f(0, 1, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.50f, 0.0f, 0.0f);
	glVertex3f(1.5f, 0.3f, 0.0f);
	glVertex3f(0.0f, 0.3f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -1.5f);
	glVertex3f(0.0f, 0.3f, -1.5f);
	glVertex3f(0.0f, 0.3f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(1.5f, 0.0f, 0.0f);
	glVertex3f(1.5f, 0.0f, -1.5f);
	glVertex3f(1.5f, 0.3f, -1.5f);
	glVertex3f(1.5f, 0.3f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(0.0f, 0.0f, -1.5f);
	glVertex3f(1.50f, 0.0f, -1.5f);
	glVertex3f(1.5f, 0.3f, -1.5f);
	glVertex3f(0.0f, 0.3f, -1.5f);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.50f, 0.0f, 0.0f);
	glVertex3f(1.5f, 0.0f, -1.5f);
	glVertex3f(0.0f, 0.0f, -1.5f);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(0.0f, 0.3f, 0.0f);
	glVertex3f(1.50f, 0.3f, 0.0f);
	glVertex3f(1.5f, 0.3f, -1.5f);
	glVertex3f(0.0f, 0.3f, -1.5f);
	glEnd();
	
	glDisable(GL_BLEND);
}

void draw_whiteArea() {
	glEnable(GL_BLEND);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
	glColorMaterial(GL_FRONT, GL_SPECULAR);
	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
	
	glBegin(GL_QUADS);
	glTranslatef(0.0f, 0.0f, 0.0f);
	glNormal3f(0, 1, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.50f, 0.0f, 0.0f);
	glVertex3f(1.5f, 0.3f, 0.0f);
	glVertex3f(0.0f, 0.3f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -1.5f);
	glVertex3f(0.0f, 0.3f, -1.5f);
	glVertex3f(0.0f, 0.3f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(1.5f, 0.0f, 0.0f);
	glVertex3f(1.5f, 0.0f, -1.5f);
	glVertex3f(1.5f, 0.3f, -1.5f);
	glVertex3f(1.5f, 0.3f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(0.0f, 0.0f, -1.5f);
	glVertex3f(1.50f, 0.0f, -1.5f);
	glVertex3f(1.5f, 0.3f, -1.5f);
	glVertex3f(0.0f, 0.3f, -1.5f);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.50f, 0.0f, 0.0f);
	glVertex3f(1.5f, 0.0f, -1.5f);
	glVertex3f(0.0f, 0.0f, -1.5f);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(0.0f, 0.3f, 0.0f);
	glVertex3f(1.50f, 0.3f, 0.0f);
	glVertex3f(1.5f, 0.3f, -1.5f);
	glVertex3f(0.0f, 0.3f, -1.5f);
	glEnd();
	
	glDisable(GL_BLEND);
}


void drawChessBoard() {
	_displayListId_blackArea = glGenLists(1);
	glNewList(_displayListId_blackArea, GL_COMPILE); 
	draw_BlackArea(); 
	glEndList();

	_displayListId_whiteArea = glGenLists(2);
	glNewList(_displayListId_whiteArea, GL_COMPILE);
	draw_whiteArea(); 
	glEndList();	

	for (float j = 0.0; j>(-8 * 1.5); j -= 1.5) {
		k++;

		for (i = 0.0; i<(4 * 3.0); i += 3.0) {
			if (k % 2 == 0) {
				glPushMatrix();
				glTranslatef(i, 0.0, j);
				glCallList(_displayListId_blackArea);
				glPopMatrix();
			}
			else {
				glPushMatrix();
				glTranslatef(i + 1.5, 0.0, j);
				glCallList(_displayListId_blackArea);
				glPopMatrix();
			}
		}
	}

	for (float j = 0.0; j>(-8 * 1.5); j -= 1.5) {
		k++;

		for (i = 0.0; i<(4 * 3.0); i += 3.0) {
			if (k % 2 != 0) {
				glPushMatrix();
				glTranslatef(i, 0.0, j);
				glCallList(_displayListId_whiteArea);
				glPopMatrix();
			}	
			else {
				glPushMatrix();
				glTranslatef(i + 1.5, 0.0, j);
				glCallList(_displayListId_whiteArea);
				glPopMatrix();
			}
		}
	}
}

