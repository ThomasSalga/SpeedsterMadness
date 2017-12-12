#include "GameObject.h"
#include "Game.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
	//Free loaded image
	SDL_DestroyTexture(m_texture);
	m_texture = NULL;
}

void GameObject::Setup(SDL_Renderer * renderer, Game * game)
{
	m_renderer = renderer;
	m_game = game;
}

void GameObject::Draw()
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { m_position.x, m_position.y, m_dimensions.x, m_dimensions.y };

	//set alpha
	SDL_SetTextureAlphaMod(m_texture, m_alpha);

	//Render to screen
	SDL_RenderCopyEx(m_renderer, m_texture, NULL, &renderQuad, m_rotation, NULL, SDL_FLIP_NONE);
}

bool GameObject::CollisionPoint(int x, int y)
{
	//check if point is in sprite collider
	if ((x > m_position.x && y > m_position.y) && (x < m_position.x + m_dimensions.x && y < m_position.y + m_dimensions.y))
		return true;
	else
		return false;
}

void GameObject::LoadTexture(std::string path)
{
	m_texture = LoadTextureFromFile(path);
}

void GameObject::LoadFont(std::string path, int size)
{
	//Open the font
	m_font = TTF_OpenFont(path.c_str(), size);
	if (m_font == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
	}
}

void GameObject::DrawTextColor(std::string text, SDL_Color color)
{
	//Render text
	if (!(m_texture=LoadFontInTexture(text, color)))
	{
		printf("Failed to render text texture!\n");
	}
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


//from : http://lazyfoo.net/tutorials/SDL/16_true_type_fonts/index.php
SDL_Texture * GameObject::LoadFontInTexture(std::string text, SDL_Color color)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, text.c_str(), color);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			m_dimensions.x = textSurface->w;
			m_dimensions.y = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return newTexture;
}
