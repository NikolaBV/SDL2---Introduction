#include <iostream>
#include "SDL.h"
#include <SDL_image.h>
#include "Player.h"

int main(int argc, char* argv[])
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderTarget = nullptr;
	int currentTime = 0;
	int prevTime = 0;
	float deltaTime = 0.0f;
	const Uint8* keyState;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("First Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	Player playerOne(renderTarget, "resources/standard/walk.png", 0, 0, 9, 4); //Set framesX to the width of the sprite and framesY to the height of the sprite
	Player playerTwo(renderTarget, "resources/standard/walk.png", 600, 400, 9, 4);

	bool isRunning = true;
	SDL_Event ev;

	//Game loop
	while (isRunning) {
		prevTime = currentTime;
		currentTime = SDL_GetTicks();

		deltaTime = (currentTime - prevTime) / 1000.0f;
		//Event loop
		while (SDL_PollEvent(&ev) != 0) {
			if (ev.type == SDL_QUIT) {
				isRunning = false;
			}
		}

		keyState = SDL_GetKeyboardState(NULL);

		playerOne.Update(deltaTime, keyState);
		playerTwo.Update(deltaTime, keyState);

		playerOne.IntersectsWithDistanceBased(playerTwo);

		playerOne.Draw(renderTarget);
		playerTwo.Draw(renderTarget);

		SDL_RenderPresent(renderTarget);
		SDL_RenderClear(renderTarget);

	}

	//Clean up
	SDL_DestroyRenderer(renderTarget);
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();

	return 0;
}
