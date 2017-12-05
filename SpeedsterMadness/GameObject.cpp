#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
	//Free loaded image
	SDL_DestroyTexture(m_texture);
	m_texture = NULL;
}

GameObject::GameObject(SDL_Renderer * renderer, std::string name)
{
	m_renderer = renderer;
	m_name = name;
}

void GameObject::Start()
{
}

void GameObject::Update(float deltaTime, Input input)
{
	if (input.keyboardState[SDL_SCANCODE_RIGHT])
	{
		m_position.x += 200 * deltaTime;
	}
	if (input.keyboardState[SDL_SCANCODE_LEFT])
	{
		m_position.x -= 200 * deltaTime;
	}

	if (input.mouseState.lPressed)
	{
		if (CollisionPoint(input.mouseState.x, input.mouseState.y))
			std::cout << "Clicked" << std::endl;
	}
	
}

void GameObject::Draw()
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { m_position.x, m_position.y, m_dimensions.x, m_dimensions.y };

	//Render to screen
	SDL_RenderCopyEx(m_renderer, m_texture, NULL, &renderQuad, m_rotation, NULL, SDL_FLIP_NONE);
}

void GameObject::LoadTexture(std::string path)
{
	m_texture = LoadTextureFromFile(path);
}

bool GameObject::CollisionPoint(int x, int y)
{
	//check if point is in sprite collider
	if ((x > m_position.x && y > m_position.y) && (x < m_position.x + m_dimensions.x && y < m_position.y + m_dimensions.y))
		return true;
	else
		return false;
}

SDL_Texture * GameObject::LoadTextureFromFile(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Set width and height of the object
		m_dimensions.x = loadedSurface->w;
		m_dimensions.y = loadedSurface->h;

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}
