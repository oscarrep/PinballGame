#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = NULL;
	sprites = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	circle = App->textures->Load("pinball/wheel.png"); 
	box = App->textures->Load("pinball/crate.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	sprites = App->textures->Load("pinball/Textures2.png");

	tableRect.x = 222;
	tableRect.y = 369;
	tableRect.h = 730;
	tableRect.w = 442;

	clickerRect.x = 9;
	clickerRect.y = 565;
	clickerRect.w = 56;
	clickerRect.h = 54;

	ballRect.x = 11;
	ballRect.y = 427;
	ballRect.h = 19;
	ballRect.w = 20;

	blueCircle.x = 9;
	blueCircle.y = 519;
	blueCircle.h = 37;
	blueCircle.w = 38;

	orangeCircle.x = 22;
	orangeCircle.y = 630;
	orangeCircle.h = 28;
	orangeCircle.w = 29;

	ballPos.x = SCREEN_WIDTH / 2;
	ballPos.y = SCREEN_HEIGHT / 2 - 200;
	circlePos.x = SCREEN_WIDTH / 2;
	circlePos.y = SCREEN_HEIGHT / 2;
	bouncerPos.x = SCREEN_WIDTH / 2;
	bouncerPos.y = SCREEN_HEIGHT / 2 - 100;
		   
	ball = App->physics->CreateCircle(ballPos.x, ballPos.y, 10);

	/*circlepoint = App->physics->CreateCircleStatic(circlepos.x, circlepos.y, 18);
	circlepoint->body->GetFixtureList()->SetRestitution(1.5f);*/
	bouncer = App->physics->CreateStaticCircle(bouncerPos.x, bouncerPos.y, 27);
	bouncer->body->GetFixtureList()->SetDensity(10.0f);
	bouncer->body->GetFixtureList()->SetRestitution(1.5f);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(sprites);

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	App->renderer->Blit(sprites, 0, 0, &tableRect);
	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 8));
		circles.getLast()->data->listener = this;
	}

	if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 20,40));
	}

	/*if(App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		
	}*/

	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	ball->GetPosition(ballPos.x, ballPos.y);
	App->renderer->Blit(sprites, ballPos.x, ballPos.y, &ballRect);
	/*circlepoint->GetPosition(circlepos.x, circlepos.y);
	if (!col)
	{
	App->renderer->Blit(table, circlepos.x, circlepos.y, &bluecircle);
	}
	else
	{
	App->renderer->Blit(table, circlepos.x, circlepos.y, &orangecircle);
	}
	*/
	bouncer->GetPosition(bouncerPos.x, bouncerPos.y);
	App->renderer->Blit(sprites, bouncerPos.x, bouncerPos.y, &clickerRect);

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(sprites, x, y, &ballRect, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = clicker.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(sprites, x, y, &clickerRect, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	/*App->audio->PlayFx(bonus_fx);*/
}
