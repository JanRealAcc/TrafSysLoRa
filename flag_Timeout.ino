void flag_Timeout() {
  // Check if a timeout occurred without detecting an object with Ultrasonic sensor #2
  if (object1_Detected && !object2_Detected && (millis() - object1_DetectionTime > active_Delay)) {
    // Turn off the new LED for pedestrian green
    digitalWrite(pedGreen, TURNOFF);

    // Turn on the original LED for pedestrian red
    digitalWrite(pedRed, TURNON);

    // Turn off the new LED for vehicle green
    digitalWrite(vehicleGreen, TURNON);

    // Turn on the original LED for vehicle red
    digitalWrite(vehicleRed, TURNOFF);

    // Print a message indicating a timeout
    Serial.println("Timeout: Object not detected by Ultrasonic #2 within the specified time");

    // Reset variables and conditions for the next cycle
    object1_Detected = false;
    object2_Detected = false;
  }
}
