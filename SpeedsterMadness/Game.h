#ifndef _GAME_H
#define _GAME_H

#include "GameObject.h"

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
	~Game();
	Game(int width, int height);

	bool InitSystems(); //init window and SDL
	void Run();

	glm::vec2 GetWindowSize() { return glm::vec2(m_windowWidth, m_windowHeight); }
	
	//scene managment
	void AddObject(GameObject* object);
	void RemoveObject(std::string name);
	void ClearScene();

	//audio managment
	void ClearSounds();
	void LoadSound(std::string name, std::string path);
	void PlaySound(std::string name, bool loop);
	void StopSound(std::string name);

	void Quit();

private:
	std::vector<GameObject*> m_activeScene;
	std::vector<AudioClip*> m_audioClips;
	int m_windowHeight;
	int m_windowWidth;
	bool m_isRunning = true;

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