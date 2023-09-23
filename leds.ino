int timer_Blind_Traf = 0;
unsigned int cycleTime_Duration_Blink_Traf = 5; 
int timer_Blink_Ped = 0;
unsigned int cycleTime_Duration_Blink_Ped = 5;
int timer_Delay_Traf = 0;
unsigned int cycleTime_Duration_Delay_Traf = 3;
int timer_Delay_Ped = 0;
unsigned int cycleTime_Duration_Delay_Ped = 3; 

unsigned long previousMillis = 0;  // Variable to store the previous time
const unsigned long messageSpeed_Idle = 100;  // messageSpeed in milliseconds
const unsigned long messageSpeed_Blinking = 50;  // messageSpeed in milliseconds
const unsigned long messageSpeed_Cross = 50;  // messageSpeed in milliseconds
const unsigned long messageSpeed_Blinking2 = 30;  // messageSpeed in milliseconds

int currentLED3 = 0;
int currentLED = 0;
int currentLED2 = LED_COUNT_CIRCLE - 1; // Start from the last LED

void loadingAnimation() {
  static int pos = 0;
  static int tailLength = 25; // Adjust this value to change the length of the fading tail
  static int delayTime = 20; // Adjust this value to change animation speed
  static unsigned long previousMillis = 0;
  static int brightness_Delay = 50;
  static int brightness_Value = 50;

  // Set all pixels to off
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 0);
  }

  // Set the current position pixel to a color
  strip.setPixelColor(pos, 255, 255, 255); // Adjust the RGB values for the desired color


  // Set the tail pixels to a faded color
  for (int i = 1; i <= tailLength; i++) {
    int brightness = brightness_Delay - (i * (brightness_Delay / tailLength));
    strip.setPixelColor((pos - i + strip.numPixels()) % strip.numPixels(), 0, brightness, 0);
  }

  strip.show();

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= delayTime) {
    // Increment the position and wrap around
    pos++;
    if (pos >= strip.numPixels()) {
      pos = 0;
    }

    previousMillis = currentMillis;
  }
}


void led_blinking_Traf(){
  unsigned long startTime_Blink_Traf = millis();
  unsigned long elapsedTime_Blink_Traf = 0;

  //clear LED
 
  matrix.fillScreen(0);
  x=16;
  matrix.setCursor(x, 0);
  matrix.show();
  interruptRequested = false;
  pedestrian_Detected = true;



  while (elapsedTime_Blink_Traf <= cycleTime_Duration_Blink_Traf * 1000) {
    timer_Blind_Traf = (cycleTime_Duration_Blink_Traf * 1000 - elapsedTime_Blink_Traf) / 500;

    Serial.print("\nBlinking: ");
    Serial.print(timer_Blind_Traf);
    loadingAnimation();


    ledMessage_Blinking();


      
      if (timer_Blind_Traf % 2 && timer_Blind_Traf < cycleTime_Duration_Blink_Traf * 2) {
        digitalWrite(vehicleGreen, TURNOFF);
    }else{
        digitalWrite(vehicleGreen, TURNON);

    }
    elapsedTime_Blink_Traf = millis() - startTime_Blink_Traf;

  }

  //Process Starts Here
  Serial.print("\n    Pedestrian Ready to Cross!");
  
  // STATUS: || Vehicle = RED || Pedestrian = RED ||
  digitalWrite(vehicleGreen, TURNOFF);
  digitalWrite(vehicleRed, TURNON);
  digitalWrite(pedRed, TURNON);
  // STATUS: Delay 5 seconds
    // Set all pixels to off
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 0);    
  }
  strip.show();



  unsigned long startTime_Delay = millis();
  unsigned long elapsedTime_Delay = 0;


  while (elapsedTime_Delay <= cycleTime_Duration_Delay_Traf * 1000) {
    timer_Delay_Traf = (cycleTime_Duration_Delay_Traf * 1000 - elapsedTime_Delay) / 500;

    Serial.print("\nDelay: ");
    Serial.print(timer_Delay_Traf);
    ledMessage_Blinking();
    countdownAnimation();



    elapsedTime_Delay = millis() - startTime_Delay;

  }

  
}


void led_blinking_Ped(){
  unsigned long startTime_Blink_Ped = millis();
  unsigned long elapsedTime_Blink_Ped = 0;

  matrix.fillScreen(0);
  x=16;
  matrix.setCursor(x, 0);
  matrix.show();

  while (elapsedTime_Blink_Ped <= cycleTime_Duration_Blink_Ped * 1000) {
  timer_Blink_Ped = (cycleTime_Duration_Blink_Ped * 1000 - elapsedTime_Blink_Ped) / 500;

  Serial.print("\nBlinking: ");
  Serial.print(timer_Blink_Ped);
  ledMessage_Blinking_Ped();
    
    if (timer_Blink_Ped % 2 && timer_Blink_Ped < cycleTime_Duration_Blink_Ped * 2) {
      digitalWrite(pedGreen, TURNOFF);
  }else{
      digitalWrite(pedGreen, TURNON);

  }
  elapsedTime_Blink_Ped = millis() - startTime_Blink_Ped;

  }

  // STATUS: || Vehicle = RED || Pedestrian = RED ||
  digitalWrite(pedGreen, TURNOFF);
  digitalWrite(vehicleRed, TURNON);
  digitalWrite(pedRed, TURNON);


//DELAY
  unsigned long startTime_Delay_Ped = millis();
  unsigned long elapsedTime_Delay_Ped = 0;

  while (elapsedTime_Delay_Ped <= cycleTime_Duration_Delay_Ped * 1000) {
    timer_Delay_Ped = (cycleTime_Duration_Delay_Ped * 1000 - elapsedTime_Delay_Ped) / 500;

    Serial.print("\nDelay: ");
    Serial.print(timer_Delay_Ped);
    ledMessage_Blinking_Ped();


    elapsedTime_Delay_Ped = millis() - startTime_Delay_Ped;

  }
  // STATUS: || Vehicle = GREEN || Pedestrian = RED ||
  digitalWrite(vehicleRed, TURNOFF);
  digitalWrite(vehicleGreen, TURNON);
  x = 16;
}





void ledMessage_Idle(){
    unsigned long currentMillis = millis();  // Get the current time

    if (currentMillis - previousMillis >= messageSpeed_Idle) {
      previousMillis = currentMillis;  // Save the current time
      // Your code to be executed every 100 milliseconds
      matrix.setTextColor(colors[2]);
      matrix.fillScreen(0);
      matrix.setCursor(x, 0);
      matrix.print(F("CpE<3 CpE CpE CpE CpE CpE CpE CpE CpE"));
      if (--x < -200) {
        x = matrix.width();

      }
      matrix.show();
    }
}

void ledMessage_Blinking(){
    unsigned long currentMillis = millis();  // Get the current time


    if (currentMillis - previousMillis >= messageSpeed_Blinking) {
      previousMillis = currentMillis;  // Save the current time
      // Your code to be executed every 100 milliseconds
      matrix.setTextColor(colors[3]);
      matrix.fillScreen(0);
      matrix.setCursor(x, 0);
      matrix.print(F("PLEASE WAIT"));
      if (--x < -80) {
        x = matrix.width();
        
      }
      matrix.show();
    }
}

void ledMessage_Blinking_Ped(){
    unsigned long currentMillis = millis();  // Get the current time


    if (currentMillis - previousMillis >= messageSpeed_Blinking2) {
      previousMillis = currentMillis;  // Save the current time
      // Your code to be executed every 100 milliseconds
      matrix.setTextColor(colors[3]);
      matrix.fillScreen(0);
      matrix.setCursor(x, 0);
      matrix.print(F("Prepare to stop"));
      if (--x < -100) {
        x = matrix.width();
        
      }
      matrix.show();
    }
}


void ledMessage_Cross(){
    unsigned long currentMillis = millis();  // Get the current time'
    

    if (currentMillis - previousMillis >= messageSpeed_Blinking) {
      previousMillis = currentMillis;  // Save the current time
      // Your code to be executed every 100 milliseconds
      matrix.setTextColor(colors[1]);
      matrix.fillScreen(0);
      matrix.setCursor(x, 0);
      matrix.print(F("CROSS NOW"));
      if (--x < -65) {
        x = matrix.width();

      }
      matrix.show();
    }
}

void countdownAnimation() {
  int delayTime = 1000 / LED_COUNT_CIRCLE; // Calculate delay time for each LED
  static unsigned long previousMillis = 0;

  if (currentLED < LED_COUNT_CIRCLE) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= delayTime) {
      strip.setPixelColor(currentLED, 255, 0, 0); // Set pixel color to "off"
      strip.show();
      previousMillis = currentMillis;
      currentLED++;
    }
  }
}

void countdownAnimation2() {
  int delayTime = cycleTime_Duration*1000 / LED_COUNT_CIRCLE; // Calculate delay time for each LED
  static unsigned long previousMillis = 0;
  static unsigned long previousMillis2 = 0;


  if (currentLED3 < LED_COUNT_CIRCLE-1) {
    unsigned long currentMillis2 = millis();
      if (currentMillis2 - previousMillis2 >= 0) {
        strip.setPixelColor(currentLED3, 0, 255, 0); // Set pixel color to "off"
        if(currentLED3 <= 12) strip.setPixelColor(currentLED3, 255, 255, 0); // Set pixel color to "off"
        if(currentLED3 <= 4) strip.setPixelColor(currentLED3, 255, 0, 0); // Set pixel color to "off"

        strip.show();
        previousMillis2 = currentMillis2;
        currentLED3++;
      }
  }

  if (currentLED2 >= 0) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= delayTime) {
      strip.setPixelColor(currentLED2, 0, 0, 0); // Set pixel color to red (255, 0, 0)

      strip.show();
      previousMillis = currentMillis;
      currentLED2--;
    }
  }

}
