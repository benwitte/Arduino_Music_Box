#include <Wire.h>
float note = 440;
#define SPEAKER_PIN 13

void setup() {
  pinMode(SPEAKER_PIN, OUTPUT);
  Wire.begin(0x04);  // join I2C bus as child device #4
  Wire.onReceive(receiveEvent);  // register event
  Serial.begin(9600);
}

void loop() {
  delay(100);
}

// function that executes whenever data is received from parent
void receiveEvent(int howMany) {
  while (Wire.available()) {
    note = Wire.read();  // read the incoming byte
    Serial.println(note);
    tone(SPEAKER_PIN, note);  // play tone on speaker
  }
}
