//  MEEN 433 Final Code

// Defining pins for the two motors
int motor1pin1 = 2;
int motor1pin2 = 3;

int motor2pin1 = 5;
int motor2pin2 = 4;

// Defining pins for the sensor
int trigPin = 7;
int echoPin = 8;

// Defining distance variables
int gap = 20;  // the desired ditance between an object and our robot when it stops
int range = 50; // this is the range within which an object should be placed for our robot to identify it

int n = 0; 
int t = 15; // This is a time value (our robot will spin in one direction for this amount of time)
int rand_val = rand()%2;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Motor Stuff
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);

  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  // Sonar Sensor Stuff
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  
}

void loop() {

  rand_val = rand()%2;

  // Turning on the sonar sensor
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = microsecondsToCentimeters(duration);

  //Serial.print(distance);
  //Serial.print("cm");
  //Serial.println();

  //Serial.print("The random value is:");
  //Serial.println(rand_val);

  // Make the robot spin until an object is identified
  
  while(distance > range){
    Serial.println("in the loop");
    n = n+1;
    if(rand_val == 0){
      if(n<t){spin1();}
    else if(n<t*3){spin2();}
    else if(n<t*4){spin1();}
    else if(n>t*4){stopMotors();}
    }
    else{
      if(n<t){spin2();}
      else if(n<t*3){spin1();}
      else if(n<t*4){spin2();}
      else if(n>t*4){stopMotors();}
    }
    
    if(n<4*t){
      Serial.print("n is: ");
      Serial.println(n);
    }
    //spin();
    if(n>4*t){break;}

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW); 
    duration = pulseIn(echoPin, HIGH);
    distance = microsecondsToCentimeters(duration);


    //Serial.print("Distance in the loop: ");
    //Serial.println(distance);
    delay(500);
  }
  //Serial.println("out the loop");
  n = 0;
  
  //stopMotors();
  delay(500);

 // if(distance != gap){runMotors(distance-gap);}
  if(abs(distance - gap) > 1){runMotors(distance-gap);}
  else {stopMotors();}

  }


void spin1(){
    Serial.println("Spinning 1");
    analogWrite(9,255);
    analogWrite(10,255);
    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);

    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);

}

void spin2(){
    Serial.println("Spinning 2");
    analogWrite(9,255);
    analogWrite(10,255);
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);

    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);
  
}

void runMotors(int direction){
    // Turning on the Motors
    if(direction >0)  // Move the robot forward
    {
      Serial.println("Moving forward");
      analogWrite(9,255);
      analogWrite(10,255);
      digitalWrite(motor1pin1, HIGH);
      digitalWrite(motor1pin2, LOW);

      digitalWrite(motor2pin1, HIGH);
      digitalWrite(motor2pin2, LOW);
      //delay(1000);
    }

    else if(direction < 0)  // Move the robot backward
    {
      Serial.println("Moving backward");
      analogWrite(9,255);
      analogWrite(10,255);
      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, HIGH);

      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, HIGH);
      //delay(1000);
    }
}

void stopMotors(){
    Serial.println("Motor Stopped");
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, LOW);

    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, LOW);
    //delay(1000);

}


long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;

  exit(0);
}



























