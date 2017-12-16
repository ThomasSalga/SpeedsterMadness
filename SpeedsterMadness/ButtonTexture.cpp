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
			//sound managing through a dedicated class next time?
			m_game->PlaySound("Button",0);
			if (m_game->GetActiveScene() == 0 )
			{
				m_game->StopSound("Intro");
				if (m_sceneIndex == 1)
					m_game->PlaySound("Sugar", 1);
			} 
			else if (m_game->GetActiveScene() == 1)
			{
				//m_game->StopSound("Sugar");
			}
			else if (m_game->GetActiveScene() == 2 )
			{
				m_game->StopSound("GameOver");
				if (m_sceneIndex == 1)
					m_game->PlaySound("Sugar", 1);
			}
			m_game->SetActiveScene(m_sceneIndex);
			//if (m_game->GetActiveScene() == 3)
			//{
			//	m_game->Quit();
			//}
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
