#include "TextureMng.hpp"
#include <SDL_image.h>
#include <iostream>
#include "gsl/pointers"

namespace
{
    TextureMng::uniqueTexture
    makeUniqueTexture(gsl::not_null<SDL_Renderer *> renderer,
                      std::string_view filename);
}

namespace TextureMng
{
    static const double ZeroDegrees = 0;

    static const SDL_Point *RotationAroundCenter = nullptr;

    uniqueTexture loadTexture(gsl::not_null<SDL_Renderer *> renderer, std::string_view filename)
    {
        return makeUniqueTexture(renderer, filename);
    }

    void drawTexture(gsl::not_null<SDL_Renderer *> renderer, gsl::not_null<SDL_Texture *> texture,
                     const SDL_Rect &source,
                     const SDL_Rect &destination,
                     const SDL_RendererFlip &flip)
    {
        auto ok = SDL_RenderCopyEx(renderer, texture, &source, &destination, ZeroDegrees, RotationAroundCenter, flip);
    }
}

namespace
{

    void destroyTexture(SDL_Texture *texture)
    {
        if (texture != nullptr)
        {
            SDL_DestroyTexture(texture);
        }
    }

    TextureMng::uniqueTexture
    makeUniqueTexture(gsl::not_null<SDL_Renderer *> renderer,
                      std::string_view filename)
    {
        auto surface{IMG_Load(filename.data())};
        auto texture{SDL_CreateTextureFromSurface(renderer, surface)};
        SDL_FreeSurface(surface);
        return std::move(TextureMng::uniqueTexture{texture, destroyTexture});
    }

} // namespace
