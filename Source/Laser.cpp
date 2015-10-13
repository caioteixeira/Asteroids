#include "Laser.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "SphereCollision.h"
IMPL_ACTOR(Laser, Actor);

Laser::Laser(Game & game) :Actor(game)
{
	//Create a sprite component
	auto sprite = SpriteComponent::Create(*this);
	auto assetCache = game.GetAssetCache();
	auto texture = assetCache.Load<Texture>("Textures/Laser.png");
	sprite->SetTexture(texture);

	//Set Movement
	auto move = MoveComponent::Create(*this, Component::PreTick);
	move->SetLinearSpeed(600.0f);
	move->SetLinearAxis(1.0f);
	
	//Set SphereCollision
	auto coll = SphereCollision::Create(*this);
	coll->RadiusFromTexture(texture);
	coll->SetScale(0.9f);

}

void Laser::Tick(float deltaTime)
{
	

	Super::Tick(deltaTime);
}

void Laser::OnDieTimer()
{
	SetIsAlive(false);
}

void Laser::BeginPlay()
{
	TimerHandle handle;
	mGame.GetTime().SetTimer(handle, this, &Laser::OnDieTimer, 1.0f);
}

