  /*
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper or ground to LCD VO pin (pin 3)
 * trig 10
 * echo 8
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
*/




#include <LiquidCrystal.h>
const int trig = 10; // Trigger Pin of Ultrasonic Sensor
const int echo = 9; // Echo Pin of Ultrasonic Sensor

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  Serial.begin(9600); // Starting Serial Terminal
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  analogWrite(A1,0);
  lcd.begin(16, 2);
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Let's begin!!");
  lcd.setCursor(0, 1);
  lcd.print("distance:");
  long duration, inches, cm;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  Serial.print("inches: ");
  Serial.println(inches);
  Serial.print("in, ");
  Serial.print("centimeters: ");
  lcd.setCursor(10, 1);
  Serial.println(cm);
  lcd.print(cm);
  lcd.setCursor(14, 1);
  lcd.print("cm");
  int s = map(cm,5,100,100,255);
  

  analogWrite(A0,s);
//  analogWrite(A0,0);
  lcd.clear();
  Serial.print("cm");
  Serial.println();
  Serial.flush();
  return;
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
