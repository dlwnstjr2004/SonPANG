#include <ESP8266WiFi.h>

// Make sure to add your own information
const char* SSID = "********";
const char* PASS = "********";

void setup(void)
{
  Serial.begin(74880);
  WiFi.begin(SSID, PASS);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected!");
  Serial.println(SSID);
}

void loop(void)
{
  Serial.println("");
  Serial.print("Wemos IP : ");
  Serial.println(WiFi.localIP());
  Serial.print("Wemos MAC Address : ");
  Serial.println(WiFi.macAddress());
  Serial.print("WIFI Mode : ");  
  Serial.println(WiFi.getMode());

  delay(5000);
}
[출처] WEMOS LOLIN 초급 강좌 #004  : WIFI AP 접속해보기 (아두이노+ESP8266)|작성자 MAKECODE
