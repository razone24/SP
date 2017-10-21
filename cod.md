# SP

#include <LiquidCrystal.h>         
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //Digital pins to which you connect the LCD
const int inPin = 0;                   // A0 is where you connect the sensor
void setup()
{
  lcd.begin(16,2);
}
void loop()
{
  float sumaTemperatura;
  lcd.setCursor(0,1);
for (int i =0; i<10; i++) {
         int reading = analogRead(0);
         float voltage = reading * 5.0;
         voltage /= 1024.0;
         float temperatureCelsius = (voltage - 0.5) * 10 ;
         sumaTemperatura = sumaTemperatura + temperatureCelsius;
}
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print(sumaTemperatura);
  lcd.print("C");
  lcd.setCursor(0,0);
  lcd.print("Termometru");
  delay(1000);
}
