#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"

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
	sprites = App->textures->Load("pinball/Textures2.png");

	scoreTex = App->fonts->Load("pinball/numbers.png", "0123456789", 1);

	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");

	tableRect.x = 222;
	tableRect.y = 369;
	tableRect.h = 730;
	tableRect.w = 442;

	leftFlipperRect.x = 24;
	leftFlipperRect.y = 473;
	leftFlipperRect.h = 33;
	leftFlipperRect.w = 68;

	rightFlipperRect.x = 113;
	rightFlipperRect.y = 475;
	rightFlipperRect.h = 33;
	rightFlipperRect.w = 68;

	bouncerRect.x = 9;
	bouncerRect.y = 565;
	bouncerRect.w = 56;
	bouncerRect.h = 54;

	mediumBouncerRect.x = 91;
	mediumBouncerRect.y = 578;
	mediumBouncerRect.h = 33;
	mediumBouncerRect.w = 35;

	smallBouncerRect.x = 163;
	smallBouncerRect.y = 583;
	smallBouncerRect.h = 23;
	smallBouncerRect.w = 23;

	smallSensorRect.x = 68;
	smallSensorRect.y = 630;
	smallSensorRect.h = 29;
	smallSensorRect.w = 29;

	sSensorRect.x = 22;
	sSensorRect.y = 630;
	sSensorRect.h = 29;
	sSensorRect.w = 28;

	bouncerLight.x = 9;
	bouncerLight.y = 833;
	bouncerLight.h = 54;
	bouncerLight.w = 56;

	mediumBouncerLight.x = 84;
	mediumBouncerLight.y = 847;
	mediumBouncerLight.h = 32;
	mediumBouncerLight.w = 34;

	smallBouncerLight.x = 146;
	smallBouncerLight.y = 852;
	smallBouncerLight.h = 22;
	smallBouncerLight.w = 23;

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

	int topBumper[12] =
	{
		566, 872,
		599, 870,
		610, 862,
		619, 836,
		614, 832,
		562, 868
	};
	
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

	bumperPos.x = -SCREEN_WIDTH / 2.0f;
	bumperPos.y = -SCREEN_HEIGHT / 2.08f;

	ballPos.x = 63;
	ballPos.y = 1500;

	circlePos.x = 336;
	circlePos.y = 352;

	bouncerPos.x = 145;
	bouncerPos.y = 350;

	lHolePos.x = 80;
	lHolePos.y = 175;

	rHolePos.x = 335;
	rHolePos.y = 245;

	circlePos2.x = 233;
	circlePos2.y = 439;
		  
	circlePos3.x = 258;
	circlePos3.y = 169;
		  
	circlePos4.x = 81;
	circlePos4.y = 244;

	mBouncerPos.x = 220;
	mBouncerPos.y = 236;
	
	mBouncerPos2.x = 332;
	mBouncerPos2.y = 167;
	
	mBouncerPos3.x = 204;
	mBouncerPos3.y = 531;
	
	sBouncerPos.x = 65;
	sBouncerPos.y = 525;
		   
	ball = App->physics->CreateCircle(ballPos.x, ballPos.y, 10);

	/*circlepoint = App->physics->CreateCircleStatic(circlePos.x, circlePos.y, 18);
	circlepoint->body->GetFixtureList()->SetRestitution(1.5f);*/
	bouncer = App->physics->CreateStaticCircle(bouncerPos.x, bouncerPos.y, 25);
	bouncer->body->GetFixtureList()->SetDensity(10.0f);
	bouncer->body->GetFixtureList()->SetRestitution(1.5f);

	mediumBouncer = App->physics->CreateStaticCircle(mBouncerPos.x, mBouncerPos.y, 17);
	mediumBouncer->body->GetFixtureList()->SetDensity(10.0f);
	mediumBouncer->body->GetFixtureList()->SetRestitution(1.5f);

	mediumBouncer2 = App->physics->CreateStaticCircle(mBouncerPos2.x, mBouncerPos2.y, 17);
	mediumBouncer2->body->GetFixtureList()->SetDensity(10.0f);
	mediumBouncer2->body->GetFixtureList()->SetRestitution(1.5f);

	mediumBouncer3 = App->physics->CreateStaticCircle(mBouncerPos3.x, mBouncerPos3.y, 17);
	mediumBouncer3->body->GetFixtureList()->SetDensity(10.0f);
	mediumBouncer3->body->GetFixtureList()->SetRestitution(1.5f);

	smallBouncer = App->physics->CreateStaticCircle(sBouncerPos.x, sBouncerPos.y, 12);
	smallBouncer->body->GetFixtureList()->SetDensity(10.0f);
	smallBouncer->body->GetFixtureList()->SetRestitution(1.5f);

	sensor = App->physics->CreateCircleSensor(circlePos.x, circlePos.y, 18);
	sensor2 = App->physics->CreateCircleSensor(circlePos3.x, circlePos3.y, 18);
	sensor3 = App->physics->CreateCircleSensor(circlePos4.x, circlePos4.y, 18);

	lHoleSensor = App->physics->CreateCircleSensor(lHolePos.x, lHolePos.y, 15);
	rHoleSensor = App->physics->CreateCircleSensor(rHolePos.x, rHolePos.y, 15);

	smallSensor = App->physics->CreateCircleSensor(circlePos2.x, circlePos2.y, 15);

	tBumper = App->physics->CreateChain(bumperPos.x, bumperPos.y, topBumper, 12);
	tBumper->body->GetFixtureList()->SetRestitution(1.5f);
	
	rBumper = App->physics->CreateChain(bumperPos.x, bumperPos.y, rightBumper, 10);
	rBumper->body->GetFixtureList()->SetRestitution(1.5f);
	
	lBumper = App->physics->CreateChain(bumperPos.x, bumperPos.y, leftBumper, 14);
	lBumper->body->GetFixtureList()->SetRestitution(1.5f);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(sprites);
	App->fonts->UnLoad(scoreTex);

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	App->renderer->Blit(sprites, 0, 0, &tableRect);

	if (ballPos.y >= 768 && lifes < 4)
	{
		App->physics->world->DestroyBody(ball->body);
		ballPos.x = 300;
		ballPos.y = 600;
		ball = App->physics->CreateCircle(ballPos.x, ballPos.y, 10);
		lifes++;
		LOG("%i", lifes);
	}

	if (lifes == 4 && App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		//ballPos.x = 422;
		//ballPos.y = 600;
		if (score > highscore)
		{
			highscore = score;
		}
		App->physics->world->DestroyBody(ball->body);
		ballPos.x = 335;
		ballPos.y = 140;
		ball = App->physics->CreateCircle(ballPos.x, ballPos.y, 10);
		lifes = 0;
		score = 0;

	}

	if (rightTP)
	{
		App->physics->world->DestroyBody(ball->body);
		ballPos.x = 337;
		ballPos.y = 562;
		ball = App->physics->CreateCircle(ballPos.x, ballPos.y, 10);
		rightTP = false;
	}
	if (leftTP)
	{
		App->physics->world->DestroyBody(ball->body);
		ballPos.x = 80;
		ballPos.y = 480;
		ball = App->physics->CreateCircle(ballPos.x, ballPos.y, 10);
		leftTP = false;
	}

	if (combo == 4)
	{
		score += 40;
		combo = 0;
		collision2 = false;
		collision3 = false;
		collision4 = false;
		collision5 = false;
	}
	if (combo2 == 5)
	{
		score += 50;
		combo2 = 0;
		collision = false;
		collision6 = false;
		collision7 = false;
		collision8 = false;
		collision9 = false;
	}

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

	App->renderer->Blit(sprites, App->player->lFlipperPos.x - 78 / 2, App->player->lFlipperPos.y - 48 / 2, &leftFlipperRect, 1.0f, App->player->lFlipper->GetRotation());
	App->renderer->Blit(sprites, App->player->rFlipperPos.x - 78 / 2, App->player->rFlipperPos.y - 48 / 2, &rightFlipperRect, 1.0f, App->player->rFlipper->GetRotation());

	if (lifes <= 4)
	{
		ball->GetPosition(ballPos.x, ballPos.y);
		ball->listener = this;
		App->renderer->Blit(sprites,ballPos.x, ballPos.y, &ballRect);
	}
	
	sensor->GetPosition(circlePos.x, circlePos.y);
	if (!collision2)
	{
		App->renderer->Blit(sprites, circlePos.x, circlePos.y, &blueCircle);
	}
	else if (collision2)
	{
		App->renderer->Blit(sprites, circlePos.x, circlePos.y, &orangeCircle);
	}
	
	sensor2->GetPosition(circlePos3.x, circlePos3.y);
	if (!collision4)
	{
		App->renderer->Blit(sprites, circlePos3.x, circlePos3.y, &blueCircle);
	}
	else if (collision4)
	{
		App->renderer->Blit(sprites, circlePos3.x, circlePos3.y, &orangeCircle);
	}

	sensor3->GetPosition(circlePos4.x, circlePos4.y);
	if (!collision5)
	{
		App->renderer->Blit(sprites, circlePos4.x, circlePos4.y, &blueCircle);
	}
	else if (collision5)
	{
		App->renderer->Blit(sprites, circlePos4.x, circlePos4.y, &orangeCircle);
	}

	smallSensor->GetPosition(circlePos2.x, circlePos2.y);
	if (!collision3)
	{
		App->renderer->Blit(sprites, circlePos2.x, circlePos2.y, &smallSensorRect);
	}
	else if (collision3)
	{
		App->renderer->Blit(sprites, circlePos2.x, circlePos2.y, &sSensorRect);
	}

	bouncer->GetPosition(bouncerPos.x, bouncerPos.y);
	if (!collision)
	{
		App->renderer->Blit(sprites, bouncerPos.x, bouncerPos.y, &bouncerRect);
	}
	else if (collision)
	{
		App->renderer->Blit(sprites, bouncerPos.x, bouncerPos.y, &bouncerLight);
	}

	mediumBouncer->GetPosition(mBouncerPos.x, mBouncerPos.y);
	if (!collision6)
	{
		App->renderer->Blit(sprites, mBouncerPos.x, mBouncerPos.y, &mediumBouncerRect);
	}
	else if (collision6)
	{
		App->renderer->Blit(sprites, mBouncerPos.x, mBouncerPos.y, &mediumBouncerLight);
	}

	mediumBouncer2->GetPosition(mBouncerPos2.x, mBouncerPos2.y);
	if (!collision7)
	{
		App->renderer->Blit(sprites, mBouncerPos2.x, mBouncerPos2.y, &mediumBouncerRect);
	}
	else if (collision7)
	{
		App->renderer->Blit(sprites, mBouncerPos2.x, mBouncerPos2.y, &mediumBouncerLight);
	}

	mediumBouncer3->GetPosition(mBouncerPos3.x, mBouncerPos3.y);
	if (!collision8)
	{
		App->renderer->Blit(sprites, mBouncerPos3.x, mBouncerPos3.y, &mediumBouncerRect);
	}
	else if (collision8)
	{
		App->renderer->Blit(sprites, mBouncerPos3.x, mBouncerPos3.y, &mediumBouncerLight);
	}

	smallBouncer->GetPosition(sBouncerPos.x, sBouncerPos.y);
	if (!collision9)
	{
		App->renderer->Blit(sprites, sBouncerPos.x, sBouncerPos.y, &smallBouncerRect);
	}
	else if (collision9)
	{
		App->renderer->Blit(sprites, sBouncerPos.x, sBouncerPos.y, &smallBouncerLight);
	}
	
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

	sprintf_s(text, 10, "%7d", score);
	App->fonts->BlitText(135, 35, scoreTex, text);

	sprintf_s(text2, 10, "%7d", lifes);
	App->fonts->BlitText(300, 35, scoreTex, text2);

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	if (bodyA != NULL && bodyB != NULL)
	{
		if (bodyA == ball && bodyB == bouncer || bodyA == bouncer && bodyB == ball)
		{
			collision = !collision;
			App->audio->PlayFx(bonus_fx);
			if (collision == true)
			{
				combo2++;
			}
			else if (collision == false)
			{
				combo2--;
			}
			score += 10;
			LOG("COLLISION");
		}
		if (bodyA == ball && bodyB == sensor || bodyA == sensor && bodyB == ball)
		{
			collision2 = !collision2;
			if (collision2 == true)
			{
				combo++;
			}
			else if (collision2 == false)
			{
				combo--;
			}
			score += 10;
			LOG("COLLISION 2");
		}

		if (bodyA == ball && bodyB == lHoleSensor || bodyA == lHoleSensor && bodyB == ball)
		{
			leftTP = true;
		}
		if (bodyA == ball && bodyB == rHoleSensor || bodyA == rHoleSensor && bodyB == ball)
		{
			rightTP = true;
		}
		if (bodyA == ball && bodyB == smallSensor || bodyA == smallSensor && bodyB == ball)
		{
			collision3 = !collision3;
			if (collision3 == true)
			{
				combo++;
			}
			else if (collision3 == false)
			{
				combo--;
			}
			score += 10;
		}
		if (bodyA == ball && bodyB == sensor2 || bodyA == sensor2 && bodyB == ball)
		{
			collision4 = !collision4;
			if (collision4 == true)
			{
				combo++;
			}
			else if (collision4 == false)
			{
				combo--;
			}
			score += 10;
		}
		if (bodyA == ball && bodyB == sensor3 || bodyA == sensor3 && bodyB == ball)
		{
			collision5 = !collision5;
			if (collision5 == true)
			{
				combo++;
			}
			else if (collision5 == false)
			{
				combo--;
			}
			score += 10;
		}
		if (bodyA == ball && bodyB == mediumBouncer || bodyA == mediumBouncer && bodyB == ball)
		{
			collision6 = !collision6;
			if (collision6 == true)
			{
				combo2++;
			}
			else if (collision6 == false)
			{
				combo2--;
			}
			score += 10;
		}
		if (bodyA == ball && bodyB == mediumBouncer2 || bodyA == mediumBouncer2 && bodyB == ball)
		{
			collision7 = !collision7;
			if (collision7 == true)
			{
				combo2++;
			}
			else if (collision7 == false)
			{
				combo2--;
			}
			score += 10;
		}
		if (bodyA == ball && bodyB == mediumBouncer3 || bodyA == mediumBouncer3 && bodyB == ball)
		{
			collision8 = !collision8;
			if (collision8 == true)
			{
				combo2++;
			}
			else if (collision8 == false)
			{
				combo2--;
			}
			score += 10;
		}
		if (bodyA == ball && bodyB == smallBouncer || bodyA == smallBouncer && bodyB == ball)
		{
			collision9 = !collision9;
			if (collision9 == true)
			{
				combo2++;
			}
			else if (collision9 == false)
			{
				combo2--;
			}
			score += 10;
		}

	}
}
