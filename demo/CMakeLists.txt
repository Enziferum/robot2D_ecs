cmake_minimum_required(VERSION 3.11)
project(ecs_demo)

set(SRC
        main.cpp
        RobotSystem.cpp
        EcsState.cpp
        )

set(LIBS robot2D_ecs)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} ${LIBS})