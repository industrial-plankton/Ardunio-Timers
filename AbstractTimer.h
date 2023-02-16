#ifndef h_Abstract_Timer
#define h_Abstract_Timer

class TimerSource // Wrapper object around a system time source for creating system independent timers
{
public:
    virtual unsigned long getSystemTime() const = 0; // millis() in arduino
};

class DefaultTimerSource : public TimerSource
{
private:
    TimerSource &timerSource;

public:
    explicit DefaultTimerSource(TimerSource &timerSource) : timerSource{timerSource} {};
    unsigned long getSystemTime() const { return timerSource.getSystemTime(); };
};
static DefaultTimerSource *globalTimerSource;

class Timer
{
public:
    virtual void reset() = 0;     // Sets Timers start point to now
    virtual void next() = 0;      // Shifts timers start point along, resets if timer would be elapsed still
    virtual bool isElapsed() = 0; // Check if set duration has elapsed returns true if so
    virtual void setDelay_ms(unsigned long delay) = 0;
    virtual unsigned long getDelay_ms() const = 0; // Returns the duration (ms) this timer is set to
    // explicit Timer(const unsigned long delay, TimerSource &timerSource) : delay{delay}, timerSource{timerSource} {} // Suggested constructor on the concrete class
};

class ExtendedTimer : public Timer
{
public:
    virtual void setRemaining_ms(unsigned long remaining) = 0;
    virtual unsigned long getRemaining_ms() = 0;
    virtual void stop() = 0;
};

class TimerWithSource : public ExtendedTimer
{
private:
    volatile unsigned long Starting_ms;
    unsigned long Delay_ms;
    TimerSource &timerSource;
    bool Active = false;
    bool Elapsed = false;

public:
    explicit TimerWithSource(unsigned long delay, TimerSource &timerSource) : Delay_ms{delay},
                                                                              timerSource{timerSource}
    {
        reset();
    };

    void reset(); // Sets Timers start point to now
    void next();  // Shifts timers start point along, resets if timer would be elapsed still, not recommend if stop is used
    bool isElapsed();
    void setDelay_ms(unsigned long delay);
    unsigned long getDelay_ms() const;
    void setRemaining_ms(unsigned long remaining);
    unsigned long getRemaining_ms();
    void stop(); // stop timer, causing all isElapsed checks to return false and getRemaining_ms to return 0;
};

class TimerDefault : public TimerWithSource
{
public:
    TimerDefault(const unsigned long delay) : TimerWithSource(delay, *globalTimerSource){};
};

// Example DefaultTimerSource for Arduino
// #include <Arduino.h>
// class ArduinoTimerSource : public TimerSource // Wrapper object around a system time source for creating system independent timers
// {
// public:
//     ArduinoTimerSource(){};
//     unsigned long getSystemTime() const { return millis(); };
// };

// void dummyMain()
// {
//     ArduinoTimerSource ArduinoSource;
//     TimerWithSource timer(1000, ArduinoSource);
// or
//     ArduinoTimerSource ArduinoSource;
//     globalTimerSource = new DefaultTimerSource(ArduinoSource);
//     TimerDefault timer (1000)

//     timer.reset();
//     if (timer.isElapsed())
//     {
//         timer.setRemaining_ms(100);
//         timer.getRemaining_ms();
//     }
//     timer.stop();
// }

#endif