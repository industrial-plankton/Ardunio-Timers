#include <Timers.h>

void TimerBase::Reset()
{
    this->start = millis();
}

void TimerBase::Next()
{
    this->start = this->start + this->getSetPoint();
    if (this->isElapsed())
    {
        this->Reset();
    }
}

bool TimerOld::isElapsed() const
{
    return (millis() - this->start >= this->delay);
}

uint32_t TimerOld::getSetPoint() const
{
    return delay;
}

uint16_t TimerOld::getRemaining() const
{
    if (isElapsed())
    {
        return 0;
    }
    return (this->delay - (millis() - this->start));
}

void TimerOld::setDelay(uint16_t delay)
{
    this->delay = delay;
}

void TimerOld::setRemaining(uint16_t remaining)
{
    this->start = millis() + remaining - this->delay;
}

void LongTimer::setDelay(unsigned long delay)
{
    this->delay = delay;
}

void LongTimer::setRemaining(unsigned long remaining)
{
    this->start = millis() + remaining - this->delay;
}

bool LongTimer::isElapsed() const
{
    return (millis() - this->start >= this->delay);
}

unsigned long LongTimer::getSetPoint() const
{
    return delay;
}

unsigned long LongTimer::getRemaining() const
{
    if (this->isElapsed())
    {
        return 0;
    }
    return (this->delay - (millis() - this->start));
}

// untested
void LongTimerOneShot::Reset()
{
    LongTimer::Reset();
    this->state = true;
}

bool LongTimerOneShot::isElapsed()
{
    if (this->state && LongTimer::isElapsed())
    {
        this->state = false;
        return true;
    }
    return false;
}

void LongTimerOneShot::Stop()
{
    this->state = false;
}

// Timer that once triggered and Checked needs to be reset before it before it will be true again
void TimerOneShot::Reset()
{
    TimerOld::Reset();
    this->state = true;
}

bool TimerOneShot::isElapsed()
{
    if (this->state && TimerOld::isElapsed())
    {
        this->state = false;
        return true;
    }
    return false;
}

void TimerOneShot::Stop()
{
    this->state = false;
}

// Timer that gets reset automatically reset once it triggers
bool TimerAutoReset::isElapsed()
{
    if (TimerOld::isElapsed())
    {
        this->Next();
        return true;
    }
    return false;
}
