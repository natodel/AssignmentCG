
#include<windows.h>
#include <fstream>
#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "board.h"
using namespace std;

class GLdoublePoint {
public:
	double x, y, z;

	GLdoublePoint(double a, double b, double c){
		x = a; y = b; z = c;
	}
};

class GLPolygon {
public:
	int idxVer1, idxVer2, idxVer3;
	int normal1, normal2, normal3;

	GLPolygon(int x, int y, int z, int a, int b, int c) {
		idxVer1 = x; idxVer2 = y; idxVer3 = z;
		normal1 = a; normal2 = b; normal3 = c;
	}
};

int mouseButton;
int oldX, newX, oldY, newY;
bool rotateAxisX = false;
float rotateAngle = 0.0;
float depth;

vector<GLdoublePoint> vertice[7];
vector<GLdoublePoint> normal[7];
vector<GLPolygon> polygon[7];
int nPolArr[6];
int nVer, nPol, nNorm;

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

int getIndex(string name) {
	if (name == "king.obj") {
		return 0;
	} else if (name == "queen.obj") {
		return 1;
	} else if (name == "bishop.obj") {
		return 2;
	} else if (name == "knight.obj") {
		return 3;
	} else if (name == "rook.obj") {
		return 4;
	} else if (name == "pawn.obj") {
		return 5;
	}
}

void readfile(string name) {
	double point_x, point_y, point_z;
	int idx1, idx2, idx3;
	int nor1, nor2, nor3;
	int index = getIndex(name);


	ifstream f_in;
	f_in.open(name.c_str());

	f_in >> nVer; f_in >> nNorm; f_in >> nPol;
	nPolArr[index] = nPol;
	for (int i = 0; i < nVer; i++) {
		f_in >> point_x >> point_y >> point_z;
		GLdoublePoint point(point_x, point_y, point_z);
		vertice[index].push_back(point);
	}

	for (int i = 0; i < nNorm; i++) {
		f_in >> point_x >> point_y >> point_z;
		GLdoublePoint point(point_x, point_y, point_z);
		normal[index].push_back(point);
	}

	for (int i = 0; i < nPol; i++) {
		f_in >> idx1 >> nor1 >> idx2 >> nor2 >> idx3 >> nor3;
		GLPolygon pol(idx1, idx2, idx3, nor1, nor2, nor3);
		polygon[index].push_back(pol);
	}
}

void createChessman(string name, int color) {
	int index = getIndex(name);
	
	glPushMatrix();
	if(color == 0) {
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 2.0f);	
		
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		glColor3f(0.1f, 0.1f, 0.1f);
		glColorMaterial(GL_FRONT, GL_SPECULAR);
		glColor3f(0.1f, 0.1f, 0.1f);
	}
	else if(color == 1) {
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 4.0f);
		
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		glColor3f(1.0f, 1.0f, 1.0f);
		glColorMaterial(GL_FRONT, GL_SPECULAR);
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	for (int i = 0; i < nPolArr[index]; i++) {
		glBegin(GL_POLYGON);
		glNormal3d(normal[index][polygon[index][i].normal1 - 1].x, normal[index][polygon[index][i].normal1 - 1].y, normal[index][polygon[index][i].normal1 - 1].z);
		glVertex3d(vertice[index][polygon[index][i].idxVer1 - 1].x, vertice[index][polygon[index][i].idxVer1 - 1].y, vertice[index][polygon[index][i].idxVer1 - 1].z);
		glNormal3d(normal[index][polygon[index][i].normal2 - 1].x, normal[index][polygon[index][i].normal2 - 1].y, normal[index][polygon[index][i].normal2 - 1].z);
		glVertex3d(vertice[index][polygon[index][i].idxVer2 - 1].x, vertice[index][polygon[index][i].idxVer2 - 1].y, vertice[index][polygon[index][i].idxVer2 - 1].z);
		glNormal3d(normal[index][polygon[index][i].normal3 - 1].x, normal[index][polygon[index][i].normal3 - 1].y, normal[index][polygon[index][i].normal3 - 1].z);
		glVertex3d(vertice[index][polygon[index][i].idxVer3 - 1].x, vertice[index][polygon[index][i].idxVer3 - 1].y, vertice[index][polygon[index][i].idxVer3 - 1].z);
		glEnd();
	}
	glPopMatrix();

}

void blackChessmen(){
	glPushMatrix();
	
	glTranslatef(0.75, 0.3, -0.75);
	createChessman("rook.obj", 0);
	glTranslatef(0.0, 0.0, -1.5);
	glPushMatrix();
	
	glRotated(90, 0, 1,0);
	createChessman("knight.obj", 0);
	glPopMatrix();
	
	glTranslatef(0.0, 0.0, -1.5);
	createChessman("bishop.obj", 0);
	glTranslatef(0.0, 0.0, -1.5);
	createChessman("king.obj", 0);
	glTranslatef(0.0, 0.0, -1.5);
	createChessman("queen.obj", 0);
	glTranslatef(0.0, 0.0, -1.5);
	createChessman("bishop.obj", 0);
	glTranslatef(0.0, 0.0, -1.5);
	
	glPushMatrix();
	glRotated(90, 0, 1,0);
	createChessman("knight.obj", 0);
	glPopMatrix();
	
	glTranslatef(0.0, 0.0, -1.5);
	createChessman("rook.obj", 0);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(2.25, 0.3, -0.75);
	createChessman("pawn.obj", 0);
	for (int i = 0; i < 7; i++){
		glTranslatef(0, 0, -1.5);
		createChessman("pawn.obj", 0);
	}
	glPopMatrix();
}

void whiteChessmen(){
	glPushMatrix();
	
	glTranslatef(0.75 + 1.5 * 7, 0.3, -0.75);
	createChessman("rook.obj", 1);
	glTranslatef(0.0, 0.0, -1.5);
	
	glPushMatrix();
	glRotated(-90, 0, 1,0);
	createChessman("knight.obj", 1);
	glPopMatrix();
	
	glTranslatef(0.0, 0.0, -1.5);
	createChessman("bishop.obj", 1);
	glTranslatef(0.0, 0.0, -1.5);
	createChessman("king.obj", 1);
	glTranslatef(0.0, 0.0, -1.5);
	createChessman("queen.obj", 1);
	glTranslatef(0.0, 0.0, -1.5);
	createChessman("bishop.obj", 1);
	glTranslatef(0.0, 0.0, -1.5);
	
	glPushMatrix();
	glRotated(-90, 0, 1,0);
	createChessman("knight.obj", 1);
	glPopMatrix();
	
	glTranslatef(0.0, 0.0, -1.5);
	createChessman("rook.obj", 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.75 + 1.5 * 6, 0.3, -0.75);
	createChessman("pawn.obj", 1);
	for (int i = 0; i < 7; i++){
		glTranslatef(0, 0, -1.5);
		createChessman("pawn.obj", 1);
	}
	glPopMatrix();
}

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
}


void init() {
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
	
	glutSwapBuffers();
}

void update() {
	glutPostRedisplay();

//	glutTimerFunc(25, update, 0);
}

void mouseEvent(int button, int state, int x, int y) 
{
	mouseButton = button;
	switch(button) {
		case GLUT_LEFT_BUTTON:
			cout << "left btn";
			if (state == GLUT_DOWN) {
				oldX = x;
				oldY = y;
			}
			break;
		case GLUT_RIGHT_BUTTON:
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
	}	
}

void mouseMotion(int x, int y)
{
	if (mouseButton == GLUT_LEFT_BUTTON) {
		if (abs(x - oldX) > 0 && abs(x - oldX) > abs(y - oldY)) {
			if ((x - oldX) > 0) {
				rotateAngle += 10.0 * 0.11;
			} else {
				rotateAngle -= 10.0 * 0.11;
			}
			
			rotateAxisX = false;
		} else if (abs(y - oldY) > 0 && abs(y - oldY) > abs(x - oldX)) {
			if ((y - oldY) > 0) {
				rotateAngle += 10.0 * 0.11;
			} else {
				rotateAngle -= 100 * 0.11;
			}
			rotateAxisX = true;
		}
		oldX = x;
		oldY = y;
	}
}

void SpecialFuncKey(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP:
			rotateAngle += 20 * 0.11;
			rotateAxisX = true;
			break;
		case GLUT_KEY_DOWN:
			rotateAngle -= 20 * 0.11;
			rotateAxisX = true;
			break;
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
	readfile("rook.obj");
	readfile("bishop.obj");
	readfile("king.obj");
	readfile("knight.obj");
	readfile("pawn.obj");
	readfile("queen.obj");
	
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
	glutMotionFunc(mouseMotion);
	glutSpecialFunc(SpecialFuncKey);
	
	
	glutMainLoop();

	return 0;
}
