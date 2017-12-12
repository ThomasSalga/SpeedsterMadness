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
}

void ObstacleMng::Update(float deltaTime, Input input)
{
	time += deltaTime;
	
	if (time > 0.5)
	{
		if (pathway < 3)
		{
			AddObstacle();
			if (obstacles <= 99)
				obstacles++;
			else obstacles = 0;
			pathway++;
		}
		else pathway = 0;
		
		time = 0;
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
	std::string id((std::to_string(obstacles))); //converts int "obstacles" to string to obtain an id I can use to identify and remove safely the object
	carN += id;   
	car->SetName(carN);
	std::cout << carN << std::endl;
	m_game->AddObject(car,1);
	
	//customize car object
	car->LoadTexture("Assets/Images/Obstacle.png");
	car->Start();
}

void ObstacleMng::EraseAll()
{
	
}

