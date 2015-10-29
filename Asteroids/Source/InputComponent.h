#pragma once
#include "MoveComponent.h"
#include <string>

class InputComponent : public MoveComponent
{
	DECL_COMPONENT(InputComponent, MoveComponent);
public:
	InputComponent(Actor& owner);
	void BindLinearAxis(const std::string& name);
	void BindAngularAxis(const std::string& name);
	void OnLinearAxis(float value);
	void OnAngularAxis(float value);
private:

};
DECL_PTR(InputComponent);