#pragma once
#include "SDL.h"
#include <string>


class Player
{
private:
	SDL_Rect cropRect;
	SDL_Texture* texture;
	float moveSpeed;
	float frameCounter;
	int frameWidth, frameHeight;
	int textureWidth;
	bool isActive;
	int originX, originY;
	int radius;

	const static int MOVEMENTKEYS_LENGTH = 4;
	SDL_Scancode playerOneKeys[MOVEMENTKEYS_LENGTH] =
	{
		SDL_SCANCODE_W,
		SDL_SCANCODE_S,
		SDL_SCANCODE_A,
		SDL_SCANCODE_D
	};
	SDL_Scancode playerTwoKeys[MOVEMENTKEYS_LENGTH] =
	{
		SDL_SCANCODE_UP,
		SDL_SCANCODE_DOWN,
		SDL_SCANCODE_LEFT,
		SDL_SCANCODE_RIGHT
	};

	SDL_Scancode keys[MOVEMENTKEYS_LENGTH];


public:
	Player(SDL_Renderer *renderTarget, std::string filePath, int x, int y, int framesX, int framesY);
	~Player();

	void Update(float deltaTime, const Uint8* keyState);
	void Draw(SDL_Renderer *renderTarget);
	void UpdateSpriteAnimation(float& frameCounter, float& deltaTime, SDL_Rect& cropRect, int& frameWidth, int& textureWidth);
	bool IntersectsWithBoundingBox(Player &player);
	bool IntersectsWithDistanceBased(Player& player);

	SDL_Rect positionRect;
	int getOriginX();
	int getOriginY();
	int getRadius();
};

