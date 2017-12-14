#ifndef _SM_CONTROLLER_H
#define _SM_CONTROLLER_H

#include "Game.h"
#include "Text.h"

class SM_Controller :
	public GameObject
{
public:
	SM_Controller();
	~SM_Controller();

	void Start() override;
	void Update(float deltaTime, Input input) override;

	void OnCollision(GameObject* collider) override;
	glm::vec2 GetMovementArea() { return glm::vec2(m_movX, m_game->GetWindowSize().y); }
	void SetScore(int score);
	int GetScore();
	void AssignTextScore(Text* text);

private:
	Text* m_scoreText = nullptr;
	int m_score = 0;
	int m_movX = 300;
	float m_time = 0;
	
};

#endif // !_SM_CONTROLLER_H
