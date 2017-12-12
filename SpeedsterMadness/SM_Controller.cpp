#include "SM_Controller.h"
#include "ObstacleCar.h"
#include "Game.h"


SM_Controller::SM_Controller()
{
}

SM_Controller::~SM_Controller()
{
}

void SM_Controller::Start()
{
	m_position.x = (m_game->GetWindowSize().x / 3) - (m_dimensions.x / 2);
	m_position.y = (m_game->GetWindowSize().y *2 / 3) - (m_dimensions.y / 2);
}

void SM_Controller::Update(float deltaTime, Input input)
{
	if (input.keyboardState[SDL_SCANCODE_RIGHT])
	{
		if (m_position.x < m_game->GetWindowSize().x /3 - m_dimensions.x + GetMovementArea().x / 2)
			m_position.x += 200 * deltaTime;
	}
	if (input.keyboardState[SDL_SCANCODE_LEFT])
	{
		if (m_position.x > m_game->GetWindowSize().x / 3 - GetMovementArea().x /2)
			m_position.x -= 200 * deltaTime;
	}
	if (input.keyboardState[SDL_SCANCODE_UP])
	{
		if (m_position.y > 0 )
		m_position.y -= 100 * deltaTime;
	}
	if (input.keyboardState[SDL_SCANCODE_DOWN])
	{
		if (m_position.y < GetMovementArea().y - m_dimensions.y)
		m_position.y += 200 * deltaTime;
	}

	if (input.mouseState.lPressed)
	{
		if (CollisionPoint(input.mouseState.x, input.mouseState.y))
		{
		}
	}

	if (input.keyboardState[SDL_SCANCODE_ESCAPE])
	{
		m_game->Quit();
	}
}

void SM_Controller::OnCollision(GameObject * collider)
{
	if (collider->m_name.compare(0, 3, "car") == 0)
	{
		std::cout << m_name << " collided with " << collider->m_name << " GAME OVER" << std::endl;
		m_game->SetActiveScene(2);
	}
}
