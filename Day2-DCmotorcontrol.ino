

//IN LATER CODES WE CALL THESE DIFFERENTLY
int LEFTPWM = 5; //PWMLeft 
int RIGHTPWM = 6; //PWMRight 
int DCPOWER = 3; //POWER 
int LEFTDIR = 7; //LEFT MOTOR DIRECTION
int RIGHTDIR = 8; //RIGHT MOTOR DIRECTION

void FORWARD()
{ digitalWrite(DCPOWER, HIGH);   // Make the power on
  digitalWrite(LEFTDIR, HIGH); //left side motors direction
  digitalWrite(RIGHTDIR, HIGH); //right motor direction
  analogWrite(LEFTPWM, 100); //left motor speed
  analogWrite(RIGHTPWM, 100); //right motor speed
  delay(2000); //units are in milliseconds
}

void STOP(){
  digitalWrite(DCPOWER, LOW);   // Make the power on
  digitalWrite(LEFTDIR, HIGH); //left side motors direction
  digitalWrite(RIGHTDIR, HIGH); //right motor direction
  analogWrite(LEFTPWM, 0); //left motor speed
  analogWrite(RIGHTPWM, 0); //right motor speed
  delay(2000);

}

void BACKWARD(){
  digitalWrite(DCPOWER, HIGH);   // Make the power on
  digitalWrite(LEFTDIR, LOW); //left side motors direction
  digitalWrite(RIGHTDIR, LOW); //right motor direction
  analogWrite(LEFTPWM, 100); //left motor speed
  analogWrite(RIGHTPWM, 100); //right motor speed
  delay(2000); //units are in milliseconds
}






void setup() {
  // put your setup code here, to run once:
  pinMode(LEFTPWM, OUTPUT); //left motor speed
  pinMode(RIGHTPWM, OUTPUT); //right motor speed

  pinMode(DCPOWER, OUTPUT); //motor power
  pinMode(LEFTDIR, OUTPUT); //left motors direction
  pinMode(RIGHTDIR, OUTPUT); //right motor direction

  digitalWrite(DCPOWER, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  //move CAR forward
  
  FORWARD();
  STOP();
  BACKWARD();
  STOP();

  //stop car

}












