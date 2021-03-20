template<typename T>
bool ComponentContainer<T>::empty() const {
    return m_container.empty();
}

template<typename T>
std::size_t ComponentContainer<T>::get_size() const {
    return m_container.size();
}

template<typename T>
ComponentContainer<T>::ComponentContainer(const std::size_t& size):
        m_container() {
    m_container.resize(size);
}

template<typename T>
void ComponentContainer<T>::clear() {
    m_container.clear();
}

template<typename T>
void ComponentContainer<T>::reset(std::size_t size) {
    //asset size
    for(auto& it: m_container)
        it = T();
}

template<typename T>
T& ComponentContainer<T>::at(const unsigned int& id) {
    return m_container[id];
}

template<typename T>
const T& ComponentContainer<T>::at(const unsigned int &id) const {
    return m_container[id];
}

template<typename T>
void ComponentContainer<T>::resize(std::size_t size) {
    m_container.resize(size);
}