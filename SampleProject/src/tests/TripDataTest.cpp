#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "TripData.h"
#include "IMutex.h"
#include "IMutex.mock"

//Example of ASSERT macros
//Example of insequence
//Example of death test

using ::testing::AnyNumber;
using ::testing::InSequence;

// Test that data can be stored and retrieved
TEST(TripData, SetAndGet)
{
    int TestDistanceInM = 1234;
    int TestTimeElapsedInS = 45678;
    int TestStartTimeHours = 10;
    int TestStartTimeMinutes = 20;
    int TestStartTimeSeconds = 30;
    int TestMaxSpeedInKmh = 59;

    MockIMutex mockMutex;

    EXPECT_CALL(mockMutex, Lock()).Times(AnyNumber());
    EXPECT_CALL(mockMutex, Unlock()).Times(AnyNumber());

    TripData dut(mockMutex);
    dut.SetDistanceInM(TestDistanceInM);
    dut.SetTimeElapsedInS(TestTimeElapsedInS);
    dut.SetStartTime(TestStartTimeHours, TestStartTimeMinutes, TestStartTimeSeconds);
    dut.SetMaxSpeedInKmh(TestMaxSpeedInKmh);

    ASSERT_EQ(TestDistanceInM, dut.GetDistanceInM());
    ASSERT_EQ(TestTimeElapsedInS, dut.GetTimeElapsedInS());
    int hour;
    int minute;
    int second;
    dut.GetStartTime(hour, minute, second);
    ASSERT_EQ(TestStartTimeHours, hour);
    ASSERT_EQ(TestStartTimeMinutes, minute);
    ASSERT_EQ(TestStartTimeSeconds, second);
    ASSERT_EQ(TestMaxSpeedInKmh, dut.GetMaxSpeedInKmh());
}

TEST(TripData, SetBeyondLimitsDeathTest)
{
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";

    int TestDistanceInMFail = -1;
    int TestTimeElapsedInSFail = -1;
    int TestStartTimeHoursOk = 23;
    int TestStartTimeHoursFail = 24;
    int TestStartTimeMinutesOk = 59;
    int TestStartTimeMinutesFail = 60;
    int TestStartTimeSecondsOk = 59;
    int TestStartTimeSecondsFail = 60;
    int TestMaxSpeedInKmh = -1;

    MockIMutex mockMutex;
    TripData dut(mockMutex);

    //Prevent "uninteresting function call" warnings
    EXPECT_CALL(mockMutex, Lock()).Times(AnyNumber());
    EXPECT_CALL(mockMutex, Unlock()).Times(AnyNumber());

    EXPECT_EXIT(dut.SetDistanceInM(TestDistanceInMFail), ::testing::ExitedWithCode(3), "");
    EXPECT_EXIT(dut.SetTimeElapsedInS(TestTimeElapsedInSFail), ::testing::ExitedWithCode(3), "");
    EXPECT_EXIT(dut.SetDistanceInM(TestDistanceInMFail), ::testing::ExitedWithCode(3), "");
    EXPECT_EXIT(dut.SetDistanceInM(TestDistanceInMFail), ::testing::ExitedWithCode(3), "");
    EXPECT_EXIT(dut.SetStartTime(TestStartTimeHoursOk, TestStartTimeMinutesOk, TestStartTimeSecondsFail), ::testing::ExitedWithCode(3), "");
    EXPECT_EXIT(dut.SetStartTime(TestStartTimeHoursOk, TestStartTimeMinutesFail, TestStartTimeSecondsOk), ::testing::ExitedWithCode(3), "");
    EXPECT_EXIT(dut.SetStartTime(TestStartTimeHoursFail, TestStartTimeMinutesOk, TestStartTimeSecondsOk), ::testing::ExitedWithCode(3), "");
    EXPECT_EXIT(dut.SetMaxSpeedInKmh(TestMaxSpeedInKmh), ::testing::ExitedWithCode(3), "");
}

TEST(TripData, SetAndGetUsesMutex)
{
    int TestStartTimeHours = 10;
    int TestStartTimeMinutes = 20;
    int TestStartTimeSeconds = 30;

    MockIMutex mockMutex;
    TripData dut(mockMutex);
    {
        InSequence s;
        EXPECT_CALL(mockMutex, Lock());
        EXPECT_CALL(mockMutex, Unlock());
        dut.SetStartTime(TestStartTimeHours, TestStartTimeMinutes, TestStartTimeSeconds);
    }
    {
        InSequence s;
        EXPECT_CALL(mockMutex, Lock());
        EXPECT_CALL(mockMutex, Unlock());
        int hour;
        int minute;
        int second;
        dut.GetStartTime(hour, minute, second);
    }
}
