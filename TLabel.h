#ifndef TLABEL_H
#define TLABEL_H

#include "TObject.h"
#include <string.h>
#include <cstdio>


class TLabel : public TObject
{
    public:
        TLabel();
        ~TLabel();

        enum TEXT_ALIGN {
            TEXT_LEFT = 0,
            TEXT_CENTER,
            TEXT_RIGHT,
            TEXT_TOP,
            TEXT_BOTTOM,
        };

        void SetText(const char *str);
        char *GetText(){return text;}

        void SetHorAlignment(enum TEXT_ALIGN aAlign);
        void SetVerAlignment(enum TEXT_ALIGN aAlign);

        int GetTextLength(){return length;}
    protected:

    private:
        char text[256];
        enum TEXT_ALIGN alignHorizontal;
        enum TEXT_ALIGN alignVertical;
        int length;

        void ShowText();
};

#endif // TLABEL_H
