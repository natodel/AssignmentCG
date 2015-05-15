
#include <GL/gl.h>
#include <GL/glut.h>
#include <windows.h>
#include <math.h>
#include "particle.h"

using namespace std;

GLfloat texture[10];

const int ParticleCount = 150;

typedef struct
{
	double Xpos;
	double Ypos;
	double Zpos;
	double Xmov;
	double Zmov;
	double Direction;
	double Acceleration;
	double Deceleration;
	double Scalez;
	bool Visible;
}PARTICLES;

PARTICLES Particle[ParticleCount];

void glCreateParticles (void) {
int i;
for (i = 1; i < ParticleCount; i++)
{
	Particle[i].Xpos = 5;
	Particle[i].Ypos = 10;
	Particle[i].Zpos = -5;
	Particle[i].Xmov = (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.0015) - (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.0015);
	Particle[i].Zmov = (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.0015) - (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.0015);
	Particle[i].Scalez = 0.02;
	Particle[i].Direction = 0;
	Particle[i].Acceleration = ((((((8 - 5 + 2) * rand()%11) + 5) - 1 + 1) * rand()%11) + 1) * 0.005;
	Particle[i].Deceleration = 0.005;
}
}

void glUpdateParticles (void) {
	int i;
	for (i = 1; i < ParticleCount; i++)
	{
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		glColor3f(1.0f, 0.0f, 0.0f);
		glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
		glColor3f(1.0f, 1.0f, 1.0f);
		
		Particle[i].Ypos = Particle[i].Ypos + Particle[i].Acceleration - Particle[i].Deceleration;
		Particle[i].Deceleration = Particle[i].Deceleration + 0.0025;
		
		Particle[i].Xpos = Particle[i].Xpos + Particle[i].Xmov;
		Particle[i].Zpos = Particle[i].Zpos + Particle[i].Zmov;
		
		Particle[i].Direction = Particle[i].Direction + ((((((int)(0.5 - 0.1 + 0.1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1);
		
		if (Particle[i].Ypos < 10)
		{
			Particle[i].Xpos = 5;
			Particle[i].Ypos = 10;
			Particle[i].Zpos = -5;
			Particle[i].Direction = 0;
			Particle[i].Acceleration = ((((((8 - 5 + 2) * rand()%11) + 5) - 1 + 1) * rand()%11) + 1) * 0.01;
			Particle[i].Deceleration = 0.0025;
		}
		
	}
}

void glDrawParticles (void) {
	int i;
	for (i = 1; i < ParticleCount; i++)
	{
		glPushMatrix();
	
	    glTranslatef (Particle[i].Xpos, Particle[i].Ypos, Particle[i].Zpos);
//	    glRotatef (Particle[i].Direction - 90, 0, 0, 1);
	   
	    glScalef (Particle[i].Scalez, Particle[i].Scalez, Particle[i].Scalez);
	   
	    glEnable (GL_BLEND);
//	    glDisable (GL_DEPTH_TEST);
	        
		glColor4f(1.0f, 0.0f, 0.0f, 0.8f);
		
	    glBegin (GL_QUADS);
		glNormal3f(0, 1, 0);
	    glVertex3f (-1, 0, -1);
	    glVertex3f (1, 0, -1);
	    glVertex3f (1, 0, 1);
	    glVertex3f (-1, 0, 1);
	    glEnd();

		glColor4f(1.0f, 0.0f, 0.0f, 0.8f);
		
	    glBegin (GL_QUADS);
	    glVertex3f (-1, 0, -1);
	    glVertex3f (1, 0, -1);
	    glVertex3f (1, 0, 1);
	    glVertex3f (-1, 0, 1);
	    glEnd();
	        
//	    glEnable(GL_DEPTH_TEST);
	    glDisable(GL_BLEND);
	
		glPopMatrix();
	}
}

void displayParticle (void) {
    glClearDepth (1);
    
    glPushMatrix();
    glUpdateParticles();
    glDrawParticles();
    glPopMatrix();
}

void initilization (void) {
    glCreateParticles();
}

