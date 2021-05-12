#ifndef MUSIK_H
#define MUSIK_H


#include <SOIL/SOIL.h>

#include <SDL/SDL_mixer.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Game.h"

using namespace glm;

class Musik :
	public Engine::Game
{
public:
	Musik();
	~Musik();
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	void InitAudio();
	void Musikkontrol();
	Mix_Music* music;
};
#endif

