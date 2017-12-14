#ifndef _GO_H
#define _GO_H

class Game; //forward declaration

#include "Input.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Setup(SDL_Renderer* renderer, Game* game);
	void SetName(std::string name) { m_name = name; }

	virtual void Start() = 0;
	virtual void Update(float deltaTime,Input input) = 0;
	virtual void Draw();

	void LoadTexture(std::string path);
	void LoadFont(std::string path, int size);
	void DrawTextColor(std::string text, SDL_Color color);

	bool CollisionPoint(int x, int y);
	virtual void OnCollision(GameObject* object) = 0;

	std::string m_name = "";
	glm::vec2 m_position{ 0,0 };
	glm::vec2 m_dimensions{ 0,0 };
	double m_rotation = 0;
	Uint8 m_alpha = 255;


protected:
	SDL_Texture* LoadTextureFromFile(std::string path);
	SDL_Texture* LoadFontInTexture(std::string text, SDL_Color color);

	SDL_Texture* m_texture=NULL;
	SDL_Renderer* m_renderer;
	//Globally used font
	TTF_Font *m_font = NULL;
	Game* m_game;
};
#endif