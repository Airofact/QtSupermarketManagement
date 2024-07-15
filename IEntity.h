#ifndef IENTITY_H
#define IENTITY_H

#include <QMap>

template<class T>
class IEntity{
    static QMap<uint,T> m_database;
public:
    virtual uint getId() const = 0;
    virtual bool setId(uint id) = 0;
    virtual uint getNewId() = 0;

    static const T& getEntity(uint id);
    static bool addEntity(const T& entity);
    static bool removeEntity(uint id);
    static bool containsEntity(uint id);
};

#endif // IENTITY_H
