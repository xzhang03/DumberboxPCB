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
        Serial.println("1: Threshold = 1");
        Serial.println("3: Threshold = 3");
        Serial.println("5: Threshold = 5");
        Serial.println("7: Threshold = 7");
        Serial.println("9: Threshold = 9");
        Serial.println("b: Threshold = b");
        Serial.println("d: Threshold = d");
        Serial.println("f: Threshold = f");
        break;

      case '1': // threshold 1
        Serial.println("Threshold = 0x01/0x05");
        setnewthresh(0x01);
        break;

      case '3': // threshold 3
        Serial.println("Threshold = 0x03/0x07");
        setnewthresh(0x03);
        break;
      
      case '5': // threshold 5
        Serial.println("Threshold = 0x05/0x09");
        setnewthresh(0x05);
        break;

      case '7': // threshold 7
        Serial.println("Threshold = 0x07/0x0B");
        setnewthresh(0x07);
        break;

      case '9': // threshold 9
        Serial.println("Threshold = 0x09/0x0D");
        setnewthresh(0x09);
        break;

      case 'b': // threshold 11
        Serial.println("Threshold = 0x0b/0x1f");
        setnewthresh(0x0b);
        break;
      
      case 'd': // threshold 13
        Serial.println("Threshold = 0x0d/0x11");
        setnewthresh(0x0d);
        break;

      case 'f': // threshold 15
        Serial.println("Threshold = 0x0f/0x13");
        setnewthresh(0x0f);
        break;


    }
  } 
}
