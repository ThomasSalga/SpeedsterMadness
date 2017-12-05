#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
	ClearScene();

	//Destroy window	
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	m_window = NULL;
	m_renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
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
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
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
			}
		}
	}

	m_deltaTime = SDL_GetTicks();

	return success;
}

void Game::Run()
{
	Start();

	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;



	//While application is running
	while (!quit)
	{
		//calculate deltaTime
		double time = SDL_GetTicks();
		double delta = time - m_deltaTime;
		m_deltaTime = time;

		//
		Input input;

		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			//If mouse event happened
			if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
			{
				//Get mouse position
				int x, y;
				SDL_GetMouseState(&x, &y);
				input.mouseState.x = x;
				input.mouseState.y = y;

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

GameObject * Game::AddObject(std::string name)
{
	m_activeScene.push_back(new GameObject(m_renderer, name));
	return m_activeScene.at(m_activeScene.size() - 1);
}

void Game::RemoveObject(std::string name)
{
	for (int a = 0; a < m_activeScene.size(); a++)
	{
		if (m_activeScene.at(a)->m_name == name)
		{
			m_activeScene.erase(m_activeScene.begin() + a);
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

void Game::Start()
{
	for (GameObject* go : m_activeScene)
	{
		go->Start();
	}
}

void Game::Update(double delta, Input in)
{
	for (GameObject* go : m_activeScene)
	{
		go->Update(delta, in);
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

	//Render our fonts
	DrawText();

	//Update screen
	SDL_RenderPresent(m_renderer);
}

void Game::DrawText()
{
}
