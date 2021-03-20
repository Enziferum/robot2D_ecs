#include <thread>
#include <random>

#include <robot2D/Core/App.h>
#include "EcsState.h"

enum States{
    Ecs
};

struct DemoMessage{
    float x;
    float y;
    enum Status{
        alive = 0,
        stopped = 1,
        dead = 2,
    };
    Status status;
};

enum MsgType{
    Demo = ecs::Message::Count
};


void mock_post(ecs::MessageBus& bus, std::mt19937& mt){
    auto* msg = bus.post<DemoMessage>(MsgType::Demo);
    std::uniform_real_distribution<float> xdist(100.f, 800.f);
    std::uniform_real_distribution<float> ydist(100.f, 600.f);
    std::uniform_real_distribution<float> statusdist(0, 3);
    msg->x = xdist(mt);
    msg->y = ydist(mt);
    msg->status = static_cast<DemoMessage::Status>(int(statusdist(mt)));
}

void forwardMessage(const ecs::Message& message) {
    if (message.id == MsgType::Demo) {
        auto data = message.unpack<DemoMessage>();
        LOG_INFO("got message demo x = % y = % status = % \n",
                 data.x, data.y, data.status);
    }
}

void bus_test(){
    std::random_device rd;
    std::mt19937 mt(rd());


    ecs::MessageBus bus;
    while (true) {

        while(!bus.empty()) {

            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            const auto &m = bus.poll();
            forwardMessage(m);
        }

        mock_post(bus, mt);
    }

}

int main() {
    robot2D::App app;
    app.register_state<EcsState>(States::Ecs, app);
    app.run();


    return 0;
}
