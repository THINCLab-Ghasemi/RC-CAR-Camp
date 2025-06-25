#include <IRremote.h>
int RECV_PIN = 9;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long val;

#define ENA 5
#define ENB 6
#define IN1 3
#define IN2 4
#define IN3 7
#define IN4 8

int maxspeed  = 100;
int turnspeed  = 50;

 void forward(){ 
  analogWrite(ENA,maxspeed);
  analogWrite(ENB,maxspeed);
  digitalWrite(IN1,HIGH);
  //digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,HIGH);
  Serial.println("go forward!");
}
void back(){
  analogWrite(ENA,100);
  analogWrite(ENB,100);
  digitalWrite(IN1,HIGH);
  //digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  Serial.println("go back!");
}
void left(){
  analogWrite(ENA,turnspeed);
  analogWrite(ENB,turnspeed);
  digitalWrite(IN1,HIGH);
  //digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW); 
  Serial.println("go left!");
}
void right(){
  analogWrite(ENA,turnspeed);
  analogWrite(ENB,turnspeed);
  digitalWrite(IN1,HIGH);
  //digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  Serial.println("go right!");
}
void nomove(){
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  Serial.println("STOP!");  
}

void setup()
{
  Serial.begin(9600);
  Serial.println("connected");
  irrecv.enableIRIn(); // Start the receiver
}

void loop()
{
  if (irrecv.decode(&results))
    {
     val = results.value;
     Serial.println(val);
     if (val == 16736925) //button up arrow
     {
      //Serial.println("forward");
      forward();
      delay(500);
     }
     if (val == 16754775) //button down arrow
     {
      //Serial.println("backwards");
      back();
      delay(500);
     }
     if (val == 16720605) //button left arrow
     {
      //Serial.println("left");
      left();
      delay(500);
     }
     if (val == 16761405)// "button right arrow"
     {
      right();
      delay(500);
     }
     if (val == 16712445) // button "ok"
     {
      nomove();
      delay(500);
     }
     if (val == 16738455) // button "1"
     {
      maxspeed = 150;
     }
     if (val == 16724175) // button "4"
     {
      
     }
     //CREATE TWO NEW BUTTONS
     //BUTTON "2", maxspeed is 100
     //BUTTON "3", maxspeed is 200
     //BUTTON "4", increase maxspeed
     //Button "5", decrease maxspeed
     irrecv.resume(); // Receive the next value
    }
}
