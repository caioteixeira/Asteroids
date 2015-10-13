#pragma once
#include "Actor.h"
#include "InputComponent.h"
#include "MeshComponent.h"
#include "Laser.h"
#include "AudioComponent.h"
#include "SphereCollision.h"

class Ship : public Actor
{
	DECL_ACTOR(Ship, Actor);

public:
	Ship(Game & game);
	InputComponentPtr GetInputComponent();
	AudioComponentPtr GetAudioComponent();
	SphereCollisionPtr GetCollision() { return mColl; };
	void EnableCollision();
	void Tick(float deltaTime) override;
	void FireMissile();
	void BeginPlay() override;
	void BeginTouch(Actor & other) override;
	void OnRespawnShip();
private:
	InputComponentPtr mInput;
	MeshComponentPtr mMeshComponent;
	AudioComponentPtr mAudio;
	TexturePtr mTexture1;
	TexturePtr mTexture2;
	SoundPtr mFireSound;
	SoundPtr mEngineSound;
	SoundCue mEngineCue;
	SphereCollisionPtr mColl;
	bool mCollisionIsEnabled;
};
DECL_PTR(Ship);