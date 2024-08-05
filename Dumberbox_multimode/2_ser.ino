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
        Serial.println("m: menu");
        Serial.println("i: i2c scan");
        Serial.println("s: boardstate");
        Serial.println("p: test MCP");
        Serial.println("5: Threshold = 5");
        Serial.println("7: Threshold = 7");
        Serial.println("9: Threshold = 9");
        Serial.println("b: Threshold = b");
        Serial.println("d: Threshold = d");
        Serial.println("f: Threshold = f");
        break;

      case 's':
        Serial.print("I2c states: ");
        Serial.print(hasmprs[0]);
        Serial.print(" ");
        Serial.print(hasmprs[1]);
        Serial.print(" ");
        Serial.print(hasmprs[2]);
        Serial.print(" ");
        Serial.println(hasmprs[3]);

        Serial.print("Lick states: ");
        Serial.print(i2clicks[0]);
        Serial.print(" ");
        Serial.print(i2clicks[1]);
        Serial.print(" ");
        Serial.println(i2clicks[2]);

        Serial.print("Lick pulses: ");
        Serial.print(onLicks[0]);
        Serial.print(" ");
        Serial.print(onLicks[1]);
        Serial.print(" ");
        Serial.println(onLicks[2]);

        Serial.print("Lick pulse times: ");
        Serial.print(TonLicks[0]);
        Serial.print(" ");
        Serial.print(TonLicks[1]);
        Serial.print(" ");
        Serial.println(TonLicks[2]);

        Serial.print("Solinoid ready on: ");
        Serial.print(dosolenoids[0]);
        Serial.print(" ");
        Serial.print(dosolenoids[1]);
        Serial.print(" ");
        Serial.println(dosolenoids[2]);

        Serial.print("Solinoid on: ");
        Serial.print(onSolenoids[0]);
        Serial.print(" ");
        Serial.print(onSolenoids[1]);
        Serial.print(" ");
        Serial.println(onSolenoids[2]);

        Serial.print("Solinoid on times: ");
        Serial.print(TonSolenoids[0]);
        Serial.print(" ");
        Serial.print(TonSolenoids[1]);
        Serial.print(" ");
        Serial.println(TonSolenoids[2]);
        
        break;

      case 'p':
        testMCP23008();
        break;
      
      case '5': // threshold 5
        Serial.println("Threshold = 0x05");
        setnewthresh(0x05);
        break;

      case '7': // threshold 7
        Serial.println("Threshold = 0x07");
        setnewthresh(0x07);
        break;

      case '9': // threshold 9
        Serial.println("Threshold = 0x09");
        setnewthresh(0x09);
        break;

      case 'b': // threshold 11
        Serial.println("Threshold = 0x0b");
        setnewthresh(0x0b);
        break;
      
      case 'd': // threshold 13
        Serial.println("Threshold = 0x0d");
        setnewthresh(0x0d);
        break;

      case 'f': // threshold 15
        Serial.println("Threshold = 0x0f");
        setnewthresh(0x0f);
        break;


    }
  } 
}
