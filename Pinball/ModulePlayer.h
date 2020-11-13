#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "Animation.h"

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	PhysBody* rFlipper;
	PhysBody* lFlipper;
	PhysBody* spring;

	Animation springAnim;
	Animation idle;
	Animation* current_animation = nullptr;

	SDL_Rect springRect;

	uint flipperfx;

	iPoint rFlipperPos, lFlipperPos, springPos;
};