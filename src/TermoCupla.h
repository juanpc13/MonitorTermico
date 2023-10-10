#include <Arduino.h>

#include <max6675.h>

int thermoDO = 10;
int thermoCS = 11;
int thermoCLK = 12;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

float ReadCelsius()
{
    return thermocouple.readCelsius();
}