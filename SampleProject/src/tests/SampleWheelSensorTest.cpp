#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "SampleWheelSensor.h"
#include "IWheelSensor.h"
#include "IConfigurationData.h"
#include "ITripData.h"
#include "IWheelSensor.mock"
#include "IConfigurationData.mock"
#include "ITripData.mock"

//Example of EXPECT_CALL usage
//Demonstation of a technic to call private member in device under test in multiple tests and only use one "friend"

using ::testing::Return;
using ::testing::_;			//This enables parameter ignoring using '_'
using ::testing::InSequence;

void CallPrivateSensorEvent(SampleWheelSensor& dut)
{
    dut.SensorEvent();
}

// Test that Init connects to wheel sensor with correct pointer
TEST(SampleWheelSensor, Init) 
{
    MockIWheelSensor iWheelSensorMock;
    MockIConfigurationData iConfigurationDataMock;
    MockITripData iTripDataMock;

    SampleWheelSensor dut(iWheelSensorMock,
                          iConfigurationDataMock,
                          iTripDataMock);

    EXPECT_CALL(iWheelSensorMock, ConnectClient(&dut));
    dut.Init();
}

//Test that SensorEvent reads configuration, calculates correct and stores data in Trip data.
TEST(SampleWheelSensor, OneSensorEvent)
{
    const int TestDistancePrRotationInMm = 2095;
    const int ExpectedDistanceInM = 2;

    MockIWheelSensor iWheelSensorMock;
    MockIConfigurationData iConfigurationDataMock;
    MockITripData iTripDataMock;

    SampleWheelSensor dut(iWheelSensorMock,
        iConfigurationDataMock,
        iTripDataMock);

    EXPECT_CALL(iTripDataMock, SetDistanceInM(ExpectedDistanceInM));
    EXPECT_CALL(iConfigurationDataMock, GetDistancePrRotationInMm()).WillOnce(Return(TestDistancePrRotationInMm));
    CallPrivateSensorEvent(dut);
}

//Test that SensorEvent reads configuration, calculates correct and stores data in Trip data.
//Verify the sequence
TEST(SampleWheelSensor, OneSensorEventInSequence)
{
    const int TestDistancePrRotationInMm = 2095;
    const int ExpectedDistanceInM = 2;

    MockIWheelSensor iWheelSensorMock;
    MockIConfigurationData iConfigurationDataMock;
    MockITripData iTripDataMock;

    SampleWheelSensor dut(iWheelSensorMock,
        iConfigurationDataMock,
        iTripDataMock);

    {
        InSequence s;
        EXPECT_CALL(iConfigurationDataMock, GetDistancePrRotationInMm()).WillOnce(Return(TestDistancePrRotationInMm));
        EXPECT_CALL(iTripDataMock, SetDistanceInM(ExpectedDistanceInM));
    }
    CallPrivateSensorEvent(dut);
}


//Test that SensorEvent calculates correct after long distance.
//Is done by calling SensorEvent specified number of times and verify that Trip data is updated as expected.
TEST(SampleWheelSensor, MultipleSensorEvent)
{
    const int TestDistancePrRotationInMm = 2095;
    const int ExpectedDistanceInM = 20950;
    const int TestWheelRotations = 10000;

    MockIWheelSensor iWheelSensorMock;
    MockIConfigurationData iConfigurationDataMock;
    MockITripData iTripDataMock;

    SampleWheelSensor dut(iWheelSensorMock,
        iConfigurationDataMock,
        iTripDataMock);

    EXPECT_CALL(iConfigurationDataMock, GetDistancePrRotationInMm()).WillRepeatedly(Return(TestDistancePrRotationInMm));
    EXPECT_CALL(iTripDataMock, SetDistanceInM(_)).Times(TestWheelRotations - 1);
    EXPECT_CALL(iTripDataMock, SetDistanceInM(ExpectedDistanceInM));

    for (int n = 0; n < TestWheelRotations; n++)
    {
        CallPrivateSensorEvent(dut);
    }
}

//Test that ResetCount resets the internal counter.
//Is done by calling SensorEvent specified number of times, call ResetCount and verify that Trip data is updated as expected.
TEST(SampleWheelSensor, ResetCount)
{
    const int TestDistancePrRotationInMm = 2095;
    const int ExpectedDistanceInM = 2;
    const int TestWheelRotations = 10000;

    MockIWheelSensor iWheelSensorMock;
    MockIConfigurationData iConfigurationDataMock;
    MockITripData iTripDataMock;

    SampleWheelSensor dut(iWheelSensorMock,
        iConfigurationDataMock,
        iTripDataMock);

    EXPECT_CALL(iConfigurationDataMock, GetDistancePrRotationInMm()).WillRepeatedly(Return(TestDistancePrRotationInMm));
    EXPECT_CALL(iTripDataMock, SetDistanceInM(_)).Times(TestWheelRotations);
    for (int n = 0; n < TestWheelRotations; n++)
    {
        CallPrivateSensorEvent(dut);
    }

    dut.ResetCount();
    EXPECT_CALL(iTripDataMock, SetDistanceInM(ExpectedDistanceInM));                //Place this expect after execution of multiple calls
    CallPrivateSensorEvent(dut);
}
