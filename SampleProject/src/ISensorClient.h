#ifndef ISENSORCLIENT_H
#define ISENSORCLIENT_H

//! This class abstracts a sensor client which is interested to be called each time an event is generated.
//! The client will inherit this class in order to inform the sensor driver which method to call on an event
//! In this example "SensorEvent()" will be called each time the wheel magnet passes the sensor.
class ISensorClient
{
public:
    
    //! \brief The sensor driver will call this method on each sensor event
    virtual void SensorEvent() = 0;

    ~ISensorClient() {};
};

#endif  //#ifndef ISENSORCLIENT_H