#ifndef MUTEX_H
#define MUTEX_H

#include "types.h"

class Mutex
{
public:
    Mutex(int priority);
    void Lock();
    void Unlock();
private:
    OS_EVENT* mMutex;
};

#endif  //#ifndef MUTEX_H