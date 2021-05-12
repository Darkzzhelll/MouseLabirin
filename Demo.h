#ifndef DEMO_H
#define DEMO_H


#include <SOIL/SOIL.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Game.h"
#include "player.h"
#include "tile.h"
#include "gui.h"
#include "musik.h"

using namespace glm;

class Demo :
	public Engine::Game
{
public:
	Demo();
	~Demo();
	Tile* tile;
	Player* player;
	Gui* gui;
	Musik* musik;
	bool play = false;
	bool finish = false;
	int sec = 0, msec = 0;
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	
private:
	GLuint VBO, VAO, EBO, texture, program, VBO2, VAO2, EBO2, texture2, program2;
	unsigned int frame_idx = 0, flip = 0;
	bool IsCollided(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2);
	void ControlPlayerSprite(float deltaTime);
	void Menu();
};
#endif

