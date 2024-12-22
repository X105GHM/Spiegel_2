#ifndef LIGHTCONTROL_H
#define LIGHTCONTROL_H

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>
#include "FanControl/FanControl.h"

class LightController
{
public:
    LightController(int ledPin, FanController &fanController, int pirPin);
    void start();

private:
    int ledPin;
    FanController &fanController;
    int pirPin;
    TimerHandle_t fadeTimer;
    TimerHandle_t pirTimer;
    bool motionDetected;

    void fadeLED();
    void handlePIR();

    static void fadeTask(void *pvParameters);
    static void pirTask(void *pvParameters);
    static void pirTimerCallback(TimerHandle_t xTimer);
};

#endif