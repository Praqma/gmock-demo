#ifndef TRIPDATA_H
#define TRIPDATA_H

class IMutex;

class TripData
{
public:
    TripData(IMutex& mutex);

    void SetDistanceInM(int distanceInM);
    void SetTimeElapsedInS(int timeInS);
    void SetStartTime(int hours, int minutes, int seconds);
    void SetMaxSpeedInKmh(int maxSpeedInKmh);

    int GetDistanceInM();
    int GetTimeElapsedInS();
    void GetStartTime(int &hours, int &minutes, int &seconds);
    int GetMaxSpeedInKmh();

private:
    IMutex& mMutex;
    int mDistanceInM;
    int mTimeInS;
    int mStartHours;
    int mStartMinutes;
    int mStartSeconds;
    int mMaxSpeedInKmh;
};

#endif  //#ifndef TRIPDATA_H