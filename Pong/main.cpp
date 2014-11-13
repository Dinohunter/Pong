#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
//#include "texture.h"
//#include "mainMenu.h"
//#include "ball.h"
//#include "paddle.h"
#include <string>

using namespace std;

//screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TOTAL_BUTTONS = 4;

//starts up sdl and creates window, we also test if its working
bool init();

//load media, also a test to see if its working
bool loadMedia();

//frees media and shuts down sdl
void close();

//loads the images individually, using a pointer to point to the location. good for memory
SDL_Surface* loadSurface(string path);

//loads the background
SDL_Surface* loadBackground(string path);

//the window where all the images and things will be rendered to.
SDL_Window* gWindow = NULL;

// pointer for the background png file. 
SDL_Surface* gBackground = NULL;

//the surface contained by the window, 
SDL_Surface* gScreenSurface = NULL;

/*displays the current image that the user sees. the program works by rendering
an image underneath the current surface then switching it out with the current surface*/
SDL_Surface* gCurrentSurface = NULL;

//this function returns true or false if everything can be initialized
bool init()
{
	bool success = true;

	/*sdl init initializes here and then it starts up init video, which we use because
	we have a display thing. if it is anything less than 0 theres an issue*/
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		//getError actually gets the problem that was produced
		cout << "SDL could not initialize, SDL Error: " << SDL_GetError() << endl;
		success = false;
	}

	else
	{
		/*create the window create window has multiple inputs. the first is name of the window
		second is x position on monitor where itll be placed, third is y position, fourth and
		fifth get the constants of the width and height and the sixth shows the window.
		The wiki for sdl says that window shown is auto set and ignored by the create window
		only when you set it as hidden does it not show up. but window shown can be queried later using
		getwindowflags which could be useful for bug testing*/
		gWindow = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		// so if the pointer to create window doesnt work then itll go through here to check
		if (gWindow == NULL)
		{
			cout << "Window could not be created!" << SDL_GetError << endl;
			success = false;
		}

		else
		{
			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				cout << "SDL_image could not initialize! SDL_image Error:" << IMG_GetError() << endl;
				success = false;
			}
			else
			{
				/* so this part get window surgace pulls the stuff from gWindow to gscreen surface
				 I think this allows things to be drawn onto the screen and not rendered*/
				gScreenSurface = SDL_GetWindowSurface(gWindow);
			}
		}
	}

	return success;
}

/*this section here we load media and return false if it isnt loaded this isnt
anything to do with displaying the images just loads and checks to make sure they
are working. we check if the bg works*/
bool loadMedia()
{
	bool success = true;

	gBackground = loadSurface("bg.png");
	if (gBackground == NULL)
	{
		cout << "Failed to load bg.png for Background" << endl;
		success = false;
	}

	return success;
}

//closing function
void close()
{
	SDL_FreeSurface(gBackground);
	gBackground = NULL;

	//destroy window and frees the gWindow pointer
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//quit sdl subsystems
	SDL_Quit();
}

//this part takes in the image path then optimizes it then returns it as optimized bg surface
//it also check if the image works
SDL_Surface* loadSurface(string path)
{
	// this is the optimized surface
	SDL_Surface* optimizedBGSurface = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL)
	{
		cout << "unable to load image" << path.c_str() << "SDL ERROR" << SDL_GetError() << endl;
	}

	else
	{
		/*convert surace to screen format. also note that convert surface returns a copy of 
		  the original in a new format and the original is still in memory so you need to 
		  free the original loaded surface or else there will be in two copies*/
		optimizedBGSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, NULL);

		if (optimizedBGSurface == NULL)
		{
			cout << "Unable to optimized image" << path.c_str() << SDL_GetError() << endl;
		}

		//get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedBGSurface;
}

// this allows external input from cmd line to run
int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		cout << "Failed to initialize!" << endl;
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			cout << "Failed to load media!" << endl;
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler i think this makes e an event queue thingy
			SDL_Event event;


			//While application is running
			while (!quit)
			{
				//while there are things in the queue it run. also poll event is a thread
				while (SDL_PollEvent(&event) != 0)
				{
					//User requests quit or hits the x in the top right
					if (event.type == SDL_QUIT)
					{
						quit = true;
					}
					
				}

				//Apply the current image
				SDL_BlitSurface(gBackground, NULL, gScreenSurface, NULL);

				//Update the surface
				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}