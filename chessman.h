#ifndef CHESSMAN_H_
#define CHESSMAN_H_

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

char rook[] = {'r', 'o', 'o', 'k', '.', 'o', 'b', 'j'};
char bishop[] = {'b', 'i', 's', 'h', 'o', 'p', '.', 'o', 'b', 'j'};
char king[] = {'k', 'i', 'n', 'g', '.', 'o', 'b', 'j'};
char knight[] = {'k', 'n', 'i', 'g', 'h', 't', '.', 'o', 'b', 'j'};
char queen[] = {'q', 'u', 'e', 'e', 'n', '.', 'o', 'b', 'j'};
char pawn[] = {'p', 'a', 'w', 'n', '.', 'o', 'b', 'j'};

extern GLdoublePoint** vertice;
extern GLdoublePoint** normal;
extern GLPolygon** polygon;
extern int nPolArr[6];
extern int nVer, nPol, nNorm;
extern void readfile(char name[]);
extern void blackChessmen(void);
extern void whiteChessmen(void);
extern void initReadfile();
#endif 
