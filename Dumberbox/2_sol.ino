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
