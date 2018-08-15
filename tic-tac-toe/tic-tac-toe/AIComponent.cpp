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

PlayState * AIComponent::SelectBestPlay()
{
	// Go through the generated gameState first moves
	// Select the one with the highest point
	// Make player place on the best position
}

