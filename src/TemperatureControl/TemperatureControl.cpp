#include "TemperatureControl/TemperatureControl.h"
#include "Temperature/Temperature.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <Arduino.h>

TemperatureController::TemperatureController(FanController &fanController)
    : fanController(fanController) {}

void TemperatureController::start()
{
    xTaskCreate(temperatureTask, "TemperatureTask", 4096, this, 1, nullptr);
}

void TemperatureController::temperatureTask(void *pvParameters)
{
    auto *controller = static_cast<TemperatureController *>(pvParameters);
    for (;;)
    {
        float temperature = getTemperature();
        controller->fanController.controlFan(temperature);
        Serial.print("Temperature: ");
        Serial.println(temperature);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
