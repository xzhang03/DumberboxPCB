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
    digitalWrite(lickttl2, false);
    digitalWrite(lickled, false);
    digitalWrite(lickled2, false);
    digitalWrite(onboardled, false);
  }
  
  else if (!onLick && i2click == HIGH && now - TonLick > LICKTIME/5) {
    onLick = true;
    TonLick = now;
    digitalWrite(lickttl, true);
    digitalWrite(lickttl2, true);
    digitalWrite(lickled, true);  
    digitalWrite(lickled2, true);  
    digitalWrite(onboardled, true);
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

void setnewthresh(byte thresh){
  byte thresh_t = thresh;
  byte thresh_r = thresh + 0x04;
  
  set_register(0x5A, ELE0_T, thresh_t);
  set_register(0x5A, ELE0_R, thresh_r);
 
  set_register(0x5A, ELE1_T, thresh_t);
  set_register(0x5A, ELE1_R, thresh_r);
  
  set_register(0x5A, ELE2_T, thresh_t);
  set_register(0x5A, ELE2_R, thresh_r);
  
  set_register(0x5A, ELE3_T, thresh_t);
  set_register(0x5A, ELE3_R, thresh_r);
  
  set_register(0x5A, ELE4_T, thresh_t);
  set_register(0x5A, ELE4_R, thresh_r);
  
  set_register(0x5A, ELE5_T, thresh_t);
  set_register(0x5A, ELE5_R, thresh_r);
  
  set_register(0x5A, ELE6_T, thresh_t);
  set_register(0x5A, ELE6_R, thresh_r);
  
  set_register(0x5A, ELE7_T, thresh_t);
  set_register(0x5A, ELE7_R, thresh_r);
  
  set_register(0x5A, ELE8_T, thresh_t);
  set_register(0x5A, ELE8_R, thresh_r);
  
  set_register(0x5A, ELE9_T, thresh_t);
  set_register(0x5A, ELE9_R, thresh_r);
  
  set_register(0x5A, ELE10_T, thresh_t);
  set_register(0x5A, ELE10_R, thresh_r);
  
  set_register(0x5A, ELE11_T, thresh_t);
  set_register(0x5A, ELE11_R, thresh_r);
}
