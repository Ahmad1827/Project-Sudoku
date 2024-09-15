#pragma once

#include "ColliderComponent.h"
#include "Components.h"
#include "Map.h"

class AnimateComponent : public Component
{
public:
	int elementId;
	TransformComponent* transformer[10];
	AnimateComponent(int i)
	{
		elementId = i;
	}
	void init() override
	{
		transformer[elementId] = &entity->getComponent<TransformComponent>();
	}

	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	int JumpVec[125];
	int posJump = 0;

	void update() override {
		transformer[elementId]->velocity.x = 0;
		transformer[elementId]->velocity.y = 0;
		if (elementId == 3)
		{
			transformer[elementId]->velocity.x = 0.02;
			transformer[elementId]->velocity.y = 0.01;
		}

		
	}
};
