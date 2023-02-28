#ifndef h_FuncTimer
#define h_FuncTimer
#include <functional>

struct FuncTimer
{
    unsigned long Starting_ms;
    unsigned long delay;
    bool Active = true;
    bool Elapsed = false;
    std::function<unsigned long(void)> getSystemTime;
};

FuncTimer reset(FuncTimer timerData); // Sets Timers start point to now
FuncTimer next(FuncTimer timerData);  // Shifts timers start point along, resets if timer would be elapsed still, not recommend if stop is used
FuncTimer isElapsed(FuncTimer timerData);
FuncTimer setRemaining_ms(FuncTimer timerData, unsigned long remaining);
unsigned long getRemaining_ms(FuncTimer timerData);
FuncTimer stop(FuncTimer timerData);

unsigned long getDuration(FuncTimer timerData)
{
    return timerData.getSystemTime() - timerData.Starting_ms;
}

FuncTimer reset(FuncTimer timerData)
{
    timerData.Active = true;
    timerData.Elapsed = false;
    timerData.Starting_ms = timerData.getSystemTime();
    return timerData;
}

FuncTimer next(FuncTimer timerData)
{
    timerData.Active = true;
    timerData.Elapsed = false;
    timerData.Starting_ms += timerData.delay;
    timerData = isElapsed(timerData);
    if (timerData.Elapsed) // still elapsed after forward shift
    {
        timerData = reset(timerData);
    }
    return timerData;
}

FuncTimer isElapsed(FuncTimer timerData)
{
    if (timerData.Active && getDuration(timerData) >= timerData.delay)
    {
        timerData.Elapsed = true;
    }
    return timerData;
}

FuncTimer setRemaining_ms(FuncTimer timerData, unsigned long remaining)
{
    timerData.Elapsed = false;
    // Starting_ms = timerSource.getSystemTime() + remaining - Delay_ms;
    timerData.Starting_ms += getRemaining_ms(timerData) - remaining;
}

unsigned long getRemaining_ms(FuncTimer timerData)
{
    if (timerData.Elapsed || getDuration(timerData) >= timerData.delay)
    {
        return 0;
    }
    return timerData.delay - getDuration(timerData);
}

FuncTimer stop(FuncTimer timerData)
{
    timerData.Active = false;
    return timerData;
}

#endif