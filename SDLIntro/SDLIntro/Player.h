#pragma once
#include "SDL.h"
#include <string>

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};

class Player
{
private:
	SDL_Rect cropRect;
	SDL_Texture* texture;
	Direction movementDirection;
	float moveSpeed;
	float frameCounter;
	int frameWidth, frameHeight;
	int textureWidth;
	bool isActive;
	SDL_Scancode keys[4];

public:
	Player(SDL_Renderer *renderTarget, std::string filePath, int x, int y, int framesX, int framesY);
	~Player();

	void Update(float deltaTime, const Uint8* keyState);
	void Draw(SDL_Renderer *renderTarget);
	void UpdateSpriteAnimation(float& frameCounter, float& deltaTime, SDL_Rect& cropRect, int& frameWidth, int& textureWidth);

	SDL_Rect positionRect;
};

