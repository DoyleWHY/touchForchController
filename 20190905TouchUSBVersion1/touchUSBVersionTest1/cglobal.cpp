#include "cglobal.h"

CGlobal::CGlobal()
{
}
CGlobal::~CGlobal()
{
}
int CGlobal::testValue = 11;
DeviceStateStruct CGlobal::touchState = {
    {0 , 0, 0, 0, 0, 0},
    0,
    {0.0,0.0,0.0},
    {0.0,0.0,0.0},
    {0.0,0.0,0.0},
    {0.0,0.0,0.0},
    {0.0,0.0,0.0}
};
SetDeviceStateStruct CGlobal::setTouchState = {
    {0.0,0.0,0.0},
    {0.0,0.0,0.0},
    {0.0,0.0,0.0}
};

