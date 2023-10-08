#include <Arduino.h>

void PantallaInicial()
{
    
}

void PantallaSelecionarPrueba(int selecion)
{
    
}

void PantallaEstadoPrueba()
{
    
}

int pantallaActual = 0;
int pruebaSeleccionada = 0;

void ActualizarUI()
{
    if (pantallaActual == 0)
    {
        PantallaInicial();
    }
    else if(pantallaActual == 1)
    {
        PantallaSelecionarPrueba(pruebaSeleccionada);
    }
    else if(pantallaActual == 2)
    {
        PantallaEstadoPrueba();
    }
    else
    {
        PantallaInicial();
    }
}