#ifndef TEMPERATURECONTROL_H
#define TEMPERATURECONTROL_H

#include "FanControl/FanControl.h"


class TemperatureController
{
public:
    TemperatureController(FanController &fanController);
    void start();

private:
    FanController &fanController;

    static void temperatureTask(void *pvParameters);
};

#endif