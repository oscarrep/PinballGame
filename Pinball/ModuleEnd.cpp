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
#include "ModuleFonts.h"


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
	scoreTex = App->fonts->Load("pinball/Score.png", "0123456789", 1);

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
	sprintf_s(scoreChar, 10, "%7d", App->scene_intro->finalScore);
	App->fonts->BlitText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, scoreTex, scoreChar);
	return UPDATE_CONTINUE;
}

bool ModuleEnd::CleanUp()
{
	App->textures->Unload(initTex);
	return true;
}