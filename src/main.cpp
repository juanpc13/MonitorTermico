#include <Arduino.h>

#include <ListaPruebas.h>
#include <Tablero.h>
#include <Menus.h>
#include <Pantalla.h>

void setup()
{
  CargarListaPruebas();
  IniciarPantalla();
}

void loop()
{
  char key = keypad.getKey();

  if (key != NO_KEY){
    //ActualizarUI();
    Serial.println(key);
  }
}