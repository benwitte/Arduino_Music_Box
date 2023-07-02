#include "MPU6050.h";
#include "Wire.h";

MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

//#define OUTPUT_READABLE_ACCELGYRO
#define LED_PIN 13
#define SPEAKER_PIN 11


bool blinkState = false;

void setup() {
    Wire.begin();
    Serial.begin(38400);
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

 // Serial.println("a/g:\t");
  Serial.print(ax); Serial.print("\t");
  Serial.print(ay); Serial.print("\t");
  Serial.print(az); Serial.print("\t");
  Serial.print(gx); Serial.print("\t");
  Serial.print(gy); Serial.print("\t");
  Serial.println(gz);

  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);

  int prev_ax = ax;
  if(ax - prev_ax != 0){
    tone(SPEAKER_PIN, 440, 500);
  }
}