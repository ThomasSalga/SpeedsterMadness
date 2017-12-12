#ifndef _BG_H
#define _BG_H

#include "GameObject.h"

class BackGround :
	public GameObject
{
public:
	BackGround();
	~BackGround();

	void Start() override;
	void Update(float deltaTime, Input input) override;

	void OnCollision(GameObject* collider) override;
};

#endif