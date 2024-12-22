#include "FanControl/FanControl.h"
#include <Arduino.h>

FanController::FanController(int fanPin) : fanPin(fanPin)
{
    pinMode(fanPin, OUTPUT);
    digitalWrite(fanPin, LOW);
}

void FanController::controlFan(float temperature)
{
    if (temperature >= 35.0)
    {
        digitalWrite(fanPin, HIGH);
    }
    else
    {
        digitalWrite(fanPin, LOW);
    }
}
