#include <Wire.h>
#define i2cadd 9

const byte pins[4] = {10, 9, 7 , 5};
const byte ledpin = 13;

unsigned long int tnow;
unsigned long int tpins[4];
bool pinstates[4] = {false, false, false, false};
bool pinstates_received[4] = {false, false, false, false};
unsigned long int tcycle = 40000;

byte i;

// Wire
byte m, n;
bool newdata = false;

// Heart beat
unsigned long int tbeat;
unsigned long int durbeat = 100;
unsigned long int cyclebeat = 2000;
bool beaton = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledpin, OUTPUT);
  for (i = 0; i < 4; i++){
    pinMode(pins[i],OUTPUT);
  }

  // Wire
  Wire.begin(i2cadd);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  tnow = millis();

  // Start serial
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  tnow = millis();

  // New data sync to turn on lights
  if (newdata){
    newdata = false;
    for (i = 0; i < 4; i++){
      if (pinstates_received[i]){
        // receive good
        if (pinstates[i]){
          // already good
          tpins[i] = tnow;
        }
        else{
          // bad -> good
          pinstates[i] = true;
          tpins[i] = tnow;
          digitalWrite(pins[i], HIGH);
        }
      }
      else{
        // receive bad
        if (pinstates[i]){
          // good -> bad
          pinstates[i] = false;
          digitalWrite(pins[i], LOW);
        }
        else{
          // bad -> bad
        }
      }
    }
  }

  // Turn lights off
  for (i = 0; i < 4; i++){
    if ((tnow - tpins[i]) > tcycle){
      pinstates[i] = false;
      digitalWrite(pins[i], LOW);
    }
  }

  // heart beat
  if (((tnow - tbeat) < durbeat) && ~beaton){
    beaton = true;
    digitalWrite(ledpin, HIGH);
  }
  else if (((tnow - tbeat) >= durbeat) && beaton){
    beaton = false;
    digitalWrite(ledpin, LOW);
  }
  else if ((tnow - tbeat) >= cyclebeat){
    tbeat = tnow;
  }
  
  // Serial
  checkserial();
}

void requestEvent(){
  Wire.write("m:"); // 2 bytes
  Wire.write(m); // 1 byte
  Wire.write(" P0:"); // 4 bytes
  Wire.write(pinstates[0]); // 1 byte
  Wire.write(pinstates_received[0]); // 1 byte
  Wire.write(" P1:"); // 4 bytes
  Wire.write(pinstates[1]); // 1 byte
  Wire.write(pinstates_received[1]); // 1 byte
  Wire.write(" P2:"); // 4 bytes
  Wire.write(pinstates[2]); // 1 byte
  Wire.write(pinstates_received[2]); // 1 byte
  Wire.write(" P3:"); // 4 bytes
  Wire.write(pinstates[3]); // 1 byte
  Wire.write(pinstates_received[3]); // 1 byte
}

void receiveEvent(int bytes){
  // state
  newdata = true;
  m = Wire.read();
  for (i = 0; i < 4; i++){
    pinstates_received[i] = ((m >> i) & 0B1) == 1;
  }
  
}
