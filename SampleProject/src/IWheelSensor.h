#ifndef IWHEELSENSOR_H
#define IWHEELSENSOR_H

class ISensorClient;

//! This class abstracts a sensor which generates an event each time a sensor event is detected.
//! For this example it will be the wheel sensor
class IWheelSensor
{
public:
    
    //! \brief Connects a client which will be called at each sensor event (in this example for each turn of the wheel).
    //! \param client The client instance to call
    virtual void ConnectClient(ISensorClient* client) = 0;

    ~IWheelSensor() {};
};

#endif  //#ifndef IWHEELSENSOR_H