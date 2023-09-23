//*************************************************************************************************
//                                          HEADER 
//*************************************************************************************************
#include <SPI.h>  // Include the SPI library for communication
#include <LoRa.h> // Include the LoRa library for LoRa communication

#include <Adafruit_GFX.h>      // Include Adafruit's GFX library for graphics
#include <Adafruit_NeoMatrix.h> // Include Adafruit's NeoMatrix library for LED matrix control
#include <Adafruit_NeoPixel.h>  // Include Adafruit's NeoPixel library for LED strip control
#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif

#define PIN_SQUARE 3         // Define the pin for the square LED matrix
#define PIN_CIRCLE 2         // Define the pin for the circular LED strip
#define LED_COUNT_CIRCLE 32 // Define the number of LEDs in the circular strip

// Create a NeoMatrix object for the square LED matrix
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(16, 8, PIN_SQUARE,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

// Create a NeoPixel object for the circular LED strip
Adafruit_NeoPixel strip(LED_COUNT_CIRCLE, PIN_CIRCLE, NEO_GRB + NEO_KHZ800);

// Define an array of color values for later use
const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255), matrix.Color(255, 255, 0) };

// Define LoRa communication pins
#define LORA_SS 53
#define LORA_RST 48
#define LORA_DIO0 49

// Define constants for controlling lights
#define TURNON 0      // 0 = ON  - Reversed due to Module Relay conflict
#define TURNOFF 1     // 1 = OFF - Reversed due to Module Relay conflict

int x    = matrix.width(); // Initialize a variable 'x' with the width of the matrix

String address_LoRa = "hello"; // Define a LoRa address for sending a trigger to NodeA
bool duplicatePreventer = false; // Variable to track if the first "hello" packet has been processed
bool interruptRequested = false;  // Flag to indicate if an interruption is requested

// Define pins for traffic lights and ultrasonic sensors
const int vehicleGreen = 4; // Traffic Light COLOR: GREEN
const int vehicleRed = 5;   // Traffic Light COLOR: RED
const int pedGreen = 6;     // Pedestrian Light COLOR: GREEN
const int pedRed = 7;       // Pedestrian Light COLOR: RED

// Define pins for ultrasonic sensors
const int trigPin1 = 24;
const int echoPin1 = 25;

const int trigPin2 = 26;
const int echoPin2 = 27;

bool vehicle_Detected = false; // Variable to track if a vehicle is detected
bool pedestrian_Detected = false; // Variable to track if a pedestrian is detected
bool object1_Detected = false; // Variable to track if object 1 is detected
bool object2_Detected = false; // Variable to track if object 2 is detected

unsigned long object1_DetectionTime = 0; // Store the time of object 1 detection
unsigned long lastPrintTime = 0; // Store the last time a message was printed
const unsigned long active_Delay = 5000; // How long will Trigger 1 stay active in milliseconds?
unsigned int cycleTime_Duration = 32; // CYCLE TIME DEFAULT - CAN BE CHANGE ANYTIME BY ADMIN - NEED TO RESET IF YOU WANT TO SET TO DEFAULT :>
