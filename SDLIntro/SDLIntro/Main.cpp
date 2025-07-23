#include <iostream>
#include "SDL.h"
int main(int argc, char* argv[])
{
	SDL_Window *window = nullptr;
	SDL_Surface *windowSurface = nullptr;
	SDL_Surface *imageSurfcace = nullptr;

	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		std::cout << "Video init error: " << SDL_GetError();
	}
	else {
		window = SDL_CreateWindow("First Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			std::cout << "Window creation failed: " << SDL_GetError();

		}
		else {
			//After window has been created
			windowSurface = SDL_GetWindowSurface(window);
			imageSurfcace = SDL_LoadBMP("resources/test.bmp");

			if (imageSurfcace == NULL) {
				std::cout << "Image load error: " << SDL_GetError();
			}
			else {
				//Take the image surface and display it on the window surface
				SDL_BlitSurface(imageSurfcace, NULL, windowSurface, NULL);
				SDL_UpdateWindowSurface(window);
				SDL_Delay(5000);
			}
		}
	}

	SDL_FreeSurface(imageSurfcace);
	imageSurfcace = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;
	windowSurface = nullptr;
	SDL_Quit();
	return 0;
}
