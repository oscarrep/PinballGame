#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class ModuleEnd : public Module
{
public:
	ModuleEnd(Application* app, bool start_enabled = true);
	~ModuleEnd();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* initTex;
	PhysBody* play;
	SDL_Rect initRect;


};