#include <Timers.h>

void Timer::Reset()
{
    this->start = millis();
}

void Timer::Next()
{
    this->start = this->start + this->SetPoint();
    if (this->Check()){
        this->Reset();
    }
}

bool Timer::Check() const
{
    return (millis() - this->start >= this->delay);
}

uint16_t Timer::SetPoint() const
{
    return delay;
}

uint16_t Timer::Remaining() const
{
    if (Check())
    {
        return 0;
    }
    return (this->delay - (millis() - this->start));
}

void Timer::Set(uint16_t delay)
{
    this->delay = delay;
}

void Timer::Adjust(uint16_t remaining)
{
    this->start = millis() + remaining - this->delay;
}

void LongTimer::Set(unsigned long delay)
{
    this->delay = delay;
}

void LongTimer::Adjust(unsigned long remaining)
{
    this->start = millis() + remaining - this->delay;
}

bool LongTimer::Check() const
{
    return (millis() - this->start >= this->delay);
}

unsigned long LongTimer::SetPoint() const
{
    return delay;
}

unsigned long LongTimer::Remaining() const
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
        this->Next();
        return true;
    }
    return false;
}
