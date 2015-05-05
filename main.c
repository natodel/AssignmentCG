#include <GL/glut.h>
#include<stdio.h>
#include "pieces.h"
float angle= 0;
float i;
int k=0;
int m,n;
GLuint displayList_blackArea;
GLuint displayList_whiteArea;
int whitepawn[][2]={{1,0},{1,1},{1,2},{1,3},{1,4},{1,5},{1,6},{1,7}};
int whitepowers[][3]={{0,0,1},{0,1,2},{0,2,3},{0,3,4},{0,4,5},{0,5,3},{0,6,2},{0,7,1}};
int blackpawn[][2]={{6,0},{6,1},{6,2},{6,3},{6,4},{6,5},{6,6},{6,7}};
int blackpowers[][3]={{7,0,1},{7,1,2},{7,2,3},{7,3,4},{7,4,5},{7,5,3},{7,6,2},{7,7,1}};
void Keypress(unsigned char key,int x,int y)
{
	switch(key)
	{
		case 27:
			exit(0);
	}
}
void myReshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(double)w/(double)h,1.0,200);
	gluLookAt(0.0f, 5.5f, 15.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);
}
void draw_BlackArea()
{
glBegin(GL_QUADS);
		glColor3f(0.05f,0.05f,0.05f);
		glTranslatef(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(1.50f,0.0f,0.0f);
		glVertex3f(1.5f,0.3f,0.0f);
		glVertex3f(0.0f,0.3f,0.0f);
	glEnd();
	glBegin(GL_QUADS);
		glColor3f(0.05f,0.05f,0.05f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,-1.5f);
		glVertex3f(0.0f,0.3f,-1.5f);
		glVertex3f(0.0f,0.3f,0.0f);
	glEnd();
	glBegin(GL_QUADS);
		glColor3f(0.05f,0.05f,0.05f);
		glVertex3f(1.5f,0.0f,0.0f);
		glVertex3f(1.5f,0.0f,-1.5f);
		glVertex3f(1.5f,0.3f,-1.5f);
		glVertex3f(1.5f,0.3f,0.0f);
	glEnd();
	glBegin(GL_QUADS);
		glColor3f(0.05f,0.05f,0.05f);
		glVertex3f(0.0f,0.0f,-1.5f);
		glVertex3f(1.50f,0.0f,-1.5f);
		glVertex3f(1.5f,0.3f,-1.5f);
		glVertex3f(0.0f,0.3f,-1.5f);
	glEnd();
	glBegin(GL_QUADS);
		glColor3f(0.05f,0.05f,0.05f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(1.50f,0.0f,0.0f);
		glVertex3f(1.5f,0.0f,-1.5f);
		glVertex3f(0.0f,0.0f,-1.5f);
	glEnd();
	glBegin(GL_QUADS);
		glColor3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.3f,0.0f);
		glVertex3f(1.50f,0.3f,0.0f);
		glVertex3f(1.5f,0.3f,-1.5f);
		glVertex3f(0.0f,0.3f,-1.5f);
	glEnd();
}
void draw_WhiteArea()
{
	glBegin(GL_QUADS);
		glColor3f(0.05f,0.05f,0.05f);
		glTranslatef(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(1.50f,0.0f,0.0f);
		glVertex3f(1.5f,0.3f,0.0f);
		glVertex3f(0.0f,0.3f,0.0f);
	glEnd();
	glBegin(GL_QUADS);
		glColor3f(0.05f,0.05f,0.05f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,-1.5f);
		glVertex3f(0.0f,0.3f,-1.5f);
		glVertex3f(0.0f,0.3f,0.0f);
	glEnd();
	glBegin(GL_QUADS);
		glColor3f(0.05f,0.05f,0.05f);
		glVertex3f(1.5f,0.0f,0.0f);
		glVertex3f(1.5f,0.0f,-1.5f);
		glVertex3f(1.5f,0.3f,-1.5f);
		glVertex3f(1.5f,0.3f,0.0f);
	glEnd();
	glBegin(GL_QUADS);
		glColor3f(0.05f,0.05f,0.05f);
		glVertex3f(0.0f,0.0f,-1.5f);
		glVertex3f(1.50f,0.0f,-1.5f);
		glVertex3f(1.5f,0.3f,-1.5f);
		glVertex3f(0.0f,0.3f,-1.5f);
	glEnd();
	glBegin(GL_QUADS);
		glColor3f(0.05f,0.05f,0.05f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(1.50f,0.0f,0.0f);
		glVertex3f(1.5f,0.0f,-1.5f);
		glVertex3f(0.0f,0.0f,-1.5f);
	glEnd();
	glBegin(GL_QUADS);
		glColor3f(0.52f,0.37f,0.26f);
		glVertex3f(0.0f,0.3f,0.0f);
		glVertex3f(1.50f,0.3f,0.0f);
		glVertex3f(1.5f,0.3f,-1.5f);
		glVertex3f(0.0f,0.3f,-1.5f);
	glEnd();
}
void myinit()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.0f,0.0f,0.2f,1.0f);
	displayList_blackArea = glGenLists(1);
	glNewList(displayList_blackArea, GL_COMPILE);
	draw_BlackArea();
	glEndList();
	displayList_whiteArea = glGenLists(2);
	glNewList(displayList_whiteArea, GL_COMPILE);
	draw_WhiteArea();
	glEndList();
}
void drawScene()
{
	float j;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(-angle, 0.0f, 1.0f, 0.0f);
	glTranslatef(-4*1.5, 0.0, 4*1.5);
	for(j=0.0;j>(-8*1.5);j-=1.5)
	{
		k++;
		for(i=0.0;i<(4*3.0);i+=3.0)
		{
			if(k%2==0)
			{
				glPushMatrix();
				glTranslatef(i,0.0,j);
				glCallList(displayList_blackArea);
				glPopMatrix();
			}
			else
			{
				glPushMatrix();
				glTranslatef(i+1.5,0.0,j);
				glCallList(displayList_blackArea);
				glPopMatrix();
			}
		}
	}
	for(j=0.0;j>(-8*1.5);j-=1.5)
	{
		k++;
		for(i=0.0;i<(4*3.0);i+=3.0)
		{
			if(k%2!=0)
			{
				glPushMatrix();
				glTranslatef(i,0.0,j);
				glCallList(displayList_whiteArea);
				glPopMatrix();
			}
			else
			{
				glPushMatrix();
				glTranslatef(i+1.5,0.0,j);
				glCallList(displayList_whiteArea);
				glPopMatrix();
			}
		}
	}
	PawnDisplay();
	glutSwapBuffers();
}


void update(int value)
{
	angle += 0.5f;
	if (angle > 360)
	{
		angle -= 360;
	}
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Chess Board");
	myinit();
	PiecesInit();
	glutFullScreen();
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(Keypress);
	glutReshapeFunc(myReshape);
	//glutTimerFunc(25, update, 0);
	glutMainLoop();
	return 0;
}





