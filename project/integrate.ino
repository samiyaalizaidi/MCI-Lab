//
//
//////////////////////////////////////////////////////
////Ultrasonic Pins Definition
//const int echo_left = 14, Trig_left = 13;  // Pins for Left Ultrasonic
//const int echo_right = 17, Trig_right = 8; // Pins for Right Ultrasonic
//
//////////////////////////////////////////////////////
////Time Update Variables
//long duration_left, duration_right, cm_left, cm_right; // Variables for timing and distances
//unsigned long lastSensorUpdate = 0; // For sensor update timing
//const unsigned long sensorInterval = 50; // Update sensors every 50ms
//
//////////////////////////////////////////////////////
//// For Motors
//// Motor A, TivaC and L298N connections
//int enA = 40;   // ENABLE pin (PF2) for Motor A PWM -> right wheel
//int in1 = 12;   // IN1 pin (PA3) for Motor A direction -> right wheel
//int in2 = 11;   // IN2 pin (PA2) for Motor A direction -> right wheel 
//
//int enB = 39;   // ENABLE pin (PF3) for Motor B PWM -> left wheel
//int in3 = 9;    // IN3 pin (PA6) for Motor B direction -> left wheel
//int in4 = 10;   // IN4 pin (PA7) for Motor B direction -> left wheel
//
//
//////////////////////////////////////////////////////
//// For Infrared Sensor
//int IR_SENSOR = 28;
//
//////////////////////////////////////////////////////
//// Setup Function
//void setup() {
//  Serial.begin(115200);             // Initialize Serial COM Port with 115200 baud rate
//  pinMode(Trig_left, OUTPUT);       // Trigger is OUTPUT
//  pinMode(echo_left, INPUT);        // Echo is INPUT
//  pinMode(Trig_right, OUTPUT);      
//  pinMode(echo_right, INPUT);
//
//  pinMode(enA, OUTPUT);
//  pinMode(enB, OUTPUT);
//  pinMode(in1, OUTPUT);
//  pinMode(in2, OUTPUT);
//  pinMode(in3, OUTPUT);
//  pinMode(in4, OUTPUT);
//  
//  pinMode(IR_SENSOR, INPUT);  
//}
//
//////////////////////////////////////////////////////
//// Main Loop
//void loop() {
//  unsigned long currentMillis = millis();
//
//  // Update distances at regular intervals
//  if (currentMillis - lastSensorUpdate >= sensorInterval) {
//    lastSensorUpdate = currentMillis;
//    updateUltrasonic();
//  }
//
//  // Control the motors
//  controlMotors();
//}
//
//////////////////////////////////////////////////////
//// Ultrasonic Update Function
//void updateUltrasonic() {
//  // Get distance from the left sensor
//  cm_left = getDistance(Trig_left, echo_left);
//
//  // Short delay to prevent interference
//  delayMicroseconds(100);
//
//  // Get distance from the right sensor
//  cm_right = getDistance(Trig_right, echo_right);
//
//  // Print results
//  Serial.print("Left: ");
//  Serial.print(cm_left);
//  Serial.print(" cm\t");
//
//  Serial.print("Right: ");
//  Serial.print(cm_right);
//  Serial.println(" cm");
//
//  if (cm_left > 15) {
//    Serial.print("Time to turn left\n");
//  }
//}
//
//////////////////////////////////////////////////////
//// Function to Measure Distance from a Sensor
//long getDistance(int trigPin, int echoPin) {
//  long duration, distance_cm;
//
//  // Send a short pulse to the trigger pin
//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(2);
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);
//
//  // Measure the duration of the echo
//  duration = pulseIn(echoPin, HIGH, 30000); // Timeout after 30ms (max ~5 meters)
//
//  if (duration == 0) return 0; // No echo detected
//  distance_cm = (0.0343 * duration) / 2; // Speed of sound: 343 m/s or 0.0343 cm/us
//  return distance_cm;
//}
//
//////////////////////////////////////////////////////
//// Motor Control Function
//void controlMotors() {
//  // Set motor speed
//  analogWrite(enA, 255); // Full speed for right motor
//  analogWrite(enB, 255); // Full speed for left motor
//
//  // Set motor directions
//  digitalWrite(in1, LOW);
//  digitalWrite(in2, HIGH); 
//  digitalWrite(in3, LOW);
//  digitalWrite(in4, HIGH); 
//}

////////////////////////////////////////////////////
// Ultrasonic Pins Definition
const int echo_left = 14, Trig_left = 13;  // Pins for Left Ultrasonic
const int echo_right = 17, Trig_right = 8; // Pins for Right Ultrasonic

////////////////////////////////////////////////////
// Time Update Variables
long duration_left, duration_right, cm_left, cm_right; // Variables for timing and distances
unsigned long lastSensorUpdate = 0; // For sensor update timing
const unsigned long sensorInterval = 50; // Update sensors every 50ms

////////////////////////////////////////////////////
// For Motors
// Motor A, TivaC and L298N connections
int enA = 40;   // ENABLE pin (PF2) for Motor A PWM -> right wheel
int in1 = 12;   // IN1 pin (PA3) for Motor A direction -> right wheel
int in2 = 11;   // IN2 pin (PA2) for Motor A direction -> right wheel 

int enB = 39;   // ENABLE pin (PF3) for Motor B PWM -> left wheel
int in3 = 9;    // IN3 pin (PA6) for Motor B direction -> left wheel
int in4 = 10;   // IN4 pin (PA7) for Motor B direction -> left wheel

////////////////////////////////////////////////////
// For Infrared Sensor
int IR_SENSOR = 28; // Analog pin PE2 (A3)

////////////////////////////////////////////////////
// Setup Function
void setup() {
  Serial.begin(115200);             // Initialize Serial COM Port with 115200 baud rate
  pinMode(Trig_left, OUTPUT);       // Trigger is OUTPUT
  pinMode(echo_left, INPUT);        // Echo is INPUT
  pinMode(Trig_right, OUTPUT);      
  pinMode(echo_right, INPUT);

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  pinMode(IR_SENSOR, INPUT);  // IR sensor pin set as INPUT
}

////////////////////////////////////////////////////
// Main Loop
void loop() {
  unsigned long currentMillis = millis();

  // Update sensors at regular intervals
  if (currentMillis - lastSensorUpdate >= sensorInterval) {
    lastSensorUpdate = currentMillis;
    updateSensors();
  }

  // Control the motors
  controlMotors();
}

////////////////////////////////////////////////////
// Sensor Update Function
void updateSensors() {
  // Get distance from the left ultrasonic sensor
  cm_left = getDistance(Trig_left, echo_left);

  // Short delay to prevent interference
  delayMicroseconds(100);

  // Get distance from the right ultrasonic sensor
  cm_right = getDistance(Trig_right, echo_right);

  // Get IR sensor reading
  int ir_reading = analogRead(IR_SENSOR); // Read analog value from the IR sensor
  float ir_cm = mapIRDistance(ir_reading);
  
  // Print all sensor readings to the Serial Monitor
  Serial.print("Left: ");
  Serial.print(cm_left);
  Serial.print(" cm\t");

  Serial.print("Right: ");
  Serial.print(cm_right);
  Serial.print(" cm\t");

  Serial.print("IR: ");
  Serial.println(ir_cm);

  // Example condition: Take action based on sensor values
  if (cm_left > 15) {
    Serial.println("Action: Turn left");
  } else if (cm_right > 15) {
    Serial.println("Action: Turn right");
  } else {
    Serial.println("Action: Move forward");
  }
}

float mapIRDistance(int ir_value) {
  // This function maps the analog reading to a distance in cm
  // Formula based on the sensor's datasheet or empirical testing
  // For example, for the Sharp GP2Y0A21YK0F sensor:
  // distance = (a * analog_read + b) where 'a' and 'b' are constants derived from the sensor's curve.
  // For simplicity, we can use a simple approximation. You may need to tune this formula.
  
  if (ir_value < 100) {
    return 0; // Return 0 if the sensor is out of range
  }
  float distance = 27.98 * pow(ir_value, -1.15);  // Example formula (this is for specific IR sensors)
  return distance; // Return distance in cm
}


////////////////////////////////////////////////////
// Function to Measure Distance from a Sensor
long getDistance(int trigPin, int echoPin) {
  long duration, distance_cm;

  // Send a short pulse to the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the echo
  duration = pulseIn(echoPin, HIGH, 30000); // Timeout after 30ms (max ~5 meters)

  if (duration == 0) return 0; // No echo detected
  distance_cm = (0.0343 * duration) / 2; // Speed of sound: 343 m/s or 0.0343 cm/us
  return distance_cm;
}

////////////////////////////////////////////////////
// Motor Control Function
void controlMotors() {
  // Set motor speed
  analogWrite(enA, 255); // Full speed for right motor
  analogWrite(enB, 255); // Full speed for left motor

  // Set motor directions
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
}
