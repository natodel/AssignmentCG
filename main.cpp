
#include<windows.h>
#include <fstream>
#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>

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


//vector<GLdoublePoint> vertice;
//vector<GLdoublePoint> normal;
//vector<GLPolygon> polygon;


vector<GLdoublePoint> vertice[7];
vector<GLdoublePoint> normal[7];
vector<GLPolygon> polygon[7];
int nPolArr[6];

int nVer, nPol, nNorm;

int camX = 3;
int camY = 0;
int camZ = 0;
int lookX = 0;
int lookY = 0;
int lookZ = 0;
int upX = 0;
int upY = 1;
int upZ = 0;
int angle;
int angle2;
/* -- LOCAL VARIABLES ---------------------------------------------------- */

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

void createChessman(string name) {
	
	int index = getIndex(name);
//int index = 5;
	
	glPushMatrix();
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
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	
	glTranslatef(0.75, 0.3, -0.75);
	createChessman("rook.obj");
	glTranslatef(0.0, 0.0, -1.5);
	glPushMatrix();
	
	glRotated(90, 0, 1,0);
	createChessman("knight.obj");
	glPopMatrix();
	
	glTranslatef(0.0, 0.0, -1.5);
	createChessman("bishop.obj");
	glTranslatef(0.0, 0.0, -1.5);
	createChessman("king.obj");
	glTranslatef(0.0, 0.0, -1.5);
	createChessman("queen.obj");
	glTranslatef(0.0, 0.0, -1.5);
	createChessman("bishop.obj");
	glTranslatef(0.0, 0.0, -1.5);
	
	glPushMatrix();
	glRotated(90, 0, 1,0);
	createChessman("knight.obj");
	glPopMatrix();
	
	glTranslatef(0.0, 0.0, -1.5);
	createChessman("rook.obj");
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(2.25, 0.3, -0.75);
	createChessman("pawn.obj");
	for (int i = 0; i < 7; i++){
		glTranslatef(0, 0, -1.5);
		createChessman("pawn.obj");
	}
	glPopMatrix();
}

void whiteChessmen(){
	glColor3f(0.5, 0.5, 0.3);
	
	glPushMatrix();
	
	glTranslatef(0.75 + 1.5 * 7, 0.3, -0.75);
	createChessman("rook.obj");
	glTranslatef(0.0, 0.0, -1.5);
	
	glPushMatrix();
	glRotated(-90, 0, 1,0);
	createChessman("knight.obj");
	glPopMatrix();
	
	glTranslatef(0.0, 0.0, -1.5);
	createChessman("bishop.obj");
	glTranslatef(0.0, 0.0, -1.5);
	createChessman("king.obj");
	glTranslatef(0.0, 0.0, -1.5);
	createChessman("queen.obj");
	glTranslatef(0.0, 0.0, -1.5);
	createChessman("bishop.obj");
	glTranslatef(0.0, 0.0, -1.5);
	
	glPushMatrix();
	glRotated(-90, 0, 1,0);
	createChessman("knight.obj");
	glPopMatrix();
	
	glTranslatef(0.0, 0.0, -1.5);
	createChessman("rook.obj");
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.75 + 1.5 * 6, 0.3, -0.75);
	createChessman("pawn.obj");
	for (int i = 0; i < 7; i++){
		glTranslatef(0, 0, -1.5);
		createChessman("pawn.obj");
	}
	glPopMatrix();
}

void PiecesInit(void) {
	GLfloat mat_ambient[] = { 0, 0.5, 1, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position0[] = { 1.0, 2.0, 2.0, 0.0 };
	GLfloat light_position1[] = { 1.0, 2.0, -25.0, 0.0 };
	GLfloat model_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat red[] = { 1.0, 0.3, 0.0 };
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat blue[] = { 0.0, 0.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, red);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, red);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, red);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, red);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);

	blackChessmen();
	whiteChessmen();
}




float _angle = 0;
float i;
int k = 0;
GLuint _displayListId_blackArea; //The OpenGL id of the display list
GLuint _displayListId_whiteArea; //The OpenGL id of the display list

void handleKeypress(unsigned char key, int x, int y)
{

	switch (key)
	{
	case 27:
		exit(0);
	}

}



void handleResize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200);
	gluLookAt(7.0f, 20.0f, -7.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}



void draw_BlackArea()
{

	// glPushMatrix();

	//glTranslatef(1.5f,0.0f,0.0f);

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

void draw_whiteArea()

{

	// glPushMatrix();

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

	// glPopMatrix();



}



void initRendering()

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

void drawScene()

{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

//	gluLookAt(0.0, 1.0, 0.0, 0.0, 0.0, -2.0, 0.0, 1.0, 0.0);
	
	depth -= 0.003f;
	
	
	if (rotateAxisX == true) {
		glRotatef(rotateAngle, 1.0f, 0.0f, 0.0f);
	} else {
		glRotatef(rotateAngle, 0.0f, 1.0f, 0.0f);
	}
	
	glTranslatef(-4*1.5, 0.0, 4*1.5);



	for (float j = 0.0; j>(-8 * 1.5); j -= 1.5)

	{

		k++;

		for (i = 0.0; i<(4 * 3.0); i += 3.0)

		{

			if (k % 2 == 0)

			{

				glPushMatrix();

				glTranslatef(i, 0.0, j);

				glCallList(_displayListId_blackArea);

				glPopMatrix();

			}

			else

			{

				glPushMatrix();

				glTranslatef(i + 1.5, 0.0, j);

				glCallList(_displayListId_blackArea);

				glPopMatrix();

			}

		}

	}

	for (float j = 0.0; j>(-8 * 1.5); j -= 1.5)

	{

		k++;

		for (i = 0.0; i<(4 * 3.0); i += 3.0)

		{

			if (k % 2 != 0)

			{

				glPushMatrix();

				glTranslatef(i, 0.0, j);

				glCallList(_displayListId_whiteArea);

				glPopMatrix();
			}

			else
			{
				glPushMatrix();

				glTranslatef(i + 1.5, 0.0, j);

				glCallList(_displayListId_whiteArea);

				glPopMatrix();
			}

		}

	}
	glBegin(GL_LINE_STRIP);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(5, 0, 0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 5, 0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 5);
	glEnd();

	PiecesInit();
	glutSwapBuffers();
	glutPostRedisplay();
}

void update(int value) {
	_angle += 1.0f;

	if (_angle > 360) {
		_angle -= 360;
	}

	glutPostRedisplay();

	glutTimerFunc(25, update, 0);
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

int main(int argc, char** argv)
{
	
	readfile("rook.obj");
	readfile("bishop.obj");
	readfile("king.obj");
	readfile("knight.obj");
	readfile("pawn.obj");
	readfile("queen.obj");
	
	
	glutInit(&argc, argv);
	

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(800, 600);

	glutCreateWindow("basic shape");

	

	initRendering();

//	glutFullScreen();
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	//	glutTimerFunc(25, update, 0);
	glutMouseFunc(mouseEvent);
	glutMotionFunc(mouseMotion);
	
	glutMainLoop();

	return 0;
}
