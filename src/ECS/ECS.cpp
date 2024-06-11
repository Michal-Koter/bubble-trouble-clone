//
// Created by koter on 11.06.2024.
//

#import "ECS.h"

void Entity::addGroup(Group mGroup) {
    groupBitSet[mGroup] = true;
    manager.AddToGroup(this, mGroup);
}