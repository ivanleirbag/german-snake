#ifndef TEDIT_H
#define TEDIT_H

#include "TObject.h"
#include <string.h>
#include <ctype.h>
#include <time.h>

#define TEXTLENGTH      256


class TEdit : public TObject
{
    public:
        TEdit();
        ~TEdit();

        void SetText(const char *str);
        char *GetText();
        short Task(short opt);

        void AttachOnKeyPressed(short (*aOnKeyPressed)(TEdit *ed, short key));

        int DoTask(void *arg) override;

    protected:

    private:

        int curPosDisplay;
        int curPosText;
        int length;
        bool showCursor;

        clock_t lastTime;

        char text[TEXTLENGTH];

        short (*onKeyPressed)(TEdit *ed, short key);
};

#endif // TEDIT_H
