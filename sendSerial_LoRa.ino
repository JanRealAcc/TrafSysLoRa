void sendSerial(const char* message) {
  int messageSize = strlen(message);
  LoRa.beginPacket();
  LoRa.print("LoRa1\n");
  LoRa.write(message, messageSize);
  LoRa.endPacket();
}
