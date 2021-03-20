
template<typename T>
void System::check_component() {
    auto id = std::type_index(typeid(T));
    m_checkComponents.push_back(id);
}

template<typename T, typename... Args>
T& SystemManager::addSystem(Args &&... args) {
    auto& system = m_systems.emplace_back(
            std::make_unique<T>(std::forward<Args>(args)...));

    return *(dynamic_cast<T*>(m_systems.back().get()));
}

template<typename T>
T* System::postMessage(Message::ID id) {
    return m_bus.post<T>(id);
}

