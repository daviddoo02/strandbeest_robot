// Define pins for motor control
int motor1Pin1 = 2; // Motor 1 - Forward
int motor1Pin2 = 3; // Motor 1 - Backward

int motor2Pin1 = 5; // Motor 2 - Forward
int motor2Pin2 = 4; // Motor 2 - Backward

// Define pins for the sonar sensor
int trigPin = 7;
int echoPin = 8;
int range = 50; // this is the range within which an object should be placed for our robot to identify it


// Constants for PID control
const int targetDistance = 20; // Target distance in centimeters

// Constants for PID terms
const double Kp = 40; // Proportional gain

void setup() {
  // Initialize motor control pins
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  // Sonar Sensor Stuff
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);

  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Turning on the sonar sensor
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = microsecondsToCentimeters(duration);

  // Print values for debugging (optional)
  //Serial.print("Distance: ");
  //Serial.println(distance);

  // Calculate error (difference between target and current distance)
  int error = targetDistance - distance;
  //Serial.println(error);

  // Calculate the control output using proportional control (P-control)
  double output = Kp * error;

  // Map the output to control the motors
  int motorSpeed1 = constrain(output, -255, 255);
  int motorSpeed2 = constrain(output, -255, 255);

  Serial.print("motor speed: ");
  Serial.println(motorSpeed1);

  // Adjust motor speeds based on the error
  if (error < 0) {
    moveForward(motorSpeed1, motorSpeed2); // Move forward if too far from the target
  } else {
    moveBackward(motorSpeed1, motorSpeed2); // Move backward if too close to the target
  }

  delay(100); // Adjust the delay according to your system's requirements
}

void moveForward(int speed1, int speed2) {
  //Serial.println("Moving forward");
  analogWrite(9, abs(speed1));
  analogWrite(10, abs(speed2));
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);

  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  // Adjust motor speeds as needed for forward movement
}

void moveBackward(int speed1, int speed2) {
  //Serial.println("Moving backward");
  analogWrite(9, abs(speed1));
  analogWrite(10, abs(speed2));
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);

  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  // Adjust motor speeds as needed for backward movement
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;

  exit(0);
}
