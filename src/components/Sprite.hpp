#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "Transform.hpp"
#include "../TextureMng.hpp"
#include "../AssetMng.hpp"

class Sprite : public Component
{

private:
    SDL_Rect m_srcRectangle;
    SDL_Rect m_destRectangle;
    SDL_Texture *m_texture;
    Transform *m_transform;
    SDL_RendererFlip m_spriteFlip = SDL_FLIP_NONE;

public:
    Sprite(const Entity &owner, std::string_view assetTextureID)
        : Component{owner}
    {
        setTexture(assetTextureID);
        initialize();
    }

    void setTexture(std::string_view assetTextureID)
    {
        m_texture = AssetMng::texture(assetTextureID);
    }

    void initialize() override
    {
        m_transform = m_owner.component<Transform>();
        m_srcRectangle.x = 0;
        m_srcRectangle.y = 0;
        m_srcRectangle.w = m_transform->w();
        m_srcRectangle.h = m_transform->h();
    }

    void update(float deltaTime) override
    {
        const auto &pos = m_transform->pos();
        m_destRectangle.x = static_cast<int>(pos.x);
        m_destRectangle.y = static_cast<int>(pos.y);
        m_destRectangle.w = m_transform->w() * m_transform->scale();
        m_destRectangle.h = m_transform->h() * m_transform->scale();
    }

    void render(gsl::not_null<SDL_Renderer *> renderer) override
    {
        TextureMng::drawTexture(renderer, m_texture, m_srcRectangle, m_destRectangle, m_spriteFlip);
    }

    void destroy() override
    {
    }
};

#endif // !SPRITE_HPP