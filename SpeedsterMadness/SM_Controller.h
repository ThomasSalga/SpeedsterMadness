#pragma once
#include "GameObject.h"

class SM_Controller :
	public GameObject
{
public:
	SM_Controller();
	~SM_Controller();

	void Start() override;
	void Update(float deltaTime, Input input) override;

	void OnCollision(GameObject* collider) override;
};

