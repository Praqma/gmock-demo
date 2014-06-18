:: Praqma test script
:: This command file generates mocks for the tests used in the demonstration project

@set GMOCKDIR=..\..\
@set PROJDIR=..\..\..\
@set MOCKDIR=%PROJDIR%mocks\

@if not exist %MOCKDIR% mkdir %MOCKDIR%

:: Loop through all relevant interface files and generate a mock
:: Add additional tests here
@for %%I in (
  %PROJDIR%src\IWheelSensor.h
  %PROJDIR%src\IConfigurationData.h
  %PROJDIR%src\ITripData.h
  %PROJDIR%src\IMutex.h
  %PROJDIR%src\IUcos.h
) do @%GMOCKDIR%scripts\generator\gmock_gen.py %%I > %MOCKDIR%%%~nI.mock
