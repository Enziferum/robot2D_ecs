cmake_minimum_required(VERSION 3.17)
project(robot2D_ecs)

option(BUILD_DEMO "Build demo project ?" ON)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 3.3 REQUIRED)
find_package(robot2D REQUIRED)
find_package(robot2D_ext REQUIRED)

set(SRC
        include/ecs/Scene.h
        include/ecs/System.h
        include/ecs/Logger.h
        include/ecs/ComponentID.h
        include/ecs/Container.h
        )


set(SRC
        ${SRC}
        src/Entity.cpp
        src/Scene.cpp
        src/SpriteRenderSystem.cpp
        src/System.cpp
        src/Components.cpp
        src/ComponentID.cpp
        src/logger.cpp
        src/Container.cpp
        src/MessageBus.cpp
        src/Message.cpp
        )

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(robot2D_ecs ${SRC})
target_link_libraries(${PROJECT_NAME} robot2D)
target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)
if(BUILD_DEMO)
    add_subdirectory(demo)
endif()