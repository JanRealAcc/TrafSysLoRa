void PedCrossingGo(){

  matrix.fillScreen(0);
  x=16;
  matrix.setCursor(x, 0);
  matrix.show();

  Serial.print("\n    Pedestrian Safe to Cross!");
  // STATUS: || Vehicle = RED || Pedestrian = GREEN ||
  digitalWrite(pedGreen, TURNON);
  digitalWrite(pedRed, TURNOFF);

  // PED DURATION: 3 SECONDS
      
  //TIMER
  unsigned long startTime = millis();
  unsigned long elapsedTime = 0;
  while (elapsedTime <= cycleTime_Duration * 1000) {
    receiveMessage();
    Serial.print("\nETR: ");
    Serial.print((cycleTime_Duration * 1000 - elapsedTime) / 1000);
    ledMessage_Cross();
    countdownAnimation2();
    // Check if an interruption is requested
    if (interruptRequested) {
      Serial.println("\n    Execution interrupted!");
      return;
    }
    elapsedTime = millis() - startTime;
  }
  Serial.println("\n    Ready to Stop Pedestrian!");

}


void pedestrianTrigger(){
  led_blinking_Traf();
  PedCrossingGo();
  led_blinking_Ped();

  // Reset variables and conditions for the next cycle
  object1_Detected = false;
  object2_Detected = false;
  interruptRequested = false;
  Serial.println("  Resetting for the next detection");

  currentLED = 0;
  currentLED2 = LED_COUNT_CIRCLE - 1;
  currentLED3 = 0;

}