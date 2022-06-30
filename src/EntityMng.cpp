#include "Component.hpp"
#include "Entity.hpp"
#include "EntityMng.hpp"

namespace
{
    std::vector<std::unique_ptr<Entity>> _entities;
    const std::vector<std::unique_ptr<Entity>> &_entitiesConstRef{_entities};
}

namespace EntityMng
{
    void clearData()
    {
        for (auto &&entity : _entities)
        {
            entity->destroy();
        }
    }

    void update(float deltaTime)
    {
        for (auto &&entity : _entitiesConstRef)
        {
            entity->update(deltaTime);
        }
    }

    void render(gsl::not_null<SDL_Renderer *> renderer)
    {
        for (auto &&entity : _entitiesConstRef)
        {
            entity->render(renderer);
        }
    }

    Entity &addEntity(std::string entityName)
    {
        _entities.emplace_back(std::make_unique<Entity>(entityName));
        return *(_entities.back());
    }

    const std::vector<std::unique_ptr<Entity>> &entities()
    {
        return _entitiesConstRef;
    }

    int32_t entityCount()
    {
        return static_cast<int32_t>(_entitiesConstRef.size());
    }

    bool hasNoEntities()
    {
        return _entitiesConstRef.empty();
    }
}
