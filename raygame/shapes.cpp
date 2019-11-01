#include "shapes.h"
#include "glm/glm.hpp"
#include "physics.h"


bool checkCircleCircle(glm::vec2 posA, circle circleA, glm::vec2 posB, circle circleB)
{
	// get distance
	float dist = glm::length(posA - posB);
	// get sum of radii
	float sum = circleA.radius + circleB.radius;
	//make comparison
	return dist < sum;
}

bool checkAABBAABB(glm::vec2 posA, aabb aabbA, glm::vec2 posB, aabb aabbB)
{
	return posA.x - aabbA.halfExtents.x < posB.x - aabbB.halfExtents.x && // l r
		   posA.x + aabbA.halfExtents.x > posB.x - aabbB.halfExtents.x && // r l
		   posA.y - aabbA.halfExtents.y < posB.y + aabbB.halfExtents.y && // t b
		   posA.y + aabbA.halfExtents.y > posB.y - aabbB.halfExtents.y;   // b t
}

bool checkCirlceAABB(glm::vec2 circlePos, circle _circle, glm::vec2 aabbPos, aabb _aabb)
{
	float distX = circlePos.x - glm::clamp(circlePos.x, aabbPos.x - _aabb.halfExtents.x, aabbPos.x + _aabb.halfExtents.x);
	float distY = circlePos.y - glm::clamp(circlePos.y, aabbPos.y - _aabb.halfExtents.y, aabbPos.y + _aabb.halfExtents.y);

	return distX * distX + distY * distY < _circle.radius * _circle.radius;
}

bool checkCircleX(glm::vec2 posA, circle lhs, glm::vec2 posB, shape rhs)
{
	return rhs.match([posA, lhs, posB](circle s) {return checkCircleCircle(posA, lhs, posB, s); },
					 [posA, lhs, posB](aabb s)   {return checkCirlceAABB(posA, lhs, posB, s); });
}

bool checkAABBX(glm::vec2 posA, aabb lhs, glm::vec2 posB, shape rhs)
{
	return rhs.match([posA, lhs, posB](aabb s) {return checkAABBAABB(posA, lhs, posB, s); },
					 [posA, lhs, posB](circle s) {return checkCirlceAABB(posA, s, posB, lhs); });
}

void resolvePhysBodies(physicsObj& lhs, physicsObj& rhs)
{
	glm::vec2 resImpulses[2];

	glm::vec2 normal;
	float pen;

	normal = lhs.collider.match([lhs, rhs, &pen](circle c) {
		float dist = glm::length(lhs.pos - rhs.pos);
		float sum = lhs.collider.get<circle>().radius + rhs.collider.get<circle>().radius;

		pen = sum - dist;
		return glm::normalize(lhs.pos - rhs.pos);
	},
		[lhs, rhs, &pen](aabb a) {
		return glm::vec2();
	});

	resolveCollision(lhs.pos, lhs.vel, lhs.mass, rhs.pos, rhs.vel, rhs.mass, 1.f, normal, resImpulses);

	lhs.pos += normal * pen;
	rhs.pos -= normal * pen;

	lhs.vel = resImpulses[0];
	rhs.vel = resImpulses[1];
}

void resolveCollision(glm::vec2 posA, glm::vec2 velA, float massA, glm::vec2 posB, glm::vec2 velB, float massB, float elasticity, glm::vec2 normal, glm::vec2* dst)
{
	glm::vec2 relVel = velA - velB;
	float impulseMag = (glm::dot(-(1.f + elasticity) * relVel, normal) / glm::dot(normal, normal * (1 / massA + 1 / massB))) / 2;

	dst[0] = velA + (impulseMag / massA) * normal;
	dst[1] = velB - (impulseMag / massB) * normal;
}
