#ifndef PIECES_H_
#define PIECES_H_
extern GLuint startList;
extern int moving,startx,starty;
extern GLfloat angle1,angle2;
extern int whitepawn[][2];
extern int whitepowers[][3];
extern int blackpawn[][2];
extern int blackpowers[][3];
extern void errorCallback(GLenum errorCode);
extern void PiecesInit(void);
extern void PiecesDisplay(void);
#endif
