#include<windows.h>
#include <fstream>
#include <GL/glut.h>
#include <cstdlib>
#include <vector>
#include <iostream>
#include "chessman.h"

using namespace std;

void createChessman(int name, int color);
void readfile(string name);

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

vector<GLdoublePoint> vertice[6];
vector<GLdoublePoint> normal[6];
vector<GLPolygon> polygon[6];
int nPolArr[6];
int nVer, nPol, nNorm;

Chessman::Chessman() {
	name = 0; coorX = 0; coorY = 0; coorZ = 0; life = true; side = 0;
}

void Chessman::setProfile(int s, double x, double y, double z, int index, bool b, int a) {
	name = s; coorX = x; coorY = y; coorZ = z; currIndex = index, life = b; side = a;
}

void Chessman::destroy(float x, float z) {
	coorX = x;
	coorZ = z;
	currIndex = -1;
	//life = false;
}

void Chessman::display(int color) {
	int index = name;
	if (!life) return;
	glPushMatrix();
	glTranslatef(0,coorY,0);
	if(name == KNIGHT && side ==0) {
		glRotated(90, 0, 1, 0);
	}
	else if(name == KNIGHT && side == 1) {
		glRotated(-90, 0, 1, 0);
	}
	
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
		glBegin(GL_TRIANGLES);
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

void Chessman::move(double x, double z) {
	int x1 = x/1.5;
	int z1 = z/1.5;
	coorX = x1 * 1.5;
	coorZ = z1 * 1.5;
}

void Chessman::move_up() {
	coorY = 1.5;
}

void Chessman::move_down() {
	coorY = 0;
}

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

void initReadfile() {
	readfile("king.obj");
	readfile("queen.obj");
	readfile("bishop.obj");
	readfile("knight.obj");
	readfile("rook.obj");
	readfile("pawn.obj");
}

void drawChessmen() {
	glPushMatrix();
	glTranslatef(0.75, 0.3, -0.75);
	glTranslatef(chessMan[0].coorX, 0, chessMan[0].coorZ);
	chessMan[0].display(0);
	int color;
	for(int i=1; i<32; i++)
	{
	
		if(i<16) color = 0;
		else color = 1;
		glTranslated(chessMan[i].coorX-chessMan[i-1].coorX, 0, chessMan[i].coorZ-chessMan[i-1].coorZ);
		if(chessMan[i].life)
			chessMan[i].display(color);
	}
	glPopMatrix();
}

