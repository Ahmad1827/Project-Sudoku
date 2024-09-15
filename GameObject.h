#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
class GameObject {
public:
	GameObject(const char* texturesheet,int x,int y);
	~GameObject();

	void Update();
	void Render();
private:
	int xpos;
	int ypos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
};