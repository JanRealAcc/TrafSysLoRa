void flag_Timeout(){
// Check if timeout occurred without detecting an object with Ultrasonic sensor #2
  if (object1_Detected && !object2_Detected && (millis() - object1_DetectionTime > active_Delay)) {
    digitalWrite(pedGreen, TURNOFF); // Turn off the new LED
    digitalWrite(pedRed, TURNON); // Turn on the original LED
    digitalWrite(vehicleGreen, TURNON); // Turn off the new LED
    digitalWrite(vehicleRed, TURNOFF);

    Serial.println("Timeout: Object not detected by Ultrasonic #2 within the specified time");

    // Reset variables and conditions for the next cycle
    object1_Detected = false;
    object2_Detected = false;
  }

  
}  