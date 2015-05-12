#ifndef BOARD_H_
#define BOARD_H_
extern GLuint _displayListId_blackArea; //The OpenGL id of the display list
extern GLuint _displayListId_whiteArea; //The OpenGL id of the display list
extern void draw_BlackArea(void);
extern void draw_whiteArea(void);
extern void initRendering(void);
#endif
