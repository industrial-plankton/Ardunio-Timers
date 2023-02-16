#include <AbstractTimer.h>
void TimerWithSource::Reset()
{
    this->start = timerSource.SystemTime();
    this->running = true;
};

// Sets Timers start point to now
void TimerWithSource::Next()
{
    this->start = this->start + this->getDelay();
    if (this->timerSource.SystemTime())
    {
        this->Reset();
    }
};

// Shifts timers start point along, resets if timer would be elapsed still
bool TimerWithSource::isElapsed() const
{
    return (running && (this->timerSource.SystemTime() - this->start) >= this->delay);
};

void TimerWithSource::setDelay(unsigned long delay)
{
    this->delay = delay;
};

// Check if set duration has elapsed returns true if so
unsigned long TimerWithSource::getDelay() const
{
    return delay;
};

// Returns the duration (ms) this timer is set to
void TimerWithSource::setRemaining(unsigned long remaining)
{
    this->start = this->timerSource.SystemTime() + remaining - this->delay;
};

unsigned long TimerWithSource::getRemaining() const
{
    if (isElapsed() || !this->running)
    {
        return 0;
    }
    return (this->delay - (this->timerSource.SystemTime() - this->start));
};

void TimerWithSource::Stop()
{
    this->running = false;
};