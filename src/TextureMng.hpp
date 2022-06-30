
#ifndef TEXTUREMNG_HPP
#define TEXTUREMNG_HPP

#include <SDL2/SDL.h>
#include <string_view>
#include <memory>
#include "gsl/pointers"

namespace TextureMng
{
    using uniqueTexture = std::unique_ptr<SDL_Texture, void (*)(SDL_Texture *)>;

    uniqueTexture loadTexture(gsl::not_null<SDL_Renderer *> renderer, std::string_view filename);

    void drawTexture(gsl::not_null<SDL_Renderer *> renderer, gsl::not_null<SDL_Texture *> texture,
                     const SDL_Rect &source,
                     const SDL_Rect &destination,
                     const SDL_RendererFlip &flip);

}

#endif // TEXTUREMNG_HPP
