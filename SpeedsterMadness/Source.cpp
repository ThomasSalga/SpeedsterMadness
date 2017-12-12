
#include "Game.h"
#include "BackGround.h"
#include "ButtonTexture.h"
#include "Text.h"
#include "SM_Controller.h"
#include "ObstacleMng.h"

/*
void CreateObject(Game g, GameObject* obj, std::string name, std::vector<int> allIndexes)
{
	obj->SetName(name);
	for(int sIndex : allIndexes)
		g.AddObject(obj, sIndex);
	//customize ButtonTexture object
	//obj->LoadTexture("Assets/Images/ButtonTexture.png");
	//obj->m_position = glm::vec2(g.GetWindowSize().x / 2 - obj->m_dimensions.x / 2, g.GetWindowSize().y / 2 - obj->m_dimensions.y / 2);
}

void CustomizeButton(Game g, GameObject* obj, std::string path, glm::vec2 pos)
{
	//customize button object
	obj->LoadTexture(path);
	obj->m_position = glm::vec2(g.GetWindowSize().x * pos[0] - obj->m_dimensions.x / 2, g.GetWindowSize().y * pos[1] - obj->m_dimensions.y / 2);
}
void CustomizeText(GameObject* obj, std::string path, int dimension, std::string text, SDL_Color color, glm::vec2 pos)
{
	//customize text object
	obj->LoadFont(path, dimension);
	obj->DrawTextColor(text, color);
	obj->m_position = pos;
}
*/


int main(int argc, char* args[])
{
	Game game = Game(1024, 768);
	if (game.InitSystems())
	{
		//create scenes for our game
		game.AddSceneToGame();//the intro scene			index 0
		game.AddSceneToGame();//the menu scene			index 1
		game.AddSceneToGame();//the game scene			index 2
		//game.AddSceneToGame();//the end scene			index 3
		//game.AddSceneToGame();//the score scene		index 4

		/*=====================================================================================================================================================*/
		/*================================================================    INTRO SCENE    ==================================================================*/
		/*=====================================================================================================================================================*/
		
////////// create BackGround  
#pragma region BackGround
		BackGround* bg = new BackGround();
		bg->SetName("backGround");
		game.AddObject(bg, 0);
		game.AddObject(bg, 1);
		game.AddObject(bg, 2);
		//customize background object
		bg->LoadTexture("Assets/Images/BackGround.png");
		bg->m_position = glm::vec2(game.GetWindowSize().x / 2 - bg->m_dimensions.x / 2, game.GetWindowSize().y / 2 - bg->m_dimensions.y / 2);
#pragma endregion
		////////// create BackGround  
#pragma region Road
		BackGround* rd = new BackGround();
		rd->SetName("road");
		game.AddObject(rd, 1);
		//customize background object
		rd->LoadTexture("Assets/Images/Road.png");
		rd->m_position = glm::vec2(game.GetWindowSize().x / 3 - rd->m_dimensions.x / 2, game.GetWindowSize().y / 2 - rd->m_dimensions.y / 2);
#pragma endregion
////////// create Title
#pragma region Title
		Text* title = new Text();
		Text* title2 = new Text();

		title->SetName("title1");
		game.AddObject(title, 0);
		//customize ButtonTexture object
		title->LoadFont("Assets/PressStart2P.ttf", 30);
		title->DrawTextColor("RETROFUTURISTICARCADE", { 200,80,255 });
		title->m_position = glm::vec2(glm::vec2(game.GetWindowSize().x / 2 - title->m_dimensions.x / 2, game.GetWindowSize().y / 6 - title->m_dimensions.y / 2));

		title2->SetName("title2");
		game.AddObject(title2, 0);
		//customize ButtonTexture object
		title2->LoadFont("Assets/PressStart2P.ttf", 30);
		title2->DrawTextColor("SPEEDSTER MADNESS", { 20,30,255 });
		title2->m_position = glm::vec2(glm::vec2(game.GetWindowSize().x / 2 - title2->m_dimensions.x / 2, game.GetWindowSize().y / 5 - title2->m_dimensions.y / 2));
#pragma endregion
////////// create ButtonTexture object (background sprite for all the buttons)
#pragma region Play button
		ButtonTexture* play_sprite = new ButtonTexture();
		play_sprite->SetName("playBtn");
		game.AddObject(play_sprite, 0);
		//customize ButtonTexture object
		play_sprite->AssignSceneLinkIndex(1);
		play_sprite->LoadTexture("Assets/Images/ButtonSprite.png");
		play_sprite->m_position = glm::vec2(game.GetWindowSize().x / 5 - play_sprite->m_dimensions.x / 2, game.GetWindowSize().y * 4 / 5 - play_sprite->m_dimensions.y / 2);
//////////create ButtonFont objects (text on top of the button)
		Text* btn_play_text = new Text();
		btn_play_text->SetName("btn_play_text");
		game.AddObject(btn_play_text,0);
		//customize ButtonFont object
		btn_play_text->LoadFont("Assets/PressStart2P.ttf", 12);
		btn_play_text->DrawTextColor("PLAY", { 100,150,255 });
		btn_play_text->m_position = glm::vec2(game.GetWindowSize().x / 5 - btn_play_text->m_dimensions.x / 2, game.GetWindowSize().y * 4 / 5 - btn_play_text->m_dimensions.y / 2);
#pragma endregion
//GAMEOVER text
#pragma region GAMEOVE_text
		Text* gameover_text = new Text();
		gameover_text->SetName("gameover_text");
		game.AddObject(gameover_text, 2);
		//customize ButtonFont object
		gameover_text->LoadFont("Assets/PressStart2P.ttf", 40);
		gameover_text->DrawTextColor("GAME OVER", { 200,50,255 });
		gameover_text->m_position = glm::vec2(game.GetWindowSize().x / 2 - gameover_text->m_dimensions.x / 2, game.GetWindowSize().y / 6 - gameover_text->m_dimensions.y / 2);
#pragma endregion
//////////create ButtonFont objects (text on top of the button)
#pragma region Replay button
		ButtonTexture* replay_sprite = new ButtonTexture();
		replay_sprite->SetName("replayBtn");
		game.AddObject(replay_sprite, 2);
		//customize ButtonTexture object
		replay_sprite->AssignSceneLinkIndex(1);
		replay_sprite->LoadTexture("Assets/Images/ButtonSprite.png");
		replay_sprite->m_position = glm::vec2(game.GetWindowSize().x / 5 - replay_sprite->m_dimensions.x / 2, game.GetWindowSize().y * 4 / 5 - replay_sprite->m_dimensions.y / 2);
//////////create ButtonFont objects (text on top of the button)
		Text* btn_replay_text = new Text();
		btn_replay_text->SetName("btn_replay_text");
		game.AddObject(btn_replay_text, 2);
		//customize ButtonFont object
		btn_replay_text->LoadFont("Assets/PressStart2P.ttf", 12);
		btn_replay_text->DrawTextColor("REPLAY", { 100,150,255 });
		btn_replay_text->m_position = glm::vec2(game.GetWindowSize().x / 5 - btn_replay_text->m_dimensions.x / 2, game.GetWindowSize().y * 4 / 5 - btn_replay_text->m_dimensions.y / 2);
#pragma endregion
//////////create player object
#pragma region Player
		SM_Controller* player = new SM_Controller();
		player->SetName("playerObject");
		game.AddObject(player,1);
		//customize player object
		player->LoadTexture("Assets/Images/SMPlayer1.png");
		player->m_position = glm::vec2(game.GetWindowSize().x / 3 - player->m_dimensions.x / 2, game.GetWindowSize().y / 2 - player->m_dimensions.y / 2);
		//Load sounds for player
#pragma endregion		
//////////create Obstacles
#pragma region Obstacles
		ObstacleMng* cars = new ObstacleMng();
		cars->SetName("car");
		game.AddObject(cars, 1);
#pragma endregion
		
		
		
		//Load all required audio here
		game.LoadSound("Ambient", "Assets/Audio/beat.wav"); //check sound name and path, when working place in correct spot !!!
		game.LoadSound("Button", "Assets/Audio/Button.mp3");
		

		game.SetActiveScene(0);
		//once you Run nobody is gonna stop you
		game.Run(); // don't add anything after this line
		game.~Game(); //does game destructor be called when the main scope ends??
	}
	return 0;
}