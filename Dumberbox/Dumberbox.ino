
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
const byte lickttl2 = A5;
const byte lickled = 6;
const byte lickled2 = A4;
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
  pinMode(lickttl2, OUTPUT);
  

  pinMode(onboardled, OUTPUT);
  
  pinMode(but3, INPUT);
  
  pinMode(but2, INPUT); // neutral
  
  pinMode(but1, INPUT); // plus
  
  
  pinMode(ttl3, INPUT);
  pinMode(ttl2, INPUT);
  pinMode(ttl1, INPUT);
  pinMode(lickled, OUTPUT);
  pinMode(lickled2, OUTPUT);
  
  Wire.begin();

  checklick();
  
  mpr121_setup();
  delay(1000);

  // Start serial
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  now = millis();
  checkLick();
  checkSolenoids();
  checkserial();
}
