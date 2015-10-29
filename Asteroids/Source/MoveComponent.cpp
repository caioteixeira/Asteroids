#include "MoveComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"

IMPL_COMPONENT(MoveComponent, Component);

MoveComponent::MoveComponent(Actor& owner)
	:Component(owner)
	,mLinearSpeed(0.0f)
	,mAngularSpeed(0.0f)
	,mLinearAxis(0.0f)
	,mAngularAxis(0.0f)
{

}

void MoveComponent::Tick(float deltaTime)
{
	if (!Math::IsZero(mLinearAxis))
	{
		//Update velocity on current forward
		mVelocity = mOwner.GetForward()*(mLinearSpeed*mLinearAxis);
		//Update position of owner based on velocity
		mOwner.SetPosition(mOwner.GetPosition() + (mVelocity*deltaTime));

		//Screen Wrap
		Vector3 position = mOwner.GetPosition();
		float newX = position.x;
		float newY = position.y;
		bool wrapped = false;
		if (position.x < -512.0f || position.x > 512.0f)
		{
			newX = position.x * -1;
			wrapped = true;
		}
		if (position.y < -384 || position.y > 384)
		{
			newY = position.y * -1;
			wrapped = true;
		}
		if (wrapped)
		{
			Vector3 newPos(newX, newY, position.z);
			mOwner.SetPosition(newPos);
		}
		
	}
}

void MoveComponent::AddToLinearAxis(float delta)
{
	mLinearAxis += delta;
	mLinearAxis = Math::Clamp(mLinearAxis, -1.0f, 1.0f);
}

void MoveComponent::AddToAngularAxis(float delta)
{
	mAngularAxis += delta;
	mAngularAxis = Math::Clamp(mAngularAxis, -1.0f, 1.0f);
}

void MoveComponent::SetLinearAxis(float axis)
{
	mLinearAxis = Math::Clamp(axis, -1.0f, 1.0f);
}

void MoveComponent::SetAngularAxis(float axis)
{
	mAngularAxis = Math::Clamp(axis, -1.0f, 1.0f);
}
