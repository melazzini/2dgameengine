#ifndef __ENTITYMNG__HPP__
#define __ENTITYMNG__HPP__

#include "Entity.hpp"
#include "Component.hpp"
#include <cstdint>
#include <vector>

namespace EntityMng
{
    void clearData();
    void update(float deltaTime);
    void render(gsl::not_null<SDL_Renderer *>);
    bool hasNoEntities();
    Entity &addEntity(std::string entityName);
    const std::vector<std::unique_ptr<Entity>> &entities();
    int32_t entityCount();
};

#endif // __ENTITYMNG__HPP__
