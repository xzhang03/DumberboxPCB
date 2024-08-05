void mcpini(void){
  MCP.begin();
  MCP.pinMode8(0b00000000);  // 0 = output, 1 = input
  MCP.write8(0x00);
}

void testMCP23008(void){
  for (byte iled = 0; iled < 8; iled++){
    MCP.digitalWrite(iled, HIGH);
    delay(250);
    MCP.digitalWrite(iled, LOW);
  }
}
