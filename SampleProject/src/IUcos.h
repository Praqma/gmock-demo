#ifndef IUCOS_H
#define IUCOS_H

#include "types.h"

//! \brief This class demonstrates how to mock static "C" interfaces
//! The interface holds all those functions needed to mock
class IUcos
{
public:
    virtual void OSMutexPend(OS_EVENT *pevent, INT16U timeout, INT8U *err) = 0;
    virtual OS_EVENT *OSMutexCreate(INT8U prio, INT8U *err) = 0;
    virtual INT8U OSMutexPost(OS_EVENT *pevent) = 0;
    ~IUcos() {};
};

#endif  //#ifndef IUCOS_H
