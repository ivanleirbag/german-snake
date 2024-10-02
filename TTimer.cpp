#include "TTimer.h"


TTimer::TTimer()
{
    //ctor
    onTimer = nullptr;
    onTimerCpp = nullptr;
    arg = nullptr;
    enabled = false;
    timerTime = 0;
}

TTimer::~TTimer()
{
    //dtor
}

void TTimer::AttachOnTimerReady(void(*aOnTimer)(void* arg), void *aArg)
{
    onTimer = aOnTimer;
    arg = aArg;
}

void TTimer::AttachOnTimerEnttReady(void(*aOnEnttTimer)(Entity* arg), Entity *aArg)
{
    onEnttTimer = aOnEnttTimer;
    EnttArg = aArg;
}


void TTimer::StartTimer(int mSec, enum TIMER_MODE mode)
{
    if(mSec != 0){
        enabled = true;
        timerMode = mode;
        lastTime = clock();
        timerTime = mSec;
    }
}

void TTimer::StopTimer()
{
    enabled = false;
}

void TTimer::TimerTask()
{
    currentTime = clock();
    if(enabled && ((currentTime - lastTime)>=timerTime)){
        lastTime = currentTime;
        if(timerMode == TIMER_ONE_SHOT)
            enabled = false;
        if(onTimer != nullptr)
            onTimer(arg);
        if(onTimerCpp != nullptr)
            onTimerCpp(arg);

        if(onEnttTimer != nullptr)
            onEnttTimer(EnttArg);
    }
}

