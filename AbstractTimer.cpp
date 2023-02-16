#include <AbstractTimer.h>
void TimerWithSource::Reset()
{
    this->start = timerSource.SystemTime();
    this->running = true;
};

void TimerWithSource::Next()
{
    this->start = this->start + this->getDelay();
    if (this->timerSource.SystemTime())
    {
        this->Reset();
    }
};

bool TimerWithSource::isElapsed() const
{
    return (running && (this->timerSource.SystemTime() - this->start) >= this->delay);
};

void TimerWithSource::setDelay(unsigned long delay)
{
    this->delay = delay;
};

unsigned long TimerWithSource::getDelay() const
{
    return delay;
};

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