#include <Timers.h>

void Timer::Reset()
{
    this->start = millis();
}

bool Timer::Check()
{
    return (millis() - this->start >= this->delay);
}

unsigned int Timer::SetPoint()
{
    return delay;
}

unsigned int Timer::Remaining()
{
    if (Check())
    {
        return 0;
    }
    return (this->delay - (millis() - this->start));
}

void Timer::Set(unsigned int delay)
{
    this->delay = delay;
}

void LongTimer::Set(unsigned long delay)
{
    this->delay = delay;
}

bool LongTimer::Check()
{
    return (millis() - this->start >= this->delay);
}

unsigned long LongTimer::SetPoint()
{
    return delay;
}

unsigned long LongTimer::Remaining()
{
    if (this->Check())
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

bool LongTimerOneShot::Check()
{
    if (this->state && LongTimer::Check())
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
    Timer::Reset();
    this->state = true;
}

bool TimerOneShot::Check()
{
    if (this->state && Timer::Check())
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
bool TimerAutoReset::Check()
{
    if (Timer::Check())
    {
        this->Reset();
        return true;
    }
    return false;
}
