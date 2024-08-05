// Check whether the solenoids should be turned on or off, then turn them on or off
void checkSolenoids() {
  // Sol 0, 1, 2
  for (uint8_t i = 0; i < 3; i++){
    if (!i2clicks[1] && onSolenoids[i] && (now - TonSolenoids[i] > SOLPTIME) && (digitalRead(but_pins[i]) == LOW)) {
      // ** test no i2c lick
      onSolenoids[i] = false;
      MCP.digitalWrite(mcppins[i+3], LOW);
      digitalWrite(ledsol_pins[i], LOW);
      digitalWrite(ttl_pins[i], LOW);
      digitalWrite(sol_pins[i], LOW);
    }
    else if (dosolenoids[i] || (digitalRead(but_pins[i]) == HIGH)) {
      if (onSolenoids[i]){
        // Already on
        dosolenoids[i] = false;
        TonSolenoids[i] = now;
      }
      else {
        // Turn on
        dosolenoids[i] = false;
        onSolenoids[i] = true;
        TonSolenoids[i] = now;
        digitalWrite(sol_pins[i], true);
        digitalWrite(ledsol_pins[i], HIGH);
        digitalWrite(ttl_pins[i], HIGH);
        MCP.digitalWrite(mcppins[i+3], HIGH);
      }
    }
  }
}
