//////////////////////////////////////////////////////
////Ultrasonic Pins Definition, here we specify pin usage for our tivaC Board
//
//const int echo_left = 14, Trig_left = 13;  //Pin connections for Left Ultrasonic
//const int echo_right = 17, Trig_right = 8; // Pin connections for right ultrasonic
//
//////////////////////////////////////////////////////
////Time Update Variables
//
//long duration_left, duration_right, cm_left, cm_right;                          //To measure pulse width and distance in cm
//long distance = 0;                          //To return distance of object
//
//////////////////////////////////////////////////////
////Initializing Pins Function
//
//void setup()
//{
//  Serial.begin(115200);     //Initialize Serial COM Port with 115200 buad rate
//  pinMode(Trig_left, OUTPUT);    //Trigger is output since it will send 8 pulses at 40KHz from HC-SR04
//  pinMode(echo_left, INPUT);     //Echo is input since it will detect the reflected wave from HC-SR04
//  pinMode(Trig_right, OUTPUT);
//  pinMode(echo_right, INPUT);
//}
//
//
//
//////////////////////////////////////////////////////
////Main Loop that will keep on running, it is similar to int main()
//void loop()
//{
//       
//    Update_Ultra_Sonic(); //This function operates HC-SR04
//    delay(10);           //Delay between prints on Serial Monitor
//   
//}
//
//////////////////////////////////////////////////////
////Will update ultrasonic sensors through Serial port
//
//void Update_Ultra_Sonic()
//{
//  //Setting Trig Signal HIGH for 10us to produce burst of 8 pulses at 40KHz
//  digitalWrite(Trig_left, LOW);
//  digitalWrite(Trig_right, LOW);
//  delayMicroseconds(2);
//  digitalWrite(Trig_left, HIGH);
//  digitalWrite(Trig_right, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(Trig_left, LOW);
//  digitalWrite(Trig_right, LOW);
//
//  //digitalRead(anypin/switch) //Use this function to read the state of any Pin/Switch i.e. SW1 and SW2
//
//  duration_left = pulseIn(echo_left, HIGH);
//  duration_right = pulseIn(echo_right, HIGH);
//  cm_left = microsecondsToCentimeters(duration_left);
//  cm_right = microsecondsToCentimeters(duration_right);
//
//
//  
//  //Sending through serial port to print on Monitor
//  Serial.print("Distance Left=");
//  Serial.print("\t");
//  Serial.print(cm_left);
//  Serial.print("\t");
//  Serial.print("Distance Right=");
//  Serial.print("\t");
//  Serial.print(cm_right);
//  Serial.print("\n");  
//  delay(100); 
//}
//
//////////////////////////////////////////////////////
////Conversion of microsecond to centimeter
//long microsecondsToCentimeters(long microseconds)
//{
//// The speed of sound is 340 m/s or 29 microseconds per centimeter.
//
//// convert speed of sound from m/s to cm/us
//// Use the formula:     distance(cm) = speed(cm/us) * time(us)
//// Write distance formula here
//distance = 0.0343  * microseconds;
//
//// We take half of the distance travelled since its a reflected wave
//return distance / 2;
//}


////////////////////////////////////////////////////
//Ultrasonic Pins Definition
const int echo_left = 14, Trig_left = 13;  // Pins for Left Ultrasonic
const int echo_right = 17, Trig_right = 8; // Pins for Right Ultrasonic

////////////////////////////////////////////////////
//Time Update Variables
long duration_left, duration_right, cm_left, cm_right; // Variables for timing and distances

////////////////////////////////////////////////////
// Setup Function
void setup() {
  Serial.begin(115200);             // Initialize Serial COM Port with 115200 baud rate
  pinMode(Trig_left, OUTPUT);       // Trigger is OUTPUT
  pinMode(echo_left, INPUT);        // Echo is INPUT
  pinMode(Trig_right, OUTPUT);      
  pinMode(echo_right, INPUT);

  //Specify pinModes for enA, in1 and in2 for right motor
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // Specify pinModes for enB, in3, and in4 for left motor
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
}

////////////////////////////////////////////////////
// Main Loop
void loop() {
  // Update distances from both sensors
  updateUltrasonic();

  // Delay for stability
  delay(100); 
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
