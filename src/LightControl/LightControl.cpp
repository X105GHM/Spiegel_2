#include "LightControl/LightControl.h"
#include "Temperature/Temperature.h"
#include <Arduino.h>
#include <cmath>

LightController::LightController(int ledPin, FanController &fanController, int pirPin)
    : ledPin(ledPin), fanController(fanController), pirPin(pirPin), motionDetected(false)
{
    fadeTimer = xTimerCreate("FadeTimer", pdMS_TO_TICKS(20), pdTRUE, this, [](TimerHandle_t xTimer) {
        static_cast<LightController *>(pvTimerGetTimerID(xTimer))->fadeLED();
    });

    pirTimer = xTimerCreate("PIRTimer", pdMS_TO_TICKS(60000), pdFALSE, this, pirTimerCallback);
}

void LightController::start()
{
    pinMode(ledPin, OUTPUT);
    pinMode(pirPin, INPUT_PULLDOWN);

    digitalWrite(ledPin, LOW);

    ledcSetup(0, 30000, 10);
    ledcAttachPin(ledPin, 0); 

    xTaskCreate(fadeTask, "FadeTask", 2048, this, 2, nullptr);
    xTaskCreate(pirTask, "PIRTask", 2048, this, 2, nullptr);
}

void LightController::fadeLED()
{
    static int brightness = 0;
    static bool fadingUp = false;
    static bool fadingDown = false;

    if (motionDetected && !fadingUp && brightness == 0)
    {   
        ledcWrite(0, 0);
        fadingUp = true;
    }

    if (!motionDetected && !fadingDown && brightness > 0)
    {
        fadingDown = true;
    }

    if (fadingUp)
    {
        brightness += 5;
        if (brightness >= 1023)
        {
            brightness = 1023;
            fadingUp = false;
        }
        ledcWrite(0, brightness);
    }
    else if (fadingDown)
    {
        brightness -= 5;
        if (brightness <= 0)
        {
            brightness = 0;
            fadingDown = false;
        }
        ledcWrite(0, brightness);
    }
}

void LightController::handlePIR()
{
    bool currentState = digitalRead(pirPin);

    if (currentState)
    {
        motionDetected = true;
        xTimerStart(pirTimer, 0);
        Serial.println("PIR HIGH");
    }
}

void LightController::fadeTask(void *pvParameters)
{
    auto *controller = static_cast<LightController *>(pvParameters);
    for (;;)
    {
        controller->fadeLED();
        vTaskDelay(pdMS_TO_TICKS(25));
    }
}

void LightController::pirTask(void *pvParameters)
{
    auto *controller = static_cast<LightController *>(pvParameters);
    for (;;)
    {
        controller->handlePIR();
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void LightController::pirTimerCallback(TimerHandle_t xTimer)
{
    auto *controller = static_cast<LightController *>(pvTimerGetTimerID(xTimer));
    controller->motionDetected = false;
}