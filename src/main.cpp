#include <iostream>
#include <robot2D/Core/App.h>

#include "ecs/EcsState.h"

int main() {
    robot2D::App app;
    app.register_state<EcsState>(0, app);
    //todo auto set current - last setted, if now direct usage method
    app.setCurrent(0);
    app.run();
    return 0;
}
