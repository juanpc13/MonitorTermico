#include <Arduino.h>

#include <TermoCupla.h>
#include <Tablero.h>
#include <Pantalla.h>
#include <Menus.h>

#define ONE_SECOND 1000
unsigned long lastTime;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  IniciarPantalla();
  char key = keypad.getKey();
  while(key == NO_KEY)
  {
    key = keypad.getKey();
    delay(50);
  }
  delay(450);
  lastTime = millis();
}

void OneSecond()
{
  unsigned long currentTime = millis();
  if(currentTime - lastTime >= ONE_SECOND)
  {
    UpdateLedStatus();
    UpdateTempWasReach();
    TiempoTotalOneSecond();
    TiempoTotalPruebaOneSecond();

    ActualizarUI('-');
    lastTime = currentTime;
  }
}

void loop()
{
  OneSecond();

  char key = keypad.getKey();

  if (key != NO_KEY){
    if(key == '*')
    {
      BtnIzquierda();
    }
    else if(key == '#')
    {
      BtnDerecha();
    }

    ActualizarUI(key);
    Serial.println(key);
    delay(500);
  }
}