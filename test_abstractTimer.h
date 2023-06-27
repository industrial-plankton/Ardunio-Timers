#include "unity.h"
#include <AbstractTimer.h>
#include <DummyTime.h>

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
    DummyTimeSource testTime;
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
    DummyTimeSource testTime;
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
