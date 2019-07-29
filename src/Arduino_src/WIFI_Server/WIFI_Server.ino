#include <SoftwareSerial.h>

SoftwareSerial softSerial(2,3); // RX, TX

void setup()

{

uint32_t baud = 9600;

Serial.begin(baud);

softSerial.begin(baud);

Serial.println("AT+CIPMUX=1");
delay(30);
Serial.println("AT+CIPSERVER=1,8000");
delay(30);
Serial.println("AT+CIFSR");
delay(30);

}

void loop()

{

while(softSerial.available() > 0)

{

char a = softSerial.read();

if(a == '\0')

continue;

if(a != '\r' && a != '\n' && (a < 32))

continue;

Serial.print(a);

}

while(Serial.available() > 0)

{

char a = Serial.read();

Serial.write(a);

softSerial.write(a);

}

}
