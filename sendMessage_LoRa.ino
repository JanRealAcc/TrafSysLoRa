void sendMessage(){
 // Send a message to the receiver traffic light
        Serial.print("\n\n\n\n*************************************\nSENDING TRIGGER: ");
      // send packet
        LoRa.beginPacket();
        LoRa.print(address_LoRa);
        LoRa.endPacket();
        Serial.print("Success!");
}
     