
#include<windows.h>
#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#include "board.h"
#include <fstream>

using namespace std;

float i;
int k = 0;

GLuint LoadTexture(const char * pic, int width, int height)
{
	GLuint Texture;
	BYTE * data;
	FILE * picfile;

	picfile = fopen(pic, "rb");
	if (picfile == NULL)
		return 0;

	data = (BYTE *)malloc(width * height * 3);

	fread(data, width * height, 3, picfile);
	fclose(picfile);
	
    glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D,  Texture);

	for(int i = 0; i < width * height ; ++i)
	{
	   int index = i*3;
	   unsigned char B,R;
	   B = data[index];
	   R = data[index+2];
	
	   data[index] = R;
	   data[index+2] = B;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	free(data);
	return Texture;
}

void draw_BlackArea() {
	glEnable(GL_BLEND);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glColor4f(0.1f, 0.1f, 0.2f, 0.5f);
	glColorMaterial(GL_FRONT, GL_SPECULAR);
	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
	
	glBegin(GL_QUADS);
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

	glEnable(GL_TEXTURE_2D);
	GLuint bTexture;
	bTexture = LoadTexture("blue.bmp", 600, 450);
	
	glBegin(GL_QUADS);
	glBindTexture(GL_TEXTURE_2D, bTexture);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f);		
	glVertex3f(0.0f, 0.3f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.50f, 0.3f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.5f, 0.3f, -1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 0.3f, -1.5f);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void draw_WhiteArea() {
	glEnable(GL_BLEND);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
	glColorMaterial(GL_FRONT, GL_SPECULAR);
	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
	
	glBegin(GL_QUADS);
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

	glEnable(GL_TEXTURE_2D);
	GLuint wTexture;
	wTexture = LoadTexture("white.bmp", 900, 900);

	glBegin(GL_QUADS);
	glBindTexture(GL_TEXTURE_2D, wTexture);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.3f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.50f, 0.3f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.5f, 0.3f, -1.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.3f, -1.5f);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}


void drawChessBoard() {
	_displayListId_blackArea = glGenLists(1);
	glNewList(_displayListId_blackArea, GL_COMPILE); 
	draw_BlackArea(); 
	glEndList();

	_displayListId_whiteArea = glGenLists(2);
	glNewList(_displayListId_whiteArea, GL_COMPILE);
	draw_WhiteArea(); 
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

