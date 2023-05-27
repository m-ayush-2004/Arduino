
/*
materials

ARDUINO uno,
HC-05,
LED (RGB)
jumper wires
Bread boarD


connections to leds
  ----------------------
 |   UNO         led   |
  ----------------------
 |   D6   -->     R    |
  ----------------------
 |   D5   -->     G    |
  ----------------------
 |   D3   -->     B    |
  ---------------------- 
 |   3.3v -->   led+   |
  ----------------------
  
  
  connections to HC-05
  ----------------------
 |   UNO        HC-05  |
  ----------------------
 |   10   -->    RX    |
  ----------------------
 |   11   -->    TX    |
  ----------------------
 |   GND  -->   GND    |
  ---------------------- 
 |   3.3v -->   VCC   |
  ----------------------
*/
#include <SoftwareSerial.h>
#define red 6
#define green 5
#define blue 3
SoftwareSerial mySerial(10, 11); // RX, TX
void setup() 
{
  Serial.begin(9600);  
  mySerial.begin(38400);   
  pinMode(red, OUTPUT); 
  pinMode(green, OUTPUT); 
  pinMode(blue, OUTPUT);      
  Serial.println("Board is connected!!");   
}

float arr[3]={0,0,0};
void loop()
{
// COLLECTOR SECTION OF THE CODE THAT COLLECTS THE VALUE OF HSV FROM THE BURT APP CLIENT INERACTIONS AND DISCARDING ALL STOP START AND INTRMEDIATE BIT VALUES
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
//CONVERTER CODE THAT CONVERTS THE VALUES HSV TO RGB
if(h>0 && s>0 && v>0){
    Serial.println("HSV (recived): ");
    Serial.print("h:");
    Serial.print(h);
    Serial.print(" , s:");
    Serial.print(s);
    Serial.print(" , v:");
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
    analogWrite(red,255-r);
    analogWrite(green,255-g);
    analogWrite(blue,255-b);
    Serial.println("RGB (converted): ");
    Serial.print("r:");
    Serial.println(r);
    Serial.print(" , g:");
    Serial.println(g);
    Serial.print(" , b:");
    Serial.println(b);
    arr[0]=0;
    arr[1]=0;
    arr[2]=0;
}
if (Serial.available())
mySerial.write(Serial.read());

delay(500);
}
