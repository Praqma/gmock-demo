#ifndef ICONFIGURATIONDATA_H
#define ICONFIGURATIONDATA_H

//! \brief This class holds all user configurable data
//! The content of the instance is persisted in FLASH
class IConfigurationData
{
public:
    //! \brief  Get the distance one turn of the wheel will move the bike foreward
    //!
    //! \return int Rotation distance in mm
    virtual int GetDistancePrRotationInMm() = 0;

    ~IConfigurationData() {};
};

#endif  //#ifndef ICONFIGURATIONDATA_H