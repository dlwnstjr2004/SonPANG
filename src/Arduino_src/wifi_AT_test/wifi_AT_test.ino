#include <SoftwareSerial.h>

SoftwareSerial mySerial(8, 9); // TX, RX

void setup() {
  Serial.begin(9600);
  mySerial.begin(115200);
}

void loop() {
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }

  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}
