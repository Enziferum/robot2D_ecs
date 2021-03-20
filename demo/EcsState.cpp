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
#include "ecs/Components.h"
#include "ecs/SpriteRenderSystem.h"

#include "MessageIDs.h"
#include "Robot.h"
#include "EcsState.h"
#include "RobotSystem.h"

EcsState::EcsState(robot2D::IStateMachine& machine) : State(machine),
m_scene(m_bus) {
    setup();
}

void EcsState::handleEvents(const robot2D::Event& event) {
    m_scene.forwardEvent(event);
}

void EcsState::update(float dt) {
    m_scene.update(dt);
    while (!m_bus.empty()){
        const auto& msg = m_bus.poll();
        handleMessages(msg);
    }
}

void EcsState::render() {
   m_window.draw(m_scene);
}

void EcsState::setup() {

    if(!m_textures.loadFromFile("logo","res/textures/logo.png",
                            true)){
        LOG_ERROR_E("Dont load texture logo")
    }

    setup_ecs();
}

void EcsState::setup_ecs() {
    //base system to render sprites

    // concept entites to be render by spritesystem should have
    // component SpriteRender and TransformComponent

    m_scene.addSystem<ecs::SpriteRenderSystem>(m_bus);
    m_scene.addSystem<RobotSystem>(m_bus);


    auto entity = m_scene.addEntity();
    entity.addComponent<ecs::TransformComponent>();
    entity.addComponent<ecs::SpriteComponent>();
    entity.addComponent<Robot>();

    if(!entity.hasComponent<ecs::SpriteComponent>()){
        LOG_ERROR_E("face Entity don't have sprite component")
        return;
    }

    entity.getComponent<ecs::TransformComponent>()
            .setPosition(robot2D::vec2f(100.f, 100.f));
    entity.getComponent<ecs::TransformComponent>()
            .setScale(robot2D::vec2f(100.f, 100.f));
    entity.getComponent<ecs::SpriteComponent>()
            .setTexture(m_textures.get("logo"));

    // just now we should see sprite object with scale and position
}

void EcsState::handleMessages(const Message& message) {
    if(message.id == robotDemo){
        //get entity by id !!!
        auto msg = message.unpack<robotDemoEvent>();
        LOG_INFO("pos = % : % \n", msg.pos.x, msg.pos.y)
    }
    m_scene.forwardMessage(message);
}

