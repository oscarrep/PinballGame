#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:

	//int count = 0;
	bool collision = false;

	//int count2 = 0;
	bool collisionSensor = false;

	bool rightTP = false;
	bool leftTP = false;

	p2List<PhysBody*>	circles;
	p2List<PhysBody*>	boxes;
	p2List<PhysBody*>	Bouncer;
	p2List<PhysBody*>	chains;


	PhysBody*			sensor;
	PhysBody*			rHoleSensor;
	PhysBody*			lHoleSensor;
	PhysBody*			ball;
	PhysBody*			circlePoint;
	PhysBody*			bouncer;
	PhysBody*			tBumper;
	PhysBody*			lBumper;
	PhysBody*			rBumper;

	SDL_Texture*		circle;
	SDL_Texture*		box;
	SDL_Texture*		sprites;

	SDL_Rect			tableRect;
	SDL_Rect			ballRect;
	SDL_Rect			bouncerRect;
	SDL_Rect			blueCircle;
	SDL_Rect			orangeCircle;
	SDL_Rect			bouncerLight;
	
	iPoint				ballPos; 
	iPoint				circlePos; 
	iPoint				bouncerPos;
	iPoint				bumperPos;
	iPoint				rHolePos;
	iPoint				lHolePos;

	uint				bonus_fx;
};
