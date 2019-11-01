#include "physics.h"
#include "raylib.h"

glm::vec2 physicsObj::zeroVel()
{
	return { 0,0 };
}

physicsObj::physicsObj()
{
	pos = { 0,0 };
	vel = { 0,0 };
	forces = { 0,0 };
	mass = 1.0f;
	drag = 1.f;
}

void physicsObj::tickPhys(float delta)
{
	//integrating forces into velocity
	vel += forces * delta;
	forces = zeroVel();
	vel *= 1.f - delta * drag;
	//integrating velocity into position
	pos += vel * delta;
}

void physicsObj::draw() const
{
	collider.match([this](aabb s)   { DrawRectangleLines((int)pos.x, (int)pos.y, s.halfExtents.x, s.halfExtents.y, BLUE); },
				   [this](circle s) { DrawCircleLines((int)pos.x, (int)pos.y, 15.f, RED); });
}

void physicsObj::addForce(glm::vec2 force)
{
	forces += force * (1.f / mass);
}

void physicsObj::addImpulse(glm::vec2 impulse)
{
	vel += impulse * (1.f / mass);
}

void physicsObj::addAccel(glm::vec2 accel)
{
	forces += accel;
}

void physicsObj::addVelocityChange(glm::vec2 delta)
{
	vel += delta;
}
