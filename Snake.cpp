#include "Snake.h"

enum DIRECTIONS{
    UP = 0,
    RIGHT,
    DOWN,
    LEFT,
};

Snake::Snake(int startX, int startY,
        int bWidth, int bHeight,
        int zeroX, int zeroY)
        : Entity(startX, startY, 'A') {
             Entity::SetBoundaries(bWidth, bHeight, zeroX, zeroY);
         body.push_back(*this);
         }

Snake::~Snake(){
}

void Snake::MovingTo(DIRECTIONS direction){
    int nextX = GetPosx();
    int nextY = GetPosy();

    switch (direction)
    {
    case UP:
        nextY -= 1;
        if (nextY < GetBZeroy()){
            nextY = bZeroy + GetBHeight(); 
        }
        break;
    case RIGHT:
        nextY += 1;
        if (nextY > bZeroy+bHeight){
            nextY = bZeroy + bWidth; 
        }
        break;
    case DOWN:

        break;
    case LEFT:

        break;
    default:
        break;
    }
}

void Snake::Grow();


void Snake::Draw();