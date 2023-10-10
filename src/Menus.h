#include <Arduino.h>

void(* resetFunc) (void) = 0;

void PantallaInicial()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("UES * FIA * EIM ");
    lcd.setCursor(0,1);
    lcd.print("  Velocidad de  ");
    lcd.setCursor(0,2);
    lcd.print(" Calentamiento  ");
    lcd.setCursor(0,3);
    lcd.print("Inicio - Apagar ");
}

bool NeedZeroDigit(int val)
{
    return val < 10;
}

String timeToWatch(int segundos)
{
    int horas = segundos / 3600;          // 1 hora = 3600 segundos
    int minutos = (segundos % 3600) / 60; // 1 minuto = 60 segundos
    int segundosRestantes = segundos % 60;

    String horaTxt = "";
    if(NeedZeroDigit(horas)){horaTxt += "0";}
    horaTxt += horas;
    horaTxt += ":";
    if(NeedZeroDigit(minutos)){horaTxt += "0";}
    horaTxt += minutos;
    if(NeedZeroDigit(segundosRestantes)){horaTxt += "0";}
    horaTxt += ":";
    horaTxt += segundosRestantes;
    return horaTxt;
}

void PantallaSelecionarPrueba()
{
    PruebaTermica prueba = pruebasTermicas[TOTAL_PRUEBAS];
    lcd.clear();
    lcd.setCursor(0,0);
    String salida = "";
    salida = "Material:";
    salida += prueba.material;
    lcd.print(salida);
    lcd.setCursor(0,1);
    salida = "Temp:";
    salida += prueba.temperaturaTarget;
    salida += "C";
    lcd.print(salida);
    lcd.setCursor(0,2);
    salida = "Tiempo:";
    salida += timeToWatch(prueba.tiempo);
    lcd.print(salida);
    lcd.setCursor(0,3);
    lcd.print("Iniciar-Cambiar ");
}

void PantallaEstadoPrueba()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("TermoCupla:9999C");
    lcd.setCursor(0,1);
    lcd.print("Total - 99:59:59");
    lcd.setCursor(0,2);
    lcd.print("Probeta-99:59:59");
    lcd.setCursor(0,3);
    //PAUSAR-CONTINUAR-INICIO
    if(estadoPrueba == 0)
    {
        lcd.print("Pausa - Detener ");
    }
    else if(estadoPrueba == 1)
    {
        lcd.print("Continua-Detener");
    }
    else if(estadoPrueba == 2)
    {
        lcd.print("Inicio - Apagar ");
    }
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