#include <iostream>
#include "Game.h"
#include <functional>

Game::Game() : isRunning{false}, window{nullptr}, renderer{nullptr}
{
}

Game::~Game() {}

bool Game::IsRunning() const
{
	return this->isRunning;
}

float projectilePosX = 0.0f;
float projectilePosY = 0.0f;
float projectileVelX = 0.02f;
float projectileVelY = 0.02f;

void Game::Initialize(int width, int height)
{
	// this initializes the sdl lib
	// when everything Ok -> 0
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "error initializing sdl" << std::endl;
		return;
	}

	window = SDL_CreateWindow(nullptr, // NO TITLE
							  SDL_WINDOWPOS_CENTERED,
							  SDL_WINDOWPOS_CENTERED,
							  width,
							  height,
							  SDL_WINDOW_BORDERLESS);

	if (!window)
	{
		std::cerr << "error initializing sdl window" << std::endl;
		return;
	}

	renderer = SDL_CreateRenderer(window,
								  -1, // index of the driver screen where you want to render,  -1 the first one supporting the requested flags
								  0	  // no flags
	);

	if (!renderer)
	{
		std::cerr << "error initializing sdl renderer" << std::endl;
		return;
	}

	isRunning = true;
}

void Game::ProcessInput()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
	{
		isRunning = false;
		break;
	}
	case SDL_KEYDOWN:
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			isRunning = false;
			break;
		}
	}
	default:
		break;
	}
}

void Game::Update()
{
	projectilePosX += projectileVelX;
	projectilePosY += projectileVelY;
}

void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 210, 21, 21, 255);
	SDL_RenderClear(renderer);

	SDL_Rect projectile;
	projectile.x = static_cast<int>(projectilePosX);
	projectile.y = static_cast<int>(projectilePosY);
	projectile.w=10;
	projectile.h=10;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer,&projectile);

	// swap the render buffer(ie the renderer)
	SDL_RenderPresent(renderer);

}

void Game::Destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
