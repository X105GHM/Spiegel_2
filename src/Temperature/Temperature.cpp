#include "Temperature/Temperature.h"
#include <Arduino.h>
#include <cmath>

const int THERMISTORPIN = 0;          // G0
const float SERIESRESISTOR = 10000.0;
const float THERMISTORNOMINAL = 10000.0;
const float TEMPERATURENOMINAL = 6.0;
const float BCOEFFICIENT = 3950.0;

float getTemperature()
{
    float temperature;
    int adcValue = analogRead(THERMISTORPIN);
    float resistance = SERIESRESISTOR * ((4095.0 / adcValue) - 1);

    temperature = resistance / THERMISTORNOMINAL;
    temperature = log(temperature);
    temperature /= BCOEFFICIENT;
    temperature += 1.0 / (TEMPERATURENOMINAL + 273.15);
    temperature = 1.0 / temperature;
    temperature -= 273.15;

    return temperature;
}
