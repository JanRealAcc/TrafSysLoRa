char buffer[25];

void flag_2(){
// ***Check if Ultrasonic sensor #2 detects an object within the specified time***
  if (object1_Detected && !object2_Detected && (millis() - object1_DetectionTime <= active_Delay)) {
    int distance2 = measureDistance(trigPin2, echoPin2);
    Serial.print("F2 - ");
    Serial.println(distance2);
    receiveMessage();  


    if (distance2 < 15) {
      for(int i=0; i<2 ; i++){
        sendMessage();
      }

      delay(200);

      activateTrafficSensor();
      delay(50);


      snprintf(buffer, sizeof(buffer), "Duration_Execute: %d", cycleTime_Duration);
      sendSerial(buffer);

      pedestrianTrigger();
      deactivateTrafficSensor();




    }
  }

}
