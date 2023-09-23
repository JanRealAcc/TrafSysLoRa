void receiveMessage() {
    
if (LoRa.parsePacket()) {
    int rssi = LoRa.packetRssi();
    String receivedData = LoRa.readString();


      Serial.print("Received data: ");
      Serial.println(receivedData);


    // Add identifier based on the transmitter node
    if (receivedData.equals("hello")) {
      delay(250);
      pedestrianTrigger();
    } 


       // Add identifier based on the transmitter node
    if (receivedData.equals("olla")) {
        interruptRequested = true;
    } 


    //Duration time change
    if (receivedData.startsWith("cycle ")) {
        int value = receivedData.substring(6).toInt(); // Remove "cycle " prefix

        Serial.println("RECEIVED!");

        // Check if a valid value was received
        if (value >= 8) {
            cycleTime_Duration = value;  // Update the cycleTime_Duration variable
            Serial.print("New cycle duration: ");
            Serial.println(cycleTime_Duration);
            //delay(100);
            sendSerial("Duration - Updated!");
        }
    }
}

}
