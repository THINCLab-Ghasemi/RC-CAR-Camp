//Line Tracking IO define
#define LT_M digitalRead(A1)
#define LT_R digitalRead(A0)

#define LEFTPWM 5
#define RIGHTPWM 6
#define DCPOWER 3
#define LEFTDIR 7
#define RIGHTDIR 8

#define carSpeed 50

void forward(){
  analogWrite(LEFTPWM, carSpeed);
  analogWrite(RIGHTPWM, carSpeed);
  digitalWrite(DCPOWER, HIGH);
  //digitalWrite(IN2, LOW);
  digitalWrite(LEFTDIR, HIGH);
  digitalWrite(RIGHTDIR, HIGH);
//  Serial.println("go forward!");
}

void back(){
  analogWrite(LEFTPWM, carSpeed);
  analogWrite(RIGHTPWM, carSpeed);
  digitalWrite(DCPOWER, HIGH);
  //digitalWrite(IN2, HIGH);
  digitalWrite(LEFTDIR, LOW);
  digitalWrite(RIGHTDIR, LOW);
//  Serial.println("go back!");
}

void left(){
  analogWrite(LEFTPWM, carSpeed);
  analogWrite(RIGHTPWM, carSpeed);
  digitalWrite(DCPOWER, HIGH);
  //digitalWrite(IN2, HIGH);
  digitalWrite(LEFTDIR, HIGH);
  digitalWrite(RIGHTDIR, LOW);
//  Serial.println("go left!");
}

void right(){
  analogWrite(LEFTPWM, carSpeed);
  analogWrite(RIGHTPWM, carSpeed);
  digitalWrite(DCPOWER, HIGH);
  //digitalWrite(IN2, LOW);
  digitalWrite(LEFTDIR, LOW);
  digitalWrite(RIGHTDIR, HIGH); 
//  Serial.println("go right!");
} 

void nomove(){
   digitalWrite(LEFTPWM, LOW);
   digitalWrite(RIGHTPWM, LOW);
//   Serial.println("Stop!");
} 


void setup(){
//  Serial.begin(9600);
  pinMode(LT_R,INPUT);
  pinMode(LT_M,INPUT);
  pinMode(LT_L,INPUT);
}

void loop() {
 if(LT_M) {
    forward();
    while(LT_M);
  }
  else if(LT_R) { 
    right();
    while(LT_R);  
  }   
  else if(LT_L){
    left(); 
    while(LT_L);
  }
}
