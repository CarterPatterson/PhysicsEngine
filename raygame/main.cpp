#include "raylib.h"
#include "game.h"

game app;

int main()
{
	app.init();
	app.targetFixedStep = 1.f / 30.f;

	while (!app.shouldClose())
	{
		app.tick();

		while (app.shouldPhys()) {
			app.tickPhys();
		}


		app.draw();
	}


	return 0;
}