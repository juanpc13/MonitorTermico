#include <Arduino.h>

#include <max6675.h>

int thermoDO = 4;
int thermoCS = 5;
int thermoCLK = 6;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

float ReadCelsius()
{
    return thermocouple.readCelsius();
}