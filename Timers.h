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

class TimerBase
{
public:
  volatile unsigned long start = 0;
  void Reset();                             // Sets Timers start point to now
  void Next();                              // Shifts timers start point along, resets if timer would be elapsed still
  virtual bool isElapsed() const = 0;       // isElapsed if set duration has elapsed returns true if so
  virtual uint32_t getSetPoint() const = 0; // Returns the duration (ms) this timer is set to
  TimerBase() { Reset(); }
};

class Timer : public TimerBase
{
protected:
  uint16_t delay;

public:
  explicit Timer(const uint16_t delay) : TimerBase(), delay{delay} {}

  // Change the timers setpoint
  void setDelay(uint16_t delay);

  // setRemaining remaining time
  void setRemaining(uint16_t remaining);

  bool isElapsed() const override;
  uint32_t getSetPoint() const override;

  // Return ms remaining before duration is reached
  uint16_t getRemaining() const;
};

// Timer using a Long for its setpoint for very slow events
class LongTimer : public TimerBase
{
protected:
  unsigned long delay;

public:
  explicit LongTimer(const unsigned long delay) : TimerBase(), delay{delay} {}

  void setDelay(unsigned long delay);
  void setRemaining(unsigned long remaining);
  bool isElapsed() const override;
  unsigned long getSetPoint() const override;
  unsigned long getRemaining() const;
};

// untested
class LongTimerOneShot : public LongTimer
{
protected:
  bool state = false;

public:
  explicit LongTimerOneShot(const unsigned long delay) : LongTimer(delay) {}

  void Reset();
  bool isElapsed();
  void Stop();
};

// Timer that once triggered and Checked needs to be reset before it before it will be true again.
// Main purpose is to allow triggering of an event x time after another event, but not continuously
class TimerOneShot : public Timer
{
protected:
  bool state = false;

public:
  explicit TimerOneShot(const uint16_t delay) : Timer(delay) {}

  void Reset();
  bool isElapsed();
  void Stop();
};

// Timer that gets reset automatically reset once it triggers
// Main purpose is a periodic event
class TimerAutoReset : public Timer
{
public:
  explicit TimerAutoReset(const uint16_t delay) : Timer(delay) {}

  bool isElapsed();
};

#endif