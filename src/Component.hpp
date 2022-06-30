#ifndef __COMPONENT__HPP__
#define __COMPONENT__HPP__

#include "SDL_render.h"
#include <gsl/gsl>
class Entity;

class Component {
protected:
   const Entity &m_owner;
public:

    Component(const Entity& owner):m_owner(owner) {}

    virtual ~Component() {}
    virtual void initialize()=0;
    virtual void update(float deltaTime)=0;
    virtual void render(gsl::not_null<SDL_Renderer*>)=0;
    virtual void destroy()=0;
};


#endif//__COMPONENT__HPP__
