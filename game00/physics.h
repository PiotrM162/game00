#pragma once
#include <box2d/box2d.h>
#include "GRenderer.h"

class myDebugDraw;

class contactListener
{
public:
	virtual void OnBeginContact() = 0;
	virtual void OnEndContact() = 0;
};

class physics
{
public:
	static void init();
	static void update(float deltaTime);
	static void debugDraw(GRenderer Renderer);

	static b2World world;
	static myDebugDraw* DebugDraw;
};