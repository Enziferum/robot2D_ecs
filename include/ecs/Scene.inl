
template<typename T, typename... Args>
T& Scene::addSystem(Args&&... args) {
    //auto& system = m_systemManager.addSystem<T>(std::forward<Args>(args)...);

    auto& system = m_systems.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
    system -> m_scene = this;
    system -> processComponents(m_componentManager);

    if constexpr (std::is_base_of<robot2D::Drawable, T>::value){
        m_drawables.push_back(dynamic_cast<robot2D::Drawable*>(system.get()));
    }

    return *dynamic_cast<T*>(m_systems.back().get());
}