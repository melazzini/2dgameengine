#ifndef __TRANSFORM__HPP__
#define __TRANSFORM__HPP__

#include "../EntityMng.hpp"
#include "Entity.hpp"
#include "SDL_pixels.h"
#include "SDL_render.h"
#include <glm/ext/vector_float2.hpp>
#include <SDL_rect.h>
#include <gsl/gsl>
#include <tuple>

class Transform : public Component
{

private:
    glm::vec2 m_position;
    glm::vec2 m_velocity;
    int m_width;
    int m_height;
    int m_scale;

public:
    Transform(const Entity &owner, int posx, int posy, int velx, int vely, int w, int h, int scale)
        : Component(owner), m_position(posx, posy), m_velocity(velx, vely), m_width(w), m_height(h), m_scale{scale}
    {
        initialize();
    }

    void initialize() override
    {
    }

    void update(float deltaTime) override
    {
        m_position.x += deltaTime * m_velocity.x;
        m_position.y += deltaTime * m_velocity.y;
    }

    void render(gsl::not_null<SDL_Renderer *> renderer) override
    {
        // SDL_Rect transformRectangle{
        //     static_cast<int>(m_position.x), static_cast<int>(m_position.y),
        //     static_cast<int>(m_width), static_cast<int>(m_height)};

        // SDL_SetRenderDrawColor(renderer, 200, 200, 200, SDL_ALPHA_OPAQUE);
        // SDL_RenderFillRect(renderer, &transformRectangle);
        // SDL_RenderPresent(renderer);
    }

    void destroy() override {}

    std::pair<int, int> wh() const { return {m_width, m_height}; }

    int w() const { return m_width; }
    int h() const { return m_height; }

    int scale() const { return m_scale; }

    glm::vec2 pos() const { return m_position; }
};

#endif // __TRANSFORM__HPP__
