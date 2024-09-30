#ifndef SNAKE_H
#define SNAKE_H

#include <ncurses.h>
#include <vector>
#include "Entity.h"

using namespace std;

class Snake : public Entity{

private:
    vector<Entity>body;
    int direction = LEFT;

public:

    enum DIRECTIONS{
        UP = 0,
        RIGHT,
        DOWN,
        LEFT,
    };
    Snake(int startX, int startY,
          int bWidth, int bHeight,
          int zeroX, int zeroY);
        /*: Entity(startX, startY, 'A'); {
            Entity::SetBoundaries(bWidth, bHeight, zeroX, zeroY);
            body.push_back(*this)
    }*/
    
    void move(DIRECTIONS direction) override;

    void draw() override;
};

#endif //SNAKE_H