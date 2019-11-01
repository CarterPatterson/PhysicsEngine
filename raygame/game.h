#pragma once

#include <vector>

#include "physics.h"

class game 
{
	float accumulatedFixedTime;

	std::vector<physicsObj> physicsObjs;

public:
	game();

	void init();
	void tick();
	void tickPhys();
	void draw() const;
	void exit();

	bool shouldClose() const;
	bool shouldPhys() const;

	float targetFixedStep;
};