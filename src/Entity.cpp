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

#include <algorithm>
#include "ecs/Entity.h"

namespace ecs{
    Entity::Entity(): m_id(0) {}

    const u8& Entity::get_index() const {
        return m_id;
    }

    const component_mask& Entity::get_mask() const {
        return m_entityManager->getEntityMask(*this);
    }

    constexpr u8 max_components = 128;

    EntityManager::EntityManager(): m_entitiesCount(0),
    m_masks(max_components),
    m_containers(max_components)
    {
    }


    Entity EntityManager::addEntity() {
        Entity entity;
        entity.m_id = m_entitiesCount;
        entity.m_entityManager = this;
        ++m_entitiesCount;
        return entity;
    }

    void EntityManager::destroyEntity(Entity entity) {
        const auto index = entity.get_index();
//        auto found = std::find_if(m_entites.begin(), m_entites.end(),[=](Entity ent){
//           return ent.get_index() == index;
//        });
//        //nothing to delete make warn
//        if(found == m_entites.end()){
//            return;
//        }
        //in the end
        --m_entitiesCount;
    }

    const u8 &EntityManager::get_size() const {
        return m_entitiesCount;
    }

    const component_mask &EntityManager::getEntityMask(Entity entity) const {
        auto entID = entity.get_index();
        //assert entID = m_masks.size();
        return m_masks[entID];
    }

}