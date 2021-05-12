#include "Demo.h"

Demo::Demo()
{
}


Demo::~Demo()
{
}

void Demo::Init()
{
	player = new Player (GetScreenWidth(), GetScreenHeight(), 800, 600);
	tile = new Tile(GetScreenWidth(), GetScreenHeight());
	gui = new Gui(GetScreenWidth(), GetScreenHeight());
	musik = new Musik();
	musik -> InitAudio();
	player -> BuildPlayerSprite();
	tile ->BuildCrateSprite();
	gui -> InitText();
	gui -> InitButton();
	gui ->program = BuildShader("shader.vert", "shader.frag");

	// Add input mapping
	// to offer input change flexibility you can save the input mapping configuration in a configuration file (non-hard code) !
	InputMapping("Move Right", SDLK_d);
	InputMapping("Move Left", SDLK_a);
	InputMapping("Move Right", SDL_BUTTON_RIGHT);
	InputMapping("Move Left", SDL_BUTTON_LEFT);
	InputMapping("Move Right", SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	InputMapping("Move Left", SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	InputMapping("Move Up", SDLK_w);
	InputMapping("Move Down", SDLK_s);
	InputMapping("Move Up", SDLK_0);
	InputMapping("Move Down", SDL_BUTTON_MIDDLE);
	InputMapping("Quit", SDLK_ESCAPE);
	InputMapping("SelectButton", SDLK_SPACE);
	InputMapping("NextButton", SDLK_DOWN);
	InputMapping("PrevButton", SDLK_UP);
	InputMapping("Menu", SDLK_m);
}

void Demo::Update(float deltaTime)
{
	if (IsKeyDown("Quit")) {
		SDL_Quit();
		exit(0);
	}
	if (finish) {
		if (IsKeyDown("Menu")) {
			play = false;
		}
	}
	if (play == false) {
		if (IsKeyDown("SelectButton")) {
			Menu();
		}

		if (IsKeyUp("NextButton")) {
			if (gui->activeButtonIndex < NUM_BUTTON - 1) {
				gui->activeButtonIndex++;
				SDL_Delay(150);
			}
		}

		if (IsKeyUp("PrevButton")) {
			if (gui->activeButtonIndex > 0) {
				gui->activeButtonIndex--;
				SDL_Delay(150);
			}
		}
	}

	player->UpdatePlayerSpriteAnim(deltaTime);
	ControlPlayerSprite(deltaTime);
}



void Demo::ControlPlayerSprite(float deltaTime)
{
	player -> walk_anim = false;
	player-> oldxpos = player->xpos;
	player-> oldypos = player->ypos;

	if (IsKeyDown("Move Right")) {
		player->xpos += deltaTime * player->xVelocity;
		player->flip = 0;
		player->walk_anim = true;
	}

	if (IsKeyDown("Move Left")) {
		player->xpos -= deltaTime * player->xVelocity;
		player->flip = 1;
		player->walk_anim = true;
	}

	if (IsKeyDown("Move Up")) {
		player->ypos -= deltaTime * player->yVelocity;
		player->walk_anim = true;
	}

	if (IsKeyDown("Move Down")) {
		player->ypos += deltaTime * player->yVelocity;
		player->walk_anim = true;
	}


	for (size_t i = 0; i < 12; i++)
	{
		if (IsCollided(player->xpos, player->ypos, player->frame_width, player->frame_height, tile->x[i], tile->y[i], tile->w[i], tile ->h[i])) {
			player->xpos = player->oldxpos;
			player->ypos = player->oldypos;
		}
	}

	if (player->ypos < 0) {
		player->ypos = 0;
	}

	if (player->ypos > GetScreenHeight() - player->frame_height) {
		finish = true;
		cout << sec << ":"
			<< msec << endl;
	}
}

void Demo::Menu()
{
	if (gui->activeButtonIndex == 2) {
		SDL_Quit();
		exit(0);
	}
	else if (gui->activeButtonIndex == 1) {
		musik->Musikkontrol();
	}
	else if (gui->activeButtonIndex == 0) {
		play = true;
		player->ypos = 30;
		player->xpos = 30;
		sec = 0;
		finish = false;
	}
}

void Demo::Render()
{
	//Setting Viewport
	glViewport(0, 0, GetScreenWidth(), GetScreenHeight());

	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (play) {
		if (finish) {
			
			//Set the background color
			glClearColor(0.0f, 0.55f, 0.35f, 1.0f);

			// Set orthographic projection
			mat4 projection;
			projection = ortho(0.0f, static_cast<GLfloat>(GetScreenWidth()), static_cast<GLfloat>(GetScreenHeight()), 0.0f, -1.0f, 1.0f);
			glUniformMatrix4fv(glGetUniformLocation(gui->program, "projection"), 1, GL_FALSE, value_ptr(projection));


			gui->RenderText("Selamat anda menyelesaikan Labirin", 140, 200, 0.8f, vec3(245.0f / 126.0f, 49.0f / 66.0f, 73.0f / 255.0f));
			gui->RenderText("Tekan esc untuk keluar game", 270, 250, 0.5f, vec3(245.0f / 126.0f, 49.0f / 66.0f, 73.0f / 255.0f));
			gui->RenderText("Tekan m untuk kembali ke menu", 260, 300, 0.5f, vec3(245.0f / 126.0f, 49.0f / 66.0f, 73.0f / 255.0f));
			gui->RenderText("Anda berhasil menyelesaikan game dalam waktu  " + to_string(sec)+" s", 150, 350, 0.5f, vec3(245.0f / 126.0f, 49.0f / 66.0f, 73.0f / 255.0f));
		}

		else {
			

			//Set the background color
			glClearColor(0.3f, 0.2f, 0.05f, 1.0f);
			player->DrawPlayerSprite();
			for (size_t i = 0; i < 12; i++)
			{
				tile->DrawCrateSprite(tile->x[i], tile->y[i], tile->h[i], tile->w[i]);
			}
			msec++;
			if (msec > 60) {
				sec++;
				msec = 0;
			}
			gui->RenderText("Waktu : " + to_string(sec) + " s", 650, 10, 0.4f, vec3(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
		}
	}
	else {
	
		//Set the background color
		glClearColor(0.0f, 0.55f, 0.35f, 1.0f);
		// Set orthographic projection
		mat4 projection;
		projection = ortho(0.0f, static_cast<GLfloat>(GetScreenWidth()), static_cast<GLfloat>(GetScreenHeight()), 0.0f, -1.0f, 1.0f);
		glUniformMatrix4fv(glGetUniformLocation(gui->program, "projection"), 1, GL_FALSE, value_ptr(projection));
		gui -> RenderText("Mouse Labirin", 230, 30, 1.5f, vec3(245.0f / 126.0f, 49.0f / 66.0f, 73.0f / 255.0f));
		gui -> RenderButton();
	}
}


bool Demo::IsCollided(float x1, float y1, float width1, float height1,
	float x2, float y2, float width2, float height2) {
	return (x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 && y1 + height1 > y2);
}

int main(int argc, char** argv) {

	Engine::Game& game = Demo();
	game.Start("Mouse labirin progress 3", 800, 600, false, WindowFlag::WINDOWED, 60, 1);

	return 0;
}