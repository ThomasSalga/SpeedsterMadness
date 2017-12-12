#ifndef _OBSTACLECAR_H
#define _OBSTACLECAR_H
#include "Game.h"

class ObstacleCar :
	public GameObject
{
public:
	ObstacleCar();
	~ObstacleCar();

	Uint8 m_velocity = 150;

	void Start() override;
	void Update(float deltaTime, Input input) override;

	void OnCollision(GameObject* collider) override;

	glm::vec2 GetMovementArea() { return glm::vec2(m_movX, m_game->GetWindowSize().y + m_dimensions.y * 2); }

private:
	int m_movX = 300;
};

#endif

