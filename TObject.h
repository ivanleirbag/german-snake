#ifndef TOBJECT_H
#define TOBJECT_H

#include <conio.h>


class TObject
{
    public:
        TObject(int x = 1, int y = 1);
        virtual ~TObject();

        void SetPosx(int aPosx);
        int GetPosx(){return posx;}
        void SetPosy(int aPosy);
        int GetPosy(){return posy;}
        void SetWidth(int aWidth);
        int GetWidth(){return width;}
        void SetHeight(int aHeight);
        int GetHeight(){return height;}
        void SetTxtColor(int aTxtColor);
        int GetTxtColor(){return txtColor;}
        void SetBackColor(int aBackColor);
        int GetBackColor(){return backColor;}
        void SetFocused(bool type);
        bool GetIsFocused(){return isFocused;}
        bool GetDoTask(){return doTask;}

        virtual int DoTask(void *arg);

    protected:

        int posx;
        int posy;
        int width;
        int height;
        bool tabStop;
        bool isFocused;
        bool doTask;

    private:
        int txtColor;
        int backColor;



};

#endif // TOBJECT_H
