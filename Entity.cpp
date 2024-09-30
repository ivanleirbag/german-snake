#include "Entity.h"

    Entity::Entity(int cPosx, int cPosy, char cSymbol){
        posx = cPosx;
        posy = cPosy;
        symbol = cSymbol;
    }

    Entity::~Entity(){
        //dctor
    }

    int Entity::GetPosx(){
        return posx;
    }
    int Entity::GetPosy(){
        return posy;
    }
    char Entity::GetSymbol(){
        return symbol;
    }

    void Entity::SetPosx(int sPosx){
        posx = sPosx;
    }
    void Entity::SetPosy(int sPosy){
        posy = sPosy;
    }
    void Entity::SetSymbol(char sSymbol){
        symbol = sSymbol;
    }

    void Entity::SetBoundaries(int sWidth, int sHeight, int sZerox, int sZeroy){
        bWidth = sWidth;
        bHeight = sHeight;
        bZerox = sZerox;
        bZeroy = sZeroy;
    }

    void Entity::move(){
    }

    void Entity::draw(void *arg){
        move(posy, posx);
        printw("%c", symbol);
    }

    bool Entity::collidesWith(const Entity& other){
        return (this->posx == other.GetPosx() && this->posy == other.GetPosy())
    }