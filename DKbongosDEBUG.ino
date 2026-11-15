#include <Arduino.h>

//Pins for the piezo discs
constexpr uint8_t PIEZO_LEFT = A1;
constexpr uint8_t PIEZO_RIGHT = A0;
//Pin for the mic
constexpr uint8_t CLAP_PIN = A2;
//Pin for the button
constexpr uint8_t START_BTN = 5;

// Threshold that if passed it will count as a hit on the bongo
constexpr uint16_t TH_PIEZO = 200;
// Threshold that if passed it will count as clap
constexpr uint16_t TH_CLAP = 580;

void setup() {
  Serial.begin(9600);
  pinMode(PIEZO_LEFT,  INPUT);
  pinMode(PIEZO_RIGHT, INPUT);
  pinMode(CLAP_PIN,    INPUT);
  pinMode(START_BTN,   INPUT_PULLUP);

  Serial.println("Starting debug...");
  Serial.println();
  delay(300);
}

void loop() {
  // Leemos varias veces en ventana corta para captar picos de piezo
  int maxL = 0, maxR = 0;
  unsigned long t0 = millis();

  // We read the input every 16ms (1 game frame) to not saturate the console
  while (millis() - t0 < 16) {
    int l = analogRead(PIEZO_LEFT);
    int r = analogRead(PIEZO_RIGHT);
    if (l > maxL) maxL = l;
    if (r > maxR) maxR = r;
  }

  int clap = analogRead(CLAP_PIN);

  // Check if the inputs pass the threshold
  bool hitL  = maxL > TH_PIEZO;
  bool hitR  = maxR > TH_PIEZO;
  bool start = digitalRead(START_BTN) == LOW;
  bool clapDetected = clap > TH_CLAP;

  // Print through serial the inputs 
  if (hitL) {
    Serial.print("PIEZO LEFT  -> valor: ");
    Serial.println(maxL);
  }
  if (hitR) {
    Serial.print("PIEZO RIGHT    -> valor: ");
    Serial.println(maxR);
  }
  if (clapDetected) {
    Serial.print("MICROPHONE       -> valor: ");
    Serial.println(clap);
  }
  if (start) {
    Serial.println("START BUTTON PRESSED");
  }
}