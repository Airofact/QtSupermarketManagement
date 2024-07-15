#include "IEntity.h"

template<class T>
const T &IEntity<T>::getEntity(uint id)
{
    return m_database[id];
}

template<class T>
bool IEntity<T>::addEntity(const T &entity)
{
    m_database[entity.getId()] = entity;
    return true;
}

template<class T>
bool IEntity<T>::removeEntity(uint id)
{
    m_database.remove(id);
    return true;
}

template<class T>
bool IEntity<T>::containsEntity(uint id)
{
    return m_database.contains(id);
}
