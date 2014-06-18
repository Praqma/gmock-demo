#ifndef SAMPLEWHEELSENSOR_H
#define SAMPLEWHEELSENSOR_H

#include "ISensorClient.h"

class IWheelSensor;
class IConfigurationData;
class ITripData;

class SampleWheelSensor : public ISensorClient
{
public:
    SampleWheelSensor(
        IWheelSensor& wheelSensor,
        IConfigurationData& configurationData,
        ITripData& tripData);

    void Init();

    void ResetCount();

private:
    IWheelSensor& mWheelSensor;
    IConfigurationData& mConfigurationData;
    ITripData& mTripData;
    int mRotationCount;

    void SensorEvent();

friend void CallPrivateSensorEvent(SampleWheelSensor& dut);
};

#endif  //#ifndef SAMPLEWHEELSENSOR_H