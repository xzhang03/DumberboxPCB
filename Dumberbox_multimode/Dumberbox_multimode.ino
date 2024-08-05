// This is multimode. Do not use on regular dumberbox

#include "mpr121.h"
#include <Wire.h>

//#define LICKMIN 60
//#define DISPMIN 50
//#define DEBOUNCE 50
#define LICKTIME 10
//#define SOLMTIME 20
//#define SOLNTIME 20
#define SOLPTIME 20

// MCP23008 settings
#include "MCP23008.h"
MCP23008 MCP(0x20);
const byte mcppins[6] = {0, 2, 3, 4, 6, 7}; // {lick0 lick1 lick2 sol0 sol1 sol2}

// MPR121 settings
const byte mpradds[4] = {0x5A, 0x5B, 0x5C, 0x20};
bool hasmprs[4] = {false, false, false, false};

// Licks
bool i2clicks[3] = {false, false, false};
bool onLicks[3] = {false, false, false};
unsigned long int TonLicks[3] = {0, 0, 0};
bool lickledon = false;

// Solenoids
bool onSolenoids[3] = {false, false, false};
bool dosolenoids[3] = {false, false, false};
unsigned long int TonSolenoids[3] = {0, 0, 0};

unsigned long int now;

// Pins
const byte sol_pins[3] = {5, 7, 9};
const byte but_pins[3] = {10, 11, 12};
const byte lickled = 6;
const byte lickled2 = A4;
const byte ttl_pins[3] = {14, 16, 15};
const byte ledsol_pins[3] = {20, 19, 18};

const byte onboardled = 13;

void setup() {
  for (uint8_t i = 0; i < 3; i++){
    pinMode(sol_pins[i], OUTPUT);
    pinMode(ledsol_pins[i], OUTPUT);
    pinMode(but_pins[i], INPUT);
    pinMode(ttl_pins[i], OUTPUT);
  }
  pinMode(onboardled, OUTPUT);
 
  pinMode(lickled, OUTPUT);
  pinMode(lickled2, OUTPUT);
  
  Wire.begin();

  checki2c();

  // Initialize lick
  for (byte impr = 0; impr < 3; impr++){
    if (hasmprs[impr]){
      mpr121_setup(mpradds[impr]);
    }
  }

  // Initialize mcp
  if (hasmprs[3]){
    mcpini();
  }
  
  delay(200);

  // Start serial
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  now = millis();
  checkLick();
  Lickpulses();
  checkSolenoids();
  checkserial();
}
