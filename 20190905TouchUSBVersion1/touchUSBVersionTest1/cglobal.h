#ifndef CGLOBAL_H
#define CGLOBAL_H

#include <HD/hd.h>
//#include <HDU/hduError.h>
#include <HDU/hduVector.h>
//#include "hdDevice.h"
#include "eigen3/Eigen/Eigen"
#include "eigen3/Eigen/Dense"

#define MAX_INPUT_DOF   6
#define MAX_OUTPUT_DOF  6

using namespace Eigen;

typedef struct{
    Vector3d position;
    Vector3d velocity;
    Vector3d button;
    Vector3d forceValues;
    Vector3d jointTorqueValues;
    Vector3d gimbalTorqueValues;
    Vector3d maxPositionLimit;
    Vector3d minPositionLimit;
    Vector3d virtualposition;
} MasterStateStruct;

typedef struct
{
    HDlong encoder_values[MAX_INPUT_DOF];
    int touch_buttons;
    hduVector3Dd position;
    HDfloat velocity[3];
    HDdouble forceValues[3];
    HDdouble jointTorqueValues[3];
    HDdouble gimbalTorqueValues[3];
} DeviceStateStruct;

typedef struct
{
    HDdouble forceValues[3];
    HDdouble jointTorqueValues[3];
    HDdouble gimbalTorqueValues[3];
} SetDeviceStateStruct;


class CGlobal
{
public:
    CGlobal();
    ~CGlobal();

public:
    static DeviceStateStruct touchState;
    static SetDeviceStateStruct setTouchState;
    static int testValue;

};

#endif // CGLOBAL_H
