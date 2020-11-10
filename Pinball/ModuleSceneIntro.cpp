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

	bouncerRect.x = 9;
	bouncerRect.y = 565;
	bouncerRect.w = 56;
	bouncerRect.h = 54;

	bouncerLight.x = 9;
	bouncerLight.y = 833;
	bouncerLight.h = 54;
	bouncerLight.w = 56;

	ballRect.x = 11;
	ballRect.y = 427;
	ballRect.h = 19;
	ballRect.w = 20;

	blueCircle.x = 9;
	blueCircle.y = 519;
	blueCircle.h = 37;
	blueCircle.w = 38;

	orangeCircle.x = 68;
	orangeCircle.y = 520;
	orangeCircle.h = 35;
	orangeCircle.w = 37;

	int rightBumper[10] = 
	{
		547, 1048,
		587, 974,
		588, 957,
		581, 946,
		524, 1048
	};

	int leftBumper[14] = 
	{
		365, 1046,
		310, 946,
		303, 957,
		303, 975,
		349, 1055,
		357, 1056,
		363, 1052
	};

	int topBumper[12] = 
	{
		566, 872,
		599, 870,
		610, 862,
		619, 836,
		614, 832,
		562, 868
	};

	bumperPos.x = -SCREEN_WIDTH / 2.0f;
	bumperPos.y = -SCREEN_HEIGHT / 2.08f;

	ballPos.x = SCREEN_WIDTH / 2;
	ballPos.y = SCREEN_HEIGHT / 2 - 50;
	circlePos.x = SCREEN_WIDTH / 2;
	circlePos.y = SCREEN_HEIGHT / 2;
	bouncerPos.x = SCREEN_WIDTH / 2;
	bouncerPos.y = SCREEN_HEIGHT / 2 - 100;
		   
	ball = App->physics->CreateCircle(ballPos.x, ballPos.y, 10);

	/*circlepoint = App->physics->CreateCircleStatic(circlePos.x, circlePos.y, 18);
	circlepoint->body->GetFixtureList()->SetRestitution(1.5f);*/
	//bouncer = App->physics->CreateStaticCircle(bouncerPos.x, bouncerPos.y, 27);
	//bouncer->body->GetFixtureList()->SetDensity(10.0f);
	//bouncer->body->GetFixtureList()->SetRestitution(1.5f);
	sensor = App->physics->CreateCircleSensor(circlePos.x, circlePos.y, 18);

	rBumper = App->physics->CreateChain(bumperPos.x, bumperPos.y, rightBumper, 10);
	rBumper->body->GetFixtureList()->SetRestitution(2.0f);
	
	lBumper = App->physics->CreateChain(bumperPos.x, bumperPos.y, leftBumper, 14);
	lBumper->body->GetFixtureList()->SetRestitution(2.0f);
	
	tBumper = App->physics->CreateChain(bumperPos.x, bumperPos.y, topBumper, 12);
	tBumper->body->GetFixtureList()->SetRestitution(2.0f);

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
	ball->listener = this;
	App->renderer->Blit(sprites, ballPos.x, ballPos.y, &ballRect);
	
	sensor->GetPosition(circlePos.x, circlePos.y);
	if (!collision2)
	{
		App->renderer->Blit(sprites, circlePos.x, circlePos.y, &blueCircle);
	}
	else if (collision2)
	{
		App->renderer->Blit(sprites, circlePos.x, circlePos.y, &orangeCircle);
	}
	
	/*bouncer->GetPosition(bouncerPos.x, bouncerPos.y);
	if (!collision)
	{
		App->renderer->Blit(sprites, bouncerPos.x, bouncerPos.y, &bouncerRect);
	}
	else if (collision)
	{
		App->renderer->Blit(sprites, bouncerPos.x, bouncerPos.y, &bouncerLight);
	}
	*/
	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(sprites, x, y, &ballRect, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	/*c = Bouncer.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(sprites, x, y, &bouncerRect, 1.0f, c->data->GetRotation());
		c = c->next;
	}*/

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	if (bodyA != NULL && bodyB != NULL)
	{
		if (bodyA == ball && bodyB == bouncer || bodyA == bouncer && bodyB == ball)
		{
			count++;
			if (count == 1)
			{
				collision = true;
			}
			if (count == 2)
			{
				collision = false;
				count = 0;
			}
			App->audio->PlayFx(bonus_fx);
			LOG("COLLISION");
		}
		if (bodyA == ball && bodyB == sensor || bodyA == sensor && bodyB == ball)
		{
			count2++;
			if (count2 == 1)
			{
				collision2 = true;
			}
			if (count2 == 2)
			{
				collision2 = false;
			}
		}

	}
}
