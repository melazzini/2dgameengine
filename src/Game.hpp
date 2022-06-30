#ifndef GAME_H
#define GAME_H

#include "SDL_render.h"
#include "SDL_stdinc.h"
#include "SDL_video.h"
#include <SDL2/SDL.h>
#include <memory>
#include <sys/types.h>
#include "EntityMng.hpp"

class Game
{
	static constexpr float DT = 0.0166f;

private:
	bool m_running;

	std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer *)> m_renderer;
	std::unique_ptr<SDL_Window, void (*)(SDL_Window *)> window;
	std::unique_ptr<Uint32, void (*)(Uint32 *)> sdl_lib;
	uint32_t m_ticks{};
	float m_dt_s{};

public:
	Game();
	~Game();
	bool running() const;
	void initialize(int width, int height);
	void processInput();
	void update();
	void render();
	void destroy();
	void loadLevel(int level);
};

#endif
