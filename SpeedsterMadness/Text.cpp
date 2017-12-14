#include "Text.h"



Text::Text()
{
}


Text::~Text()
{
}

void Text::Start()
{
}

void Text::Update(float deltaTime, Input input)
{
}

void Text::Update(std::string newText, SDL_Color newColor)
{
	m_text = newText;
	m_color = newColor;

	Draw();
}

void Text::Draw()
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { m_position.x, m_position.y, m_dimensions.x, m_dimensions.y };

	//set alpha
	SDL_SetTextureAlphaMod(m_texture, m_alpha);

	//Render to screen
	SDL_RenderCopyEx(m_renderer, m_texture, NULL, &renderQuad, m_rotation, NULL, SDL_FLIP_NONE);
	
	DrawTextColor(m_text, m_color);
}

void Text::OnCollision(GameObject * collider)
{
}

void Text::SetText(std::string newText)
{
	m_text = newText;
}

void Text::SetColor(SDL_Color newColor)
{
	m_color = newColor;
}
