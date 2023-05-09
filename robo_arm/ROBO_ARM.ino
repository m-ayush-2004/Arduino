#include <Servo.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ArduinoJson.h>
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti multifi;
const char *ssid1="your_ssid";
const char *pass1="your_password";
const char controls[] PROGMEM= R"rawliteral(
<!DOCTYPE html>{
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ROBO ARM</title>
    <style>
        .container{
            display: flex;
            justify-content: center;
            justify-self: center;
            height: 100vh;
            width: 100vw;
        }
        .inner-container{
            /* display: flex; */
            background: #000;
            border-radius: 200px;
            width: 285px;
            padding: 20px;
            height: fit-content;
            justify-items: center;
            justify-self: center;
            justify-content: center;
            align-self: center;
            align-items: center;
        }
        .pad1{
            padding-left: 80.16px;
            border-radius: 100px;
        }
        /* .btns{

            background: tomato;
        } */
        .pad2{
            padding-left: 90.18px;
        }
        .btn1{
            align-self: center;
            background-color: teal;
            color: aliceblue;
            font-family: sans-serif;
            font-size: medium;
            border: solid teal 4px;
            border-radius: 10px;
            padding: 10px;
            width: 100px;
        }
        a{
            text-decoration: none;
            color: aliceblue;
        }
    </style>
</head>
<body>
    <div class="container">
        <div class="inner-container">
            <span class="pad2"></span>
            <button type="button" value="up" class="btn1"><a href="/up">UP</a> </button>
            <br>
            <br>
            <button type="button" value="left" class="btn1"><a href="/left">LEFT</a> </button>
            <!-- <button></button> -->
            <span class="pad1"></span>
            <button type="button" value="right" class="btn1"><a href="right">RIGHT</a> </button>
            <br>
            <br>
            <span class="pad2"></span>
            <button type="button" value="down" class="btn1"><a href="/down">DOWN</a> </button>
        </div>
    </div>
</body>
</html>}
)rawliteral";


const char error_Window[] PROGMEM = R"rawliteral(
  <!DOCTYPE html>{
  <html lang='en'>
  <head>
    <meta charset='UTF-8'>
    <meta http-equiv='X-UA-Compatible' content='IE=edge'>
    <meta name='viewport' content='width=device-width, initial-scale=1.0'>
    <title>ERROR MESSAGE</title>
    <style>
        .container{
            height: 100vh;
            width: 100vw;
            display: flex;
            justify-content: center;
        }
        .inner_container{
            display:flex;
            width: 95vw;
            height: 15vw;
            border-radius:20px ;
            border: dashed rgba(232, 73, 73, 0.722);
            background-color: rgba(250, 56, 22, 0.296);
            justify-content: center;
            align-items: center;
        }
        .error{
            text-align: center;
            color: crimson;
        }
        a{
            text-align: center;
            color: crimson;
            padding-left: 10px;
            text-decoration: none;
        }
        a:hover{
            text-decoration: underline;
        }
                @media only screen and (min-height: 700px) {
            /* For tablets: */
            .col-s-1 {height: 8.33%;}
            .col-s-2 {height: 16.66%;}
            .col-s-3 {height: 25%;}
            .col-s-4 {height: 33.33%;}
            .col-s-5 {height: 41.66%;}
            .col-s-6 {height: 50%;}
            .col-s-7 {height: 58.33%;}
            .col-s-8 {width: 66.66%;}
            .col-s-9 {height: 75%;}
            .col-s-10 {height: 83.33%;}
            .col-s-11 {height: 91.66%;}
            .col-s-12 {height: 100%;}
        }
        @media only screen and (min-height: 900px) {
            /* For tablets: */
            .col-1 {height: 8.33%;}
            .col-2 {height: 16.66%;}
            .col-3 {height: 25%;}
            .col-4 {height: 33.33%;}
            .col-5 {height: 41.66%;}
            .col-6 {height: 50%;}
            .col-7 {height: 58.33%;}
            .col-8 {width: 66.66%;}
            .col-9 {height: 75%;}
            .col-10 {height: 83.33%;}
            .col-11 {height: 91.66%;}
            .col-12 {height: 100%;}
        }
    </style>
</head>
<body>
    <div class='container'>
        <div class='inner_container col-s-2 col-1'>
            <p class='error'>
                <strong>ERROR 404 : </strong>some error have occured , Please authorize yourself again to continue
                <br>
                <br>
                please click this link to login and try again!
                <a href='/'> click me </a>
            </p>
        </div>
    </div>
</body>
</html>}
)rawliteral";


Servo lower1;
Servo lower2;
Servo middle;
Servo up;
void handle_connect();
void handle_ota();
void handle_up();
void handle_down();
void handle_left();
void handle_right();
void set_server();
void notFound();
ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.println("Station MOde is now 'ACTIVE' !");
  handle_connect();
  handle_ota();
  lower1.attach(D4);
  lower2.attach(D5);
  middle.attach(D6);
  up.attach(D7);
  delay(20);
  lower1.write(20);
  lower2.write(20);
  middle.write(90);
  up.write(0);
  set_server();
}

void loop(){
  ArduinoOTA.handle();
  server.handleClient();
  }

void handle_connect(){
  multifi.addAP(ssid1,pass1);
  Serial.print("Connecting to strongest wifi...");
  while(multifi.run()!= WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.print("\n\nconnected to :");
  Serial.println(WiFi.SSID());
  Serial.print("\nIPadress :");
  Serial.println(WiFi.localIP());
}

void set_server(){
  server.on("/",handle_root);
  server.on("/up",handle_up);
  server.on("/left",handle_left);
  server.on("/right",handle_right);
  server.on("/down",handle_down);
  server.onNotFound(notFound);
  server.begin();
}

void notFound(){
//  Serial.println("WRONG COMMAND RECIVED!");
  server.send(303,"text/html",error_Window);
}

void handle_root(){
  server.send(200,"text/html",controls);
}

void handle_up(){
  up.write(50);
  lower1.write(80);
  lower2.write(80);
  Serial.println("MOVING UP !");
  server.sendHeader("Location","/");
  server.send(303);
}

void handle_down(){
  up.write(80);
  lower1.write(20);
  lower2.write(20);
  Serial.println("MOVING DOWN !");
  server.sendHeader("Location","/");
  server.send(303);
}

void handle_right(){
  middle.write(180);
  Serial.println("MOVING RIGHT !");
  server.sendHeader("Location","/");
  server.send(303);
}

void handle_left(){
  middle.write(0);
  Serial.println("MOVING LEFT !");
  server.sendHeader("Location","/");
  server.send(303);
}

void handle_ota(){
    ArduinoOTA.setHostname("ROBO_ARM");
   ArduinoOTA.setPassword("admin");
    ArduinoOTA.onStart([](){
      String type;
      delay(5000);
      if(ArduinoOTA.getCommand()==U_FLASH){
        type="sketch";
      }
      else{
        type = "filesystem";
      }
      Serial.println("Starting to update "+type);
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total){
      if ((progress / (total / 100))%10==0){
        Serial.printf("\nProgress %u%%\r", (progress / (total / 100)));
        }
      });
    ArduinoOTA.onError([](ota_error_t error){
      Serial.printf("Error[%u]:",error);
      if(error==OTA_AUTH_ERROR){
        Serial.println("AUTHENTICATION FAILED !");
      }
      else if(error==OTA_BEGIN_ERROR){
        Serial.println("BEGIN FAILED !");
      }
      else if(error==OTA_RECEIVE_ERROR){
        Serial.println("RECIVE FAILED !");
      }
      else if(error==OTA_END_ERROR){
        Serial.println("END FAILED !");
      }
      else if(error==OTA_CONNECT_ERROR){
        Serial.println("CONNECT FAILED !");
      }
      });
      ArduinoOTA.begin();
  }
