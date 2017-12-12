#include "ButtonTexture.h"
#include "Game.h"


ButtonTexture::ButtonTexture()
{
}


ButtonTexture::~ButtonTexture()
{
}

void ButtonTexture::Start()
{
}

void ButtonTexture::Update(float deltaTime, Input input)
{
	
	if (CollisionPoint(input.mouseState.x, input.mouseState.y)) // controlls if mouse coordinates are inside the button 
	{
		m_alpha = 127; // set the sprite transparency at 50% 
		if (input.mouseState.lPressed)
		{
			m_game->PlaySound("Button",0);
			if (m_sceneIndex == 1)
			{
				m_game->SetActiveScene(m_sceneIndex);
			}
		}
	}else m_alpha = 255; // set the sprite transparency at 100% 
}

void ButtonTexture::OnCollision(GameObject * collider)
{
}

void ButtonTexture::AssignSceneLinkIndex(Uint8 sceneIndex)
{
	m_sceneIndex = sceneIndex;
}
