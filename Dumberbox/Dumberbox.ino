
#include "mpr121.h"
#include <Wire.h>

//#define LICKMIN 60
//#define DISPMIN 50
//#define DEBOUNCE 50
#define LICKTIME 10
#define SOLMTIME 10
#define SOLNTIME 10
#define SOLPTIME 10

bool onLick = false;
bool onSolenoidP = false;
bool onSolenoidN = false;
bool onSolenoidM = false;
bool BsolenoidP = false;
bool BsolenoidN = false;
bool BsolenoidM = false;

boolean touchStates[12];  // to keep track of the previous touch states

unsigned long int TonLick = 0;
unsigned long int TonSolenoidP = 0;
unsigned long int TonSolenoidN = 0;
unsigned long int TonSolenoidM = 0;
unsigned long int now;

// Pins
const byte sol1 = 5;
const byte sol2 = 7;
const byte sol3 = 9;
const byte but1 = 10;
const byte but2 = 11;
const byte but3 = 12;
const byte lickttl = 8;
const byte lickled = 6;
const byte ttl1 = 14;
const byte ttl2 = 16;
const byte ttl3 = 15;
const byte ledsol1 = 20;
const byte ledsol2 = 19;
const byte ledsol3 = 18;

const byte onboardled = 13;


/* PINS:
5 Solenoid left (from back)/ right (from front)/yellow/plus
7 Solenoid middle/black/neutral
9 Solenoid right (from back)/ left (from front)/red/minus
8 Lick TTL
12 red button/minus
11 black button/neutral
10 yellow button/plus
15 TTL right (from back)/red/minus
16 TTL middle/black/neutral
14 TTL left/yellow/plus
6 Lick LED
*/

void setup() {
  pinMode(sol1, OUTPUT);
  pinMode(sol2, OUTPUT);
  pinMode(sol3, OUTPUT);
  pinMode(ledsol1, OUTPUT);
  pinMode(ledsol2, OUTPUT);
  pinMode(ledsol3, OUTPUT);
  pinMode(lickttl, OUTPUT);

  pinMode(onboardled, OUTPUT);
  digitalWrite(onboardled, HIGH);
  
  pinMode(but3, INPUT);
  
  pinMode(but2, INPUT); // neutral
  
  pinMode(but1, INPUT); // plus
  
  
  pinMode(ttl3, INPUT);
  pinMode(ttl2, INPUT);
  pinMode(ttl1, INPUT);
  pinMode(lickled, OUTPUT);
  
  Wire.begin();
  mpr121_setup();
  delay(1000);
//  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  now = millis();
  checkLick();
  checkSolenoids();
}


bool readTouchInputs(){
  //read the touch state from the MPR121
  bool out = false;
  
  Wire.requestFrom(0x5A,2); 
  byte LSB = Wire.read();
  byte MSB = Wire.read();
  uint16_t touched = ((MSB << 8) | LSB); //16bits that make up the touch states

  for (int i = 0; i < 12; i++) {  // Check what electrodes were pressed
    if(touched & (1<<i)){
    
      if(touchStates[i] == 0){
        out = true;
      
      }
    
      touchStates[i] = 1;      
    }
    else{
      
      touchStates[i] = 0;
    }
  }
  
  return out;
}

// Check for a lick, if found, pass on to TTL and LED
void checkLick() {
  bool i2click = readTouchInputs();
  if (onLick && now - TonLick > LICKTIME) {
    onLick = false;
    TonLick = now;
    digitalWrite(lickttl, false);
    digitalWrite(lickled, false);
  }
  
  else if (!onLick && i2click == HIGH && now - TonLick > LICKTIME/5) {
    onLick = true;
    TonLick = now;
    digitalWrite(lickttl, true);
    digitalWrite(lickled, true);    
  }
}

// Check whether the solenoids should be turned on or off, then turn them on or off
// This function forces only one solenoid to be on at a time
void checkSolenoids() {
  if (onSolenoidP && now - TonSolenoidP > SOLPTIME && digitalRead(ttl1) == LOW && digitalRead(but1) == LOW) {
    onSolenoidP = false;
    digitalWrite(sol1, false);
    digitalWrite(ledsol1, LOW);
  }
  else if (onSolenoidM && now - TonSolenoidM > SOLMTIME && digitalRead(ttl3) == LOW && digitalRead(but3) == LOW) {
    onSolenoidM = false;
    digitalWrite(sol3, false);
    digitalWrite(ledsol3, LOW);
  }
  else if (onSolenoidN && now - TonSolenoidN > SOLNTIME && digitalRead(ttl2) == LOW && digitalRead(but2) == LOW) {
    onSolenoidN = false;
    digitalWrite(sol2, false);
    digitalWrite(ledsol2, LOW);
  }
  
  else if (!onSolenoidP && !onSolenoidM && !onSolenoidN && (digitalRead(ttl1) == HIGH || digitalRead(but1) == HIGH)) {
    onSolenoidP = true;
    digitalWrite(sol1, true);
    TonSolenoidP = now;
    digitalWrite(ledsol1, HIGH);
  }
  else if (!onSolenoidP && !onSolenoidM && !onSolenoidN && (digitalRead(ttl3) == HIGH || digitalRead(but3) == HIGH)) {
    onSolenoidM = true;
    digitalWrite(sol3, true);
    TonSolenoidM = now;
    digitalWrite(ledsol3, HIGH);
  }
  else if (!onSolenoidP && !onSolenoidM && !onSolenoidN && (digitalRead(ttl2) == HIGH || digitalRead(but2) == HIGH)) {
    onSolenoidN = true;
    digitalWrite(sol2, true);
    TonSolenoidN = now;
    digitalWrite(ledsol2, HIGH);
  }
}


void mpr121_setup(void){

  set_register(0x5A, ELE_CFG, 0x00); 
  
  // Section A - Controls filtering when data is > baseline.
  set_register(0x5A, MHD_R, 0x01);
  set_register(0x5A, NHD_R, 0x01);
  set_register(0x5A, NCL_R, 0x00);
  set_register(0x5A, FDL_R, 0x00);

  // Section B - Controls filtering when data is < baseline.
  set_register(0x5A, MHD_F, 0x01);
  set_register(0x5A, NHD_F, 0x01);
  set_register(0x5A, NCL_F, 0xFF);
  set_register(0x5A, FDL_F, 0x02);
  
  // Section C - Sets touch and release thresholds for each electrode
  set_register(0x5A, ELE0_T, TOU_THRESH);
  set_register(0x5A, ELE0_R, REL_THRESH);
 
  set_register(0x5A, ELE1_T, TOU_THRESH);
  set_register(0x5A, ELE1_R, REL_THRESH);
  
  set_register(0x5A, ELE2_T, TOU_THRESH);
  set_register(0x5A, ELE2_R, REL_THRESH);
  
  set_register(0x5A, ELE3_T, TOU_THRESH);
  set_register(0x5A, ELE3_R, REL_THRESH);
  
  set_register(0x5A, ELE4_T, TOU_THRESH);
  set_register(0x5A, ELE4_R, REL_THRESH);
  
  set_register(0x5A, ELE5_T, TOU_THRESH);
  set_register(0x5A, ELE5_R, REL_THRESH);
  
  set_register(0x5A, ELE6_T, TOU_THRESH);
  set_register(0x5A, ELE6_R, REL_THRESH);
  
  set_register(0x5A, ELE7_T, TOU_THRESH);
  set_register(0x5A, ELE7_R, REL_THRESH);
  
  set_register(0x5A, ELE8_T, TOU_THRESH);
  set_register(0x5A, ELE8_R, REL_THRESH);
  
  set_register(0x5A, ELE9_T, TOU_THRESH);
  set_register(0x5A, ELE9_R, REL_THRESH);
  
  set_register(0x5A, ELE10_T, TOU_THRESH);
  set_register(0x5A, ELE10_R, REL_THRESH);
  
  set_register(0x5A, ELE11_T, TOU_THRESH);
  set_register(0x5A, ELE11_R, REL_THRESH);
  
  // Section D
  // Set the Filter Configuration
  // Set ESI2
  set_register(0x5A, FIL_CFG, 0x04);
  
  // Section E
  // Electrode Configuration
  // Set ELE_CFG to 0x00 to return to standby mode
  set_register(0x5A, ELE_CFG, 0x0C);  // Enables all 12 Electrodes
  
  
  // Section F
  // Enable Auto Config and auto Reconfig
  /*set_register(0x5A, ATO_CFG0, 0x0B);
  set_register(0x5A, ATO_CFGU, 0xC9);  // USL = (Vdd-0.7)/vdd*256 = 0xC9 @3.3V   set_register(0x5A, ATO_CFGL, 0x82);  // LSL = 0.65*USL = 0x82 @3.3V
  set_register(0x5A, ATO_CFGT, 0xB5);*/  // Target = 0.9*USL = 0xB5 @3.3V
  
  set_register(0x5A, ELE_CFG, 0x0C);
  
}

void set_register(int address, unsigned char r, unsigned char v){
    Wire.beginTransmission(address);
    Wire.write(r);
    Wire.write(v);
    Wire.endTransmission();
}
