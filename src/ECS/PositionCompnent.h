//
// Created by koter on 07.06.2024.
//

#ifndef MYGAME_POSITIONCOMPNENT_H
#define MYGAME_POSITIONCOMPNENT_H

#include "Components.h"

class PositionComponent : public Component {
public:
    PositionComponent() {
        xpos = 0;
        ypos = 0;
    }

    PositionComponent(int x, int y) {
        setPos(x, y);
    }

    int x() { return xpos; }
    int y() { return ypos; }

    void init() override {
        xpos = 0;
        ypos = 0;
    }

    void update() override {
        xpos++;
        ypos++;
    }

    void setPos(int x, int y) {
        xpos = x;
        ypos = y;
    }

private:
    int xpos;
    int ypos;

};

#endif //MYGAME_POSITIONCOMPNENT_H
