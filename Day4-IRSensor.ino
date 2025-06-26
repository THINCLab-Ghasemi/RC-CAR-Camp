int LeftSensor = A2; // connect ir sensor to arduino pin 2
int MiddleSensor = A1;
int RightSensor = A0; 
void setup() 
{
  Serial.begin(9600);
  pinMode (LeftSensor, INPUT); // sensor pin INPUT
  pinMode (MiddleSensor, INPUT); // sensor pin INPUT
  pinMode (RightSensor, INPUT); // sensor pin INPUT
  //pinMode (LED, OUTPUT); // Led pin OUTPUT
}

void loop()
{
  int LeftStatus = digitalRead (LeftSensor);
  int MiddleStatus = digitalRead (MiddleSensor);
  int RightStatus = digitalRead (RightSensor);
  
  if (LeftStatus == 0)
  {     Serial.println("Left on");
  }
  else if (MiddleStatus == 0)
  {        Serial.println("Middle on");
  }
  else if (RightStatus == 0)
  {    Serial.println("Right on");
  }
  else
  {     Serial.println("Nothing");
  }
  delay(500);
}
