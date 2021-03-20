cmake_minimum_required(VERSION 3.17)
project(robot2D_ecs)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 3.3 REQUIRED)
find_package(robot2D REQUIRED)
find_package(robot2D_ext REQUIRED)

set(SRC
        include/ecs/EcsState.h
        include/ecs/EcsState.h
        include/ecs/Scene.h
        include/ecs/System.h
        include/ecs/Logger.h
        include/ecs/ComponentID.h
        include/ecs/Container.h
        include/ecs/RobotSystem.h
        )

set(SRC
        ${SRC}
        src/EcsState.cpp
        src/Entity.cpp
        src/main.cpp
        src/Scene.cpp
        src/SpriteRenderSystem.cpp
        src/System.cpp
        src/Components.cpp
        src/ComponentID.cpp
        src/logger.cpp
        src/Container.cpp
        src/RobotSystem.cpp
        )

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(robot2D_ecs ${SRC})

target_link_libraries(${PROJECT_NAME} robot2D)