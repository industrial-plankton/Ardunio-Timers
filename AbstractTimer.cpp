#include <AbstractTimer.h>
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
    if (Active && (timerSource.getSystemTime() - Starting_ms) >= Delay_ms)
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
    Starting_ms = timerSource.getSystemTime() + remaining - Delay_ms;
};

unsigned long TimerWithSource::getRemaining_ms()
{
    if (isElapsed() || !Active)
    {
        return 0;
    }
    return (Delay_ms - (timerSource.getSystemTime() - Starting_ms));
};

void TimerWithSource::stop()
{
    Active = false;
};