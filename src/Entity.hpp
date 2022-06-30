#ifndef __ENTITY__HPP__
#define __ENTITY__HPP__

#include "Component.hpp"
#include <utility>
#include <map>
#include <string>
#include <memory>
#include <gsl/gsl>
#include <typeinfo>

template <typename T_container, typename T_key, typename T_element>
T_element getElementOrElse(const T_container &container, T_key key, T_element defaultElement)
{
    if (auto item{container.find(key)};
        item == container.end())
    {
        return defaultElement;
    }
    else
    {
        return item;
    }
}

template <typename T_container, typename T_key, typename T_result, typename T_transform>
T_result getResultOrElse(const T_container &container, T_key key, T_result defaultResult, T_transform transform)
{
    if (auto item{container.find(key)};
        item != container.end())
    {
        return static_cast<T_result>(transform(item));
    }
    else
    {
        return defaultResult;
    }
}

using componentList_t = std::map<const std::type_info *, std::unique_ptr<Component>>;
class Entity
{

private:
    bool m_isActive;
    componentList_t m_componentList;
    std::string m_name;

public:
    Entity();
    Entity(std::string name);

    const std::string &name() const
    {
        return m_name;
    }

    void update(float deltaTime);
    void render(gsl::not_null<SDL_Renderer *>);
    void destroy();
    bool active() const
    {
        return m_isActive;
    }

    template <typename T_component, typename... Args>
    T_component &addComponent(Args... args)
    {
        auto component = std::make_unique<T_component>(*this, std::forward<Args>(args)...);
        auto &componentRef = *component;
        m_componentList.emplace(&typeid(T_component), std::move(component));
        return componentRef;
    }

    const componentList_t &components() const { return m_componentList; }

    template <typename T_component>
    T_component *component() const
    {
        return getResultOrElse(m_componentList,
                               &typeid(T_component),
                               static_cast<T_component *>(nullptr),
                               ([](auto itr)
                                { return itr->second.get(); }));
    }
};

#endif // __ENTITY__HPP__
