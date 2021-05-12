#ifndef TILE_H
#define TILE_H


#include <SOIL/SOIL.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Game.h"

using namespace glm;

class Tile :
	public Engine::Game
{
public:
	Tile(float sw, float sh);
	~Tile();
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	void BuildCrateSprite();
	void DrawCrateSprite(float x, float y, float h, float w);
	float sw, sh, frame_width2 = 0, frame_height2 = 0;
	float frame_dur = 0, oldxpos = 0, oldypos = 0, xpos2 = 0, ypos2 = 0, gravity = 0, xVelocity = 0, yVelocity = 0, yposGround = 0;
	float x[12] = {0,0,100,780,100,100,100,450,610,500,300,250 }, y[12] = { 580,0,0,0,100,250,550,100,250,450,250,400 }, h[12] = { 30,600,30,600,100,150,50,100,150,50,100,100 }, w[12] = { 700,30,800,30,200,100,200,200,100,200,200,150 };
	unsigned int frame_idx = 0, flip = 0;
private:
	GLuint VBO2, VAO2, EBO2, texture2, program2;
	
};
#endif

