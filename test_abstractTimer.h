#include "unity.h"
#include <AbstractTimer.h>

class AbstractTimerDummyTime : public TimerSource // Wrapper object around a system time source for creating system independent timers
{
public:
    AbstractTimerDummyTime(){};
    long time = 0;
    unsigned long getSystemTime() const { return time; };
};

void setUpAbstractTimers(void)
{
    // put your setup code here, to run once:
}

void tearDownAbstractTimers(void)
{
    // clean stuff up here
}

void test_wraparound()
{
    AbstractTimerDummyTime testTime;
    testTime.time = 100;
    TimerWithSource TimerToTest(10, testTime);
    testTime.time = 105;
    TEST_ASSERT_FALSE(TimerToTest.isElapsed());
    testTime.time = 110;
    TEST_ASSERT_TRUE(TimerToTest.isElapsed());
    testTime.time = 10;
    TEST_ASSERT_TRUE(TimerToTest.isElapsed());
    testTime.time = 105;
    TEST_ASSERT_TRUE(TimerToTest.isElapsed());
}

void test_next()
{
    AbstractTimerDummyTime testTime;
    testTime.time = 100;
    TimerWithSource TimerToTest(10, testTime);
    TimerToTest.next();
    testTime.time = 105;
    TEST_ASSERT_FALSE(TimerToTest.isElapsed());
    testTime.time = 115;
    TEST_ASSERT_TRUE(TimerToTest.isElapsed());
    testTime.time = 150;
    TimerToTest.next();
    testTime.time = 155;
    TEST_ASSERT_FALSE(TimerToTest.isElapsed());
    testTime.time = 165;
    TEST_ASSERT_TRUE(TimerToTest.isElapsed());
}

void TestAbstractTimers(void)
{
    setUpAbstractTimers();

    RUN_TEST(test_wraparound);
    RUN_TEST(test_next);

    tearDownAbstractTimers();
}
