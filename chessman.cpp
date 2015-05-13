
#include<windows.h>
#include <fstream>
#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#include "chessman.h"

using namespace std;

void initReadfile() {
	vertice = new GLdoublePoint*[7];
	normal = new GLdoublePoint*[7];
	polygon = new GLPolygon*[6];
}

int getIndex(char name[]) {
	string n = name;
	
	if (n == "king.obj") {
		return 0;
	} else if (n == "queen.obj") {
		return 1;
	} else if (n == "bishop.obj") {
		return 2;
	} else if (n == "knight.obj") {
		return 3;
	} else if (n == "rook.obj") {
		return 4;
	} else if (n == "pawn.obj") {
		return 5;
	}
}


void readfile(char name[]) {
	double point_x, point_y, point_z;
	int idx1, idx2, idx3;
	int nor1, nor2, nor3;
	
	int index = getIndex(name);
	
	string n = name;

	ifstream f_in;
	f_in.open(n.c_str());

	f_in >> nVer; f_in >> nNorm; f_in >> nPol;
	nPolArr[index] = nPol;
	vertice[index] = new GLdoublePoint[nVer];
	normal[index] = new GLdoublePoint[nNorm];
	polygon[index] = new GLPolygon[nPol];
	for (int i = 0; i < nVer; i++) {
		f_in >> point_x >> point_y >> point_z;
		GLdoublePoint point(point_x, point_y, point_z);
		vertice[index][i] = point;
	}

	for (int i = 0; i < nNorm; i++) {
		f_in >> point_x >> point_y >> point_z;
		GLdoublePoint point(point_x, point_y, point_z);
		normal[index][i] = point;
	}

	for (int i = 0; i < nPol; i++) {
		f_in >> idx1 >> nor1 >> idx2 >> nor2 >> idx3 >> nor3;
		GLPolygon pol(idx1, idx2, idx3, nor1, nor2, nor3);
		polygon[index][i] = pol;
	}
}


void createChessman(char name[], int color) {
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

