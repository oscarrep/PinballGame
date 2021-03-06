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
#include "ModuleEnd.h"


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

	App->endScene->Disable();
	App->renderer->camera.x = App->renderer->camera.y = 0;

	sprites = App->textures->Load("pinball/textures.png");

	scoreTex = App->fonts->Load("pinball/Score.png", "0123456789", 1);

	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	bluefx = App->audio->LoadFx("pinball/bluesensor.wav");	
	tpfx = App->audio->LoadFx("pinball/tpfx.wav");

	App->audio->PlayMusic("pinball/pinball_song.ogg");
	Mix_VolumeMusic(20);

	fx = App->physics->CreateRectangleSensor(410, 42, 24, 24);
	volume = App->physics->CreateRectangleSensor(39, 42, 24, 24);

	// ---------------------------------------------------   Rectangle measurements


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

	ballRect.x = 9;
	ballRect.y = 434;
	ballRect.h = 14;
	ballRect.w = 14;

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

	// ---------------------------------------------------   Initializing all the positions of the bodies


	bumperPos.x = -SCREEN_WIDTH / 2.0f;
	bumperPos.y = -SCREEN_HEIGHT / 2.08f;

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

	ballPos.x = 415;
	ballPos.y = 400;

	// ---------------------------------------------------   Creating the bodies
	
	ball = App->physics->CreateCircle(ballPos.x, ballPos.y, 7);

	// BOUNCERS

	bouncer = App->physics->CreateStaticCircle(bouncerPos.x, bouncerPos.y, 25);
	bouncer->body->GetFixtureList()->SetRestitution(1.5f);

	mediumBouncer = App->physics->CreateStaticCircle(mBouncerPos.x, mBouncerPos.y, 17);
	mediumBouncer->body->GetFixtureList()->SetRestitution(1.5f);

	mediumBouncer2 = App->physics->CreateStaticCircle(mBouncerPos2.x, mBouncerPos2.y, 17);
	mediumBouncer2->body->GetFixtureList()->SetRestitution(1.5f);

	mediumBouncer3 = App->physics->CreateStaticCircle(mBouncerPos3.x, mBouncerPos3.y, 17);
	mediumBouncer3->body->GetFixtureList()->SetRestitution(1.5f);

	smallBouncer = App->physics->CreateStaticCircle(sBouncerPos.x, sBouncerPos.y, 12);
	smallBouncer->body->GetFixtureList()->SetRestitution(1.5f);

	// SENSORS

	sensor = App->physics->CreateCircleSensor(circlePos.x, circlePos.y, 18);
	sensor2 = App->physics->CreateCircleSensor(circlePos3.x, circlePos3.y, 18);
	sensor3 = App->physics->CreateCircleSensor(circlePos4.x, circlePos4.y, 18);

	lHoleSensor = App->physics->CreateCircleSensor(lHolePos.x, lHolePos.y, 10);
	rHoleSensor = App->physics->CreateCircleSensor(rHolePos.x, rHolePos.y, 10);

	smallSensor = App->physics->CreateCircleSensor(circlePos2.x, circlePos2.y, 15);

	// BUMPERS

	tBumper = App->physics->CreateChain(bumperPos.x, bumperPos.y, topBumper, 12);
	tBumper->body->GetFixtureList()->SetRestitution(0.5f);
	
	rBumper = App->physics->CreateChain(bumperPos.x, bumperPos.y, rightBumper, 10);
	rBumper->body->GetFixtureList()->SetRestitution(0.5f);
	
	lBumper = App->physics->CreateChain(bumperPos.x, bumperPos.y, leftBumper, 14);
	lBumper->body->GetFixtureList()->SetRestitution(0.5f);

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

	//Audio volume management

	if (App->input->GetMouseX() <= 44 && App->input->GetMouseY() <= 42 && App->input->GetMouseX() >= 20 && App->input->GetMouseY() >= 18 && App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		mute = !mute;
	}

	if (mute)
	{
		Mix_VolumeMusic(0);
	}
	if (!mute)
	{
		Mix_VolumeMusic(20);
	}

	/*if (App->input->GetMouseX() <= 410 && App->input->GetMouseY() <= 42 && App->input->GetMouseX() >= 386 && App->input->GetMouseY() >= 18 && App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		mutefx = !mutefx;
	}
	if (mutefx)
	{
		Mix_VolumeChunk(0);
	}
	if (!mutefx)
	{
		Mix_VolumeChunk(20);
	}*/

	sprintf_s(scoreChar, 10, "%7d", score);
	App->fonts->BlitText(135, 35, scoreTex, scoreChar);

	sprintf_s(lifesChar, 10, "%7d", lifes);
	App->fonts->BlitText(300, 35, scoreTex, lifesChar);

	sprintf_s(highscoreChar, 10, "%7d", highscore);
	App->fonts->BlitText(260, 35, scoreTex, highscoreChar);

	sprintf_s(prevScoreChar, 10, "%7d", prevScore);
	App->fonts->BlitText(200, 35, score, prevScoreChar);

	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		App->physics->world->DestroyBody(ball->body);
		ball = App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 7);
	}
	
	// -------------------------------------------    Player life

	if (ballPos.y >= 768 && lifes < 4)
	{
		App->physics->world->DestroyBody(ball->body);
		ballPos.x = 415;
		ballPos.y = 400;
		ball = App->physics->CreateCircle(ballPos.x, ballPos.y, 7);
		lifes++;
		LOG("%i", lifes);
		finalScore = score;

	}

	// -------------------------------------------    Restart

	if (lifes == 4)
	{
		//ballPos.x = 422;
		//ballPos.y = 600;
		if (score > highscore)
		{
			highscore = score;
		}
		App->physics->world->DestroyBody(ball->body);
		ballPos.x = 415;
		ballPos.y = 400;
		ball = App->physics->CreateCircle(ballPos.x, ballPos.y, 7);
		lifes = 0;
		score = 0;
		App->endScene->Enable();
		prevScore = finalScore;

	}

	if (rightTP && !jointed)
	{
		App->physics->world->DestroyBody(ball->body);
		ballPos.x = 337;
		ballPos.y = 562;
		ball = App->physics->CreateCircle(ballPos.x, ballPos.y, 7);
		rightTP = false;
	}
	if (leftTP && !jointed)
	{
		App->physics->world->DestroyBody(ball->body);
		ballPos.x = 80;
		ballPos.y = 480;
		ball = App->physics->CreateCircle(ballPos.x, ballPos.y, 7);
		leftTP = false;
	}

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
			App->audio->PlayFx(bluefx);

			if (collision2 == true)
			{
				combo++;
			}
			else if (collision2 == false)
			{
				combo--;
			}
			score += 5;
			LOG("COLLISION 2");
		}

		if (bodyA == ball && bodyB == lHoleSensor || bodyA == lHoleSensor && bodyB == ball)
		{
			leftTP = true;
			App->audio->PlayFx(tpfx);

		}
		if (bodyA == ball && bodyB == rHoleSensor || bodyA == rHoleSensor && bodyB == ball)
		{
			rightTP = true;
			App->audio->PlayFx(tpfx);

		}
		if (bodyA == ball && bodyB == smallSensor || bodyA == smallSensor && bodyB == ball)
		{
			collision3 = !collision3;
			App->audio->PlayFx(bluefx);

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
			App->audio->PlayFx(bluefx);

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
			App->audio->PlayFx(bluefx);

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
			App->audio->PlayFx(bonus_fx);

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
			App->audio->PlayFx(bonus_fx);

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
			App->audio->PlayFx(bonus_fx);

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
			App->audio->PlayFx(bonus_fx);

			if (collision9 == true)
			{
				combo2++;
			}
			else if (collision9 == false)
			{
				combo2--;
			}
			score += 15;
		}

	}
}