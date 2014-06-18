#ifndef IMUTEX_H
#define IMUTEX_H

//! \brief The class abstacts a mutex
class IMutex
{
public:
    //! \brief  Locks the mutex.
    //! If the mutex is locked the calling process will be suspended until the mutex is unlocked.
    virtual void Lock() = 0;

    //! \brief Unlocks the mutex
    //! Any pending processes for this mutex will be rescheduled
    virtual void Unlock() = 0;

    ~IMutex() {};
};

#endif  //#ifndef IMUTEX_H