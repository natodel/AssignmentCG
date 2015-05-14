
#include<windows.h>
#include <fstream>
#include <GL/glut.h>
#include <cstdlib>
#include <vector>
#include <iostream>
#include "chessman.h"

using namespace std;

class GLdoublePoint {
public:
	double x, y, z;
	
	GLdoublePoint() {
		x = 0; y = 0; z = 0;
	}
	GLdoublePoint(double a, double b, double c){
		x = a; y = b; z = c;
	}
};

class GLPolygon {
public:
	int idxVer1, idxVer2, idxVer3;
	int normal1, normal2, normal3;
	
	GLPolygon() {
		idxVer1 = 0; idxVer2 = 0; idxVer3 = 0;
		normal1 = 0; normal2 = 0; normal3 = 0;
	}

	GLPolygon(int x, int y, int z, int a, int b, int c) {
		idxVer1 = x; idxVer2 = y; idxVer3 = z;
		normal1 = a; normal2 = b; normal3 = c;
	}
};

string rook = "rook.obj";
string queen = "queen.obj";
string bishop = "bishop.obj";
string pawn = "pawn.obj";
string knight = "knight.obj";
string king = "king.obj";

vector<GLdoublePoint> vertice[7];
vector<GLdoublePoint> normal[7];
vector<GLPolygon> polygon[7];
int nPolArr[6];
int nVer, nPol, nNorm;

int getIndex(string name) {
	string n = name;
	
	if (name == king) {
		return 0;
	} else if (name == queen) {
		return 1;
	} else if (name == bishop) {
		return 2;
	} else if (name == knight) {
		return 3;
	} else if (name == rook) {
		return 4;
	} else if (name == pawn) {
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

void initReadfile() {
	readfile(rook);
	readfile(bishop);
	readfile(king);
	readfile(knight);
	readfile(pawn);
	readfile(queen);
}

void createChessman(string name, int color) {
	int index = getIndex(name);
	
	glPushMatrix();
	if(color == 0) {
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 2.0f);	
		
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		glColor3f(0.4f, 0.4f, 0.6f);
		glColorMaterial(GL_FRONT, GL_SPECULAR);
		glColor3f(1.0f, 1.0f, 1.0f);
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
	glPushMatrix();
	createChessman(rook, 0);
	glPopMatrix();
	glTranslatef(0.0, 0.0, -1.5);
	glPushMatrix();
	
	glRotated(90, 0, 1,0);
	createChessman(knight, 0);
	glPopMatrix();
	
	glTranslatef(0.0, 0.0, -1.5);
	createChessman(bishop, 0);
	glTranslatef(0.0, 0.0, -1.5);
	createChessman(king, 0);
	glTranslatef(0.0, 0.0, -1.5);
	createChessman(queen, 0);
	glTranslatef(0.0, 0.0, -1.5);
	createChessman(bishop, 0);
	glTranslatef(0.0, 0.0, -1.5);
	
	glPushMatrix();
	glRotated(90, 0, 1,0);
	createChessman(knight, 0);
	glPopMatrix();
	
	glTranslatef(0.0, 0.0, -1.5);
	createChessman(rook, 0);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(2.25, 0.3, -0.75);
	createChessman(pawn, 0);
	for (int i = 0; i < 7; i++){
		glTranslatef(0, 0, -1.5);
		createChessman(pawn, 0);
	}
	glPopMatrix();
}

void whiteChessmen(){
	glPushMatrix();
	
	glTranslatef(0.75 + 1.5 * 7, 0.3, -0.75);
	createChessman(rook, 1);
	glTranslatef(0.0, 0.0, -1.5);
	
	glPushMatrix();
	glRotated(-90, 0, 1,0);
	createChessman(knight, 1);
	glPopMatrix();
	
	glTranslatef(0.0, 0.0, -1.5);
	createChessman(bishop, 1);
	glTranslatef(0.0, 0.0, -1.5);
	createChessman(king, 1);
	glTranslatef(0.0, 0.0, -1.5);
	createChessman(queen, 1);
	glTranslatef(0.0, 0.0, -1.5);
	createChessman(bishop, 1);
	glTranslatef(0.0, 0.0, -1.5);
	
	glPushMatrix();
	glRotated(-90, 0, 1,0);
	createChessman(knight, 1);
	glPopMatrix();
	
	glTranslatef(0.0, 0.0, -1.5);
	createChessman(rook, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.75 + 1.5 * 6, 0.3, -0.75);
	createChessman(pawn, 1);
	for (int i = 0; i < 7; i++){
		glTranslatef(0, 0, -1.5);
		createChessman(pawn, 1);
	}
	glPopMatrix();
}

void drawChessmen() {
	blackChessmen();
	whiteChessmen();
}

