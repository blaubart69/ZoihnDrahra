#include <Arduino.h>
#include <LiquidCrystal.h>

const int   RS = 4
          , EN = 0 
          , d4 = 12
          , d5 = 13
          , d6 = 15
          , d7 = 3;

LiquidCrystal lcd(RS, EN, d4, d5, d6, d7);
int potValue = 0;
int potValueLast = 0;
unsigned long LCD_turned_on_millis = 0;

void setup(void) {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  lcd.begin(16, 2);
}

void loop(void) {

  if ( LCD_turned_on_millis > 0 ) {
    if ( (millis() - LCD_turned_on_millis) > 10 ) {
      digitalWrite(LED_BUILTIN, HIGH);
      LCD_turned_on_millis = 0;
    }
  }

  potValue = analogRead(PIN_A0);

  if (      potValue >= potValueLast-10 
        &&  potValue <= potValueLast+10) {
    return;
  }

  //Serial.printf("%d (%d)\n", potValue, potValue-potValueLast);
  lcd.setCursor(0,0);
  lcd.printf("%4d",potValue);

  potValueLast = potValue;

  digitalWrite(LED_BUILTIN, LOW);
  LCD_turned_on_millis = millis();

}