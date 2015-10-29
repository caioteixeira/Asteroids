#include "Asteroid.h"
#include "Game.h"
#include "MeshComponent.h"
#include "MoveComponent.h"
#include "Random.h"
#include "SphereCollision.h"
IMPL_ACTOR(Asteroid, Actor);


Asteroid::Asteroid(Game & game) : Actor(game)
{
	//Create a mesh component
	auto meshComponent = MeshComponent::Create(*this);
	auto& assetCache = game.GetAssetCache();
	auto mesh = assetCache.Load<Mesh>("Meshes/AsteroidMesh.itpmesh2");
	meshComponent->SetMesh(mesh);

	//Set Random rotation
	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	//Set SphereCollision
	auto coll = SphereCollision::Create(*this);
	coll->RadiusFromMesh(mesh);
	coll->SetScale(0.9f);

	//Set explosion sound
	mAudio = AudioComponent::Create(*this);
	mExplosionSound = assetCache.Load<Sound>("Sounds/AsteroidDie.wav");

	//Set Movement
	auto move = MoveComponent::Create(*this, Component::PreTick);
	move->SetLinearSpeed(150.0f);
	move->SetLinearAxis(1.0f);
}

void Asteroid::BeginTouch(Actor & other){
	if (other.IsAlive() && IsA<Laser>(other))
	{
		// Play Sound
		mAudio->PlaySound(mExplosionSound);

		//Spawn new asteroids
		if (GetScale() == 0.75f)
		{
			for (int i = 0; i < 4; i++)
			{
				auto ast = Asteroid::Spawn(mGame);
				ast->SetPosition(GetPosition());
				ast->SetScale(0.25f);
			}
		}

		//Destroy
		SetIsAlive(false);
		other.SetIsAlive(false);
	}
}