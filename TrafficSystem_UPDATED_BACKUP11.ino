//*************************************************************************************************
//                                          HEADER 
//*************************************************************************************************
#include <SPI.h>
#include <LoRa.h>

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN_SQUARE 3
#define PIN_CIRCLE 2
#define LED_COUNT_CIRCLE 32 //Circle LED #




//                                            (x) (y)   (PIN)
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(16, 8, PIN_SQUARE,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

Adafruit_NeoPixel strip(LED_COUNT_CIRCLE, PIN_CIRCLE, NEO_GRB + NEO_KHZ800);


const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255), matrix.Color(255, 255, 0) };

// Define LoRa PINS
#define LORA_SS 53
#define LORA_RST 48
#define LORA_DIO0 49
// ***Defining the OUTPUTS of lights***
#define TURNON 0      // 0 = ON  - Reversed due to Module Relay conflict
#define TURNOFF 1     // 1 = OFF - Reversed due to Module Relay conflict

int x    = matrix.width();

String address_LoRa = "hello"; // Send trigger to NodeA
bool duplicatePreventer = false; // Variable to track if the first "hello" packet has been processed
bool interruptRequested = false;  // Flag to indicate if an interruption is requested

// ***Traffic Light Pins***                                   
const int vehicleGreen = 4; //Traffic Light COLOR: GREEN      
const int vehicleRed = 5;   //Traffic Light COLOR: RED        
const int pedGreen = 6;     //Pedestrian Light COLOR: GREEN   
const int pedRed = 7;       //Pedestrian Light COLOR: RED                                     
//******Ultrasonic sensor #1 (Trigger 1 and Echo 1 pins)******//
const int trigPin1 = 24;                                      
const int echoPin1 = 25;
//******Ultrasonic sensor #2 (Trigger 2 and Echo 2 pins)******//
const int trigPin2 = 26;
const int echoPin2 = 27;
// ***Variables for detecting and timing***
bool vehicle_Detected = false;
bool pedestrian_Detected = false;
bool object1_Detected = false;
bool object2_Detected = false;
unsigned long object1_DetectionTime = 0;
unsigned long lastPrintTime = 0; // Variable to store the last time the message was printed
const unsigned long active_Delay = 5000; //How long will Trigger 1 stay active in milliseconds?
unsigned int cycleTime_Duration = 32; // CYCLE TIME DEFAULT - CAN BE CHANGE ANYTIME BY ADMIN - NEED TO RESET IF YOU WANT TO SET TO DEFAULT :>


//***************************************************************************************
//                                         SETUP 
//***************************************************************************************
void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(255);
  matrix.setTextColor(colors[0]);

  strip.begin();
  strip.show(); // Initialize all pixels to off
  
  // PINMODE for ULTRASONIC 1
  pinMode(trigPin1, OUTPUT); 
  pinMode(echoPin1, INPUT);     

  // PINMODE for ULTRASONIC 2
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  // PINMODE for LIGHTS
  pinMode(pedRed, OUTPUT);        // COLOR: RED   - PED
  pinMode(pedGreen, OUTPUT);      // COLOR: GREEN - PED
  pinMode(vehicleRed, OUTPUT);    // COLOR: RED   - VEHICLE
  pinMode(vehicleGreen, OUTPUT);  // COLOR: GREEN - VEHICLE

  // LIGHT STARTUP - Default
  digitalWrite(pedRed, TURNON);         // PED COLOR: RED         = ON
  digitalWrite(pedGreen, TURNOFF);      // PED COLOR: GREEN       = ON
  digitalWrite(vehicleGreen, TURNON);   // VEHICLE COLOR: GREEN   = ON
  digitalWrite(vehicleRed, TURNOFF);    // VEHICLE COLOR: GREEN   = ON

 
  // LORA INITIATING
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0); // NSS = 53 RST = 9 DIO0 = 8
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Receiver");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }



}



//*******************************************************************************************
//                                       LOOP 
//*******************************************************************************************
void loop() {
  ledMessage_Idle();
  flag_1();
  flag_2();
  flag_Timeout();


}

