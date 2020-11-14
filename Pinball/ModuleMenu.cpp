#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleMenu.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleSceneIntro.h"
#include "ModuleEnd.h"


ModuleMenu::ModuleMenu(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	menuTex = nullptr;
}

ModuleMenu::~ModuleMenu()
{
}

bool ModuleMenu::Start()
{
	menuRect = { 0,0,441,728 };
	menuTex = App->textures->Load("pinball/menu.png");

	App->scene_intro->Disable();
	App->player->Disable();
	App->physics->Disable();
	App->endScene->Disable();
	play = App->physics->CreateRectangleSensor(110, 366, 440, 100);
	App->player->CleanUp();

	return true;
}

update_status ModuleMenu::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		App->physics->Enable();
		App->scene_intro->Enable();
		App->player->Enable();

		this->Disable();
	}

	App->renderer->Blit(menuTex, 0, 0, &menuRect);

	return UPDATE_CONTINUE;
}

bool ModuleMenu::CleanUp()
{
	App->textures->Unload(menuTex);
	return true;
}