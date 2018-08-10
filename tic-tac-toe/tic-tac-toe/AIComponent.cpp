#include "AIComponent.h"



AIComponent::AIComponent()
{
}


AIComponent::~AIComponent()
{
}

void AIComponent::SetOwningPlayer(Player * owner)
{
	this->owner = owner;
}
