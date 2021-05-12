#include "musik.h"


Musik::Musik()
{
}


Musik::~Musik()
{

	if (music != NULL) {
		Mix_FreeMusic(music);
	}
	Mix_CloseAudio();
}

void Musik::Init()
{
}

void Musik::Update(float deltaTime)
{
}

void Musik::Render()
{
}

void Musik::Musikkontrol()
{
	if (Mix_PlayingMusic() == 0)
	{
		//Play the music
		Mix_PlayMusic(music, -1);
		SDL_Delay(150);
	}
	//If music is being played
	else
	{
		//If the music is paused
		if (Mix_PausedMusic() == 1)
		{
			//Resume the music
			Mix_ResumeMusic();
			SDL_Delay(150);
		}
		//If the music is playing
		else
		{
			//Pause the music
			Mix_PauseMusic();
			SDL_Delay(150);
		}
	}
}


void Musik::InitAudio() {
	int flags = MIX_INIT_MP3 | MIX_INIT_FLAC | MIX_INIT_OGG;
	if (flags != Mix_Init(flags)) {
		Err("Unable to initialize mixer: " + string(Mix_GetError()));
	}

	int audio_rate = 22050; Uint16 audio_format = AUDIO_S16SYS; int audio_channels = 2; int audio_buffers = 4096;

	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
		Err("Unable to initialize audio: " + string(Mix_GetError()));
	}

	music = Mix_LoadMUS("joystockpopsicle.ogg");
	if (music == NULL) {
		Err("Unable to load Music file: " + string(Mix_GetError()));
	}

}

