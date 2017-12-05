#ifndef _GO_H
#define _GO_H

#include "Input.h"

class GameObject
{
public:
	GameObject();
	~GameObject();
	GameObject(SDL_Renderer* renderer, std::string name);

	void Start();
	void Update(float deltaTime,Input input);
	void Draw();

	void LoadTexture(std::string path);
	bool CollisionPoint(int x, int y);

	std::string m_name = "";
	glm::vec2 m_position{ 0,0 };
	glm::vec2 m_dimensions{ 0,0 };
	double m_rotation = 0;


protected:
	SDL_Texture* LoadTextureFromFile(std::string path);

	SDL_Texture* m_texture;
	SDL_Renderer* m_renderer;
};
#endif