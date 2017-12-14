#ifndef _GAME_H
#define _GAME_H

#include "GameObject.h"
#include <iostream>
#include <fstream>

struct AudioClip
{
	std::string m_name;
	Mix_Chunk* m_clip;
	int m_channel = 0;
};

class Game
{
public :
	Game();
	Game(int width, int height);
	~Game();

	bool InitSystems(); //init window and SDL
	void Run();

	glm::vec2 GetWindowSize() { return glm::vec2(m_windowWidth, m_windowHeight); }
	
	//scene managment
	void AddObject(GameObject* object, int sceneIndex);
	void RemoveObject(std::string name, int sceneIndex);
	void ClearScene();
	void AddSceneToGame();
	void SetActiveScene(int sceneIndex);
	Uint8 GetActiveScene();

	//audio managment
	void ClearSounds();
	void LoadSound(std::string name, std::string path);
	void PlaySound(std::string name, bool loop);
	void StopSound(std::string name);

	void Quit();

private:
	std::vector<GameObject*> m_activeScene;
	std::vector<std::vector<GameObject*>*> m_scenes;
	std::vector<AudioClip*> m_audioClips;
	int m_windowHeight;
	int m_windowWidth;
	bool m_isRunning = true;
	Uint8 m_activeSceneIndex = 0;

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