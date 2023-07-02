#include <Wire.h>
float note = 440;
#define SPEAKER_PIN 13

void setup() {
  pinMode(SPEAKER_PIN, OUTPUT);
  Wire.begin(0x05);  // join I2C bus as child device #5
  Wire.onReceive(receiveEvent);  // register event
  Serial.begin(9600);
}

void loop() {
  delay(100);
}

// function that executes whenever data is received from parent
void receiveEvent(int howMany) {
  if (howMany == sizeof(float)) {
    byte buffer[sizeof(float)];
    for (int i = 0; i < sizeof(float); i++) {
      buffer[i] = Wire.read();
    }
    // Reassemble into the original float
    float incoming_float;
    memcpy(&incoming_float, &buffer, sizeof(float));
    note = incoming_float; 
    Serial.println(note);
    tone(SPEAKER_PIN, note);  // play tone on speaker
  }
}
