#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX

/*
*  
send command 
  AT
  AT+NAME
  AT+PSWD
  AT+NAME="NEW_NAME"
  AT+PSWD="NEW_PASS"
 *
 */
void setup() {

Serial.begin(9600);
// turning on the serial port at 9600 baud rate
pinMode(9,OUTPUT); 
digitalWrite(9,HIGH);

Serial.println("Enter AT commands:");
mySerial.begin(38400);
// turning on board communication at 34800 baud rate
}

void loop()

{
if (mySerial.available())
Serial.write(mySerial.read());

if (Serial.available())
mySerial.write(Serial.read());

}
