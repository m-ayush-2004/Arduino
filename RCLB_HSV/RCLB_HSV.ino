#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX
void setup() 
{
  Serial.begin(9600);  
  mySerial.begin(38400);   
  pinMode(6, OUTPUT); 
  pinMode(5, OUTPUT); 
  pinMode(3, OUTPUT);      
  Serial.println("Board is connected!!");   
}

float arr[3]={0,0,0};
void loop()
{
         
  for(int i=0;i<3;i++){
    if (mySerial.available()>0)
    {
      
      float temp=mySerial.read();
      Serial.println(temp);
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
    analogWrite(6,r);
    analogWrite(5,g);
    analogWrite(3,b);
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
if (Serial.available())
mySerial.write(Serial.read());

delay(500);
}
