#include <Arduino.h>

#include <ListaPruebas.h>
#include <Tablero.h>
#include <Menus.h>
#include <Pantalla.h>

#define ONE_SECOND 1000
unsigned long lastTime;

void setup()
{
  CargarListaPruebas();
  IniciarPantalla();
  lastTime = millis();
}

void OneSecond()
{
  unsigned long currentTime = millis();
  if(currentTime - lastTime >= ONE_SECOND)
  {
    ActualizarUI();
    lastTime = currentTime;
  }
}

void loop()
{
  OneSecond();

  char key = keypad.getKey();

  if (key != NO_KEY){
    if(key == '#')
    {

    }
    else if(key == '*')
    {

    }
    ActualizarUI();
    Serial.println(key);
  }
}