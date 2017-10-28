#include <LiquidCrystal.h>
#include "Wire.h"
     #define DS1307_ADDRESS 0x68
     byte zero = 0x00; //rezolva eroarea #527       
 LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //Pinii la care este conectat LCD-ul
 const int inPin = 0;                   // A0 este pinul unde este conectat senzorul de temperatura
 void setup()
 {
  lcd.begin(16,2);
  Wire.begin();
       Serial.begin(9600);
       setDateTime(); //Apelarea functiei care citeste si afiseaza ceasul
 }
 void loop()
 {
   float sumaTemperatura;
   lcd.setCursor(0,1);
 for (int i =0; i<10; i++) {
          int reading = analogRead(0);//Citeste de la senzorul de temperatura temperatura in volti
          float voltage = reading * 5.0;
          voltage /= 1024.0;                  //Transforma temperatura din volti in grade celsius
          float temperatureCelsius = (voltage - 0.5) * 10 ;
          sumaTemperatura = sumaTemperatura + temperatureCelsius;
 }
   lcd.clear();
   lcd.setCursor(0,0);
   printDate();
   lcd.setCursor(10,1);
   lcd.print(sumaTemperatura); //Afiseaza pe LCD temperatura in grade celsius
   lcd.print("C");
   delay(1000);
 }
 void setDateTime(){
  byte second =00; //0-59
  byte minute =50; //0-59
  byte hour =16; //0-23
  byte weekDay =3; //1-7             //Potrivirea ceasului
  byte monthDay =25; //1-31
  byte month =10; //1-12
  byte year  =17; //0-99
Wire.beginTransmission(DS1307_ADDRESS);
Wire.write(zero); //Opreste oscilatorul
Wire.write(decToBcd(second));
Wire.write(decToBcd(minute));
Wire.write(decToBcd(hour));
Wire.write(decToBcd(weekDay));
Wire.write(decToBcd(monthDay));
Wire.write(decToBcd(month));
Wire.write(decToBcd(year));
  Wire.write(zero); //Porneste functionarea ceasului in functie de ora potrivita
  Wire.endTransmission();
}
byte decToBcd(byte val){
//Transforma numerele zecimale in numere in numere binare
  return ( (val/10*16) + (val%10) );
}
byte bcdToDec(byte val)  {
// Transforma numerele binare in numere zecimale
  return ( (val/16*10) + (val%16) );
}
void printDate(){
  // Reseteaza registrul pointerului
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDRESS, 7);
  int second = bcdToDec(Wire.read());
  int minute = bcdToDec(Wire.read());
  int hour = bcdToDec(Wire.read() & 0b111111); //timpul in formatul de 24 de ore
  int weekDay = bcdToDec(Wire.read()); //zilele saptamanii Luni-Duminica
  int monthDay = bcdToDec(Wire.read());
  int month = bcdToDec(Wire.read());
  int year = bcdToDec(Wire.read());
  lcd.print(monthDay); //Afiseaza zilele saptamanii Luni-Duminica
  lcd.print("-");
  switch (month) { //Lunile anului Ian-Dec
    case 1:
    lcd.print("ian");
    break;
    case 2:
    lcd.print("feb");
    break;
    case 3:
    lcd.print("mar");
    break;
    case 4:
    lcd.print("apr");
    break;
    case 5:
    lcd.print("mai");
    break;
    case 6:
    lcd.print("iun");
    break;
    case 7:
    lcd.print("iul");
    break;
    case 8:
    lcd.print("aug");
    break;
    case 9:
    lcd.print("sep");
    break;
    case 10:
    lcd.print("oct");
    break;
    case 11:
    lcd.print("noi");
    break;
    case 12:
    lcd.print("dec");
    break;
  }
  lcd.print("-");
  lcd.print(year); //Afisarea anului
  lcd.print(" ");
  lcd.setCursor(0,1);
  lcd.print(hour);  //Afisarea orei
  lcd.print(":");
  lcd.print(minute);//Afisarea minutelor
  lcd.print(":");
  lcd.print(second); //Afisarea secundelor
  lcd.setCursor(0,0);
  lcd.setCursor(10,0);
  switch (weekDay) { //Zilele saptamanii Luni-Duminica
    case 1:
    lcd.print("Lun");
    break;
    case 2:
    lcd.print("Mar");
    break;
    case 3:
    lcd.print("Mie");
    break;
    case 4:
    lcd.print("Joi");
    break;
    case 5:
    lcd.print("Vin");
    break;
    case 6:
    lcd.print("Sam");
    break;
    case 7:
    lcd.print("Dum");
    break;
  }
}
