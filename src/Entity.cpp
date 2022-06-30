#include "Entity.hpp"
#include "Component.hpp"
#include "SDL_render.h"
#include <utility>

Entity::Entity()
{

    m_isActive = true;
}

Entity::Entity(std::string name)
{

    m_name = std::move(name);
    m_isActive = true;
}

void Entity::update(float deltaTime)
{

    for (auto &&component : m_componentList)
    {
        component.second->update(deltaTime);
    }
}

void Entity::render(gsl::not_null<SDL_Renderer *> renderer)
{
    for (auto &&component : m_componentList)
    {
        component.second->render(renderer);
    }
}

void Entity::destroy()
{
    m_isActive = false;
    for (auto &&component : m_componentList)
    {
        component.second->destroy();
    }
}
