#include <Arduino.h>
#include "LightControl/LightControl.h"
#include "FanControl/FanControl.h"
#include "TemperatureControl/TemperatureControl.h"

FanController fanController(33);
TemperatureController temperatureController(fanController);
LightController lightController(25, fanController, 26);

void setup()
{
    Serial.begin(115200);

    pinMode(22, OUTPUT);
    digitalWrite(22,HIGH);

    Serial.println("Initializing controllers...");
    lightController.start();
    temperatureController.start();
    vTaskDelete(NULL);

    Serial.println("Setup complete.");
}