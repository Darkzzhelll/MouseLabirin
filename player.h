#ifndef PLAYER_H
#define PLAYER_H


#include <SOIL/SOIL.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Game.h"

#define NUM_FRAMES 6
#define FRAME_DUR 80

using namespace glm;

class Player :
	public Engine::Game
{
public:
	Player(float sw, float sh, float x, float y);
	~Player();
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	void DrawPlayerSprite();
	void Start();
	void BuildPlayerSprite();
	float sw = 0, sh = 0, frame_width = 0, frame_height = 0;
	float frame_dur = 0, oldxpos = 0, oldypos = 0, xpos = 0, ypos = 0, gravity = 0, xVelocity = 0, yVelocity = 0, yposGround = 0;
	bool walk_anim = false;
	unsigned int frame_idx = 0, flip = 0;
	void UpdatePlayerSpriteAnim(float deltaTime);
private:
	GLuint VBO, VAO, EBO, texture, program;

};
#endif

