

void flag_1(){
  if (!object1_Detected) {
    int distance1 = measureDistance(trigPin1, echoPin1);

    // Display on Serial-monitor
    Serial.print("F1 - ");
    Serial.println(distance1);
    receiveMessage();


    if (distance1 < 15) {
      object1_Detected = true;
      object1_DetectionTime = millis();

      Serial.println("Object detected by Ultrasonic #1");
      
    }
  }
}