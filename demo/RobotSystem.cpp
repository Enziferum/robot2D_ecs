/*********************************************************************
(c) Alex Raag 2021
https://github.com/Enziferum
robot2D_ecs - Zlib license.
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
#include "MessageIDs.h"
#include "Robot.h"
#include "RobotSystem.h"



RobotSystem::RobotSystem(ecs::MessageBus& messageBus): System(messageBus) {
    check_component<ecs::TransformComponent>();
    check_component<Robot>();
}

void RobotSystem::process(float dt) {
    auto& entities = getEntites();
    for(auto& it: entities) {
        auto& transform = it.getComponent<ecs::TransformComponent>();
        transform.move(robot2D::vec2f(10.f * dt, 0.f));
        if(transform.getPosition().x >= 200.f){
            auto* msg = postMessage<robotDemoEvent>(robotDemo);
            msg -> status = robotDemoEvent::alive;
            msg -> pos = transform.getPosition();
        }
    }
}

void RobotSystem::on_addEntity(ecs::Entity entity) {
    System::on_addEntity(entity);
}
