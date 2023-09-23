void flag_1() {
  if (!object1_Detected) { // Check if object1 has not been detected yet.
    int distance1 = measureDistance(trigPin1, echoPin1); // Measure the distance using Ultrasonic #1.

    // Display on Serial-monitor
    Serial.print("F1 - "); // Print "F1 - " to indicate Flag 1 data.
    Serial.println(distance1); // Print the measured distance to the Serial monitor.
    receiveMessage(); // Receive a message (function purpose not provided).

    if (distance1 < 15) { // Check if the measured distance is less than 15 units.
      object1_Detected = true; // Set object1 detection status to true.
      object1_DetectionTime = millis(); // Record the detection time in milliseconds.

      Serial.println("Object detected by Ultrasonic #1"); // Print a message indicating object detection.
    }
  }
}
