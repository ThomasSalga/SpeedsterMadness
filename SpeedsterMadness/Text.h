#pragma once
#include "GameObject.h"
class Text :
	public GameObject
{
public:
	Text();
	~Text();

	void Start() override;
	void Update(float deltaTime, Input input)override;
	virtual void Update(std::string newText, SDL_Color newColor);
	virtual void Draw();

	void OnCollision(GameObject* collider) override;
	void SetText(std::string newText);
	void SetColor(SDL_Color newColor);

private:
	std::string m_text = "";
	SDL_Color m_color = { 0,0,0 };
};

