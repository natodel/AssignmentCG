#ifndef CHESSMAN_H_
#define CHESSMAN_H_

#define KING 0
#define QUEEN 1
#define BISHOP 2
#define KNIGHT 3
#define ROOK 4
#define PAWN 5

class Chessman {
	public:
		int name;
		double coorX, coorY, coorZ;
		bool life;
		int side;
		int currIndex;

		Chessman();
		void setProfile(int s, double x, double y, double z, int index, bool b, int a);	
		void destroy(float x, float z);		
		void display(int color);
		void move(double x, double z);
		void move_up();
		void move_down();
};

extern void drawChessmen();
extern void initReadfile();
extern Chessman* chessMan;
#endif
