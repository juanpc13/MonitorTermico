#include <Arduino.h>

#include <TermoCupla.h>
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
  char key = keypad.getKey();
  while(key == NO_KEY)
  {
    key = keypad.getKey();
    delay(500);
  }
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
      BtnIzquierda();
    }
    else if(key == '*')
    {
      BtnDerecha();
    }
    ActualizarUI();
    Serial.println(key);
    delay(500);
  }
}