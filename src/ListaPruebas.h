#include <Arduino.h>

struct PruebaTermica {
  String material;//7 Caracteres Max
  int temperaturaTarget;
  int tiempo;
};

#define TOTAL_PRUEBAS 3
PruebaTermica pruebasTermicas[TOTAL_PRUEBAS];

void CargarListaPruebas()
{
    pruebasTermicas[0].material = "1045";
    pruebasTermicas[0].temperaturaTarget = 800;
    pruebasTermicas[0].tiempo = 60;

    pruebasTermicas[1].material = "1046";
    pruebasTermicas[1].temperaturaTarget = 300;
    pruebasTermicas[1].tiempo = 30;

    pruebasTermicas[2].material = "1047";
    pruebasTermicas[2].temperaturaTarget = 1200;
    pruebasTermicas[2].tiempo = 120;
}