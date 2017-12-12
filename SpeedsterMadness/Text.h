#pragma once
#include "GameObject.h"
class Text :
	public GameObject
{
public:
	Text();
	~Text();

	void Start() override;
	void Update(float deltaTime, Input input) override;

	void OnCollision(GameObject* collider) override;
};

