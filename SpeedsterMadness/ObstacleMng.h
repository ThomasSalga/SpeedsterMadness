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
	void EraseAll();

	float time = 0;
	Uint8 obstacles = 0;
	Uint8 pathway = 0;

};

#endif
