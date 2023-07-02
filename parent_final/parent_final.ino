#include <Wire.h>

float gChord[] = {98.0, 123.47, 146.83}; //G,B,D,(F? 174.61) 
float dChord[] = {146.83, 185.00, 220.00}; //D,F#,A,(C?  261.63)
float eChord[] = {164.81, 207.65, 246.94}; //E,G#,B,(D? 293.66)
float cChord[] = {130.81, 164.81, 196.00}; //C,E,G,(Bb? 233.08)

float* allChords[] = {gChord, dChord, eChord, cChord}; 
int chord = 0;
int octave = 0; 

float minLightReading = 1023;
float maxLightReading;

void setup() {
  Serial.begin(9600);
  Wire.begin();  // start I2C as master
}


void loop() {
  int octave_potValue = analogRead(A4);  // read octave potentiometer value
  octave = map(octave_potValue, 0, 1023, 0, 9);
  //Serial.println(chord);

  int chord_potValue = analogRead(A3);  // read chord potentiometer value
  chord = map(chord_potValue, 0, 1023, 0, 3);
  //Serial.println(octave);

  int lightReading = analogRead(A4); // read light sensor value
  minLightReading = min(lightReading, minLightReading);   // adding dynamic calibration for sensors
  maxLightReading = max(lightReading, maxLightReading);
  int dynamicLightReading = map(lightReading, minLightReading, maxLightReading, 0, 1);
  bool playTheBeat = (dynamicLightReading > 0);
  Serial.println(dynamicLightReading);

  

  if (playTheBeat){
    for(int i=0; i < 3; i++){
      Wire.beginTransmission(i+4);  // transmit to slave device #i+4 (4,5,6)
      float note = allChords[chord][i]; //take the desired note
      float noteToTone = note * pow(2, octave);
      byte * bytePointer = (byte *) & noteToTone; // get byte pointer to float
      Wire.write(bytePointer, sizeof(float)); // send the note to the matching slave device
      Wire.endTransmission(); // stop transmitting
    }
  }

  //Wire.beginTransmission(0x04);  // transmit to slave device #4
  //Wire.write(potValue / 4);  // scale value to 0-255
  //Wire.endTransmission();  // stop transmitting
  //Wire.beginTransmission(0x05);  // transmit to slave device #5
  //Wire.write(potValue / 4);  // scale value to 0-255
  //Wire.endTransmission();  // stop transmitting
  //Wire.beginTransmission(0x06);  // transmit to slave device #6
  //Wire.write(potValue / 4);  // scale value to 0-255
  //Wire.endTransmission();  // stop transmitting
  //Wire.beginTransmission(0x07);  // transmit to slave device #7
  //Wire.write(potValue / 4);  // scale value to 0-255
  //Wire.endTransmission();  // stop transmitting
  //Serial.println(potValue);


  delay(10);
}
