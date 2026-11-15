#include "Nintendo.h"

//Pins for the piezo discs
constexpr uint8_t PIEZO_LEFT = A1;
constexpr uint8_t PIEZO_RIGHT = A0;
//Pin for the mic
constexpr uint8_t CLAP_PIN = A2;
//Pin for the button
constexpr uint8_t START_BTN = 5;

// USE THE DEBUGGER FILE TO CALIBRATE YOUR THRESHOLDS

// Threshold that if passed it will count as a hit on the bongo
constexpr uint16_t TH_PIEZO = 200;
// Threshold that if passed it will count as clap
constexpr uint16_t TH_CLAP = 580;

// We stop 14ms to get the maximum value of the analog data
constexpr uint16_t ANALOG_FRAMES = 2;

uint16_t leftMs = 0;
uint16_t rightMs = 0;

//Structure for data to be sent to console
Gamecube_Data_t data = defaultGamecubeData;
// Pin for the data cable of the physical Gamecube controller cable
CGamecubeConsole GamecubeConsole(8);

CGamecubeController GamecubeController1(7);

bool running = false;
String lastWalkingDirection = "stop";

void setup() {
  //Serial.begin(9600);
  pinMode(PIEZO_LEFT, INPUT);
  pinMode(PIEZO_RIGHT, INPUT);
  pinMode(CLAP_PIN, INPUT);
  pinMode(START_BTN, INPUT_PULLUP);

  GamecubeController1.read();
}

void loop() {
  //Default values
  int clapValue = 128;
  int stickX = 128;
  int maxL = 0;
  int maxR = 0;
  int maxClap = 0;
  bool jump = false;

  //Serial.println(leftMs);
  //Serial.println(rightMs);

  unsigned long timestampMs = millis();

  if (leftMs == 0) {
    if (analogRead(PIEZO_LEFT) > TH_PIEZO) {
      leftMs = timestampMs;
    }
  } else if ((ANALOG_FRAMES * 16) < (timestampMs - leftMs)) {
    leftMs = 0;
  }

  if (rightMs == 0) {
    if (analogRead(PIEZO_RIGHT) > TH_PIEZO) {
      rightMs = timestampMs;
    }
  } else if ((ANALOG_FRAMES * 16) < (timestampMs - rightMs)) {
    rightMs = 0;
  }

  // Consider the bongo hit when the threshold is passed
  bool hitL = leftMs > 0;
  bool hitR = rightMs > 0;
  // When both bongos are hit the A button will be pressed
  jump = hitL && hitR;

  //Calculates the direction Donkey Kong should move
  String direction = "stop";
  if (jump) {
    direction = "jump";
  } else if (hitL) {
    direction = "left";
    stickX = 0;
  } else if (hitR) {
    direction = "right";
    stickX = 255;
  }
  //Serial.println(direction);

  // XOR operator for left or right
  if (hitL ^ hitR) {
    //If Donkey Kong was already moving and is not running, make him run
    if ((lastWalkingDirection == direction && direction != "jump") && !running) {
      // To make him run we stop the joystick for this frame and if the bongo is still being hit the next one he will run
      stickX = 128;
      running = true;
    }
  }

  //Store the direction for the next frame
  lastWalkingDirection = direction;
  if (direction == "stop") {
    running = false;
  }

  //Activate clap and start button
  bool start = digitalRead(START_BTN) == LOW;
  bool clapDetected = analogRead(CLAP_PIN) > TH_CLAP;

  // Sets data for controller
  if (clapDetected) {
    clapValue = 255;
  }
  
  // Set A and B buttons for easier menu navigation
  bool buttonB = false;
  if(start && hitL){
    jump = true;
  }
  if(start && hitR){
    buttonB = true;
  }


  // Prepare the data of the controller
  data.report.origin = 0;

  data.report.a = jump;
  data.report.b = buttonB;
  data.report.x = 0;
  data.report.y = 0;
  data.report.z = 0;
  data.report.start = start;
  data.report.r = 0;
  data.report.l = 0;
  data.report.left = 0;
  data.report.xAxis = stickX;
  data.report.yAxis = 128;
  data.report.cxAxis = 128;
  data.report.cyAxis = clapValue;

  //Send data to controller
  GamecubeConsole.write(data);
}
