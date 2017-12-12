#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
	ClearScene();
	ClearSounds();

	//Destroy window	
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	m_window = NULL;
	m_renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

Game::Game(int width, int height)
{
	m_windowWidth = width;
	m_windowHeight = height;
}

bool Game::InitSystems()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)  < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		m_window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_windowWidth, m_windowHeight, SDL_WINDOW_SHOWN);
		if (m_window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
			if (m_renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}

				//Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}

	m_deltaTime = SDL_GetTicks();

	return success;
}

void Game::Run()
{
	Start();

	//Event handler
	SDL_Event e;


	//While application is running
	while (m_isRunning)
	{
		//calculate deltaTime
		double time = SDL_GetTicks();
		double delta = time - m_deltaTime;
		m_deltaTime = time;

		//
		Input input;

		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);
		input.mouseState.x = x;
		input.mouseState.y = y;

		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				m_isRunning = false;
			}

			//If mouse event happened
			if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
			{
				switch (e.type)
				{
				case SDL_MOUSEBUTTONDOWN:
					if (e.button.button == SDL_BUTTON_LEFT)
						input.mouseState.lPressed = true;
					if (e.button.button == SDL_BUTTON_RIGHT)
						input.mouseState.rPressed = true;
					break;

				case SDL_MOUSEBUTTONUP:
					if (e.button.button == SDL_BUTTON_LEFT)
						input.mouseState.lPressed = false;
					if (e.button.button == SDL_BUTTON_RIGHT)
						input.mouseState.rPressed = false;
					break;
				}
			}


		}
		const Uint8* tempInput = SDL_GetKeyboardState(NULL);
		input.keyboardState = tempInput;
		Update(delta / 1000, input);  // divided to obtain milliseconds
		Draw();
	}
}

void Game::AddObject(GameObject* object, int sceneIndex)
{
	object->Setup(m_renderer, this);
	m_scenes.at(sceneIndex)->push_back(object);
	m_activeScene = *m_scenes.at(sceneIndex);
}

void Game::RemoveObject(std::string name, int sceneIndex)
{
	for (int a = 0; a < m_scenes.at(sceneIndex)->size(); a++)
	{
		if (m_scenes.at(sceneIndex)->at(a)->m_name == name)
		{
			m_scenes.at(sceneIndex)->erase(m_scenes.at(sceneIndex)->begin() + a);
			m_activeScene = *m_scenes.at(sceneIndex);
			return;
		}
	}
	std::cout << "Could not find object name " << name << std::endl;
}

void Game::ClearScene()
{
	for (GameObject* go : m_activeScene)
	{
		if(go!=nullptr)
		{
			delete go;
		}
	}
	m_activeScene = std::vector<GameObject*>();
}

void Game::AddSceneToGame()
{
	m_scenes.push_back(new std::vector<GameObject*>());
}

void Game::SetActiveScene(int sceneIndex)
{
	m_activeScene = *m_scenes.at(sceneIndex); //dereference operator "*pointer"
	Start();
}

void Game::ClearSounds()
{
	Mix_ExpireChannel(-1, 0);
	for (AudioClip* clip : m_audioClips)
	{
		if (clip != nullptr)
		{
			delete clip;
		}
	}
}

void Game::LoadSound(std::string name, std::string path)
{
	AudioClip* newClip = new AudioClip;
	newClip->m_clip = Mix_LoadWAV(path.c_str());
	newClip->m_name = name;
	m_audioClips.push_back(newClip);
}

void Game::PlaySound(std::string name, bool loop)
{
	for (AudioClip* clip : m_audioClips)
	{
		if (clip->m_name == name)
		{
			if (loop)
				clip->m_channel = Mix_PlayChannel(-1, clip->m_clip, -1);
			else
				clip->m_channel = Mix_PlayChannel(-1, clip->m_clip, 0);
		}
	}
}

void Game::StopSound(std::string name)
{
	for (AudioClip* clip : m_audioClips)
	{
		if (clip->m_name == name)
		{
			Mix_HaltChannel(clip->m_channel);
		}
	}

}

void Game::Quit()
{
	m_isRunning = false;
}

void Game::Start()
{
	for (GameObject* go : m_activeScene)
	{
		go->Start();
	}
}

void Game::Update(double delta, Input in)
{
	//set marker for scene to prevent interaction when changing scene
	std::vector<GameObject*> workingScene = m_activeScene;
	//update objects
	for (GameObject* go : workingScene)
	{
		go->Update(delta, in);
	}

	//calculate all collisions
	for (int i = 0; i < m_activeScene.size() - 1; i++)
	{
		for (int j = i + 1; j < m_activeScene.size(); j++)
		{
			GameObject* go1 = m_activeScene.at(i);
			GameObject* go2 = m_activeScene.at(j);

			// applies only to rectangular objects that don't rotate
			if (go1->m_position.x + go1->m_dimensions.x > go2->m_position.x && go1->m_position.y + go1->m_dimensions.y > go2->m_position.y && go1->m_position.x < go2->m_position.x + go2->m_dimensions.x &&  go1->m_position.y < go2->m_position.y + go2->m_dimensions.y)
			{
				go1->OnCollision(go2);
				go2->OnCollision(go1);
			}
		}
	}
}

void Game::Draw()
{
	//Clear screen
	SDL_RenderClear(m_renderer);

	//Render all our objects
	for (GameObject* go : m_activeScene)
	{
		go->Draw();
	}

	/*
	// From Bobby Law's Lab9
	SDL_Rect tilePosXY;
	tilePosXY = { 50, 50, 100, 100 };
	// determine number of rows and columns for array
	int numRows = 6;
	int numCols = 4;
	SDL_SetRenderDrawColor(m_renderer, 150, 150, 150, 255);
	for (int col = 0; col < numCols; col++)
	{
		tilePosXY.x += 50;
	}
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	*/

	//Render our fonts
	DrawText();

	//Update screen
	SDL_RenderPresent(m_renderer);
}

void Game::DrawText()
{
}
