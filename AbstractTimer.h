#ifndef h_IP_Abstract_Timer
#define h_IP_Abstract_Timer

class TimerSource // Wrapper object around a time source for creating system independent timers
{
public:
    virtual unsigned long getSystemTime() const = 0; // millis() in arduino
};

class DefaultTimerSource : public TimerSource
{
private:
    // Tried using std::function<unsigned long(void)> getSystemTime; and lambdas
    // It felt cleaner in alot of ways be you couldn't change the global/default source on the fly or assign in the declaration section of code

    // Also tried Raw function pointers (unsigned long (*DefaultSystemTime)(void);)
    // but thats just virtual TimerSource with less abstraction, could be better, could be more prone to error.

    TimerSource &timerSource;

public:
    explicit DefaultTimerSource(TimerSource &timerSource) : timerSource{timerSource} {};
    unsigned long getSystemTime() const { return timerSource.getSystemTime(); };
};
static DefaultTimerSource *globalTimerSource;

class Timer
{
private:
    virtual unsigned long getDuration() const = 0;

public:
    virtual void reset() = 0; // Sets Timers start point to now
    virtual void next() = 0;  // Shifts timers start point along, resets if timer would be elapsed still
    virtual bool isElapsed() = 0;
    virtual void setDelay_ms(unsigned long delay_ms) = 0;
    virtual unsigned long getDelay_ms() const = 0; // Returns the duration (ms) this timer is set to
};

class ExtendedTimer : public Timer
{
public:
    virtual void setRemaining_ms(unsigned long remaining) = 0;
    virtual unsigned long getRemaining_ms() const = 0;
    virtual void stop() = 0;
};

class TimerWithSource : public ExtendedTimer
{
private:
    volatile unsigned long Starting_ms;
    unsigned long Delay_ms;
    TimerSource &timerSource;
    bool Active = true;
    bool Elapsed = false;
    unsigned long getDuration() const;

public:
    explicit TimerWithSource(unsigned long delay_ms, TimerSource &timerSource) : Delay_ms{delay_ms},
                                                                                 timerSource{timerSource}
    {
        reset();
    };

    void reset(); // Sets Timers start point to now
    void next();  // Shifts timers start point along, resets if timer would be elapsed still, not recommend if stop is used
    bool isElapsed();
    void setDelay_ms(unsigned long delay_ms);
    unsigned long getDelay_ms() const;
    void setRemaining_ms(unsigned long remaining);
    unsigned long getRemaining_ms() const;
    void stop(); // stop timer, causing all isElapsed checks to return false and getRemaining_ms to return 0;
};

class TimerDefault : public TimerWithSource
{
public:
    TimerDefault(const unsigned long delay_ms) : TimerWithSource(delay_ms, *globalTimerSource){};
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