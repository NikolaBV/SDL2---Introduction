#include "Player.h"
#include <SDL_image.h>
#include <iostream>

Player::Player(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY) {
	SDL_Surface* surface = IMG_Load(filePath.c_str());

	if (surface == NULL) {
		std::cout << "Error" << std::endl;
	}
	else {
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
	}
	SDL_FreeSurface(surface);

	SDL_QueryTexture(texture, NULL, NULL, &cropRect.w, &cropRect.h);

	positionRect.x = x;
	positionRect.y = y;

	textureWidth = cropRect.w;

	cropRect.w /= framesX;
	cropRect.h /= framesY;

	frameWidth = positionRect.w = cropRect.w;
	frameHeight = positionRect.h = cropRect.h;

	isActive = false;

	static int playerNumber = 0;
	playerNumber++;

	if (playerNumber == 1) {
		//TODO Use a for loop to assgin these
		keys[0] = SDL_SCANCODE_W;
		keys[1] = SDL_SCANCODE_S;
		keys[2] = SDL_SCANCODE_A;
		keys[3] = SDL_SCANCODE_D;
	}
	else {
		keys[0] = SDL_SCANCODE_UP;
		keys[1] = SDL_SCANCODE_DOWN;
		keys[2] = SDL_SCANCODE_LEFT;
		keys[3] = SDL_SCANCODE_RIGHT;
	}

	moveSpeed = 1.0f;
}
Player::~Player() {
	SDL_DestroyTexture(texture);
}


void Player::Update(float deltaTime, const Uint8* keyState) {

	isActive = true;
	if (keyState[keys[3]]) {
		(positionRect.x += moveSpeed)* deltaTime;
		cropRect.y = frameHeight * 3;
	}
	else if (keyState[keys[2]]) {
		(positionRect.x -= moveSpeed)* deltaTime;
		cropRect.y = frameHeight;

	}
	else if (keyState[keys[0]]) {
		(positionRect.y -= moveSpeed)* deltaTime;
		cropRect.y = 0;

	}
	else if (keyState[keys[1]]) {
		(positionRect.y += moveSpeed)* deltaTime;
		cropRect.y = frameHeight * 2;

	}
	else {
		isActive = false;
	}

	if (isActive) {
		frameCounter += deltaTime;

		if (frameCounter >= 0.05f) {
			frameCounter = 0;
			cropRect.x += frameWidth;
			if (cropRect.x >= textureWidth) {
				cropRect.x = 0;
			}
		}
	}
	else {
		frameCounter = 0;
		cropRect.x = frameWidth;
	}
}

void Player::Draw(SDL_Renderer* renderTarget) {
	SDL_RenderCopy(renderTarget, texture, &cropRect, &positionRect);
}