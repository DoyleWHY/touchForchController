#ifndef TOUCHUSBNODE_H
#define TOUCHUSBNODE_H

#include <conio.h>
#include <HD/hd.h>
#include <HDU/hduError.h>
#include <HDU/hduVector.h>
#include "hdDevice.h"
#include <iostream>
#include <QDebug>
#include "eigen3/Eigen/Eigen"
#include "eigen3/Eigen/Dense"
#include "cglobal.h"

using namespace std;

class touchUSBNode
{
public:
    touchUSBNode();
    ~touchUSBNode();
    bool initUSBTouch();
    void realTimeTouch();

    void disableForceFeedback(int mode);

    void setForce();
    void setTorque();

private:
    HDErrorInfo error;
    HHD hHD;
    HDSchedulerHandle hjointTorqueWell = HD_INVALID_HANDLE;
    HDSchedulerHandle heffectorForceWell = HD_INVALID_HANDLE;

    bool hHDInitOK = false;
};

#endif // TOUCHUSBNODE_H
