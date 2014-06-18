#ifndef SCOPEDMUTEX_H
#define SCOPEDMUTEX_H

#include "IMutex.h"

//! \brief This class is used to protect a scope.
//! The Lock() method is called when the default constructer is called when entering the scope.
//! The Unlock() is called when the scoped mutex is automatically deleted when leaving the scope
//! This implementation has the great advantage that Unlock() is allways called whatever the program is doing.
class ScopedMutex
{
public:
    ScopedMutex(IMutex& mutex) : mMutex(mutex)
    {
        mMutex.Lock();
    }

    ~ScopedMutex()
    {
        mMutex.Unlock();
    }

private:
    IMutex& mMutex;
};

#endif  //#ifndef SCOPEDMUTEX_H