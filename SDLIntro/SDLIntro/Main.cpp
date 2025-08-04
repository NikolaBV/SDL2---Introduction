#include <iostream>
#include "SDL.h"
#include <SDL_image.h>
#include "Player.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Texture* LoadTexture(std::string filePath, SDL_Renderer* renderTarget)
{
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = IMG_Load(filePath.c_str());
	if (surface == NULL)
		std::cout << "Error" << std::endl;
	else
	{
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		if (texture == NULL)
			std::cout << "Error" << std::endl;
	}

	SDL_FreeSurface(surface);

	return texture;
}

int main(int argc, char* argv[])
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderTarget = nullptr;
	int currentTime = 0;
	int prevTime = 0;
	float deltaTime = 0.0f;
	const Uint8* keyState;
	SDL_Rect cameraRect = { 0,0,640,480 };
	int levelWidth, levelHeight;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("First Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	Player playerOne(renderTarget, "resources/standard/walk.png", 0, 0, 9, 4); //Set framesX to the width of the sprite and framesY to the height of the sprite
	Player playerTwo(renderTarget, "resources/standard/walk.png", SCREEN_WIDTH, SCREEN_HEIGHT, 9, 4);

	SDL_Texture* texture = LoadTexture("resources/maps/test.png", renderTarget);
	SDL_QueryTexture(texture, NULL, NULL, &levelWidth, &levelHeight);

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


		cameraRect.x = playerOne.getOriginX() - (SCREEN_WIDTH / 2);
		cameraRect.y = playerOne.getOriginY() - (SCREEN_HEIGHT / 2);

		if (cameraRect.x < 0) {
			cameraRect.x = 0;
		}
		if (cameraRect.y < 0) {
			cameraRect.y = 0;
		}

		if (cameraRect.x + cameraRect.w >= levelWidth) {
			cameraRect.x = levelWidth - SCREEN_WIDTH;
		}
		if (cameraRect.y + cameraRect.h >= levelHeight) {
			cameraRect.y = levelHeight - SCREEN_HEIGHT;
		}

		playerOne.IntersectsWithDistanceBased(playerTwo);

		playerOne.Draw(renderTarget, cameraRect);
		playerTwo.Draw(renderTarget, cameraRect);

		SDL_RenderPresent(renderTarget);
		SDL_RenderClear(renderTarget);
		SDL_RenderCopy(renderTarget, texture, &cameraRect, NULL);

	}

	//Clean up
	SDL_DestroyRenderer(renderTarget);
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(texture);

	texture = nullptr;
	window = nullptr;
	renderTarget = nullptr;
	keyState = nullptr;
	SDL_Quit();

	return 0;
}
