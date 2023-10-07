#include <Arduino.h>

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 4);

void IniciarPantalla()
{
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
}