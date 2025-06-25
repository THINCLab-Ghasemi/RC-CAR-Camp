#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards



void setup() {
  myservo.attach(10);  // attaches the servo on pin 10 to the servo object

}

void loop() {
    myservo.write(10);              // tell servo to go to position in variable 'pos'
    delay(3000);                       // waits 15ms for the servo to reach the position
    myservo.write(45);
    delay(3000);
    myservo.write(100);
    delay(3000);
    myservo.write(135);
    delay(3000);
    myservo.write(170);              // tell servo to go to position in variable 'pos'
    delay(3000);                       // waits 15ms for the servo to reach the position
}
