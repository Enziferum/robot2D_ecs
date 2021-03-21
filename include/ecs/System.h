/*********************************************************************
(c) Alex Raag 2021
https://github.com/Enziferum
robot2D_game - Zlib license.
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
#include <memory>
#include <vector>

#include "ComponentID.h"
#include "Entity.h"
#include "MessageBus.h"

namespace ecs{
    class Scene;
    class System{
    public:
        System(MessageBus& messageBus);
        virtual ~System() = 0;

        virtual void handleMessage(const Message& message);
        virtual void process(float dt);
        void setActive(const bool& status);

    protected:
        virtual void on_addEntity(Entity entity);
        //check required components
        template<typename T>
        void check_component();

        template<typename T>
        T* postMessage(Message::ID);

        std::vector<Entity>& getEntites();

        //for const marked functions
        const std::vector<Entity>& getEntites() const;


        component_mask getSystemMask() const;
    private:
        void addEntity(Entity entity);
        void processComponents(ComponentID& manager);
    protected:
        Scene* m_scene;
        MessageBus& m_bus;
    private:

        friend class Scene;
        friend class SystemManager;
        using Ptr = std::unique_ptr<System>;

        std::vector<Entity> m_entities;
        std::vector<std::type_index> m_checkComponents;

        component_mask m_mask;
        bool m_active;
    };


    class SystemManager{
    public:
        SystemManager(Scene& scene);
        ~SystemManager() = default;

        void process(float dt);

        template<typename T, typename ...Args>
        T& addSystem(Args&& ...args);
    private:
        std::vector<System::Ptr> m_systems;
        Scene& m_scene;
    };

#include "System.inl"
}

