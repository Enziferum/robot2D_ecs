template<typename T>
void Entity::addComponent(const T& component) {
    m_entityManager -> addComponent<T>(*this, component);
}

template<typename T, typename... Args>
T& Entity::addComponent(Args&& ... args) {
    return m_entityManager -> addComponent<T>(*this,
                                              std::forward<Args>(args)...);
}

template<typename T>
bool Entity::hasComponent() {
    return m_entityManager -> hasComponent<T>(*this);
}

template<typename T>
T& Entity::getComponent() {
    return m_entityManager -> getComponent<T>(*this);
}

template<typename T>
const T& Entity::getComponent() const {
    return m_entityManager -> getComponent<T>(*this);
}


template<typename T>
void EntityManager::addComponent(Entity entity, T component) {
    auto componentID = get_component_id<T>();
    auto entID = entity.get_index();

    auto& container = getContainer<T>();
    if(entID > container.get_size())
        container.resize(entID);

    container[entID] = std::move(component);
    m_masks[entID].set(componentID);
}

template<typename T, typename... Args>
T& EntityManager::addComponent(Entity entity, Args &&... args) {
    //here we create in memory component, because we have args
    T component(std::forward<Args>(args)...);
    addComponent<T>(entity, std::move(component));

    return getComponent<T>(entity);
}

template<typename T>
bool EntityManager::hasComponent(Entity entity) {
    auto componentID = get_component_id<T>();
    auto entID = entity.get_index();
    //assert size
    return m_masks[entID].test(componentID);
}

template<typename T>
T& EntityManager::getComponent(Entity entity) {
    auto componentID = get_component_id<T>();
    auto entID = entity.get_index();

    //get pool by_id
    auto* pool = (dynamic_cast<ComponentContainer<T>*>(m_containers[componentID].get()));
    return pool->at(entID);
}


template<typename T>
const T& EntityManager::getComponent(Entity entity) const {
    return getComponent<T>(entity);
}


template<typename T>
int32_t EntityManager::get_component_id() {
    return m_componentManager.get_mask<T>();
}


template<typename T>
ComponentContainer<T>& EntityManager::getContainer() {
    auto id = get_component_id<T>();
    const std::size_t buffer_sz = 256;

    if(!m_containers[id]){
        m_containers[id] = std::make_unique<ComponentContainer<T>>(buffer_sz);
    }

    return *(dynamic_cast<ComponentContainer<T>*>((m_containers[id].get())));
}
