#include <Arduino.h>

void(* resetFunc) (void) = 0;

void PantallaInicial()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Hello, world!");
    lcd.setCursor(0,1);
    lcd.print("Hello, world!");
    lcd.setCursor(0,2);
    lcd.print("Hello, world!");
    lcd.setCursor(0,3);
    lcd.print("Hello, world!");
}

void PantallaSelecionarPrueba()
{
    
}

void PantallaEstadoPrueba()
{
    
}

int pantallaActual = 0;
int pruebaSeleccionada = 0;

int estadoPrueba = 0;

void ActualizarUI()
{
    if (pantallaActual == 0)
    {
        PantallaInicial();
    }
    else if(pantallaActual == 1)
    {
        PantallaSelecionarPrueba();
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

void BtnIzquierda()
{
    if (pantallaActual == 0)
    {
        //GO TO NEXT PANTALLA
        pantallaActual = 1;
    }
    else if(pantallaActual == 1)
    {
        //Iniciar el monitoreo en la Prueba seleccionadas
        pantallaActual = 2;
        estadoPrueba = 0;
    }
    else if(pantallaActual == 2)
    {
        //PAUSAR-CONTINUAR-INICIO
        if(estadoPrueba == 0)
        {

        }
        else if(estadoPrueba == 1)
        {

        }
        else if(estadoPrueba == 2)
        {
            pantallaActual = 0;
            estadoPrueba = 0;
        }
    }
}

void BtnDerecha()
{
    if (pantallaActual == 0)
    {
        //APAGAR
        lcd.clear();
        resetFunc();
    }
    else if(pantallaActual == 1)
    {
        //SIGUENTE PRUEBA
        pruebaSeleccionada++;
        if(pruebaSeleccionada >= TOTAL_PRUEBAS)
        {
            pruebaSeleccionada = 0;
        }
    }
    else if(pantallaActual == 2)
    {
        //DETENER-DETENER-APAGAR
        if(estadoPrueba == 0)
        {

        }
        else if(estadoPrueba == 1)
        {

        }
        else if(estadoPrueba == 2)
        {
            lcd.clear();
            resetFunc();
        }
    }
}