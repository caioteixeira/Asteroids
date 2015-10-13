#pragma once
#include "Actor.h"

class Laser: public Actor
{
	DECL_ACTOR(Laser, Actor);

public:
	Laser(Game & game);
	void Tick(float deltaTime) override;
	void OnDieTimer();
	void BeginPlay() override;
private:
};
DECL_PTR(Laser);