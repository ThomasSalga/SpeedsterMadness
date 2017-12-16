#include "ObstacleMng.h"
//#include "Timer.h"


ObstacleMng::ObstacleMng()
{
}


ObstacleMng::~ObstacleMng()
{
}

void ObstacleMng::Start()
{
	m_carTexture = LoadTextureFromFile("Assets/Images/Obstacle.png");
}

void ObstacleMng::Update(float deltaTime, Input input)
{
	m_time += deltaTime;
	
	if (m_time > 0.5)
	{
		if (m_pathway < 3)
		{
			AddObstacle();
			if (m_obstacles <= 99)
				m_obstacles++;
			else m_obstacles = 0;
			m_pathway++;
		}
		else m_pathway = 0;
		
		m_time = 0;
	}
}

void ObstacleMng::OnCollision(GameObject * collider)
{
}

void ObstacleMng::AddObstacle()
{
	//add object to scene
	ObstacleCar* car = new ObstacleCar();
	std::string carN("car");
	std::string id((std::to_string(m_obstacles))); //converts int "obstacles" to string to obtain an id I can use to identify and remove safely the object
	carN += id;   
	car->SetName(carN);
	std::cout << carN << std::endl;
	m_game->AddObject(car,1);
	
	//customize car object
	car->m_texture = m_carTexture;
	car->LoadTexture("Assets/Images/Obstacle.png");
	car->Start();
}


