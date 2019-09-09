#include "touchusbnode.h"

static CGlobal touchStateLocal;

touchUSBNode::touchUSBNode()
{

}

touchUSBNode::~touchUSBNode()
{
    /* For cleanup, unschedule callback and stop the scheduler. */
    hdStopScheduler();
    hdUnschedule(hjointTorqueWell);
    hdUnschedule(heffectorForceWell);

    /* Disable the device. */
    hdDisableDevice(hHD);
    hHDInitOK = false;
}

/*****************************************************************************
 Callback that retrieves state.
*****************************************************************************/
HDCallbackCode HDCALLBACK DevicePositionCallback(void *pUserData)
{
    hdBeginFrame(hdGetCurrentDevice());
    hdGetDoublev(HD_CURRENT_POSITION, touchStateLocal.touchState.position);
    hdGetLongv(HD_CURRENT_ENCODER_VALUES, touchStateLocal.touchState.encoder_values);
    hdGetIntegerv(HD_CURRENT_BUTTONS, &touchStateLocal.touchState.touch_buttons);
    hdGetFloatv(HD_CURRENT_VELOCITY, touchStateLocal.touchState.velocity);
    hdEndFrame(hdGetCurrentDevice());
    hdGetDoublev(HD_CURRENT_FORCE, touchStateLocal.touchState.forceValues);
    hdGetDoublev(HD_CURRENT_JOINT_TORQUE, touchStateLocal.touchState.jointTorqueValues);
    hdGetDoublev(HD_CURRENT_GIMBAL_TORQUE, touchStateLocal.touchState.gimbalTorqueValues);
//    qDebug("\nhdcallbackcode: %.d, %.3f,%.3f,%.3f\n", touchStateLocal.touchState.touch_buttons, touchStateLocal.touchState.position[0], touchStateLocal.touchState.position[1], touchStateLocal.touchState.position[2]);
    touchStateLocal.testValue = 12;
    return HD_CALLBACK_DONE;
}

HDCallbackCode HDCALLBACK jointTorqueCallback(void *data)
{
    HHD hHD2 = hdGetCurrentDevice();
    /* Begin haptics frame.  ( In general, all state-related haptics calls
           should be made within a frame. ) */
    hdBeginFrame(hHD2);

    cout << touchStateLocal.setTouchState.jointTorqueValues[0] << endl;
    hdSetDoublev(HD_CURRENT_JOINT_TORQUE, touchStateLocal.setTouchState.jointTorqueValues);

    /* End haptics frame. */
    hdEndFrame(hHD2);

    cout << "jointTor" << endl;
//    return HD_CALLBACK_CONTINUE;
    return HD_CALLBACK_DONE;
}

HDCallbackCode HDCALLBACK effectorForceCallback(void *data)
{
    HHD hHD2 = hdGetCurrentDevice();
    /* Begin haptics frame.  ( In general, all state-related haptics calls
           should be made within a frame. ) */
    hdBeginFrame(hHD2);

    cout << touchStateLocal.setTouchState.forceValues[0] << endl;
    hdSetDoublev(HD_CURRENT_FORCE, touchStateLocal.setTouchState.forceValues);

    /* End haptics frame. */
    hdEndFrame(hHD2);

    cout << "effector" << endl;
//    return HD_CALLBACK_CONTINUE;
    return HD_CALLBACK_DONE;
}


bool touchUSBNode::initUSBTouch()
{
    if(hHDInitOK)
    {
        hdStopScheduler();
        hdUnschedule(hjointTorqueWell);
        hdUnschedule(heffectorForceWell);
        hdDisableDevice(hHD);
        hHDInitOK = false;
    }

    /* Initialize the device, must be done before attempting to call any hd
           functions. Passing in HD_DEFAULT_DEVICE causes the default device to be
           initialized. */
    hHD = hdInitDevice(HD_DEFAULT_DEVICE);
//    hHD = hdInitDevice("Default Device");
    cout << hHD << endl;
    if (HD_DEVICE_ERROR(error = hdGetError()))
    {
         hduPrintError(stderr, &error, "Failed to initialize haptic device");
         hHDInitOK = false;
         getch();
         return -1;
    }
    else
    {
        hHDInitOK = true;
        qDebug()<<"Found device model:%s.\n\n"<<hdGetString(HD_DEVICE_MODEL_TYPE);
    }

    hdStartScheduler();
    if (HD_DEVICE_ERROR(error = hdGetError()))
    {
        hduPrintError(stderr, &error, "Failed to start the scheduler");
        hHDInitOK = false;
        return -1;
    }
    else
    {
        hHDInitOK = true;
        qDebug()<<"Scheduler--OK";
        hdEnable(HD_FORCE_OUTPUT);
        return 0;
    }
}

void touchUSBNode::realTimeTouch()
{
    if(hHDInitOK)
    {
        hdScheduleSynchronous(DevicePositionCallback, &(touchStateLocal.testValue), HD_DEFAULT_SCHEDULER_PRIORITY);
    }
    else
    {
        qDebug() << "Something is wrong" << endl;
    }
}

void touchUSBNode::setTorque()
{
    hjointTorqueWell = hdScheduleAsynchronous(
            jointTorqueCallback, 0,
            HD_MAX_SCHEDULER_PRIORITY);
}

void touchUSBNode::setForce()
{
    heffectorForceWell = hdScheduleAsynchronous(
            effectorForceCallback, 0,
            HD_MAX_SCHEDULER_PRIORITY);
}

void touchUSBNode::disableForceFeedback(int mode)
{
    if (mode == 1){
        hdUnschedule(heffectorForceWell);
        cout << "Force mode is close!" << endl;
    }
    else if (mode == 2){
        hdUnschedule(hjointTorqueWell);
        cout << "Torque mode is close!" << endl;
    }
    else {
        cout << "Force and Torque feedback mode is close!" << endl;
    }
}
