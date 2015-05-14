#ifndef CHESSMAN_H_
#define CHESSMAN_H_
class Chessman {
	private:
		int name;
		double coorX, coorZ;
		bool life, selected;
		int side;
	public:
		Chessman();
		Chessman(int s, double x, double z, bool b, bool c, int a);
		
		int getName();	
		double getCoorZ();	
		double getCoorX();	
		void setCoor(double x, double z, int s, int n);		
		void setSelected();		
		void setUnSelected();		
		void destroy();		
		void display();		
		void move(double x, double z);
};

Chessman rook1(ROOK, 0, 0, true, false, 0);
Chessman knight1(KNIGHT, 0, -1.5, true, false, 0);
Chessman bishop1(BISHOP, 0, -3.0, true, false, 0);
Chessman king1(KING, 0, -4.5, true, false, 0);
Chessman queen1(QUEEN, 0, -6.0, true, false, 0);
Chessman bishop2(BISHOP, 0, -7.5, true, false, 0);
Chessman knight2(KNIGHT, 0, -9.0, true, false, 0);
Chessman rook2(ROOK, 0, -10.5, true, false, 0);
Chessman* pawn1 = new Chessman[8];

Chessman rook3(ROOK, 1.5*7, 0, true, false, 0);
Chessman knight3(KNIGHT, 1.5*7, -1.5, true, false, 0);
Chessman bishop3(BISHOP, 1.5*7, -3.0, true, false, 0);
Chessman king2(KING, 1.5*7, -4.5, true, false, 0);
Chessman queen2(QUEEN, 1.5*7, -6.0, true, false, 0);
Chessman bishop4(BISHOP, 1.5*7, -7.5, true, false, 0);
Chessman knight4(KNIGHT, 1.5*7, -9.0, true, false, 0);
Chessman rook4(ROOK, 1.5*7, -10.5, true, false, 0);
Chessman* pawn2 = new Chessman[8];

extern void drawChessmen();
extern void initReadfile();
#endif 
