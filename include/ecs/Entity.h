/*********************************************************************
(c) Alex Raag 2021
https://github.com/Enziferum
hakka_game - Zlib license.
This software is provided 'as-is', without any express or
implied warranty. In no event will the authors be held
liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions:
1. The origin of this software must not be misrepresented;
you must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment
in the product documentation would be appreciated but
is not required.
2. Altered source versions must be plainly marked as such,
and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any
source distribution.
*********************************************************************/

#pragma once

#include <cstdint>
#include <unordered_map>
#include <vector>
#include <memory>
#include <bitset>

#include "Container.h"
#include "ComponentID.h"
#include "MessageBus.h"

namespace ecs{
    using u8 = unsigned int;

    namespace Details{
        enum {
            MaxComponents = 64
        };
    }

    using component_mask = std::bitset<Details::MaxComponents>;


    class EntityManager;
    class Entity{
    public:
        Entity();

        template<typename T>
        void addComponent(const T&);

        template<typename T, typename ...Args>
        T& addComponent(Args&& ...args);

        template<typename T>
        bool hasComponent();

        template<typename T>
        T& getComponent();

        template<typename T>
        const T& getComponent() const;

        const u8& get_index() const;

        bool operator == (Entity r)
        {
            return get_index() == r.get_index();
        }

        bool operator != (Entity r)
        {
            return get_index() != r.get_index();
        }

        bool operator < (Entity r)
        {
            return get_index() < r.get_index();
        }

        bool operator <= (Entity r)
        {
            return get_index() <= r.get_index();
        }

        bool operator > (Entity r)
        {
            return get_index() > r.get_index();
        }

        bool operator >= (Entity r)
        {
            return get_index() >= r.get_index();
        }

        friend bool operator < (const Entity& l, const Entity& r)
        {
            return (l.get_index() < r.get_index());
        }

        friend bool operator == (const Entity& l, const Entity& r)
        {
            return (l.get_index() == r.get_index());
        }

        const component_mask& get_mask()const;
    private:
        friend class EntityManager;
        friend class Scene;
        EntityManager* m_entityManager;
        u8 m_id;
    };



    class EntityManager{
    public:
        EntityManager(MessageBus&, ComponentID&);
        EntityManager(const EntityManager&) = delete;
        EntityManager(const EntityManager&&) = delete;
        EntityManager& operator=(const EntityManager&) = delete;
        EntityManager& operator=(const EntityManager&&) = delete;
        ~EntityManager() = default;

        Entity addEntity();
        void destroyEntity(Entity entity);

        template<typename T>
        void addComponent(Entity entity, T);

        template<typename T, typename ...Args>
        T& addComponent(Entity entity, Args&& ...args);

        template<typename T>
        bool hasComponent(Entity entity);

        template<typename T>
        T& getComponent(Entity entity);

        template<typename T>
        const T& getComponent(Entity entity) const;

        const u8& get_size() const;

        const component_mask& getEntityMask(Entity entity) const;
    private:
        template<typename T>
        int32_t get_component_id();

        template<typename T>
        ComponentContainer<T>& getContainer();
    private:
        MessageBus& m_bus;
        u8 m_entitiesCount;
        ComponentID& m_componentManager;
        std::vector<Container::Ptr> m_containers;
        std::vector<component_mask> m_masks;
    };


#include "Entity.inl"

}
