#ifndef NUMBERBOX_H
#define NUMBERBOX_H

#include <ncurses.h>
#include <vector>

#define ENTER 10
#define DELETE 

using namespace std;

class NumberBox{

public:
    bool isFocused;

    NumberBox();
    ~NumberBox();
        //seters
    void SetPosx(int sPosx);

    void SetPosy(int sPosy);
    
    void SetWidth(int sWidth);
    
    void SetContent(int keyPressed);

    void SetColors(int setColorPair);

    void UseColors();

    //getters
    int GetPosx();

    int GetPosy();

    int GetWidth();

    vector<int> GetContent();

    //display
    void DisplayBox();


private:
    int posx, posy;
    bool useColor;
    int colorPair;
    vector<int> content;
    int width;
};




#endif //NUMBERBOX_H