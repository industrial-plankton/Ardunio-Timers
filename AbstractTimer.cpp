#include <AbstractTimer.h>

unsigned long TimerWithSource::getDuration() const
{
    return timerSource.getSystemTime() - Starting_ms;
}

void TimerWithSource::reset()
{
    Active = true;
    Elapsed = false;
    Starting_ms = timerSource.getSystemTime();
};

void TimerWithSource::next()
{
    Active = true;
    Elapsed = false;
    Starting_ms += getDelay_ms();
    if (isElapsed()) // still elapsed after forward shift
    {
        reset();
    }
};

bool TimerWithSource::isElapsed()
{
    if (Active && getDuration() >= Delay_ms)
    {
        Elapsed = true;
    }
    return Active && Elapsed;
};

void TimerWithSource::setDelay_ms(unsigned long delay_ms)
{
    Delay_ms = delay_ms;
};

unsigned long TimerWithSource::getDelay_ms() const
{
    return Delay_ms;
};

void TimerWithSource::setRemaining_ms(unsigned long remaining)
{
    Elapsed = false;
    // Starting_ms = timerSource.getSystemTime() + remaining - Delay_ms;
    Starting_ms += getRemaining_ms() - remaining;
};

unsigned long TimerWithSource::getRemaining_ms() const
{
    if (Elapsed || getDuration() >= Delay_ms)
    {
        return 0;
    }
    return Delay_ms - getDuration();
};

void TimerWithSource::stop()
{
    Active = false;
};