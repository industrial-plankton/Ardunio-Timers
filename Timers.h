#ifndef IP_TIMERS_H
#define IP_TIMERS_H
/*
MIT License

Copyright (c) 2021 industrial-plankton

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <Arduino.h>

class Timer
{
protected:
  volatile unsigned long start = 0;
  unsigned int delay;

public:
  Timer(const unsigned int delay) : delay{delay}
  {
    Reset();
  }

  void Reset()
  {
    this->start = millis();
  }

  bool Check()
  {
    return (millis() - this->start >= this->delay);
  }

  unsigned int SetPoint()
  {
    return delay;
  }

  unsigned int Remaining()
  {
    if (Check())
    {
      return 0;
    }
    return (this->delay - (millis() - this->start));
  }
};

class SetableTimer : public Timer
{
public:
  SetableTimer(const unsigned int delay) : Timer{delay}
  {
  }

  void Set(unsigned int delay)
  {
    this->delay = delay;
  }
};

class SetableLongTimer : public Timer
{
protected:
  unsigned long delay;

public:
  SetableLongTimer(const unsigned long delay) : Timer{10000}
  {
    Set(delay);
  }

  void Set(unsigned long delay)
  {
    this->delay = delay;
  }

  bool Check()
  {
    return (millis() - this->start >= this->delay);
  }

  unsigned long SetPoint()
  {
    return delay;
  }

  unsigned long Remaining()
  {
    if (this->Check())
    {
      return 0;
    }
    return (this->delay - (millis() - this->start));
  }
};

// untested
class SetableLongTimerOneShot : public SetableLongTimer
{
protected:
  bool state = false;

public:
  SetableLongTimerOneShot(const unsigned long delay) : SetableLongTimer{10000}
  {
    Set(delay);
  }

  void Reset()
  {
    SetableLongTimer::Reset();
    this->state = true;
  }

  bool Check()
  {
    if (this->state && SetableLongTimer::Check())
    {
      this->state = false;
      return true;
    }
    return false;
  }

  void Stop()
  {
    this->state = false;
  }
};

// Timer that allows to two have 2 delay times that can be used
class TimerMulti : public Timer
{
protected:
  unsigned int delay1;
  unsigned int delay2;

public:
  TimerMulti(const unsigned int delay, const unsigned int delay2) : Timer{delay}, delay1{delay}, delay2{delay2}
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

#endif