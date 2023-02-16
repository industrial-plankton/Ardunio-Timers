#include <AbstractTimer.h>
void TimerWithSource::reset()
{
    this->Starting_ms = timerSource.getSystemTime();
    this->Active = true;
    Elapsed = false;
};

void TimerWithSource::next()
{
    this->Starting_ms = this->Starting_ms + this->getDelay_ms();
    if (this->timerSource.getSystemTime())
    {
        this->reset();
    }
};

bool TimerWithSource::isElapsed()
{
    if (Active && (this->timerSource.getSystemTime() - this->Starting_ms) >= this->Delay_ms)
    {
        Elapsed = true;
    }
    return Elapsed;
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