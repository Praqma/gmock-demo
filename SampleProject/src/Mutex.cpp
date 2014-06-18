#include "Mutex.h"
#include "ucos.h"
#include "assert.h"

Mutex::Mutex(int priority)
{
    INT8U err;
    mMutex = OSMutexCreate(priority, &err);
    assert(err == OS_NO_ERR);
}

void Mutex::Lock()
{
    const INT16U NoTimeout = 0;
    INT8U err;
    OSMutexPend(mMutex, NoTimeout, &err);
    assert(err == OS_NO_ERR);
}

void Mutex::Unlock()
{
    INT8U err;
    err = OSMutexPost(mMutex);
    assert(err == OS_NO_ERR);
}