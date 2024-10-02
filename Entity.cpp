#include "Entity.h"

    Entity::Entity(int cPosx, int cPosy, char cSymbol){
        posx = cPosx;
        posy = cPosy;
        symbol = cSymbol;
        bWidth = 0;
        bHeight = 0;
        bZerox = 0;
        bZeroy = 0;
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
    int Entity::GetBZerox(){
        return bZerox;
    }
    int Entity::GetBZeroy(){
        return bZeroy;
    }
    int Entity::GetBHeight(){
        return bHeight;
    }
    int Entity::GetBWidth(){
        return bWidth;
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

    /*void Entity::moveTo(){
    }*/

    void Entity::draw(void *arg){
        move((posy), (posx));
        printw("%c", symbol);
    }

    bool Entity::collidesWith(Entity& other){
        if (posx == other.GetPosx() && posy == other.GetPosy()){
            return true;
        }else{
            return false;
        }
    }