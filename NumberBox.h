#ifndef NUMBERBOX_H
#define NUMBERBOX_H

#include <ncurses.h>
#include <vector>
#include <cmath>

#define ENTER 10
#define ESC 27 

using namespace std;

class NumberBox{

public:
    bool isFocused;

    NumberBox(int cPosx, int cPosy, int cWidth);
    ~NumberBox();
        //seters
    void SetPosx(int sPosx);

    void SetPosy(int sPosy);
    
    void SetWidth(int sWidth);
    
    void SetContent(int keyPressed);

    void SetColors(int setColorPair);

    void Focus();

    void UseColors();

    //getters
    int GetPosx();

    int GetPosy();

    int GetWidth();

    int GetContent();

    //display
    void DisplayBox();


private:
    int posx, posy;
    bool useColor;
    int colorPair;
    int width;
    vector<int> content;  

    int zeroRel = posx+width;
    int relX = 0;
    int relY = posy;
};




#endif //NUMBERBOX_H