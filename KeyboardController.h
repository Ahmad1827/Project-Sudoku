#pragma once

#include "ColliderComponent.h"
#include "Components.h"
#include "Map.h"

class KeyboardController : public Component
{
public:
	int isJumping = 0;
	int elementI;
	TransformComponent* transform[70];
	KeyboardController(int i)
	{
		elementI = i;
	}
	void init() override
	{
		transform[elementI] = &entity->getComponent<TransformComponent>();
		for (int i = 0; i < 20; ++i)
		{
			JumpVec[i] = 3;
		}
		for (int i = 20; i < 40; ++i)
		{ 
			JumpVec[i] = -3;
		}
	}

	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	int JumpVec[125];
	int posJump = 0;

	void update() override {
		

		if (keystates[SDL_SCANCODE_UP]) {
			isJumping = 1;
		}
		if (keystates[SDL_SCANCODE_DOWN]) {
			//transform->velocity.y = 1;
		}//if(elementI==2 || elementI>=5
		if (keystates[SDL_SCANCODE_RIGHT]) {
			if (elementI == 2 || (elementI >= 5 && elementI!=9))
			{
				transform[elementI]->velocity.x = -1;
			}
		}
		else if(keystates[SDL_SCANCODE_LEFT]) {
			if (elementI == 2 || (elementI >= 5 && elementI != 9))
			{
				transform[elementI]->velocity.x = 1;
			}
		}
		else
		{
			if (elementI == 2 || (elementI >= 5 && elementI != 9))
			{
				transform[elementI]->velocity.x = 0;
			}
		}
		if (keystates[SDL_SCANCODE_ESCAPE]){
			std::cout << "Game cleaned" << std::endl;
		}
		if (isJumping == 1 && elementI==1)
		{
			transform[elementI]->position.y -= JumpVec[posJump++];
			if (posJump == 40)
			{
				isJumping = 0;
				posJump = 0;
			}
		}
	}
};
