#include <StepperMulti.h>
#include <SoftwareSerial.h>
#include <Stepper.h>
#include "ESP8266.h"

#define ssid      "VLSI_2_4"
#define password  "vlsilab110224"
#define port      8001

SoftwareSerial esp8266Serial = SoftwareSerial(10, 11);
ESP8266 wifi = ESP8266(esp8266Serial);

const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 6, 8, 7, 9); //6879
Stepper myStepper2(stepsPerRevolution, 2, 4, 3, 5);

void setup()
{
    Serial.begin(9600);
    myStepper.setSpeed(100);
    myStepper2.setSpeed(100);

    
    // ESP8266
    esp8266Serial.begin(9600);
    wifi.begin();
    wifi.setTimeout(10000);

    // getVersion
    char version[64] = {};
    Serial.print("getVersion: ");
    Serial.print(getStatus(wifi.getVersion(version, 64)));
    Serial.print(" : ");
    Serial.println(version);

    // setWifiMode
    Serial.print("setWifiMode: ");
    Serial.println(getStatus(wifi.setMode(ESP8266_WIFI_BOTH)));

    // joinAP
    Serial.print("joinAP: ");
    Serial.println(getStatus(wifi.joinAP(ssid, password)));

    // getAP
    char ap[32] = {};
    Serial.print("getAP: ");
    Serial.print(getStatus(wifi.getAP(ap)));
    Serial.print(" : ");
    Serial.println(ap);




    // setMultipleConnections
    Serial.print("setMultipleConnections: ");
    Serial.println(getStatus(wifi.setMultipleConnections(true)));

    Serial.print("deleteServer: ");
    Serial.println(getStatus(wifi.deleteServer()));
    // createServer
    Serial.print("createServer: ");
    Serial.println(getStatus(wifi.createServer(port)));
}

void loop()
{
    // read data
    unsigned int id;
    int length;
    int totalRead;
    char buffer[11] = {};

    if ((length = wifi.available()) > 0) 
    {
      id = wifi.getId();
      totalRead = wifi.read(buffer, 128);

      if (length > 0) {
        Serial.print("Received ");
        Serial.print(totalRead);
        Serial.print("/");
        Serial.print(length);
        Serial.print(" bytes from client ");
        Serial.print(id);
        Serial.print(": ");
        Serial.println((char*)buffer);
      }

      if(!strcmp(buffer, "1\n"))
      {
        Serial.print("먹자구구구\n");
        int i = 0;

        
        multiturn(myStepper, myStepper2, 200);
        
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        
      }
      else
      {
        Serial.print("그만먹어\n");
        int i = 0;
        
        multiturn(myStepper, myStepper2, -200);
        
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        
      }
    }
}

void multiturn(Stepper moter1, Stepper moter2, int Step)
{
  int i = 0;
  if(Step > 0)
  {
    for(i = 0;i < Step; i++)
    {
      moter1.step(-1);
      moter2.step(1);
    }
  }
  else
  {
    for(i = Step;i < 0; i++)
    {
      moter1.step(1);
      moter2.step(-1);
    }
  }
  
}

String getStatus(bool status)
{
    if (status)
        return "OK";

    return "KO";
}

String getStatus(ESP8266CommandStatus status)
{
    switch (status) {
    case ESP8266_COMMAND_INVALID:
        return "INVALID";
        break;

    case ESP8266_COMMAND_TIMEOUT:
        return "TIMEOUT";
        break;

    case ESP8266_COMMAND_OK:
        return "OK";
        break;

    case ESP8266_COMMAND_NO_CHANGE:
        return "NO CHANGE";
        break;

    case ESP8266_COMMAND_ERROR:
        return "ERROR";
        break;

    case ESP8266_COMMAND_NO_LINK:
        return "NO LINK";
        break;

    case ESP8266_COMMAND_TOO_LONG:
        return "TOO LONG";
        break;

    case ESP8266_COMMAND_FAIL:
        return "FAIL";
        break;

    default:
        return "UNKNOWN COMMAND STATUS";
        break;
    }
}

String getRole(ESP8266Role role)
{
    switch (role) {
    case ESP8266_ROLE_CLIENT:
        return "CLIENT";
        break;

    case ESP8266_ROLE_SERVER:
        return "SERVER";
        break;

    default:
        return "UNKNOWN ROLE";
        break;
    }
}

String getProtocol(ESP8266Protocol protocol)
{
    switch (protocol) {
    case ESP8266_PROTOCOL_TCP:
        return "TCP";
        break;

    case ESP8266_PROTOCOL_UDP:
        return "UDP";
        break;

    default:
        return "UNKNOWN PROTOCOL";
        break;
    }
}
