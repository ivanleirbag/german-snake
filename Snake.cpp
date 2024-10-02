#include "Snake.h"

Snake::Snake(int startX, int startY,
        int bWidth, int bHeight,
        int zeroX, int zeroY)
        : Entity(startX, startY, 'A') {
        Entity::SetBoundaries(bWidth, bHeight, zeroX, zeroY);
        direction = LEFT;
        lastDirection = direction;
        isDead = false;
        body.push_back(*this);
        }

Snake::~Snake(){
}

void Snake::ResetSnake(){
    body.clear();
    Entity head(GetBWidth()/2, GetBHeight()/2, 'A');
    direction = LEFT;
    lastDirection = direction;
    isDead = false;
    body.push_back(head);
}

void Snake::SetDirection(int direc){
    if (direc != (-1)*direction){
        lastDirection = direction;
        direction = direc;
    }else{
        //no se puede ir para atras :P
    }
}

int Snake::GetDirection(){
    return direction;
}

void Snake::MovingTo(Entity *fruit){
    Entity oldHead = body.at(0);
    nextX = oldHead.GetPosx();
    nextY = oldHead.GetPosy();

    switch (direction)
    {
    case UP:
        nextY -= 1;
        if (nextY < GetBZeroy()){
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
    body.insert(body.begin(), newHead);
    body.pop_back();

    //Chequea colisiones
   if (body.size() > 4){
        for (int i = 2; i < body.size(); i++){
            if (body.at(0).collidesWith(body.at(i-1))){
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

void Snake::Grow(){
    Entity newHead(nextX, nextY, 'A');
    if(body.back().GetSymbol() == 90){
        newHead.SetSymbol('a');
    }
    body.insert(body.begin(), newHead);
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

Entity Snake::GetHead(){
    return body.at(0);
}