#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleMenu.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"


ModuleMenu::ModuleMenu(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	menuTex = nullptr;
}

ModuleMenu::~ModuleMenu()
{
}

bool ModuleMenu::Start()
{
	//menuRect = { 0,0,441,728 };
	//menuTex = App->textures->Load("pinball/menu.png");

	//App->player->CleanUp();

	return true;
}

update_status ModuleMenu::Update()
{
	//App->renderer->Blit(menuTex, 0, 0, &menuRect);

	return UPDATE_CONTINUE;
}

bool ModuleMenu::CleanUp()
{
	//App->textures->Unload(menuTex);
	return true;
}