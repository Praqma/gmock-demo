#ifndef ITRIPDATA_H
#define ITRIPDATA_H

//! \brief This class holds all user data for the display
//! The class is only a container. No functionality are provided
//! 1) The different data in the record are not "atomized".
//! 2) Only the time record are "atomized".
class ITripData
{
public:
    
    //! \brief The total distance biked for this session
    //! Set total distance
    //! \param distanceInM the distance in m
    virtual void SetDistanceInM(int distanceInM) = 0;

    //! \brief The total time for this session
    //! Set total time
    //! \param timeInS time in seconds
    virtual void SetTimeElapsedInS(int timeInS) = 0;

    //! \brief The start time for this session
    //! \param hours the hours [0..23]
    //! \param minutes the minutes [0..59]
    //! \param seconds the seconds [0..59]
    virtual void SetStartTime(int hours, int minutes, int seconds) = 0;

    //! \brief The maximum speed for this session
    //! \param maxSpeedInKmh Max speed in km/h
    virtual void SetMaxSpeedInKmh(int maxSpeedInKmh) = 0;

    //! \brief See SetDistanceInM
    //! \return int Distance biked in m
    virtual int GetDistanceInM() = 0;

    //! \brief See SetTimeElapsedInS
    //! \return int elapsed time in s
    virtual int GetTimeElapsedInS() = 0;

    //! \brief see SetStartTime
    //! \param hours    see SetStartTime
    //! \param minutes
    //! \param seconds
    virtual void GetStartTime(int &hours, int &minutes, int &seconds) = 0;

    //! \brief See SetMaxSpeedInKmh
    //! \return int the max speed in km/h
    virtual int GetMaxSpeedInKmh() = 0;

    ~ITripData() {};
};

#endif  //#ifndef ITRIPDATA_H