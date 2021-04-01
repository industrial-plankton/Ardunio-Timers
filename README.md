# Simple Timers to simplify orchestration of timed events. 

Mainly used to ensure a certain length of time has passed since another event, as it does not use interupts to immidially execute when the timer has elapesed, and they need to be checked manually.

## ```C++Timer(const unsigned int delay)```
The base timer
ex:
```C++
Timer timer(800U);
if (timer.Check()){
  // do things
  timer.Reset();
}
```

## TimerMulti(const unsigned int delay, const unsigned int delay2)
Allows changing delay between two values
ex: 
```C++
TimerMulti timer(800U, 50000U);
if (Timer.Check()){
 if (/*cond*/){
  timer.Reset1(); // Triigger in 0.8s
  } else {
  timer.Reset2(); // Triigger in 50s
  }
}
```

## TimerOneShot(const unsigned int delay)
Once triggered and Checked() needs to be Reset() before it before Checked() returns true again
ex: 
```C++
TimerOneShot timer(800U);
if (timer.Check()){
  // do things
}
```

## TimerAutoReset(const unsigned int delay)
Resets itself when Check() returns true
ex: 
```C++
TimerAutoReset timer(800U);
if (timer.Check()){
  // do things
}
```
