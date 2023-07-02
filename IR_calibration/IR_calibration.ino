int max_d = 700;

float min_IR = 1023;
float max_IR;


void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);

}

void loop() {
  int IR_value = analogRead(A0);
  Serial.println(IR_value);

  
  // adding dynamic calibration for sensors
  //min_IR = min(IR_value, min_IR);
  //max_IR = max(IR_value, max_IR);

  if (IR_value < max_d){
    int chord_index = map(IR_value, 0, max_d, 0 ,3);
    Serial.println(chord_index);
    }

}
