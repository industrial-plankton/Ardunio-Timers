#ifndef h_Abstract_Timer
#define h_Abstract_Timer

class TimerSource // Wrapper object around a system time source for creating system independent timers
{
public:
    virtual unsigned long SystemTime() const = 0; // millis() in arduino
};

class DefaultTimerSource : public TimerSource
{
private:
    const TimerSource &timerSource;

public:
    explicit DefaultTimerSource(const TimerSource &timerSource) : timerSource{timerSource} {};
    unsigned long SystemTime() const { return timerSource.SystemTime(); };
};
DefaultTimerSource *globalTimerSource = __null;

class Timer
{
public:
    virtual void Reset() = 0;           // Sets Timers start point to now
    virtual void Next() = 0;            // Shifts timers start point along, resets if timer would be elapsed still
    virtual bool isElapsed() const = 0; // Check if set duration has elapsed returns true if so
    virtual void setDelay(unsigned long delay) = 0;
    virtual unsigned long getDelay() const = 0; // Returns the duration (ms) this timer is set to
    // explicit Timer(const unsigned long delay, TimerSource &timerSource) : delay{delay}, timerSource{timerSource} {} // Suggested constructor on the concrete class
};

class ExtendedTimer : public Timer
{
public:
    virtual void setRemaining(unsigned long remaining) = 0;
    virtual unsigned long getRemaining() const = 0;
    virtual void Stop() = 0;
};

class TimerWithSource : public ExtendedTimer
{
private:
    volatile unsigned long start;
    unsigned long delay;
    const TimerSource &timerSource;
    bool running = false;

public:
    explicit TimerWithSource(const unsigned long delay, const TimerSource &timerSource) : delay{delay}, timerSource{timerSource} { Reset(); };

    void Reset();           // Sets Timers start point to now
    void Next();            // Shifts timers start point along, resets if timer would be elapsed still, not recommend if stop is used
    bool isElapsed() const; // Check if set duration has elapsed returns true if so
    void setDelay(unsigned long delay);
    unsigned long getDelay() const; // Returns the duration (ms) this timer is set to
    void setRemaining(unsigned long remaining);
    unsigned long getRemaining() const;
    void Stop(); // Stop timer, causing all isElapsed checks to return false and getRemaining to return 0;
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
//     unsigned long SystemTime() const { return millis(); };
// };

// void dummyMain()
// {
//     const ArduinoTimerSource ArduinoSource;
//     TimerWithSource timer(1000, ArduinoSource);
// or
//     const ArduinoTimerSource ArduinoSource;
//     globalTimerSource = new DefaultTimerSource(ArduinoSource);
//     TimerDefault timer (1000)

//     timer.Reset();
//     if (timer.isElapsed())
//     {
//         timer.setRemaining(100);
//         timer.getRemaining();
//     }
//     timer.Stop();
// }

#endif