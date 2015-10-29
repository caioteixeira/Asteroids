#include "Ship.h"
#include "Game.h"
#include "Sound.h"
#include "Asteroid.h"
#include "Mesh.h"


IMPL_ACTOR(Ship, Actor);

Ship::Ship(Game & game) : Actor(game)
{
	//Create a mesh component
	mMeshComponent = MeshComponent::Create(* this);
	auto& assetCache = game.GetAssetCache();
	auto mesh = assetCache.Load<Mesh>("Meshes/PlayerShip.itpmesh2");
	mMeshComponent->SetMesh(mesh);

	//Load the laser sound
	mAudio = AudioComponent::Create(*this);
	mFireSound = assetCache.Load<Sound>("Sounds/Laser.wav");
	mEngineSound = assetCache.Load<Sound>("Sounds/ShipEngine.wav");
	mEngineCue = GetAudioComponent()->PlaySound(mEngineSound,true);
	mEngineCue.Pause();

	//Set Movement
	mInput = InputComponent::Create(*this, Component::PreTick);
	mInput->SetLinearSpeed(150.0f);
	mInput->SetAngularSpeed(Math::TwoPi);
	
	//Set SphereCollision
	mColl = SphereCollision::Create(*this);
	mColl->RadiusFromMesh(mesh);
	mColl->SetScale(0.5f);
	mCollisionIsEnabled = false;

	SetScale(0.5f);
}

void Ship::BeginPlay()
{
	mInput->BindAngularAxis("Rotate");
	mInput->BindLinearAxis("Move");
	mGame.GetInput().BindAction("Fire", IE_Pressed, this, &Ship::FireMissile);
	
	TimerHandle handle;
	mGame.GetTime().SetTimer(handle, this, &Ship::EnableCollision, 1.5f);
}

InputComponentPtr Ship::GetInputComponent()
{
	return mInput;
}

AudioComponentPtr Ship::GetAudioComponent()
{
	return mAudio;
}

void Ship::Tick(float deltaTime)
{
	//Update the rotation
	if (mInput->GetAngularSpeed() != 0.0f)
	{
		auto newRotation = GetRotation() + (mInput->GetAngularSpeed() * mInput->GetAngularAxis() * deltaTime);
		SetRotation(newRotation); 
	}

	//Update the Texture and turn on/off the engine sound
	if (mInput->GetLinearAxis() != 0.0f)
	{
		mEngineCue.Resume();
	}
	else
	{
		mEngineCue.Pause();
	}

	

	Super::Tick(deltaTime);
}
void Ship::FireMissile()
{
	if (GetIsPaused())
		return;

	auto laser = Laser::Spawn(GetGame());
	laser->SetPosition(GetPosition());
	laser->SetRotation(GetRotation());

	GetAudioComponent()->PlaySound(mFireSound);
}

void Ship::BeginTouch(Actor& other)
{
	if (other.IsAlive() && IsA<Asteroid>(other) && mCollisionIsEnabled)
	{
		//Play sound
		SetIsPaused(true);
		mMeshComponent->SetIsVisible(false);
		TimerHandle handle;
		mGame.GetTime().SetTimer(handle, this, &Ship::OnRespawnShip, 1.0f);
	}
}

void Ship::OnRespawnShip()
{
	SetIsPaused(false);
	SetRotation(Math::PiOver2);
	SetPosition(Vector3::Zero);
	mCollisionIsEnabled = false;
	mMeshComponent->SetIsVisible(true);

	TimerHandle handle;
	mGame.GetTime().SetTimer(handle, this, &Ship::EnableCollision, 2.0f);
}

void Ship::EnableCollision()
{
 	mCollisionIsEnabled = true;
}