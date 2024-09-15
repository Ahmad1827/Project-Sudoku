#pragma once
#include "Components.h"
#include "ECS.h"
#include "Vector2D.h"
class TransformComponent: public Component
{
public:
	Vector2D position;
	Vector2D velocity;

	int height = 32, width = 32;
	int scale = 1;

	int speed = 3;


	TransformComponent()
	{
		position.Zero();
	}

	TransformComponent(int sc)
	{
		position.Zero();
		scale = sc;
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y,int h,int w,int sc)
	{
		height = h;
		width = w;
		scale = sc;
		position.x = x;
		position.y = y;
	}

	void gone()
	{
		height = 0;
		width = 0;
		scale = 0;
		position.x = 0;
		position.y = 0;
	}

	void init() override
	{
		velocity.Zero();
	}

	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}

};