#include "InputComponent.h"
#include "Actor.h"
#include "InputManager.h"
#include "Game.h"

IMPL_COMPONENT(InputComponent, MoveComponent);

InputComponent::InputComponent(Actor& owner):
	MoveComponent(owner)
{

}

void InputComponent::BindAngularAxis(const std::string &name)
{
	InputManager input = mOwner.GetGame().GetInput();
	input.BindAxis(name, this, &InputComponent::OnAngularAxis);
}

void InputComponent::BindLinearAxis(const std::string &name)
{
	InputManager input = mOwner.GetGame().GetInput();

	input.BindAxis(name, this, &InputComponent::OnLinearAxis);
}

void InputComponent::OnAngularAxis(float value)
{
	SetAngularAxis(value);
}

void InputComponent::OnLinearAxis(float value)
{
	SetLinearAxis(value);
}