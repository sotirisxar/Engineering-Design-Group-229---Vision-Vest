// Pin Definitions
int echopinfront = 2; //yellow marked
int trigpinfront = 3; //yellow
int echopinleft = 4; //brown 
int trigpinleft = 5; //orange
int echopinright = 6; //blue marked
int trigpinright = 7; //blue

int motorPinfront = 10; //white
int motorPinright = 11; //green
int motorPinleft = 9; //white


void setup() {
  Serial.begin(9600);

  pinMode(trigpinfront, OUTPUT);
  pinMode(echopinfront, INPUT);
  pinMode(trigpinleft, OUTPUT);
  pinMode(echopinleft, INPUT);
  pinMode(trigpinright, OUTPUT);
  pinMode(echopinright, INPUT);

  pinMode(motorPinfront, OUTPUT);
  pinMode(motorPinright, OUTPUT);
  pinMode(motorPinleft, OUTPUT);

}

long measureDistance(int trigPin, int echoPin) {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

void buzzerResponse(int distance, int motorPin) {
  if (distance <= 100 && distance > 50) {
    analogWrite(motorPin, 100);
  } else if (distance <= 50 && distance > 20) {
    analogWrite(motorPin, 150);
  } else if (distance <= 20) {
    analogWrite(motorPin, 255);
  } else {
    analogWrite(motorPin, 0); //turn off the buzzer
  }
}

void buzzerResponseFront(int distance, int motorPin) {
  if (distance <= 150 && distance > 100) {
    analogWrite(motorPin, 100);
  } else if (distance <= 100 && distance > 50) {
    analogWrite(motorPin, 150);
  } else if (distance <= 50) {
    analogWrite(motorPin, 255);
  } else {
    analogWrite(motorPin, 0); //turn off the buzzer
  }
}


void loop() {
  long distancefront = measureDistance(trigpinfront, echopinfront);
  long distanceleft = measureDistance(trigpinleft, echopinleft);
  long distanceright = measureDistance(trigpinright, echopinright);

  buzzerResponseFront(distancefront, motorPinfront);
  buzzerResponse(distanceright, motorPinright);
  buzzerResponse(distanceleft, motorPinleft);

  //Print distances
  Serial.print("Distance front: ");
  Serial.print(distancefront);
  Serial.print("cm | ");
  Serial.print("Distance left: ");
  Serial.print(distanceleft);
  Serial.println("cm");
  Serial.print("Distance right: ");
  Serial.print(distanceright);
  Serial.print("cm | ");


  delay(500);
}