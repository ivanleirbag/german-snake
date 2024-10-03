#include "NumberBox.h"


void NumberBox::SetPosx(int sPosx){
    posx = sPosx;
}

void NumberBox::SetPosy(int sPosy){
    posy = sPosy;
}
    
void NumberBox::SetWidth(int sWidth){
    width = sWidth;
}

void  NumberBox::SetColors(int setColorPair){
    colorPair = setColorPair;
}

void  NumberBox::UseColors(){
    useColor = true;
}

    
void NumberBox::SetContent(int keyPressed){
    if(isFocused && content.size()>4){
        switch(keyPressed){
            case ENTER:
                isFocused = !isFocused;
                break;
            case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
                content.insert(content.begin(), (keyPressed-48));
                if(content.size() > width){
                    content.pop_back();
                }
                break;
            default:
                break;
        }
    }
}

//getters
int NumberBox::GetPosx(){
    return posx;
}

int NumberBox::GetPosy(){
    return posy;
}

int NumberBox::GetWidth(){
    return posx;
}

vector<int> NumberBox::GetContent(){
    return content;
}

//display
void NumberBox::DisplayBox(){
    if(useColor){
        attron(COLOR_PAIR(colorPair));
    }
    for(int j = 0; j < 3; j++){
        for (int i = 0; i < width+2; i++){
            move(posy+j, posx+i);
            printw(" ");
            if(j == 1){
                if(i>0 && i < width+2){
                    printw("%d", content.at(width-i));
                }
            }
        }
    }
    if(useColor){
        attroff(COLOR_PAIR(colorPair));
    }
}