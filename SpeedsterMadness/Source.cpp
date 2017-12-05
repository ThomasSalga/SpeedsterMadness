
#include "Game.h"

int main(int argc, char* args[])
{
	Game game = Game(1280, 768);
	if (game.InitSystems())
	{
		GameObject* panel = game.AddObject("panel");
		panel->LoadTexture("texture.png");

		game.Run();
	}
	return 0;
}