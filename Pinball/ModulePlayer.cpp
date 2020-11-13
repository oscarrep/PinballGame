#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	rFlipperPos = { 271,695 };
	lFlipperPos = { 175,695 };

	lFlipper = App->physics->CreateFlipper(lFlipperPos.x, lFlipperPos.y, 60, 30, false);
	rFlipper = App->physics->CreateFlipper(rFlipperPos.x, rFlipperPos.y, 60, 30, true);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		rFlipper->body->ApplyTorque(250.0, true);
	}
	else if (rFlipper->body->IsAwake())
	{
		rFlipper->body->ApplyTorque(-250.0, false);
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		lFlipper->body->ApplyTorque(-250.0, true);
	}
	else if (lFlipper->body->IsAwake())
	{
		lFlipper->body->ApplyTorque(250.0, false);
	}
	
	return UPDATE_CONTINUE;
}



