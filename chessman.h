#ifndef CHESSMAN_H_
#define CHESSMAN_H_

#define KING 0
#define QUEEN 1
#define BISHOP 2
#define KNIGHT 3
#define ROOK 4
#define PAWN 5
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

extern Chessman rook1;
extern Chessman knight1;
extern Chessman bishop1;
extern Chessman king1;
extern Chessman queen1;
extern Chessman bishop2;
extern Chessman knight2;
extern Chessman rook2;
extern Chessman* pawn1;

extern Chessman rook3;
extern Chessman knight3;
extern Chessman bishop3;
extern Chessman king2;
extern Chessman queen2;
extern Chessman bishop4;
extern Chessman knight4;
extern Chessman rook4;
extern Chessman* pawn2;

extern void drawChessmen();
extern void initReadfile();
#endif 
