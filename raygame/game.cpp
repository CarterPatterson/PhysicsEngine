#include "game.h"
#include "raylib.h"
#include <iostream>

game::game()
{
	targetFixedStep = 1.f / 30.f;
	accumulatedFixedTime = 0;
}

void game::init()
{
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);
}

void game::tick()
{
	accumulatedFixedTime += GetFrameTime();

	bool mb0 = IsMouseButtonPressed(0);
	bool mb1 = IsMouseButtonPressed(1);

	if (mb0 || mb1) {
		physicsObjs.emplace_back();
		std::cout << "Added a new physics object." << std::endl;

		auto& babyPhys = physicsObjs[physicsObjs.size() - 1];
		auto mousePos = GetMousePosition();
		babyPhys.pos = { mousePos.x, mousePos.y };

		if (mb0){
			babyPhys.collider = circle{ 15.f };
		}

		if (mb1) {
			babyPhys.collider = aabb{ {15.f, 15.f} };
		}
	}
}

void game::tickPhys()
{
	accumulatedFixedTime -= targetFixedStep;
	
	for (auto& i : physicsObjs) {
		i.tickPhys(targetFixedStep);
	}

	for (auto& i : physicsObjs) {
		for (auto& j : physicsObjs) {
			// skip self collision
			if (&i == &j) { continue; }

			bool collision = false;

			i.collider.match([i, j, &collision](circle c) {if (checkCircleX(i.pos, c, j.pos, j.collider)) { collision = true; } },
							 [i, j, &collision](aabb a) {if (checkAABBX(i.pos, a, j.pos, j.collider)) { collision = true; } });
			if (collision) { resolvePhysBodies(i, j); }
		}
	}
}

void game::draw() const
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	for (const auto& i : physicsObjs) {
		i.draw();
	}

	EndDrawing();
}

void game::exit()
{
}

bool game::shouldClose() const
{
	return WindowShouldClose();
}

bool game::shouldPhys() const
{
	return accumulatedFixedTime >= targetFixedStep;
}
