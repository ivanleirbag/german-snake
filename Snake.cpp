#include "Snake.h"

Snake::Snake(int startX, int startY,
        int bWidth, int bHeight,
        int zeroX, int zeroY)
        : Entity(startX, startY, 'A') {
             Entity::SetBoundaries(bWidth, bHeight, zeroX, zeroY);
        this->SetPosx(startX);
        this->SetPosy(startY);
        this->direction = LEFT;
        this->lastDirection = direction;
        body.push_back(*this);
        }

Snake::~Snake(){
}

void Snake::SetDirection(int direc){
    lastDirection = direction;
    direction = direc;
}

int Snake::GetDirection(){
    return direction;
}

void Snake::MovingTo(Entity *fruit){
    Entity oldHead = body.at(0);
    int nextX = oldHead.GetPosx();
    int nextY = oldHead.GetPosy();

    switch (direction)
    {
    case UP:
        nextY -= 1;
        if (nextY < GetBZerox()){
            nextY = GetBZeroy() + GetBHeight(); 
        }
        break;
    case RIGHT:
        nextX += 1;
        if (nextX > (GetBZerox() + GetBWidth())){
            nextX = GetBZerox();
        }
        break;
    case DOWN:
        nextY += 1;
        if (nextY > (GetBZeroy() + GetBHeight())){
            nextY = GetBZeroy();
        }
        break;
    case LEFT:
        nextX -= 1;
        if (nextX < GetBZerox()){
            nextX = GetBZerox() + GetBWidth(); 
        }
        break;
    default:
        break;
    }

    Entity newHead(nextX, nextY, 'A');
    

    //Chequea si comio una fruta
    if(body.at(0).GetPosx() == fruit->GetPosx() && body.at(0).GetPosy() == fruit->GetPosy()){
        body.insert(body.begin(), newHead);
    }else{
        body.insert(body.begin(), newHead);
        body.pop_back();
    }

    //Chequea colisiones
   if (body.size() > 2){
        for (int i = 1; i < body.size(); i++){
            if (body.at(i).collidesWith(body.at(i-1))){
                isDead = true;
            }
        }
    }

    //Mantiene el cuerpo de la serpiente de la A a la Z
    for (int j = 1; j < body.size(); j++)
    {
        char nextLetter = body.at(j).GetSymbol();
        nextLetter++;
        body.at(j).SetSymbol(nextLetter);     
    }
}

void Snake::DrawSnake(void *arg){
    for(int i = 1; i < body.size(); i++){
        body.at(i).draw(nullptr);
    }
}

void Snake::KillSnake(){
    isDead = true;
}

vector<Entity> Snake::GetBody(){
    return body;
}