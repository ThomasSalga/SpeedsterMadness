#ifndef _OBSTACLE_MNG_H
#define _OBSTACLE_MNG_H

#include "ObstacleCar.h"
#include "Game.h"

class ObstacleMng: public GameObject
{
public:
	ObstacleMng();
	~ObstacleMng();

	void Start() override;
	void Update(float deltaTime, Input input) override;

	void OnCollision(GameObject* collider) override;

private:
	std::vector<ObstacleCar*> myObstacles;
	
	void AddObstacle();
	//void EraseAll();

	SDL_Texture* m_carTexture = nullptr;
	ObstacleCar* m_car = nullptr;
	float m_time = 0;
	Uint8 m_obstacles = 0;
	Uint8 m_pathway = 0;
};

#endif
