#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include <iostream>
#include <ctime>

using namespace std;

void render(void);

//variables
int x = 0, y = 0;

int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_EVERYTHING);//Initialize SDL
	
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	SDL_WM_SetCaption( "SDL - test", NULL);
	
	SDL_SetVideoMode(600,400,32, SDL_OPENGL);//velikost, barve, opengl
	
	glClearColor(0,0,0,1); //RGBA
	glViewport(0,0,600,400);//kordinate levi zgornji kot(0,0), desni spodnji kot(600,400)
	glShadeModel(GL_SMOOTH);//color blending
	glMatrixMode(GL_PROJECTION);//2D
	glLoadIdentity();//save settings
	
	glDisable(GL_DEPTH_TEST);//ker nimamo 3D
	
	//variables
	bool isRunning = true;
	SDL_Event event; //event handling event
	x = 300;
	y = 200;
	//main loop
	while (isRunning)
	{
		//events
		while (SDL_PollEvent(&event))
		{
			if ((event.type == SDL_QUIT) || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)) // X , esc
				isRunning = false;
			if (event.type == SDL_KEYUP)
			{
				if (event.key.keysym.sym == SDLK_w)
					y += 32;
				else if (event.key.keysym.sym == SDLK_s)
					y -= 32;
				else if (event.key.keysym.sym == SDLK_d)
					x += 32;
				else if (event.key.keysym.sym == SDLK_a)
					x -= 32;
			}
		}
		
		//logic
		
		cout << "test" << endl;
		//rendering
		glClear(GL_COLOR_BUFFER_BIT);
		
		render();
		
		SDL_GL_SwapBuffers();
	}
	
	//SDL Quit
	SDL_Quit();
	
	return 0;
}

void render()
{
	glPushMatrix(); //start
		
	glOrtho(0,600,0,400,-1,1); //Set matrix
		
	glBegin(GL_TRIANGLES);
	glColor4f(1,0,0,1);
	glVertex2f(x-16,y-16);
	glColor4f(0,1,0,1);
	glVertex2f(x+16,y-16);
	glColor4f(0,0,1	,1);
	glVertex2f(x,y+16);
	glEnd();
		
	glPopMatrix(); //end
}
