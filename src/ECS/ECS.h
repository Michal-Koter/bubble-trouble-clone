//
// Created by koter on 06.06.2024.
//

#ifndef MYGAME_ECS_H
#define MYGAME_ECS_H

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;

class Entity;

class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID() noexcept {
    static ComponentID lastId = 0u;
    return lastId++;
}

template<typename T>
inline ComponentID getComponentTypeID() noexcept {
    static ComponentID typeId = getNewComponentTypeID();
    return typeId;
}

constexpr std::size_t maxComponents = 64;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;
using ComponentArray = std::array<Component *, maxComponents>;

class Component {
public:
    Entity *entity;

    virtual void init() {}

    virtual void update() {}

    virtual void draw() {}

    virtual ~Component() = default;
};

class Entity {
public:
    Entity(Manager &mManager) : manager(mManager) {}

    void update() {
        for (auto &c: components) c->update();
    }

    void draw() {
        for (auto &c: components) c->draw();
    }

    bool isActive() const { return active; }

    void destroy() { active = false; }

    bool hasGroup(Group mGroup) {
        return groupBitSet[mGroup];
    }

    void addGroup(Group mGroup);

    void delGroup(Group mGroup) {
        groupBitSet[mGroup] = false;
    }

    template<typename T>
    bool hasComponents() const {
        return componentBitSet[getComponentTypeID<T>()];
    }

    template<typename T, typename... TArgs>
    T &addComponent(TArgs &&... mArgs) {
        T *c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this;
        std::unique_ptr<Component> uPtr{c};
        components.emplace_back(std::move(uPtr));

        componentArray[getComponentTypeID<T>()] = c;
        componentBitSet[getComponentTypeID<T>()] = true;

        c->init();
        return *c;
    }

    template<typename T>
    T &getComponent() const {
        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T *>(ptr);
    }

private:
    Manager &manager;
    bool active = true;
    std::vector<std::unique_ptr<Component>> components;

    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
    GroupBitSet groupBitSet;
};

class Manager {
public:
    void update() {
        for (auto &e: entities) e->update();
    }

    void draw() {
        for (auto &e: entities) e->draw();
    }

    void refresh() {
        for (auto i(0u); i < maxGroups; i++) {
            auto &v(groupedEntities[i]);
            v.erase(
                    std::remove_if(std::begin(v), std::end(v),
                                   [i](Entity *mEntity) {
                                       return !mEntity->isActive() || !mEntity->hasGroup(i);
                                   }
                    ),
                    std::end(v));
        }

        entities.erase(
                std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity> &mEntity) {
                    return !mEntity->isActive();
                }),
                std::end(entities));

    }

    void AddToGroup(Entity* mEntity, Group mGroup){
        groupedEntities[mGroup].emplace_back(mEntity);
    }

    std::vector<Entity*>& getGroup(Group mGroup) {
        return groupedEntities[mGroup];
    }

    Entity &addEntity() {
        Entity *e = new Entity(*this);
        std::unique_ptr<Entity> uPtr{e};
        entities.emplace_back(std::move(uPtr));
        return *e;
    }
private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::array<std::vector<Entity *>, maxGroups> groupedEntities;
};

#endif //MYGAME_ECS_H
