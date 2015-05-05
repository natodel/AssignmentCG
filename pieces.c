#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "pieces.h"
GLuint startList;
int moving,startx,starty;
GLfloat angle1,angle2;
void errorCallback(GLenum errorCode)
{
   const GLubyte *estring;
   estring = gluErrorString(errorCode);
   fprintf(stderr, "Quadric Error: %s\n", estring);
   exit(0);
}
void PiecesInit(void)
{
    GLUquadricObj *qobj;
    GLfloat mat_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat model_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    startList = glGenLists(6);
    qobj = gluNewQuadric();
    gluQuadricCallback(qobj, GLU_ERROR, errorCallback);

/* To create  Pawns: */

    gluQuadricDrawStyle(qobj, GLU_FILL); // smooth shaded
    gluQuadricNormals(qobj, GLU_SMOOTH);
    glNewList(startList, GL_COMPILE);
    glPushMatrix();
    gluCylinder(qobj, 0.6, 0.2, 0.8, 15, 5); // Bottom
    glTranslatef(0,0,0.8);
    gluSphere(qobj, 0.35, 15, 10); // Middle
    glTranslatef(0,0,0.3);
    gluSphere(qobj, 0.15, 15, 10); // Top
    glPopMatrix();
    glEndList();

/* To create Elephant: */

    gluQuadricDrawStyle(qobj, GLU_FILL); // flat shaded
    gluQuadricNormals(qobj, GLU_SMOOTH);
    glNewList(startList+1, GL_COMPILE);
    glPushMatrix();
    gluDisk(qobj, 0, 0.6, 20, 4);
    gluCylinder(qobj, 0.6, 0.6, 0.5, 15, 5);
    glTranslatef(0,0,0.5);
    gluDisk(qobj, 0, 0.6, 20, 4);
    gluCylinder(qobj, 0.3, 0.3, 0.6, 15, 5);
    glTranslatef(0,0,0.6);
    gluDisk(qobj, 0, 0.6, 20, 4);
    gluCylinder(qobj, 0.6, 0.6, 0.5, 15, 5);
    glTranslatef(0,0,0.5);
    gluDisk(qobj, 0, 0.6, 20, 4);
    glPopMatrix();
    glEndList();

/* To create Knight: */

    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricNormals(qobj, GLU_SMOOTH);
    glNewList(startList+2, GL_COMPILE);
    glPushMatrix();
    gluDisk(qobj, 0, 0.6, 20, 4);
    gluCylinder(qobj, 0.6, 0.4, 0.3, 15, 5);
    glTranslatef(0,0,0.3);
    glRotatef(-20,1,0,0);
    gluCylinder(qobj, 0.4, 0.4, 0.5, 15, 5);
    glTranslatef(0,0.1,0.5);
    glRotatef(40,1,0,0);
    gluCylinder(qobj, 0.4, 0.4, 0.4, 15, 5);
    glTranslatef(0,-0.2,0.4);
    glRotatef(-40,1,0,0);
    gluCylinder(qobj, 0.4, 0.4, 0.4, 15, 5);
    glTranslatef(0,0.2,0.4);
    glRotatef(-100,1,0,0);
    glutSolidCone(0.4,0.5,15,4);
    glPopMatrix();
    glEndList();

/* To create Bishop: */

    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricNormals(qobj, GLU_SMOOTH);
    glNewList(startList+3, GL_COMPILE);
    glPushMatrix();
    gluCylinder(qobj, 0.6, 0.3, 0.3, 15, 5);
    glTranslatef(0,0,0.3);
    gluCylinder(qobj, 0.3, 0.25, 1.0, 15, 5);
    glTranslatef(0,0,1.2);
    gluSphere(qobj, 0.35, 15, 10);
    glTranslatef(0,0,0.3);
    gluSphere(qobj, 0.15, 15, 10);
    glPopMatrix();
    glEndList();

/* To create Queen: */

    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricNormals(qobj, GLU_SMOOTH);
    glNewList(startList+4, GL_COMPILE);
    glPushMatrix();
gluCylinder(qobj, 0.6, 0.5, 0.4, 15, 5);
    gluDisk(qobj, 0, 0.6, 20, 4);
    glTranslatef(0,0,0.4);
    gluCylinder(qobj, 0.5, 0.3, 0.4, 15, 5);
    glTranslatef(0,0,0.4);
    gluCylinder(qobj, 0.3, 0.5, 0.4, 15, 5);
    glTranslatef(0,0,0.4);
    gluCylinder(qobj, 0.5, 0.5, 0.4, 15, 5);
    glTranslatef(0,0,0.4);
    gluCylinder(qobj, 0.5, 0.7, 0.4, 15, 5);
    gluDisk(qobj, 0, 0.5, 20, 4);
    glPopMatrix();
    glEndList();

/* To create King: */

    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricNormals(qobj, GLU_SMOOTH);
    glNewList(startList+5, GL_COMPILE);
    glPushMatrix();
    gluDisk(qobj, 0, 0.6, 20, 4);
    gluCylinder(qobj, 0.6, 0.55, 0.4, 15, 5);
    glTranslatef(0,0,0.4);
    gluCylinder(qobj, 0.55, 0.4, 0.3, 15, 5);
    glTranslatef(0,0,0.3);
    gluCylinder(qobj, 0.4, 0.4, 0.4, 15, 5);
    glTranslatef(0,0,0.4);
    gluCylinder(qobj, 0.4, 0.5, 0.4, 15, 5);
    glTranslatef(0,0,0.4);
    gluCylinder(qobj, 0.5, 0.5, 0.4, 15, 5);
    glTranslatef(0,0,0.4);
    gluDisk(qobj, 0, 0.5, 20, 4);
    glutSolidCone(0.3,0.5,15,4);
    glTranslatef(0,0,0.5);
    glRotatef(180,1,0,0);
    glutSolidCone(0.3,0.5,15,4);
    glPopMatrix();
    glEndList();
}
void PawnDisplay(void)
{
	int i,j;

	/* To create White Pawns:  */

	glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glRotatef(-90,1,0,0);
    glTranslatef(0.75,0.75,0.3);
    for(i=0;i<=7;i++)
    {
	glPushMatrix();
	glEnable(GL_LIGHTING);
	glShadeModel (GL_SMOOTH);
	glTranslatef(whitepawn[i][0]*1.5,whitepawn[i][1]*1.5, 0);
	glCallList(startList);
	glPopMatrix();
    }

    /* To create Black Pawns:  */

    glColor3f(1.0, 0.0, 0.0);
    for(i=0;i<=7;i++)
    {
	glPushMatrix();
	glEnable(GL_LIGHTING);
        glShadeModel (GL_SMOOTH);
        glTranslatef(blackpawn[i][0]*1.5,blackpawn[i][1]*1.5, 0);
        glCallList(startList);
        glPopMatrix();
    }

    // To create Powers:

    glColor3f(1.0, 1.0, 1.0);
    for(i=0;i<=7;i++)
    {
        glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glEnable(GL_LIGHTING);
        glShadeModel (GL_SMOOTH);
        glTranslatef(whitepowers[i][0]*1.5,whitepowers[i][1]*1.5, 0);
        glCallList(startList+whitepowers[i][2]);
        glPopMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glPushMatrix();
        glEnable(GL_LIGHTING);
        glShadeModel (GL_SMOOTH);
        glTranslatef(blackpowers[i][0]*1.5,blackpowers[i][1]*1.5, 0);
        glCallList(startList+blackpowers[i][2]);
        glPopMatrix();
    }
    glPopMatrix();
}

