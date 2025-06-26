
#include <Adafruit_NeoPixel.h>

#define PIN 4             
#define NUM_PIXELS 7       

Adafruit_NeoPixel strip(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

int LEFTPWM = 5;
int RIGHTPWM = 6;
int DCPOWER = 3;
int LEFTDIR = 7;
int RIGHTDIR = 8;

void setup() {
  pinMode(LEFTPWM, OUTPUT);
  pinMode(RIGHTPWM, OUTPUT);

  pinMode(DCPOWER, OUTPUT);

  pinMode(LEFTDIR, OUTPUT);
  pinMode(RIGHTDIR, OUTPUT);

   strip.begin();    
  strip.show();    
  randomSeed(analogRead(A0)); 

}


void loop() {
 int chance = random(1000, 6000);

   digitalWrite(DCPOWER, HIGH);
  digitalWrite(LEFTDIR, LOW);
  digitalWrite(RIGHTDIR, HIGH);

  analogWrite(LEFTPWM, 100);
  analogWrite(RIGHTPWM, 100);
  delay(chance);
    digitalWrite(DCPOWER, LOW);

  
  if (chance <= 3500) {
    strip.setPixelColor(0, strip.Color(255, 0, 0));  // Red color
    strip.show();
      digitalWrite(DCPOWER, HIGH);
  digitalWrite(LEFTDIR, HIGH);
  digitalWrite(RIGHTDIR, HIGH);

  analogWrite(LEFTPWM, 100);
  analogWrite(RIGHTPWM, 100);
  delay(2000);
    digitalWrite(DCPOWER, HIGH);
  digitalWrite(LEFTDIR, LOW);
  digitalWrite(RIGHTDIR, LOW);

  analogWrite(LEFTPWM, 100);
  analogWrite(RIGHTPWM, 100);
  delay(2000);
   digitalWrite(DCPOWER, LOW);
 
  } else {
    // Else turn green
    strip.setPixelColor(0, strip.Color(0, 255, 0));  // Green color
    strip.show();
  }

  delay(3000); 

}
