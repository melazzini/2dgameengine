#include <SDL.h>
#include <string>
#include <map>
#include "gsl/pointers"
#include "EntityMng.hpp"
#include "TextureMng.hpp"

namespace
{
    std::map<std::string, TextureMng::uniqueTexture> _textures;

} // namespace

namespace AssetMng
{
    void clearData()
    {
        _textures.clear();
    }

    void addTexture(gsl::not_null<SDL_Renderer *> renderer, std::string textureId, std::string_view filepath)
    {
        _textures.emplace(std::move(textureId), TextureMng::loadTexture(renderer, filepath));
    }

    gsl::not_null<SDL_Texture *> texture(std::string_view id)
    {
        return _textures.at(id.data()).get();
    }

} // namespace