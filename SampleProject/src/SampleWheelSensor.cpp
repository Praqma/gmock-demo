#include "SampleWheelSensor.h"
#include "IWheelSensor.h"
#include "IConfigurationData.h"
#include "ITripData.h"

SampleWheelSensor::SampleWheelSensor(
    IWheelSensor& wheelSensor,
    IConfigurationData& configurationData,
    ITripData& tripData) :
    mWheelSensor(wheelSensor),
    mConfigurationData(configurationData),
    mTripData(tripData),
    mRotationCount(0)
{
}

void SampleWheelSensor::Init()
{
    mWheelSensor.ConnectClient(this);
}

void SampleWheelSensor::ResetCount()
{
    mRotationCount = 0;
}

void SampleWheelSensor::SensorEvent()
{
    const int MmPrMeter = 1000;
    mRotationCount++;
    int distanceInCm = mConfigurationData.GetDistancePrRotationInMm() * mRotationCount;
    int distanceInM = distanceInCm / MmPrMeter;
    mTripData.SetDistanceInM(distanceInM);
}