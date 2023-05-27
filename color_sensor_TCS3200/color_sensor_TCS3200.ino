/*
materials

ARDUINO uno,
TCS-3200,
jumper wires
Bread boarD



connections to TCS-3200:

  ----------------------
 |   UNO      TCS-3200 |
  ----------------------
 |   S0   -->     R    |
  ----------------------
 |   S1   -->     G    |
  ----------------------
 |   S2   -->     B    |
  ----------------------
 |   S3   -->    RX    |
  ----------------------
 |  OUT   -->    TX    |
  ----------------------
 |  GND   -->   GND    |
  ---------------------- 
 | +5.0V  -->    VCC   |
  ----------------------
*/
#define s0 2
#define s1 3
#define s2 4
#define s3 5
#define output 9
int R =0;
int G =0;
int B =0;
void setup() {
  pinMode(s0,OUTPUT);
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);
  digitalWrite(s0,HIGH);
  digitalWrite(s1,HIGH);
  pinMode(output,INPUT);
  Serial.begin(9600);
}

void loop() {
  R= red_data();
  delay(500);
  G= green_data();
  delay(500);
  B= blue_data();
  delay(500);
//   printing the values to the serial in R,G,B order 
//   this order is used in python serial at COM'N'
//   we use these values to generate the output matplotlib graphs
  Serial.print(R);
  Serial.print(",");
  Serial.print(G);
  Serial.print(",");
  Serial.println(B);
}

int red_data(){
  digitalWrite(s2,LOW);
  digitalWrite(s3,LOW);
  //red input pulse read
  int data=pulseIn(output,LOW);
  return data;
}

int green_data(){
  digitalWrite(s2,HIGH);
  digitalWrite(s3,HIGH);
  //green input pulse read
  int data=pulseIn(output,LOW);
  return data;
}

int blue_data(){
  digitalWrite(s2,LOW);
  digitalWrite(s3,HIGH);
  //blue input pulse read
  int data=pulseIn(output,LOW);
  return data;
}
