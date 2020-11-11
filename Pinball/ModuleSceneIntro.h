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

	int lifes = 0;

	//int count = 0;
	bool collision = false;
	bool collision3 = false;
	bool collision4 = false;
	bool collision5 = false;
	bool collision6 = false;
	bool collision7 = false;
	bool collision8 = false;
	bool collision9 = false;

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
	PhysBody*			smallSensor;
	PhysBody*			sensor2;
	PhysBody*			sensor3;
	PhysBody*			ball;
	PhysBody*			circlePoint;
	PhysBody*			bouncer;
	PhysBody*			mediumBouncer;
	PhysBody*			mediumBouncer2;
	PhysBody*			mediumBouncer3;
	PhysBody*			smallBouncer;
	PhysBody*			tBumper;
	PhysBody*			lBumper;
	PhysBody*			rBumper;
	PhysBody*			rFlipper;
	PhysBody*			lFlipper;

	SDL_Texture*		circle;
	SDL_Texture*		box;
	SDL_Texture*		sprites;

	SDL_Rect			tableRect;
	SDL_Rect			ballRect;
	SDL_Rect			bouncerRect;
	SDL_Rect			mediumBouncerRect;
	SDL_Rect			smallBouncerRect;
	SDL_Rect			smallSensorRect;
	SDL_Rect			blueCircle;
	SDL_Rect			orangeCircle;
	SDL_Rect			bouncerLight;
	SDL_Rect			mediumBouncerLight;
	SDL_Rect			smallBouncerLight;
	SDL_Rect			sSensorRect;
	
	iPoint				ballPos; 
	iPoint				circlePos, circlePos2, circlePos3, circlePos4;
	iPoint				bouncerPos, mBouncerPos, mBouncerPos2, mBouncerPos3, sBouncerPos;
	iPoint				bumperPos;
	iPoint				rHolePos;
	iPoint				lHolePos;
	iPoint				rightFlipperPos;
	iPoint				leftFlipperPos;

	uint				bonus_fx;
};
