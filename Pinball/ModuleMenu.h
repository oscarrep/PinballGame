#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class ModuleMenu : public Module
{
public:
	ModuleMenu(Application* app, bool start_enabled = true);
	~ModuleMenu();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* menuTex;

	SDL_Rect menuRect;


};