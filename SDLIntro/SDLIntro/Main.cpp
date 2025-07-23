#include <iostream>
#include "SDL.h"
#include <SDL_image.h>
#include <SDL_ttf.h>

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};


SDL_Texture *LoadTexture(std::string filepath, SDL_Renderer *renderTarget) {
	SDL_Texture *texture = nullptr;
	SDL_Surface *surface = IMG_Load(filepath.c_str());

	if (surface == NULL) {
		std::cout << "Error" << std::endl;
	}
	else {
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
	}
	SDL_FreeSurface(surface);
	return texture;
}

void UpdateSpriteAnimation(Direction movementDirection, float &frameTime, float &deltaTime, SDL_Rect &playerRect, int &frameWidth, int &textureWidth) {
	frameTime += deltaTime;

	if (movementDirection == DOWN) {
		playerRect.x, playerRect.y = 128;
	}
	if (movementDirection == RIGHT) {
		playerRect.x, playerRect.y = 192;
	}
	if (movementDirection == LEFT) {
		playerRect.x, playerRect.y = 64;
	}
	if (movementDirection == UP) {
		playerRect.x, playerRect.y = 0;
	}

	if (frameTime >= 0.05f) {

		frameTime = 0;
		playerRect.x += frameWidth;

		if (playerRect.x >= textureWidth) {
			playerRect.x = 0;
		}
	}
}

int main(int argc, char* argv[])
{
	const int FPS = 180;
	float frameTime = 0;
	int prevTime = 0;
	int currentTime = 0;
	float deltaTime = 0;
	float moveSpeed = 1.0f;
	const Uint8 *keyState;

	SDL_Window* window = nullptr;
	SDL_Texture *currentImage= nullptr;
	SDL_Renderer* renderTarget = nullptr;
	SDL_Rect playerRect;

	SDL_Rect playPosition;
	playPosition.x = playPosition.y = 0;
	playPosition.w = playPosition.h = 128;
	Direction movementDirection = NONE;

	int frameWidth, frameHeight;
	int textureWidth, textureHeight;

	SDL_Init(SDL_INIT_VIDEO);
	if (TTF_Init() < 0) {
		std::cout << "Error ttf: " << TTF_GetError() << std::endl;
	}
	window = SDL_CreateWindow("First Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	currentImage = LoadTexture("resources/standard/walk.png", renderTarget);

	SDL_QueryTexture(currentImage, NULL, NULL, &textureWidth, &textureHeight);

	frameWidth = textureWidth / 9;
	frameHeight = textureHeight / 4;

	playerRect.x = playerRect.y = 0;
	playerRect.w = frameWidth;
	playerRect.h = frameHeight;


	TTF_Font *font = TTF_OpenFont("resources/fonts/Stardew_Valley.otf", 20);
	SDL_Color color = { 144,77,255,255 };
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, "New added text", color);
	SDL_Texture* text = SDL_CreateTextureFromSurface(renderTarget, textSurface);
	SDL_Rect textRect;
	textRect.x = textRect.y = 0;

	SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);

	SDL_FreeSurface(textSurface);
	textSurface = nullptr;

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
		if (keyState[SDL_SCANCODE_RIGHT]) {
			movementDirection = RIGHT;
			(playPosition.x += moveSpeed)* deltaTime;
		}
		else if (keyState[SDL_SCANCODE_LEFT]) {
			movementDirection = LEFT;
			(playPosition.x -= moveSpeed)* deltaTime;
		}
		else if (keyState[SDL_SCANCODE_UP]) {
			movementDirection = UP;
			(playPosition.y -= moveSpeed)* deltaTime;
		}
		else if (keyState[SDL_SCANCODE_DOWN]) {
			movementDirection = DOWN;
			(playPosition.y += moveSpeed)* deltaTime;
		}

		if (!keyState[SDL_SCANCODE_LEFT] && !keyState[SDL_SCANCODE_RIGHT] && !keyState[SDL_SCANCODE_UP] && !keyState[SDL_SCANCODE_DOWN]) {
			movementDirection = NONE;

		}
		
		if (movementDirection != NONE) {
			UpdateSpriteAnimation(movementDirection, frameTime, deltaTime, playerRect, frameWidth, textureWidth);
		}


		SDL_RenderClear(renderTarget);
		SDL_RenderCopy(renderTarget, text, NULL, &textRect);

		SDL_RenderCopy(renderTarget, currentImage, &playerRect, &playPosition);
		SDL_RenderPresent(renderTarget);
	}
	SDL_DestroyTexture(currentImage);
	SDL_DestroyRenderer(renderTarget);
	SDL_DestroyTexture(text);
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
	IMG_Quit();
	return 0;
}
