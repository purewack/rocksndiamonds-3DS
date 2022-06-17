/*
	Hello World example made by Aurelio Mannara for libctru
	This code was modified for the last time on: 12/12/2014 21:00 UTC+1
*/

#include <3ds.h>
#include <stdio.h>
#include "SDL.h"

int main(int argc, char **argv)
{
	//The window we'll be rendering to
    //SDL_Window* window = NULL;
    
    //The surface contained by the window
	SDL_Surface* screen0 = NULL;
	screen0 = SDL_SetVideoMode(256, 224, 32, SDL_SWSURFACE); // also tried hwsurface
	
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
		return 1;
	}
	
	int i = 0;
	
	// Main loop
	while (aptMainLoop())
	{
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				exit(0);
				break;
			}
		}
		i = (i+1) % 255;
		SDL_FillRect(screen0, NULL, SDL_MapRGB(screen0->format, i, 0, 0));
	
		SDL_Flip( screen0 );
		
		gspWaitForVBlank();
	}

	return 0;
}
