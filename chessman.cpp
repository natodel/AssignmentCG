
#include<windows.h>
#include <fstream>
#include <GL/glut.h>
#include <cstdlib>
#include <vector>
#include <iostream>
#include "chessman.h"

#define KING 0
#define QUEEN 1
#define BISHOP 2
#define KNIGHT 3
#define ROOK 4
#define PAWN 5

using namespace std;

void createChessman(int name, int color);

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

Chessman::Chessman() {
	name = 0; coorX = 0; coorZ = 0; life = true; side = 0; selected = false;
}

Chessman::Chessman(int s, double x, double z, bool b, bool c, int a) {
	name = s; coorX = x; coorZ = z; life = b; side = a; selected = c;
}

int Chessman::getName() {
	return name;
}

double Chessman::getCoorZ() {
	return coorZ;
}

double Chessman::getCoorX() {
	return coorX;
}

void Chessman::setCoor(double x, double z, int s, int n) {
	coorX = x; coorZ = z; side = s; name = n;
}

void Chessman::setSelected() {
	selected = true;
}

void Chessman::setUnSelected() {
	selected = false;
}

void Chessman::destroy() {
	life = false;
}

void Chessman::display() {
	if(selected) {
		createChessman(name, 2);
		glTranslatef(0, 3, 0);
	}
	else {
		createChessman(name, side);
	}
}

void Chessman::move(double x, double z) {
	int xTran = (x - coorX)/1.5;
	int zTran = (z - coorZ)/1.5;
	glTranslatef(xTran*1.5, 0, zTran*1.5);
}

string chess[] = {"king.obj", "queen.obj", "bishop.obj", "knight.obj", "rook.obj", "pawn.obj"};
vector<GLdoublePoint> vertice[6];
vector<GLdoublePoint> normal[6];
vector<GLPolygon> polygon[6];
int nPolArr[6];
int nVer, nPol, nNorm;

int getIndex(string name) {
	string n = name;
	
	if (name == chess[KING]) {
		return KING;
	} else if (name == chess[QUEEN]) {
		return QUEEN;
	} else if (name == chess[BISHOP]) {
		return BISHOP;
	} else if (name == chess[KNIGHT]) {
		return KNIGHT;
	} else if (name == chess[ROOK]) {
		return ROOK;
	} else if (name == chess[PAWN]) {
		return PAWN;
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
	readfile(chess[ROOK]);
	readfile(chess[KING]);
	readfile(chess[QUEEN]);
	readfile(chess[BISHOP]);
	readfile(chess[KNIGHT]);
	readfile(chess[PAWN]);
}

void createChessman(int name, int color) {
	int index = name;
	
	glPushMatrix();
	if(color == 0) {
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 4.0f);	
		
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
	else if(color == 2) {
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 4.0f);
		
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		glColor3f(0.6f, 0.6f, 0.8f);
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
	
	rook1.display();
	glPopMatrix();
	
	glTranslatef(0.0, 0.0, -1.5);
	glPushMatrix();
	glRotated(90, 0, 1,0);
	
	knight1.display();
	glPopMatrix();
	
	glTranslatef(0.0, 0.0, -1.5);
	
	bishop1.display();
	
	glTranslatef(0.0, 0.0, -1.5);
	
	king1.display();
	
	glTranslatef(0.0, 0.0, -1.5);
	
	queen1.display();
		
	glTranslatef(0.0, 0.0, -1.5);
	
	bishop2.display();
	
	glTranslatef(0.0, 0.0, -1.5);
	glPushMatrix();
	glRotated(90, 0, 1,0);
	
	knight2.display();
	glPopMatrix();
	
	glTranslatef(0.0, 0.0, -1.5);
	rook2.display();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(2.25, 0.3, -0.75);
	
	pawn1[0].setCoor(1.5, 0, 0, PAWN);
	pawn1[0].display();
	for (int i = 0; i < 7; i++){
		glTranslatef(0, 0, -1.5);
		pawn1[i+1].setCoor(1.5, -1.5*i, 0, PAWN);
		pawn1[i+1].display();
	}
	glPopMatrix();
}

void whiteChessmen(){
	glPushMatrix();
	
	glTranslatef(0.75 + 1.5 * 7, 0.3, -0.75);
	rook3.display();
	glTranslatef(0.0, 0.0, -1.5);
	
	glPushMatrix();
	glRotated(-90, 0, 1,0);
	knight3.display();
	glPopMatrix();
	
	glTranslatef(0.0, 0.0, -1.5);
	bishop3.display();
	
	glTranslatef(0.0, 0.0, -1.5);
	king2.display();
	
	glTranslatef(0.0, 0.0, -1.5);
	queen2.display();
	
	glTranslatef(0.0, 0.0, -1.5);
	bishop4.display();
	
	glTranslatef(0.0, 0.0, -1.5);
	glPushMatrix();
	glRotated(-90, 0, 1,0);
	knight4.display();
	glPopMatrix();
	
	glTranslatef(0.0, 0.0, -1.5);
	rook4.display();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.75 + 1.5 * 6, 0.3, -0.75);
	pawn2[0].setCoor(1.5*6, 0, 1, PAWN);
	pawn2[0].display();
	for (int i = 0; i < 7; i++){
		glTranslatef(0, 0, -1.5);
		pawn2[i+1].setCoor(1.5*6, -1.5*i, 1, PAWN);
		pawn2[i+1].display();
	}
	glPopMatrix();
}

void drawChessmen() {
	blackChessmen();
	whiteChessmen();
}

