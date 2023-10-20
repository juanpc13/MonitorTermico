#include <Arduino.h>

int pantallaActual = 0;
int estadoPrueba = 0;

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

String TimeToWatch(int segundos)
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

String materialPrueba = "       ";//7caracteres
String temperaturaPrueba = "0000";//4caracteres
String tiempoPrueba = "00:00:00";

int labelSeleccionado = 0;
void PantallaSelecionarPrueba()
{
    String salida = "";
    
    lcd.clear();
    lcd.setCursor(0,0);
    salida = "Material:";
    salida += materialPrueba;
    lcd.print(salida);
    lcd.setCursor(0,1);
    salida = "Temp:";
    salida += temperaturaPrueba;
    salida += "C";
    lcd.print(salida);
    lcd.setCursor(0,2);
    salida = "Tiempo:";
    salida += tiempoPrueba;
    lcd.print(salida);
    lcd.setCursor(0,3);
    lcd.print("Iniciar-Siguient");
}

void UpdatePrueba(char caracter)
{
    if (!isdigit(caracter)) return;

    if(labelSeleccionado == 0)
    {
        materialPrueba += caracter;
        materialPrueba = materialPrueba.substring(1, 7);
    }
    else if(labelSeleccionado == 1)
    {
        temperaturaPrueba += caracter;
        temperaturaPrueba = temperaturaPrueba.substring(1, 5);
    }
    else if(labelSeleccionado == 2)
    {
        String currentTxt = tiempoPrueba;
        currentTxt += tiempoPrueba.substring(0, 1);
        currentTxt += tiempoPrueba.substring(3, 4);
        currentTxt += tiempoPrueba.substring(6, 7);
        currentTxt += caracter;
        tiempoPrueba = currentTxt.substring(1, 2);
        tiempoPrueba += ':';
        tiempoPrueba += currentTxt.substring(4, 5);
        tiempoPrueba += ':';
        tiempoPrueba += currentTxt.substring(7, 8);
    }
}

int tiempoTotal = 0;
void TiempoTotalOneSecond()
{
    tiempoTotal++;
}

int tiempoTotalPrueba = 0;
bool pause = false;
bool tempWasReach = false;
void TiempoTotalPruebaOneSecond()
{
    if(!pause && tempWasReach)
    {
        tiempoTotalPrueba++;
    }
}
void UpdateTempWasReach()
{
    if(!tempWasReach)
    {
        //VER TEMP ACTUAL Y TEMP TARGER
        float tempActual = ReadCelsius();
        float tempTarget = atof(temperaturaPrueba.c_str());
        if(tempActual >= tempTarget)
        {
            tempWasReach = true;
        }
    }
}

void PantallaEstadoPrueba()
{
    String salida = "";
    lcd.clear();
    lcd.setCursor(0,0);
    salida = "TermoCupla:";
    salida += ReadCelsius();
    salida += "C";
    lcd.print(salida);
    lcd.setCursor(0,1);
    salida = "Total - ";
    salida += TimeToWatch(tiempoTotal);
    lcd.print(salida);
    lcd.setCursor(0,2);
    salida = "Probeta-";
    salida += TimeToWatch(tiempoTotalPrueba);
    lcd.print(salida);
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

void ActualizarUI(char caracter)
{
    if (pantallaActual == 0)
    {
        PantallaInicial();
    }
    else if(pantallaActual == 1)
    {
        UpdatePrueba(caracter);
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
        tiempoTotal = 0;
        tiempoTotalPrueba = 0;
        pause = false;
        tempWasReach = false;
    }
    else if(pantallaActual == 2)
    {
        //PAUSAR-CONTINUAR-INICIO
        if(estadoPrueba == 0)
        {
            pause = true;
        }
        else if(estadoPrueba == 1)
        {
            pause = false;
        }
        else if(estadoPrueba == 2)
        {
            pantallaActual = 0;
            estadoPrueba = 0;
        }
    }
}

#define TOTAL_OPCIONES 3

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
        labelSeleccionado++;
        if(labelSeleccionado >= TOTAL_OPCIONES)
        {
            labelSeleccionado = 0;
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