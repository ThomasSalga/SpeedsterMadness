#include "ObstacleCar.h"
#include <time.h>
#include <random>
#include <algorithm>

ObstacleCar::ObstacleCar()
{
}


ObstacleCar::~ObstacleCar()
{
}

void ObstacleCar::Start()
{
	std::vector<int> v = { 1, 2, 3, 4};
	//https://stackoverflow.com/questions/14441680/is-it-modern-c-to-use-srand-to-set-random-seed
	std::default_random_engine gen(SDL_GetTicks());
	std::shuffle(v.begin(), v.end(), gen);
	//////////////////////////////////////////////////////////////////////////////////////////////

	//srand(SDL_GetTicks());
	//int x = 1 + (rand() % 4);
	std::cout << std::to_string(v[1]) << std::endl;
	m_position.y = 0 - m_dimensions.y * 2;
	m_position.x = ((m_game->GetWindowSize().x / 3) - (GetMovementArea().x * 3 / 4) + GetMovementArea().x / 8 - (m_dimensions.x / 2)) + (GetMovementArea().x/4 * (v[1]));
}

void ObstacleCar::Update(float deltaTime, Input input)
{
	m_position.y += m_velocity * deltaTime;

	if (m_position.y >= m_game->GetWindowSize().y)
	{
		m_game->RemoveObject(m_name, 1);
		std::cout << m_name << " has been removed" << std::endl;
	}
}

void ObstacleCar::OnCollision(GameObject * collider)
{
}
