#include <RCSwitch.h>
    
#define PIN_MOTOR 10
#define TH 50
#define NO_VOICE 0

int car_number = 2;
int recieve, value;
RCSwitch rcSwitch = RCSwitch();

void setup() { 
  // Receiver on inerrupt 0 => that is pin #2
  rcSwitch.enableReceive(0);
  pinMode(PIN_MOTOR, OUTPUT);
  for (int i = 0; i < 8; i++) {
    if (i == 0) pinMode(A0, OUTPUT);
    if (i == 1) pinMode(A1, OUTPUT);
    if (i == 2) pinMode(A2, OUTPUT);
    if (i < 3) continue;
    pinMode(i, OUTPUT);
  }
  clearLogic();
  Serial.begin(9600);
}

void clearLogic() {
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  for (int i = 3; i < 8; i++) {
    digitalWrite(i, 0);
  }
  digitalWrite(PIN_MOTOR, LOW);
}

void setLED(int val) {
  int nBit = 0;
  while (val > 0) {
    nBit++;
    val = val >> 1;
  }
  for (int i = 0; i < nBit; i++) {
    if (i == 0) digitalWrite(A0, HIGH);
    if (i == 1) digitalWrite(A1, HIGH);
    if (i == 2) digitalWrite(A2, HIGH);
    if (i < 3) continue;
    digitalWrite(i, HIGH);
  } 
}

void loop() {
  clearLogic();
  recieve = rcSwitch.getReceivedValue();
  if (rcSwitch.available()) {
    if (recieve >> 8 == car_number && recieve % 256 > TH) {
      value = recieve % 256;
      digitalWrite(PIN_MOTOR, HIGH);
      setLED(value);
      delay(300);
    }
    else {
      digitalWrite(PIN_MOTOR, LOW);
      setLED(value);
      value = value >> 1;
      delay(30);
    }
    rcSwitch.resetAvailable();
    Serial.println("Recieve " + String(recieve) + " | " + "value = " + String(value));
  }
}