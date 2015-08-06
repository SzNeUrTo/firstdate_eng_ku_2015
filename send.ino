#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();
int car_number = 2;
int car_number_prefix = car_number << 8;
int sendValue = 0;

void setup() {
  Serial.begin(9600);
  mySwitch.enableTransmit(10);
  pinMode(A0,INPUT);
}

void loop() { 
  sendValue = car_number_prefix + analogRead(A0) / 4;
  mySwitch.send(sendValue % 1024, 10);
  Serial.println(sendValue % 256);
  delay(5);   
}