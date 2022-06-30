#ifndef ASSETMNG_HPP
#define ASSETMNG_HPP
#include <string_view>
#include <string>
#include <gsl/pointers>
#include <SDL.h>

namespace AssetMng
{
    void clearData();

    void addTexture(gsl::not_null<SDL_Renderer *> renderer, std::string textureId, std::string_view filepath);

    gsl::not_null<SDL_Texture *> texture(std::string_view id);

} // namespace

#endif // !ASSETMNG_HPP