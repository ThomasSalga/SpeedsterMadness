#ifndef _BTN_TEXTURE_H
#define _BTN_TEXTURE_H

#include "GameObject.h"
class ButtonTexture :
	public GameObject
{
public:
	ButtonTexture();
	~ButtonTexture();

	virtual void Start();
	virtual void Update(float deltaTime, Input input);

	virtual void OnCollision(GameObject* collider);

	void AssignSceneLinkIndex(Uint8 sceneIndex);

private:
	Uint8 m_sceneIndex = NULL;
};

#endif // !_BTN_TEXTURE_H