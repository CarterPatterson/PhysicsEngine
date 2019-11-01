#pragma once

#include "glm/glm.hpp"
#include "shapes.h"

class physicsObj
{
	glm::vec2 zeroVel();

public:
	physicsObj();

	glm::vec2 pos;
	glm::vec2 vel;

	glm::vec2 forces;

	float mass;
	float drag;

	shape collider;

	void tickPhys(float delta);
	void draw() const;

	// add continuous force with respect to mass
	void addForce(glm::vec2 force);
	// add instantaneous force with respect to mass
	void addImpulse(glm::vec2 impulse);
	// accelerates the object w/o respect to mass
	void addAccel(glm::vec2 accel);
	// adds an instantaneous force w/o respect to mass
	void addVelocityChange(glm::vec2 delta);
};