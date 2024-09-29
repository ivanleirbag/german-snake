#ifndef TTIMER_H
#define TTIMER_H

#include <iostream>
#include <functional>
#include <time.h>


class TTimer
{
    public:
        TTimer();
        ~TTimer();

        enum TIMER_MODE{
            TIMER_PERIODIC = 0,
            TIMER_ONE_SHOT,
        };

        void AttachOnTimerReady(void (*ptrFun)(void *arg), void *aArg);

        void StartTimer(int mSec, enum TIMER_MODE mode);
        void StopTimer();

        void TimerTask();

    protected:

    private:
        clock_t lastTime;
        clock_t currentTime;
        clock_t timerTime;

        enum TIMER_MODE timerMode = TIMER_PERIODIC;

        bool enabled;

        std::function<void(void *arg)>onTimerCpp;/*No usar*/
        void (*onTimer)(void *arg);
        void *arg;
};

#endif // TTIMER_H
