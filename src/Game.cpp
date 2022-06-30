//#include <glm/ext/vector_float2.hpp>
#include <iostream>
#include "Game.hpp"
#include "SDL.h"
#include "SDL_render.h"
#include "SDL_stdinc.h"
#include "SDL_video.h"
#include <functional>
#include <glm/vec2.hpp>
#include <memory>
#include <stdexcept>
#include "components/Transform.hpp"
#include "AssetMng.hpp"
#include "./components/Sprite.hpp"

auto sdl_creator = []()
{
    // this initializes the sdl lib
    // when everything Ok -> 0
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "error initializing sdl" << std::endl;
        throw std::runtime_error{"error!"};
    }
    return new Uint32(1);
};

auto wnd_creator = []()
{
    auto wnd = SDL_CreateWindow(nullptr, // NO TITLE
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                600, 400,
                                SDL_WINDOW_BORDERLESS);

    if (!wnd)
    {
        std::cerr << "error initializing sdl window" << std::endl;
        throw std::runtime_error{"error!"};
    }
    return wnd;
};

auto renderer_creator = [](SDL_Window *wnd)
{
    auto r = SDL_CreateRenderer(wnd,
                                -1, // index of the driver screen where you want to render,  -1 the first one supporting the requested flags
                                0   // no flags
    );

    if (!r)
    {
        std::cerr << "error initializing sdl renderer" << std::endl;
        throw std::runtime_error{"error!"};
    }

    return r;
};

template <typename T, typename C, typename D, typename... Args>
std::unique_ptr<T, D> makeUnique(C creator, D deleter, Args... args)
{
    return std::unique_ptr<T, D>(creator(args...), deleter);
}

void wnd_destructor(SDL_Window *wnd)
{
    SDL_DestroyWindow(wnd);
}

void renderer_destructor(SDL_Renderer *r)
{
    if (r == nullptr)
    {
        std::cout << "empty renderer" << std::endl;
        return;
    }

    SDL_DestroyRenderer(r);
}

void sld_destructor(Uint32 *v)
{
    delete v;
    SDL_Quit();
}

Game::Game() : m_running{false},
               window{nullptr, wnd_destructor},
               m_renderer{nullptr, renderer_destructor},
               sdl_lib(nullptr, sld_destructor)
{
}

Game::~Game() {}

bool Game::running() const
{
    return this->m_running;
}

void Game::initialize(int width, int height)
{

    sdl_lib = makeUnique<Uint32>(sdl_creator, sld_destructor);

    window = makeUnique<SDL_Window>(wnd_creator, wnd_destructor);

    m_renderer = makeUnique<SDL_Renderer>(renderer_creator, renderer_destructor, window.get());

    loadLevel(0);

    m_running = true;
}

void Game::loadLevel(int level)
{
    // todo: start including new assets to the asset manager list
    std::string textureFilePath{"/home/francisco/Projects/gameEngines/sdl/2dgameEngine/assets/images/tank-big-right.png"};

    AssetMng::addTexture(m_renderer.get(), "tank-image", textureFilePath);

    // todo: add entities and add components to the entities
    auto &entity{EntityMng::addEntity("tank")};
    entity.addComponent<Transform>(0, 0, 100, 100, 52, 52, 1);
    entity.addComponent<Sprite>("tank-image");

    auto val = entity.component<Transform>();
}

void Game::processInput()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
    {
        m_running = false;
        break;
    }
    case SDL_KEYDOWN:
    {
        if (event.key.keysym.sym == SDLK_ESCAPE)
        {
            m_running = false;
            break;
        }
    }
    default:
        break;
    }
}

void Game::update()
{
    SDL_Delay(static_cast<uint32_t>(std::max((16 - static_cast<int64_t>(SDL_GetTicks() - m_ticks)), static_cast<int64_t>(0))));

    uint32_t ticksNow = SDL_GetTicks();
    uint32_t dticks = ticksNow - m_ticks;
    m_ticks = ticksNow;

    float dt_lastIteration_s = static_cast<float>(dticks) / 1000.f;

    m_dt_s += dt_lastIteration_s;

    // clamp the time to a max of 0.1seconds
    m_dt_s = (m_dt_s > 0.1) ? 0.1 : m_dt_s;

    EntityMng::update(m_dt_s);
    m_dt_s = 0.f;
}

void Game::render()
{
    SDL_SetRenderDrawColor(m_renderer.get(), 210, 21, 21, 255);
    SDL_RenderClear(m_renderer.get());

    EntityMng::render(m_renderer.get());
    SDL_RenderPresent(m_renderer.get());
}

void Game::destroy()
{
}
