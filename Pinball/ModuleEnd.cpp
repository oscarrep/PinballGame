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

ModuleEnd::ModuleEnd(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	initTex = nullptr;
}

ModuleEnd::~ModuleEnd()
{}

bool ModuleEnd::Start()
{
	initRect = { 0,0,443,727 };
	initTex = App->textures->Load("pinball/end.png");
	App->scene_intro->Disable();
	App->player->Disable();
	App->physics->Disable();
	App->menu->Disable();

	return true;
}

update_status ModuleEnd::Update()
{

	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN && App->input->GetMouseX() >= 115 && App->input->GetMouseX() <= 315 && App->input->GetMouseY() >= 450 && App->input->GetMouseY() <= 550)
	{
		App->menu->Enable();
		this->Disable();
	}

	App->renderer->Blit(initTex, 0, 0, &initRect);
	return UPDATE_CONTINUE;
}

bool ModuleEnd::CleanUp()
{
	App->textures->Unload(initTex);
	return true;
}