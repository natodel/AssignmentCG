#include<windows.h>
#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include "board.h"
#include "chessman.h"
#include "particle.h"

using namespace std;

Chessman* chessMan = new Chessman[33];

GLuint _displayListId_blackArea; //The OpenGL id of the display list
GLuint _displayListId_whiteArea; //The OpenGL id of the display list

int mouseButton;
int oldX, newX, oldY, newY;
bool rotateAxisX = false;
float rotateAngle = 0.0;
float depth;

bool choose = false;
int chooseID;
int player = 1;

float increaseX = 1.5, increaseZ = 1.5;
float WdeadX = -1.5, WdeadZ = 3;
float BdeadX = -1.5, BdeadZ = -13.5;

float width = 800, height = 600;

float _angle = 0;

GLfloat ambientLightA[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat diffuseLightA[4] = { 0.8f, 0.8f, 0.8f, 1.0f };

GLfloat ambientLightB[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat diffuseLightB[4] = { 0.8f, 0.8f, 0.8f, 1.0f };

GLfloat specularLightA[4] = { 0.3f, 0.3f, 0.3f, 1.0f };
GLfloat specularLightB[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

GLfloat lightPositionA[4] = { 1.0, 2.0, 2.0, 0.0 };
GLfloat lightPositionB[4] = { 1.0, -5.0, -5.0, 0.0 };

void handleKeypress(unsigned char key, int x, int y) {
	switch (key)
	{
		case 27:
			exit(0);
	}
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200);
	gluLookAt(7.0f, 30.0f, -7.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}

GLdouble posX = 0, posY = 0, posZ = 0;

void GetOGLPos(int x, int y)
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
 
    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
 
    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
}

void initChessMan()
{
	chessMan[0].setProfile(KING,   0,  0,  -6.0, 4, true, 0);
	chessMan[1].setProfile(QUEEN,  0,  0,  -4.5, 3, true, 0);
	chessMan[2].setProfile(BISHOP, 0,  0,  -3.0, 2, true, 0);
	chessMan[3].setProfile(BISHOP, 0,  0,  -7.5, 5, true, 0);
	chessMan[4].setProfile(KNIGHT, 0,  0,  -1.5, 1, true, 0);
	chessMan[5].setProfile(KNIGHT, 0,  0,  -9.0, 6, true, 0);
	chessMan[6].setProfile(ROOK,   0,  0,     0, 0, true, 0);
	chessMan[7].setProfile(ROOK,   0,  0, -10.5, 7, true, 0);
	chessMan[8].setProfile(PAWN,  1.5, 0,     0, 8, true, 0);
	chessMan[9].setProfile(PAWN,  1.5, 0,  -1.5, 9, true, 0);
	chessMan[10].setProfile(PAWN, 1.5, 0,  -3.0, 10, true, 0);
	chessMan[11].setProfile(PAWN, 1.5, 0,  -4.5, 11, true, 0);
	chessMan[12].setProfile(PAWN, 1.5, 0,  -6.0, 12, true, 0);
	chessMan[13].setProfile(PAWN, 1.5, 0,  -7.5, 13, true, 0);
	chessMan[14].setProfile(PAWN, 1.5, 0,  -9.0, 14, true, 0);
	chessMan[15].setProfile(PAWN, 1.5, 0, -10.5, 15, true, 0);
		
	chessMan[16].setProfile(KING,   1.5*7, 0,  -4.5, 59, true, 1);
	chessMan[17].setProfile(QUEEN,  1.5*7, 0,  -6.0, 60, true, 1);
	chessMan[18].setProfile(BISHOP, 1.5*7, 0,  -3.0, 58, true, 1);
	chessMan[19].setProfile(BISHOP, 1.5*7, 0,  -7.5, 61, true, 1);
	chessMan[20].setProfile(KNIGHT, 1.5*7, 0,  -1.5, 57, true, 1);
	chessMan[21].setProfile(KNIGHT, 1.5*7, 0,  -9.0, 62, true, 1);
	chessMan[22].setProfile(ROOK,   1.5*7, 0,     0, 56, true, 1);
	chessMan[23].setProfile(ROOK,   1.5*7, 0, -10.5, 63, true, 1);
	chessMan[24].setProfile(PAWN,   1.5*6, 0,     0, 48, true, 1);
	chessMan[25].setProfile(PAWN,   1.5*6, 0,  -1.5, 49, true, 1);
	chessMan[26].setProfile(PAWN,   1.5*6, 0,  -3.0, 50, true, 1);
	chessMan[27].setProfile(PAWN,   1.5*6, 0,  -4.5, 51, true, 1);
	chessMan[28].setProfile(PAWN,   1.5*6, 0,  -6.0, 52, true, 1);
	chessMan[29].setProfile(PAWN,   1.5*6, 0,  -7.5, 53, true, 1);
	chessMan[30].setProfile(PAWN,   1.5*6, 0,  -9.0, 54, true, 1);
	chessMan[31].setProfile(PAWN,   1.5*6, 0, -10.5, 55, true, 1);
}

void init() {
	initilization();
	initReadfile();
	initChessMan();
	glClearColor (0.8, 0.8, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLightA);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLightA);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLightA);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPositionA);
	
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLightB);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLightB);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLightB);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPositionB);
	
	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
	glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
	
	glEnable(GL_COLOR_MATERIAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void drawScene() {
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT  | GL_STENCIL_BUFFER_BIT);
	glShadeModel (GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	
	if (rotateAxisX == true) {
		glRotatef(rotateAngle, 1.0f, 0.0f, 0.0f);
	} else {
		glRotatef(rotateAngle, 0.0f, 1.0f, 0.0f);
	}
	cout<<"fuck"<<endl;
	glPushMatrix();
//	glTranslatef(0, 3, 0);
	glTranslatef(-4*1.5, 0.0, 4*1.5);
	drawChessmen();
	glPopMatrix();
	
	glEnable(GL_STENCIL_TEST); //Enable using the stencil buffer
	glColorMask(0, 0, 0, 0); //Disable drawing colors to the screen
	glDisable(GL_DEPTH_TEST); //Disable depth testing
	glStencilFunc(GL_ALWAYS, 1, 1); //Make the stencil test always pass
	
	//Make pixels in the stencil buffer be set to 1 when the stencil test passes
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	
	glPushMatrix();
	glTranslatef(-4*1.5, 0.0, 4*1.5);
	drawChessBoard();
	glPopMatrix();
	
	glColorMask(1, 1, 1, 1); //Enable drawing colors to the screen
	glEnable(GL_DEPTH_TEST); //Enable depth testing
	
	//Make the stencil test pass only when the pixel is 1 in the stencil buffer
	glStencilFunc(GL_EQUAL, 1, 1);
	
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //Make the stencil buffer not change
	
	//buffer is 1
	glPushMatrix();
	glScalef(1, -1, 1);
//	glTranslatef(0, 3, 0);
	glTranslatef(-4*1.5, 0.0, 4*1.5);
	drawChessmen();
	glPopMatrix();
	
	glDisable(GL_STENCIL_TEST); //Disable using the stencil buffer
	 
	//Blend the floor onto the screen
	
	displayParticle();
	glPushMatrix();
	glTranslatef(-4*1.5, 0.0, 4*1.5);
	drawChessBoard();
	
	glPopMatrix();
	
	glutSwapBuffers();
}

int get_selected_index(GLdouble x) {
	GLdouble value = fabs(x);
	if (value > 0 && value < 1.5) {
		return 0;
	} else if (value < 3) {
		return 1;
	} else if (value < 4.5) {
		return 2;
	} else if (value < 6) {
		return 3;
	} else if (value < 7.5) {
		return 4;
	} else if (value < 9) {
		return 5;
	} else if (value < 10.5) {
		return 6;
	} else if (value < 12) {
		return 7;
	}
	return 8;
}

void mouseEvent(int button, int state, int x, int y) 
{
	mouseButton = button;
	if(button == GLUT_LEFT_BUTTON and state == GLUT_DOWN)
	{
		oldX = x;
		oldY = y;
		GetOGLPos(oldX, oldY);
		int index = get_selected_index(posX) * 8 + get_selected_index(posZ);
		if (index >= 0 && index <= 63){
			if(!choose)
			{
				for(int i=0; i< 32; i++)
					if(chessMan[i].currIndex == index)
					{
						if(chessMan[i].side != player) return;
						chessMan[i].move_up();
						choose = true;
						chooseID = i;
						break;
					}
			}
			else
			{
				int i;
				bool existChessMan = false;
				for(i=0; i<32; i++)
					if(chessMan[i].currIndex == index)
					{
						existChessMan = true;
						break;
					}
				if (existChessMan)
				{
					if(i == chooseID)
					{
						chessMan[chooseID].move_down();
						choose = false;
						glutPostRedisplay();
						return;
					} 
					if (chessMan[i].side == chessMan[chooseID].side) return;
					
					if(chessMan[i].side == 0)
					{
						BdeadX += increaseX;
						if(BdeadX > 10.5){
							BdeadX = 0;
							BdeadZ -= increaseZ;	
						}	
						chessMan[i].destroy(BdeadX, BdeadZ);
					}
					if(chessMan[i].side == 1)
					{
						WdeadX += increaseX;
						if(WdeadX > 10.5){
							WdeadX = 0;
							WdeadZ += increaseZ;	
						}
						chessMan[i].destroy(WdeadX, WdeadZ);
					}
					glutPostRedisplay();
				}
				choose = false;
				chessMan[chooseID].currIndex = index;
				chessMan[chooseID].move(posX, posZ);
				chessMan[chooseID].move_down();
				player = abs(player-1);
			}
			glutPostRedisplay();
		}
	}
}

void SpecialFuncKey(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT:
			rotateAngle -= 20 * 0.11;
			rotateAxisX = false;
			glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT:
			rotateAngle += 20 * 0.11;
			rotateAxisX = false;
			glutPostRedisplay();
			break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize (800, 600);
	glutInitWindowPosition (100,100);
	glutCreateWindow("Chess");	
	init();
	//glutFullScreen();
	glutDisplayFunc(drawScene);
	glutIdleFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutMouseFunc(mouseEvent);
	glutSpecialFunc(SpecialFuncKey);
	glutMainLoop();
	return 0;
}
