#ifndef DummyTimer_h
#define DummyTimer_h
#include <AbstractTimer.h>

class DummyTimeSource : public TimerSource // Wrapper object around a system time source for creating system independent timers
{
public:
    DummyTimeSource() = default;
    long time = 0;
    unsigned long getSystemTime() const { return time; };
};
DummyTimeSource GlobalDummyTimerSource;

#endif