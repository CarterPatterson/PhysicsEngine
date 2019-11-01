#pragma once

#include "glm/vec2.hpp"
#include "mapbox/variant.hpp"

struct circle
{
	float radius;
};

struct aabb
{
	glm::vec2 halfExtents;
};

using shape = mapbox::util::variant<circle, aabb>;

bool checkCircleCircle(glm::vec2 posA, circle circleA, glm::vec2 posB, circle circleB);

bool checkAABBAABB(glm::vec2 posA, aabb aabbA, glm::vec2 posB, aabb aabbB);

bool checkCirlceAABB(glm::vec2 circlePos, circle _circle, glm::vec2 aabbPos, aabb _aabb);

bool checkCircleX(glm::vec2 posA, circle lhs, glm::vec2 posB, shape rhs);

bool checkAABBX(glm::vec2 posA, aabb lhs, glm::vec2 posB, shape rhs);

void resolvePhysBodies(class physicsObj& lhs, class physicsObj& rhs);

void resolveCollision(glm::vec2 posA, glm::vec2 velA, float massA, glm::vec2 posB, glm::vec2 velB, float massB, float elasticity, glm::vec2 normal, glm::vec2* dst);