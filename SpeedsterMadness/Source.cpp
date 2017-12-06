
#include "Game.h"
#include "SM_Controller.h"

int main(int argc, char* args[])
{
	Game game = Game(1280, 768);
	if (game.InitSystems())
	{
		//create BackGround object

		//create button texture object (background sprite for all the buttons)

		//create button font objects (text on top of the button)

		//create player object
		SM_Controller* player = new SM_Controller();
		player->SetName("playerObject");
		game.AddObject(player);
		//customize player object
		player->LoadTexture("Assets/Images/SMPlayer1.png");
		player->m_position = glm::vec2(game.GetWindowSize().x / 2 - player->m_dimensions.x / 2, game.GetWindowSize().y / 2 - player->m_dimensions.y / 2);
		//Load sounds for player
		
		//create obstacle object

		//
		

		/*GameObject* panel = game.AddObject("panel");
		panel->LoadTexture("texture.png");

		GameObject* font = game.AddObject("font");
		font->LoadFont("PressStart2P.ttf");
		font->DrawTextColor("Hello", { 0,0,0 });*/
		
		game.LoadSound("Ambient", "beat.wav"); //change sounds
		game.LoadSound("Button", "beat.wav");
		
		game.Run(); // don't add anything after this line
	}
	return 0;
}