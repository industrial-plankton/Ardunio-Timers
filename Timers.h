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
  Timer(const unsigned int delay) : delay{delay} { Reset(); }

  // Sets Timers start point to now
  void Reset();

  // Change the timers setpoint
  void Set(unsigned int delay);

  // Check if set duration has elapsed returns true if so
  bool Check();

  // Returns the duration (ms) this timer is set to
  unsigned int SetPoint();

  // Return ms remaining before duration is reached
  unsigned int Remaining();
};

// Timer using a Long for its setpoint for very slow events
class LongTimer : public Timer
{
protected:
  unsigned long delay;

public:
  LongTimer(const unsigned long delay) : Timer{10000} { Set(delay); }

  void Set(unsigned long delay);
  bool Check();
  unsigned long SetPoint();
  unsigned long Remaining();
};

// untested
class LongTimerOneShot : public LongTimer
{
protected:
  bool state = false;

public:
  LongTimerOneShot(const unsigned long delay) : LongTimer{10000} { Set(delay); }

  void Reset();
  bool Check();
  void Stop();
};

// Timer that once triggered and Checked needs to be reset before it before it will be true again.
// Main purpose is to allow triggering of an event x time after another event, but not continuously
class TimerOneShot : public Timer
{
protected:
  bool state = false;

public:
  TimerOneShot(const unsigned int delay) : Timer{delay} {}

  void Reset();
  bool Check();
  void Stop();
};

// Timer that gets reset automatically reset once it triggers
// Main purpose is a periodic event
class TimerAutoReset : public Timer
{
public:
  TimerAutoReset(const unsigned int delay) : Timer{delay} {}

  bool Check();
};

#endif