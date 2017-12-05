#ifndef _GAME_H
#define _GAME_H

#include "GameObject.h"

class Game
{
public :
	Game();
	~Game();
	Game(int width, int height);

	bool InitSystems(); //init window and SDL
	void Run();
	
	//scene managment
	GameObject* AddObject(std::string name);
	void RemoveObject(std::string name);
	void ClearScene();

private:
	std::vector<GameObject*> m_activeScene;
	int m_windowHeight;
	int m_windowWidth;

	//The window we'll be rendering to
	SDL_Window* m_window = NULL;

	//The window renderer
	SDL_Renderer* m_renderer = NULL;

	void Start();
	void Update(double delta, Input in);
	void Draw();
	void DrawText();

	double m_deltaTime;
};

#endif