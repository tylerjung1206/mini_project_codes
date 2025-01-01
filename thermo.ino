#include <LiquidCrystal.h>

const int thermistorPin = A0; 
const float BETA = 3950;    
const int seriesResistor = 10000; 
const int nominalResistance = 10000; 
const float nominalTemperature = 25.0 + 273.15;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  delay(1000);  
  lcd.begin(16, 2);
  lcd.print("Hello, World!");
}

void loop() {
  int analogValue = analogRead(thermistorPin);

  //beta eq conversions
  float resistance = seriesResistor / ((1023.0 / analogValue) - 1.0);
  float temperatureK = 1 / (1 / nominalTemperature + (1 / BETA) * log(resistance / nominalResistance));
  float temperatureC = temperatureK - 273.15;
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0; 

  //serial monitor display
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.print(" C / ");
  Serial.print(temperatureF);
  Serial.println(" F");

  //lcd display
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperatureC);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperatureF);
  lcd.print(" F");

  delay(2000);
}
