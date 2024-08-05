bool readTouchInputs(byte address){
  //read the touch state from the MPR121
  bool out = false;
  bool touchStates[12];  // to keep track of the previous touch states
  
  Wire.requestFrom(address,2); 
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
  for (uint8_t i = 0; i < 3; i++){
    // Check lick
    if (hasmprs[i]){
      i2clicks[i] = readTouchInputs(mpradds[i]);
    }
    else{
      i2clicks[i] = false;
    }
  }
}

void Lickpulses(){
  for (uint8_t i = 0; i < 3; i++){
    // Turn lick 1 off
    if (onLicks[i] && now - TonLicks[i] > LICKTIME) {
      onLicks[i] = false;
      TonLicks[i] = now;
  
      // Pulse low
      MCP.digitalWrite(mcppins[i], LOW);
  
      // If not lick between 3 spouts, turn led off
      if (!onLicks[0] && !onLicks[1] && !onLicks[2] && lickledon){
        digitalWrite(lickled, false);
        digitalWrite(lickled2, false);
        digitalWrite(onboardled, false);
        lickledon = false;
      }
    }
    // Turn lick 1 on
    else if (!onLicks[i] && i2clicks[i] && (now - TonLicks[i] > LICKTIME/5)) {
      onLicks[i] = true;
      TonLicks[i] = now;
      MCP.digitalWrite(mcppins[i], HIGH);
      dosolenoids[i] = true;
      
      if (!lickledon){
        digitalWrite(lickled, true);  
        digitalWrite(lickled2, true);  
        digitalWrite(onboardled, true);
        lickledon = true;
      }
    }
  }
  
}

void mpr121_setup(byte mpraddress){

  set_register(mpraddress, ELE_CFG, 0x00); 
  
  // Section A - Controls filtering when data is > baseline.
  set_register(mpraddress, MHD_R, 0x01);
  set_register(mpraddress, NHD_R, 0x01);
  set_register(mpraddress, NCL_R, 0x00);
  set_register(mpraddress, FDL_R, 0x00);

  // Section B - Controls filtering when data is < baseline.
  set_register(mpraddress, MHD_F, 0x01);
  set_register(mpraddress, NHD_F, 0x01);
  set_register(mpraddress, NCL_F, 0xFF);
  set_register(mpraddress, FDL_F, 0x02);
  
  // Section C - Sets touch and release thresholds for each electrode
  set_register(mpraddress, ELE0_T, TOU_THRESH);
  set_register(mpraddress, ELE0_R, REL_THRESH);
 
  set_register(mpraddress, ELE1_T, TOU_THRESH);
  set_register(mpraddress, ELE1_R, REL_THRESH);
  
  set_register(mpraddress, ELE2_T, TOU_THRESH);
  set_register(mpraddress, ELE2_R, REL_THRESH);
  
  set_register(mpraddress, ELE3_T, TOU_THRESH);
  set_register(mpraddress, ELE3_R, REL_THRESH);
  
  set_register(mpraddress, ELE4_T, TOU_THRESH);
  set_register(mpraddress, ELE4_R, REL_THRESH);
  
  set_register(mpraddress, ELE5_T, TOU_THRESH);
  set_register(mpraddress, ELE5_R, REL_THRESH);
  
  set_register(mpraddress, ELE6_T, TOU_THRESH);
  set_register(mpraddress, ELE6_R, REL_THRESH);
  
  set_register(mpraddress, ELE7_T, TOU_THRESH);
  set_register(mpraddress, ELE7_R, REL_THRESH);
  
  set_register(mpraddress, ELE8_T, TOU_THRESH);
  set_register(mpraddress, ELE8_R, REL_THRESH);
  
  set_register(mpraddress, ELE9_T, TOU_THRESH);
  set_register(mpraddress, ELE9_R, REL_THRESH);
  
  set_register(mpraddress, ELE10_T, TOU_THRESH);
  set_register(mpraddress, ELE10_R, REL_THRESH);
  
  set_register(mpraddress, ELE11_T, TOU_THRESH);
  set_register(mpraddress, ELE11_R, REL_THRESH);
  
  // Section D
  // Set the Filter Configuration
  // Set ESI2
  set_register(mpraddress, FIL_CFG, 0x04);
  
  // Section E
  // Electrode Configuration
  // Set ELE_CFG to 0x00 to return to standby mode
  set_register(mpraddress, ELE_CFG, 0x0C);  // Enables all 12 Electrodes
  
  
  // Section F
  // Enable Auto Config and auto Reconfig
  /*set_register(mpraddress, ATO_CFG0, 0x0B);
  set_register(mpraddress, ATO_CFGU, 0xC9);  // USL = (Vdd-0.7)/vdd*256 = 0xC9 @3.3V   set_register(mpraddress, ATO_CFGL, 0x82);  // LSL = 0.65*USL = 0x82 @3.3V
  set_register(mpraddress, ATO_CFGT, 0xB5);*/  // Target = 0.9*USL = 0xB5 @3.3V
  
  set_register(mpraddress, ELE_CFG, 0x0C);
  
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
  byte mpraddress;

  for (byte itemp = 0; itemp < 3; itemp++){
    if (hasmprs[itemp]){
      mpraddress = mpradds[itemp];
    
      set_register(mpraddress, ELE0_T, thresh_t);
      set_register(mpraddress, ELE0_R, thresh_r);
     
      set_register(mpraddress, ELE1_T, thresh_t);
      set_register(mpraddress, ELE1_R, thresh_r);
      
      set_register(mpraddress, ELE2_T, thresh_t);
      set_register(mpraddress, ELE2_R, thresh_r);
      
      set_register(mpraddress, ELE3_T, thresh_t);
      set_register(mpraddress, ELE3_R, thresh_r);
      
      set_register(mpraddress, ELE4_T, thresh_t);
      set_register(mpraddress, ELE4_R, thresh_r);
      
      set_register(mpraddress, ELE5_T, thresh_t);
      set_register(mpraddress, ELE5_R, thresh_r);
      
      set_register(mpraddress, ELE6_T, thresh_t);
      set_register(mpraddress, ELE6_R, thresh_r);
      
      set_register(mpraddress, ELE7_T, thresh_t);
      set_register(mpraddress, ELE7_R, thresh_r);
      
      set_register(mpraddress, ELE8_T, thresh_t);
      set_register(mpraddress, ELE8_R, thresh_r);
      
      set_register(mpraddress, ELE9_T, thresh_t);
      set_register(mpraddress, ELE9_R, thresh_r);
      
      set_register(mpraddress, ELE10_T, thresh_t);
      set_register(mpraddress, ELE10_R, thresh_r);
      
      set_register(mpraddress, ELE11_T, thresh_t);
      set_register(mpraddress, ELE11_R, thresh_r);
    }
  }
}
