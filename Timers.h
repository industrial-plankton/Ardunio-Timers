#include <Arduino.h>

class Timer
{
protected:
  volatile unsigned long start = 0;
  unsigned int delay;

public:
  Timer(const unsigned int delay) : delay{delay}
  {
  }

  void Reset()
  {
    this->start = millis();
  }

  bool Check()
  {
    return (millis() - this->start >= this->delay);
  }
};

// Timer that allows to two have 2 delay times that can be used
class TimerMulti : public Timer
{
protected:
  unsigned int delay1;
  unsigned int delay2;

public:
  TimerMulti(const unsigned int delay, const unsigned int delay2) : delay1{delay}, delay2{delay2}, Timer{delay}
  {
  }
  void Reset()
  {
    this->delay = this->delay1;
    Timer::Reset();
  }

  void Reset2()
  {
    this->delay = this->delay2;
    Timer::Reset();
  }
};

// Timer that once triggered and Checked needs to be reset before it before it will be true again
class TimerOneShot : public Timer
{
protected:
  bool state = false;

public:
  TimerOneShot(const unsigned int delay) : Timer{delay}
  {
  }

  void Reset()
  {
    Timer::Reset();
    this->state = true;
  }

  bool Check()
  {
    if (this->state && Timer::Check())
    {
      this->state = false;
      return true;
    }
    return false;
  }
};

// Timer that gets reset automatically reset once it triggers
class TimerAutoReset : public Timer
{
public:
  TimerAutoReset(const unsigned int delay) : Timer{delay}
  {
  }

  bool Check()
  {
    if (Timer::Check())
    {
      this->Reset();
      return true;
    }
    return false;
  }
};