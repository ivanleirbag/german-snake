#ifndef ENTITY_H
#define ENTITY_H

#include <ncurses.h>

using namespace std;

class Entity{
private:
    int posx;
    int posy;
    char symbol;
    
    //Tablero Boundaries
    int bWidth, bHeight, bZerox, bZeroy;

public:
    Entity(int cPosx, int cPosy, char cSymbol);
    ~Entity();

    int GetPosx();
    int GetPosy();
    char GetSymbol();

    void SetPosx(int sPosx);
    void SetPosy(int sPosy);
    void SetSymbol(char sSymbol);

    void SetBoundaries(int sWidth, int sHeight, int sZerox, int sZeroy);

    virtual void move(){
    }

    virtual void draw(void *arg);

    bool collidesWith(const Entity& other);

};




#endif //ENTITY_H