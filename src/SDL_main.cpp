#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include "Timer.h"
#include <math.h>

using namespace std;

void render(void);
void keyPress(SDL_Event &event);
void calculateFPS(void);
void capFramerate(void);
void func_playerFalling(void);

//constants
const int MAX_FPS = 60;
//variables
int x = 0, y = 0;
float player_fallTime = 0; //-1=on ground, >0= in air
bool isRunning;
//FPS
int frame = 0;
int fps = 0;
Timer fpsTimer;
Timer fpsUpdate;
Timer capFps;


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
	isRunning = true;
	SDL_Event event; //event handling event
	x = 300;
	y = 200;
	//Start some timers
	fpsUpdate.start();
	fpsTimer.start();
	//main loop
	while (isRunning)
	{
		capFps.start();
		//events
		keyPress(event);
		
		//logic
		func_playerFalling();
		
		//rendering
		glClear(GL_COLOR_BUFFER_BIT);
		render();
		SDL_GL_SwapBuffers();
		frame++;
		capFramerate();
		calculateFPS();
	}
	
	//SDL Quit
	SDL_Quit();
	
	return 0;
}

void capFramerate()
{
	if(capFps.getTicks() < 1000 / MAX_FPS)
	{
		SDL_Delay((1000 / MAX_FPS) - capFps.getTicks());
		if (player_fallTime != -1)
			player_fallTime+=0.1;
	}
}

void calculateFPS()
{
	if(fpsUpdate.getTicks() > 1000)
	{
		std::stringstream caption;
		fps = frame / (fpsTimer.getTicks() / 1000.f);
		caption << "FPS: " << fps;
		SDL_WM_SetCaption(caption.str().c_str(), NULL);
		fpsUpdate.start();	
	}
}

void keyPress(SDL_Event &event)
{
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
	
	glLineWidth(1.0);
	glColor4f(1,1,1,1);
	glBegin(GL_LINES);
		glVertex2f(268,100);
		glVertex2f(332,100);
	glEnd();	
		
	glPopMatrix(); //end
}

void func_playerFalling()	//Work In Progress
{
	//falling
	if (player_fallTime == -1)
		return;
	int fall = ((10*pow((double)player_fallTime,2.0))/2) - ((10*(pow((double)player_fallTime-1,2.0)))/2); //pixels fallen
	if (x < 252 || x > 348) //if x is away from the border
		return;
	if (y-fall+16 > 100 && y-fall-16 > 100) //if above border after falling
	{
		y-=fall;
		player_fallTime == -1;
		return;
	}
	y -= 100 - y+fall;
}
