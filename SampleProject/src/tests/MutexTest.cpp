#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "IUcos.h"
#include "Mutex.h"
#include "IUcos.mock"
#include "ucos.h"
#include "assert.h"

// Example of mocking C functions

using ::testing::_;			//This enables parameter ignoring using '_'
using ::testing::SetArgPointee;
using ::testing::Return;
using ::testing::AnyNumber;

MockIUcos* myUcosMock;

void OSMutexPend(OS_EVENT *pevent, INT16U timeout, INT8U *err)
{
    assert(myUcosMock != 0);
    myUcosMock->OSMutexPend(pevent, timeout, err);
}

OS_EVENT *OSMutexCreate(INT8U prio, INT8U *err)
{
    assert(myUcosMock != 0);
    return myUcosMock->OSMutexCreate(prio, err);
}

INT8U OSMutexPost(OS_EVENT *pevent)
{
    assert(myUcosMock != 0);
    return myUcosMock->OSMutexPost(pevent);
}


// Test Mutex is created as expected
TEST(Mutex, constructSunnyDay)
{
    const INT8U TestPriority = 3;
    INT8U err = OS_NO_ERR;
    OS_EVENT event;

    MockIUcos ucosMock;         //Declare this as local variable as GMOCK checks for memory leaks
    myUcosMock = &ucosMock;     //Reference to mock must be set before use

    EXPECT_CALL(ucosMock, OSMutexCreate(TestPriority, _)).WillOnce(DoAll(SetArgPointee<1>(err), Return(&event)));

    Mutex dut(TestPriority);
    myUcosMock = 0;             //Prevent others from using dead instance (ucosMock)
}

// Test that errors result in assert
TEST(Mutex, constructRainyDay)
{
    const INT8U TestPriority = 3;
    INT8U err = OS_PRIO_EXIST;
    OS_EVENT event;

    MockIUcos ucosMock;         //Declare this as local variable as GMOCK checks for memory leaks
    myUcosMock = &ucosMock;     //Reference to mock must be set before use

    EXPECT_CALL(ucosMock, OSMutexCreate(TestPriority, _)).Times(AnyNumber()).WillOnce(DoAll(SetArgPointee<1>(err), Return(&event)));    //Add Times() as GMOCk get confused when assert is thrown

    EXPECT_EXIT(Mutex dut(TestPriority), ::testing::ExitedWithCode(3), "");
    myUcosMock = 0;             //Prevent others from using deleted instance (ucosMock)
}

