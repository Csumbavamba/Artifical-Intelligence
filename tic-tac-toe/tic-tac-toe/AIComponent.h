#pragma once

class Player;

class AIComponent
{
public:
	AIComponent();
	~AIComponent();

	void SetOwningPlayer(Player * owner);

private:
	Player * owner = nullptr;
};

