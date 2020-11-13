#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleAudio.h"


ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	flipperfx = App->audio->LoadFx("pinball/FlipperDown.wav");

	rFlipperPos = { 271,695 };
	lFlipperPos = { 175,695 };

	idle.PushBack({ 21,665,21,60 });

	springAnim.PushBack({ 20,764,20,60 });
	springAnim.PushBack({ 78,708,20,70 });
	springAnim.loop = false;
	springAnim.speed = 0.05f;

	springPos = { 415, 650 };
	spring = App->physics->CreateSpring(springPos.x, springPos.y, 21, 60);

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
	current_animation = &idle;

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		rFlipper->body->ApplyTorque(250.0, true);
		App->audio->PlayFx(flipperfx);
	}
	else if (rFlipper->body->IsAwake())
	{
		rFlipper->body->ApplyTorque(-250.0, false);
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		lFlipper->body->ApplyTorque(-250.0, true);
		App->audio->PlayFx(flipperfx);
	}
	else if (lFlipper->body->IsAwake())
	{
		lFlipper->body->ApplyTorque(250.0, false);
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		current_animation = &springAnim;
		LOG("down");
		//spring->body->ApplyForceToCenter({ 0,100 }, true);
	}
	else if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
	{
		spring->body->ApplyForceToCenter({ 0,100 }, true);
		springAnim.Reset();
		LOG("up");
	}

	App->renderer->Blit(App->scene_intro->sprites, springPos.x - 10, springPos.y - 30, &(current_animation->GetCurrentFrame()));
	
	return UPDATE_CONTINUE;
}



