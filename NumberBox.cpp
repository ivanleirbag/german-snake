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
    
void NumberBox::SetContent(int keyPressed){
    if(isFocused && content.size()>4){
        switch(keyPressed){
            case ENTER:
                isFocused = !isFocused;
                break;
            case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
                content.push_back((keyPressed-48));
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

int NumberBox::GetContent(){
    return content;
}

//display
void NumberBox::DisplayBox(){

}