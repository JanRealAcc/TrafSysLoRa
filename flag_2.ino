char buffer[25]; // Declare a character array to store text data.

void flag_2() {
  // Check if Ultrasonic sensor #2 detects an object within the specified time
  if (object1_Detected && !object2_Detected && (millis() - object1_DetectionTime <= active_Delay)) {
    int distance2 = measureDistance(trigPin2, echoPin2); // Measure the distance using Ultrasonic #2.
    Serial.print("F2 - "); // Print "F2 - " to indicate Flag 2 data.
    Serial.println(distance2); // Print the measured distance to the Serial monitor.
    receiveMessage(); // Receive a message (function purpose not provided).

    if (distance2 < 15) { // Check if the measured distance is less than 15 units.
      for (int i = 0; i < 2; i++) {
        sendMessage(); // Send a message twice (function purpose not provided).
      }

      delay(200); // Delay for 200 milliseconds.

      activateTrafficSensor(); // Activate a traffic sensor (function purpose not provided).
      delay(50); // Delay for 50 milliseconds.

      // Format a text message using snprintf and store it in the 'buffer' variable.
      snprintf(buffer, sizeof(buffer), "Duration_Execute: %d", cycleTime_Duration);

      // Send the formatted message to the Serial monitor.
      sendSerial(buffer); // Function sendSerial() is used to send the message.

      pedestrianTrigger(); // Trigger a pedestrian event (function purpose not provided).
      deactivateTrafficSensor(); // Deactivate the traffic sensor (function purpose not provided).
    }
  }
}
