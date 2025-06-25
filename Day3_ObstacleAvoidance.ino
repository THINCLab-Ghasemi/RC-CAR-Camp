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
int rightDistance = 0, leftDistance = 0, middleDistance = 0;

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
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(20);
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
    myservo.write(90);  //setservo position according to scaled value
    delay(500);
    middleDistance = Distance_test();

    if(middleDistance <= 20) {    
      stop();
      delay(500);                        
      myservo.write(10);          
      delay(1000);      
      rightDistance = Distance_test();
     
      delay(500);
      myservo.write(90);              
      delay(1000);                                                  
      myservo.write(180);              
      delay(1000);
      leftDistance = Distance_test();
     
      delay(500);
      myservo.write(90);              
      delay(1000);
      if(rightDistance > leftDistance) {
        right();
        delay(360);
      }
      else if(rightDistance < leftDistance) {
        left();
        delay(360);
      }
      else if((rightDistance <= 20) || (leftDistance <= 20)) {
        back();
        delay(180);
      }
      else {
        forward();
      }
    }  
    else {
        forward();
    }                    
}
