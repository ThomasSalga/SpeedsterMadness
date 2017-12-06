#include "SM_Controller.h"
#include "Game.h"


SM_Controller::SM_Controller()
{
}


SM_Controller::~SM_Controller()
{
}

void SM_Controller::Start()
{
}

void SM_Controller::Update(float deltaTime, Input input)
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
		{
			//std::cout << "Clicked" << std::endl;
			m_game->StopSound("Button");
			m_game->PlaySound("Button", true);
		}
	}

	if (input.keyboardState[SDL_SCANCODE_ESCAPE])
	{
		m_game->Quit();
	}
}

void SM_Controller::OnCollision(GameObject * collider)
{
	//std::cout << m_name << " collided with " << object->m_name << std::endl;

}
