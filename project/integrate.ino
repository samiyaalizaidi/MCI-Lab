////////////////////////////////////////////////////
//Ultrasonic Pins Definition
const int echo_left = 14, Trig_left = 13;  // Pins for Left Ultrasonic
const int echo_right = 17, Trig_right = 8; // Pins for Right Ultrasonic

////////////////////////////////////////////////////
//Time Update Variables
long duration_left, duration_right, cm_left, cm_right; // Variables for timing and distances


////////////////////////////////////////////////////
// For Motors
// Motor A, TivaC and L298N connections
int enA = 40;   //ENABLE pin (PF2) for Motor A to provide PWM -> right wheel
int in1 = 12;   //IN1 pin (PA3) for Motor A for direction -> right wheel
int in2 = 11;   //IN2 pin (PA2) for Motor A for direction -> right wheel 

int enB = 39; // ENABLE pin (PF3) for Motor B to provide PWM -> left wheel
int in3 = 9;  // IN3 pin (PA6) for Motor B for direction -> left wheel
int in4 = 10; // IN4 pin (PA7) for Motor B for direction -> left wheel

////////////////////////////////////////////////////
// Setup Function
void setup() {
  Serial.begin(115200);             // Initialize Serial COM Port with 115200 baud rate
  pinMode(Trig_left, OUTPUT);       // Trigger is OUTPUT
  pinMode(echo_left, INPUT);        // Echo is INPUT
  pinMode(Trig_right, OUTPUT);      
  pinMode(echo_right, INPUT);
}

////////////////////////////////////////////////////
// Main Loop
void loop() {
  // Update distances from both sensors
  updateUltrasonic();

  // Delay for stability
  delay(100); 

  analogWrite(enA, 255);
  analogWrite(enB, 255);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 

  fullP_Speed();
}

////////////////////////////////////////////////////
// Ultrasonic Update Function
void updateUltrasonic() {
  // Get distance from the left sensor
  cm_left = getDistance(Trig_left, echo_left);

  // Short delay to prevent interference
  delay(50);

  // Get distance from the right sensor
  cm_right = getDistance(Trig_right, echo_right);

  // Print results
  Serial.print("Distance Left: ");
  Serial.print(cm_left);
  Serial.print(" cm\t");

  Serial.print("Distance Right: ");
  Serial.print(cm_right);
  Serial.println(" cm");
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

  distance_cm = (0.0343 * duration) / 2; // Speed of sound: 343 m/s or 0.0343 cm/us
  return distance_cm;
}

void fullP_Speed() {
    //Generates PWM of 50Hz (20ms total) with Duty Cycle of 100%
    for (int i=0; i<50; i++){
      digitalWrite(enA, HIGH);
      digitalWrite(enB, HIGH);
      delayMicroseconds(20000); // High for 2ms, Duty Cycle of 100%
  }
}
