#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include <iostream>

//Menu rendering library
bool PlayButtonGlow = false,
     ExitButtonGlow = false;

class Meni
{
	public:
		void Render(void);
};

void Meni::Render(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix(); //start
		
	glOrtho(0,600,0,400,-1,1); //Set matrix
	
	if (!PlayButtonGlow) //Play button
	{
		glColor4f(1,0.2,0.2,1); //Play button
		glBegin(GL_QUADS);
			glVertex2f(172,296);
			glVertex2f(428,296);
			glVertex2f(428,232);
			glVertex2f(172,232);
		glEnd();
	}
	else
	{
		glColor4f(1,0,0,1); //Play button
		glBegin(GL_QUADS);
			glVertex2f(172,296);
			glVertex2f(428,296);
			glVertex2f(428,232);
			glVertex2f(172,232);
		glEnd();
	}
	
	if (!ExitButtonGlow) //Play button
	{
		glColor4f(1,0.2,0.2,1); //Play button
		glBegin(GL_QUADS);
			glVertex2f(172,200);
			glVertex2f(428,200);
			glVertex2f(428,136);
			glVertex2f(172,136);
		glEnd();
	}
	else
	{
		glColor4f(1,0,0,1); //Play button
		glBegin(GL_QUADS);
			glVertex2f(172,200);
			glVertex2f(428,200);
			glVertex2f(428,136);
			glVertex2f(172,136);
		glEnd();
	}
	
	glColor4f(0,1,0,1); //Play button green border
	glBegin(GL_LINE_LOOP);
		glVertex2f(172,296);
		glVertex2f(428,296);
		glVertex2f(428,232);
		glVertex2f(171,232);
	glEnd();
	
	glColor4f(0,1,0,1); //Exit button green border
	glBegin(GL_LINE_LOOP);
		glVertex2f(172,200);
		glVertex2f(428,200);
		glVertex2f(428,136);
		glVertex2f(171,136);
	glEnd();
	
	glPopMatrix(); //stop
	
	SDL_GL_SwapBuffers();
}
