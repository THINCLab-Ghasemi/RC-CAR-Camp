#include <Servo.h>  //servo library
Servo myservo;      // create servo object to control servo

int Echo = 12;  
int Trig = 13;

#define LEFTPWM 5
#define RIGHTPWM 6
#define DCPOWER 3
#define LEFTDIR 7
#define RIGHTDIR 8
#define carSpeed 100


void forward(){
  analogWrite(LEFTPWM, carSpeed);
  analogWrite(RIGHTPWM, carSpeed);
  digitalWrite(DCPOWER, HIGH);
  digitalWrite(LEFTDIR, HIGH);
  digitalWrite(RIGHTDIR, HIGH);
  Serial.println("Forward");
}

void back() {
  analogWrite(LEFTPWM, carSpeed);
  analogWrite(RIGHTPWM, carSpeed);
  digitalWrite(DCPOWER, HIGH);
  digitalWrite(LEFTDIR, LOW);
  digitalWrite(RIGHTDIR, LOW);
  Serial.println("Back");
}

void left() {
  analogWrite(LEFTPWM, carSpeed);
  analogWrite(RIGHTPWM, carSpeed);
  digitalWrite(DCPOWER, HIGH);
  digitalWrite(LEFTDIR, HIGH);
  digitalWrite(RIGHTDIR, LOW);
  Serial.println("Left");
}

void right() {
  analogWrite(LEFTPWM, carSpeed);
  analogWrite(RIGHTPWM, carSpeed);
  digitalWrite(DCPOWER, HIGH);
  digitalWrite(LEFTDIR, LOW);
  digitalWrite(RIGHTDIR, HIGH);
  Serial.println("Right");
}

void stop() {
  digitalWrite(LEFTPWM, LOW);
  digitalWrite(RIGHTPWM, LOW);
  Serial.println("Stop!");
}

//Ultrasonic distance measurement Sub function
int Distance_test() {
  digitalWrite(Trig, LOW);  
  delay(2);
  digitalWrite(Trig, HIGH);  
  delay(20);
  digitalWrite(Trig, LOW);  
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance *.034/2;      
  return (int)Fdistance;
}  

void setup() {
  myservo.attach(10);  // attach servo on pin 3 to servo object
  Serial.begin(9600);    
  pinMode(Echo, INPUT);    
  pinMode(Trig, OUTPUT);  
  pinMode(DCPOWER, OUTPUT);
  pinMode(LEFTDIR, OUTPUT);
  pinMode(RIGHTDIR, OUTPUT);
  pinMode(LEFTPWM, OUTPUT);
  pinMode(RIGHTPWM, OUTPUT);
  stop();
}

void loop() {

  
       
}
