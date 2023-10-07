#include <Arduino.h>

struct PruebaTermica {
  String material;
  int temperaturaTarget;
  int tiempoMiliseconds;
};

#define TOTAL_PRUEBAS 3
PruebaTermica pruebasTermicas[TOTAL_PRUEBAS];

void CargarListaPruebas()
{
    pruebasTermicas[0].material = "Aluminio";
    pruebasTermicas[0].temperaturaTarget = 800;
    pruebasTermicas[0].material = 60000;

    pruebasTermicas[1].material = "Plastico";
    pruebasTermicas[1].temperaturaTarget = 300;
    pruebasTermicas[1].material = 30000;

    pruebasTermicas[2].material = "Hierro";
    pruebasTermicas[2].temperaturaTarget = 1200;
    pruebasTermicas[2].material = 120000;
}