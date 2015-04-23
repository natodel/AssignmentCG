/* Module      : MainFile.cpp
 * Author      : 
 * Email       : 
 * Course      : Computer Graphics
 *
 * Description : 
 *
 *
 * Date        : 
 *
 * History:
 * Revision      Date          Changed By
 * --------      ----------    ----------
 * 01.00         ?????          ???
 * First release.
 *
 */

/* -- INCLUDE FILES ------------------------------------------------------ */
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>

class chessMan{
	public:
		float current_x, current_y, current_z;
		float x[], y[], z[];
		virtual void moveTo(float x, float y, float z);
};

class GLintPoint  {

};

void drawDot( GLint x, GLint y )  {

}

void myInit( void )  {
  glClearColor( 1.0, 1.0, 1.0, 0.0 );
  glColor3f( 0.0, 0.0, 0.0 );
  glPointSize( 1.0 );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );
  gluOrtho2D( 0.0, 640.0, 0.0, 480.0 );
}

void readInputFile()
{
	
}

void keyboard(unsigned char key,int x,int y)         
{
	
}

void mouse(int button, int state, int x, int y)
{
	
}

void drawBoard() // ve ban co
{
	
}

void checkPoint(float x, float y) // kiem tra xem con co nao tai vi tri (x, y)
{
	
}

void changeView() // thay doi goc nhin
{
	
}

void myDisplay( void )  {
  glClear( GL_COLOR_BUFFER_BIT );
}

int main( int argc, char *argv[] )  {
  // Initialize GLUT.
  glutInit( &argc, argv );
  // Set the mode to draw in.
  glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
  // Set the window size in screen pixels.
  glutInitWindowSize( 640, 480 );
  // Set the window position in screen pixels.
  glutInitWindowPosition( 100, 150 );
  // Create the window.
  glutCreateWindow( "Assignment" );
  // Set the callback funcion to call when we need to draw something.
  glutDisplayFunc( myDisplay );
  // Use Keyboard
  glutKeyboardFunc (keyboard);
  // Use Mouse
  glutMouseFunc(mouse);
  // Initialize some things.
  myInit( );
  // Now that we have set everything up, loop responding to events.
  glutMainLoop( );
}

/* ----------------------------------------------------------------------- */
