#include "TripData.h"
#include "assert.h"
#include "ScopedMutex.h"

TripData::TripData(IMutex& mutex) :
    mMutex(mutex),
    mDistanceInM(0),
    mTimeInS(0),
    mStartHours(0),
    mStartMinutes(0),
    mStartSeconds(0),
    mMaxSpeedInKmh(0)
{
}

void TripData::SetDistanceInM(int distanceInM)
{
    assert(distanceInM >= 0);
    mDistanceInM = distanceInM;
}

void TripData::SetTimeElapsedInS(int timeInS)
{
    assert(timeInS >= 0);
    mTimeInS = timeInS;
}

void TripData::SetStartTime(int hours, int minutes, int seconds)
{
    ScopedMutex atomic(mMutex);
    assert(hours >= 0);
    assert(hours < 24);
    assert(minutes >= 0);
    assert(minutes < 60);
    assert(seconds >= 0);
    assert(seconds < 60);
    mStartHours = hours;
    mStartMinutes = minutes;
    mStartSeconds = seconds;
}

void TripData::SetMaxSpeedInKmh(int maxSpeedInKmh)
{
    assert(maxSpeedInKmh >= 0);
    mMaxSpeedInKmh = maxSpeedInKmh;
}

int TripData::GetDistanceInM()
{
    return mDistanceInM;
}

int TripData::GetTimeElapsedInS()
{
    return mTimeInS;
}

void TripData::GetStartTime(int &hours, int &minutes, int &seconds)
{
    ScopedMutex atomic(mMutex);
    hours = mStartHours;
    minutes = mStartMinutes;
    seconds = mStartSeconds;
}

int TripData::GetMaxSpeedInKmh()
{
    return mMaxSpeedInKmh;
}
