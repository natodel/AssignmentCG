
#include<windows.h>
#include <fstream>
#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "board.h"
#include <math.h>
#include<set>
#include "chessman.h"

using namespace std;

enum chessType {
	KING,
	QUEEN,
	BISHOP,
	KNIGHT,
	ROOK,
	PAWN
};

int mouseButton;
int oldX, newX, oldY, newY;
bool rotateAxisX = false;
float rotateAngle = 0.0;
float depth;


//
bool isEmpty[8][8]; // THIS WILL MARK THE STATE OF EACH PIECE ON CHESSBOARD, IF IT CONTAIN THE CHESSPIECE, WILL BE RECEIVE FALSE VALUE
bool isSelected; // TRUE IF ONE CHESSPIECE IS SELECTED - FALSE IF NO CHESSPIECE IS SELECTED.
bool blackPawnFirstMove[8]; // TRUE FOR FIRST MOVEMENT OF THE PAWN
bool whitePawnFirstMove[8]; //....

/*DECLARE THE ARRAY WHICH CONTAIN THE MOVEABLE POSITION OF EACH CHESSPIECE*/
set<int> moveablePos;

float width = 800, height = 600;

float _angle = 0;

GLuint _displayListId_blackArea;
GLuint _displayListId_whiteArea;

GLfloat ambientLightA[4] = { 0.2f, 0.2f, 0.2f, 1.0f }; 
GLfloat diffuseLightA[4] = { 0.8f, 0.8f, 0.8f, 1.0f };

GLfloat ambientLightB[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat diffuseLightB[4] = { 0.8f, 0.8f, 0.8f, 1.0f };

GLfloat specularLightA[4] = { 0.3f, 0.3f, 0.3f, 1.0f };
GLfloat specularLightB[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

GLfloat lightPositionA[4] = { 1.0, 2.0, 2.0, 0.0 };
GLfloat lightPositionB[4] = { 1.0, -5.0, -5.0, 0.0 };

GLfloat color1[4] = {0.1f, 0.1f, 0.1f, 1.0f};
GLfloat color2[4] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat color_selected_pawn[4] = {0.05f, 0.05f, 0.08f, 1.0};
GLfloat color_dark[4] = {0.1f, 0.1f, 0.2f, 1.0f};
GLfloat color_clear[4] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat color_seleted_board[4] = {0.0f, 0.0f, 1.0f, 0.2f};
GLfloat color_highlighted[4] = {1.0f, 0.0f, 0.0f, 0.5f};
GLfloat color_specular[4] = {1.0f, 1.0f, 1.0f, 1.0f};

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
	gluLookAt(7.0f, 20.0f, -7.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

//	glutPostRedisplay();
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

void updateChessBoard() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i == 0 || i == 1 || i == 6 || i == 7) {
				isEmpty[i][j] = false;
			} else {
				isEmpty[i][j] = true;
			}
		}
	}
}

void init() {
	initReadfile();
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
	
	//Need to check
	updateChessBoard();
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
	
	glTranslatef(-4*1.5, 0.0, 4*1.5);
	
	glPushMatrix();
//	glTranslatef(0, 3, 0);
	blackChessmen();
	whiteChessmen();
	glPopMatrix();
	
	glEnable(GL_STENCIL_TEST); //Enable using the stencil buffer
	glColorMask(0, 0, 0, 0); //Disable drawing colors to the screen
	glDisable(GL_DEPTH_TEST); //Disable depth testing
	glStencilFunc(GL_ALWAYS, 1, 1); //Make the stencil test always pass
	
	//Make pixels in the stencil buffer be set to 1 when the stencil test passes
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	
	drawChessBoard();
	
	glColorMask(1, 1, 1, 1); //Enable drawing colors to the screen
	glEnable(GL_DEPTH_TEST); //Enable depth testing
	
	//Make the stencil test pass only when the pixel is 1 in the stencil buffer
	glStencilFunc(GL_EQUAL, 1, 1);
	
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //Make the stencil buffer not change
	
	//buffer is 1
	glPushMatrix();
	glScalef(1, -1, 1);
//	glTranslatef(0, 3, 0);
	blackChessmen();
	whiteChessmen();
	glPopMatrix();
	
	glDisable(GL_STENCIL_TEST); //Disable using the stencil buffer
	 
	//Blend the floor onto the screen
	
	
	drawChessBoard();
	glDisable(GL_BLEND);
	
	glBegin(GL_LINE_STRIP);
	glColor3f(1, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(5, 1, 0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 5, 0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0, 0, 1);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 1, 5);
	glEnd();
	
	glutSwapBuffers();
}

void update() {
	glutPostRedisplay();

//	glutTimerFunc(25, update, 0);
}

int getIndexFromPosition(GLdouble x) {
	
	float value = fabs(x);
	
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
	switch(button) {
		case GLUT_LEFT_BUTTON:
			
			if (state == GLUT_DOWN) {
				oldX = x;
				oldY = y;
			}
			GetOGLPos(oldX, oldY);

			if((0 < posX) && (posX < 1.5f) && (-1.5f < posZ) && (posZ < 0)){
				blackRookY = 1.5;
				glutPostRedisplay();
			}
			
			cout << "Index = " << getIndexFromPosition(posX) << ""  << getIndexFromPosition(posZ) <<endl;
			
			if (isEmpty[getIndexFromPosition(posX)][getIndexFromPosition(posZ)] == true) {
				cout << "is empty" << endl;
				
			} else {
				cout << "NOT empty" << endl;
				// NEED TO BE IMPLEMENTED - LIGHT CURRENT PIECE AND THE PIECE WHICH THE CURRENT CHESSPIECE CAN MOVE
			}
			
			break;
		case GLUT_RIGHT_BUTTON:
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
	}	
}

void calculatePossibleMove(chessType piece, int currentIndex) {
	moveablePos.clear();
	
	if (piece == KING) {
		
	} else if (piece == QUEEN) {
		
	} else if (piece == BISHOP) {
		
	} else if (piece == KNIGHT) {
		
	} else if (piece == ROOK) {
		
	} else if (piece == PAWN) {
		
	}
}

void SpecialFuncKey(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT:
			rotateAngle -= 20 * 0.11;
			rotateAxisX = false;
			break;
		case GLUT_KEY_RIGHT:
			rotateAngle += 20 * 0.11;
			rotateAxisX = false;
			break;
	}
	update();
}

int main(int argc, char** argv) {
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize (800, 600);
	glutInitWindowPosition (100,100);
	glutCreateWindow("basic shape");
	init();
	
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutMouseFunc(mouseEvent);
	glutSpecialFunc(SpecialFuncKey);
	
	
	glutMainLoop();

	return 0;
}
