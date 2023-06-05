#include <SoftwareSerial.h>
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int l=0;
SoftwareSerial mySerial(10, 11); // RX, TX
unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
void setup() 
{
  Serial.begin(9600);  
  mySerial.begin(38400);   
  pinMode(6, OUTPUT); 
  pinMode(5, OUTPUT); 
  pinMode(4, INPUT); 
  pinMode(A0, INPUT); 
  pinMode(3, OUTPUT);  
  Serial.println("Board is connected!!");   
  dht.begin();
  startMillis = millis();
}

float arr[3]={0,0,0};
void loop()
{
l = digitalRead(4);
for(int i=0;i<3;i++){
    if (mySerial.available()>0)
    {
      float temp=mySerial.read();
      if(temp>0){
        arr[i]=temp;
       }
    }
  }
  float h= arr[0]/100;
  float s=arr[1]/100;
  float v=arr[2]/100;
if(h>0 && s>0 && v>0){
    Serial.print("h:");
    Serial.println(h);
    Serial.print("s:");
    Serial.println(s);
    Serial.print("v:");
    Serial.println(v);
    double r, g, b;
    int i = int(h * 6);
    double f = h * 6 - i;
    double p = v * (1 - s);
    double q = v * (1 - f * s);
    double t = v * (1 - (1 - f) * s);

    switch(i % 6){
        case 0: r = v, g = t, b = p; break;
        case 1: r = q, g = v, b = p; break;
        case 2: r = p, g = v, b = t; break;
        case 3: r = p, g = q, b = v; break;
        case 4: r = t, g = p, b = v; break;
        case 5: r = v, g = p, b = q; break;
    }

    r = r * 255;
    g = g * 255;
    b = b * 255;
    analogWrite(6,255-r);
    analogWrite(5,255-g);
    analogWrite(3,255-b);
    Serial.print("r:");
    Serial.println(r);
    Serial.print("g:");
    Serial.println(g);
    Serial.print("b:");
    Serial.println(b);
    arr[0]=0;
    arr[1]=0;
    arr[2]=0;
}
currentMillis = millis();
if (currentMillis - startMillis >= 1000){
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float moist = analogRead(A0);
  moist = map(moist, 1024, 100, 0, 100);
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  String temp = String(t);
  String hum = String(h);
  String moistt = String(moist);
  char message1[30];
  (temp+","+hum+","+"on"+","+moistt).toCharArray(message1,30);
  char message2[30];
  (temp+","+hum+","+"off"+","+moistt).toCharArray(message2,30);
  if(l==1){
  mySerial.write(message1);
  Serial.println(message1);}
  else{
  mySerial.write(message2);
  Serial.println(message2);
  }
  startMillis = millis();
}
delay(500);
}
