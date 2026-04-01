void checkserial(void){
  if (Serial.available() > 1){
    char commandCharacter = Serial.read(); //we use characters (letters) for controlling the switch-case
    Serial.read(); // Read empty
    
    //based on the command character, we decide what to do
    switch (commandCharacter){
      case 'i': // I2c
        {
          i2c_scan(); 
        }
        break;

      case 'm': // memu
        Serial.println("i: i2c scan");
        Serial.println("l: led on");
        Serial.println("k: led off");
        Serial.println("d: dump i2c");
        break;

      case 'l':
        for (i = 0; i < 4; i++){
          digitalWrite(pins[i], HIGH);
          pinstates[i] = true;
        }
        break;

      case 'k':
        for (i = 0; i < 4; i++){
          digitalWrite(pins[i], LOW);
          pinstates[i] = false;
        }
        break;

      case 'd':
        Serial.print("m: ");
        Serial.println(m);
        Serial.print("tnow: ");
        Serial.println(tnow);
        
        Serial.println("======== pin 0 ========");
        Serial.print("tpin: ");
        Serial.println(tpins[0]);
        Serial.print("pinstate: ");
        Serial.println(pinstates[0]);
        Serial.print("pintstate_received: ");
        Serial.println(pinstates_received[0]);
        
        Serial.println("======== pin 1 ========");
        Serial.print("tpin: ");
        Serial.println(tpins[1]);
        Serial.print("pinstate: ");
        Serial.println(pinstates[1]);
        Serial.print("pintstate_received: ");
        Serial.println(pinstates_received[1]);
        
        Serial.println("======== pin 2 ========");
        Serial.print("tpin: ");
        Serial.println(tpins[2]);
        Serial.print("pinstate: ");
        Serial.println(pinstates[2]);
        Serial.print("pintstate_received: ");
        Serial.println(pinstates_received[2]);
        
        Serial.println("======== pin 3 ========");
        Serial.print("tpin: ");
        Serial.println(tpins[3]);
        Serial.print("pinstate: ");
        Serial.println(pinstates[3]);
        Serial.print("pintstate_received: ");
        Serial.println(pinstates_received[3]);
        
    }
  } 
}
