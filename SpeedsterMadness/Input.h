#ifndef _INPUT_H
#define _INPUT_H

#include <SDL\SDL.h>
#include <SDL\SDL_image.h>
#include <SDL\SDL_mixer.h>
#include <SDL\SDL_ttf.h>
#include <glm\glm.hpp>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

struct MouseStateDescriptor
{
	int x, y;
	bool lPressed;
	bool rPressed;
};

class Input
{
public:
	Input() {}
	~Input() {}

	const Uint8* keyboardState;
	MouseStateDescriptor mouseState;
};

#endif