#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <math.h>

#define MPU_ADDR   0x68
#define NP_PIN     4
#define NP_COUNT   7
#define BUZZER_PIN 9

Adafruit_NeoPixel pixels(NP_COUNT, NP_PIN, NEO_GRB + NEO_KHZ800);

// dead-zone threshold (degrees)
const float TH = 5.0;

// color definitions
const uint32_t ROLL_POS_COLOR   = pixels.Color(0,   255, 0  ); // green
const uint32_t ROLL_NEG_COLOR   = pixels.Color(255, 0,   255); // pink
const uint32_t PITCH_POS_COLOR  = pixels.Color(0,   0,   255); // blue
const uint32_t PITCH_NEG_COLOR  = pixels.Color(255, 255,   0); // yellow
const uint32_t YAW_POS_COLOR    = pixels.Color(0,   0,   255); // blue
const uint32_t YAW_NEG_COLOR    = pixels.Color(255, 0,     0); // red

// IMU/filter vars
float AccErrorRoll = 0, AccErrorPitch = 0;
float GyroErrorX = 0, GyroErrorY = 0, GyroErrorZ = 0;
float gyroAngleX = 0, gyroAngleY = 0, gyroAngleZ = 0;
unsigned long prevTime;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // wake MPU6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);

  calculate_IMU_error();

  pixels.begin();
  pixels.show(); // all off
  pinMode(BUZZER_PIN, OUTPUT);
  prevTime = millis();
}

void loop() {
  // — Read accelerometer —
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);
  float Ax = (Wire.read()<<8 | Wire.read()) / 16384.0;
  float Ay = (Wire.read()<<8 | Wire.read()) / 16384.0;
  float Az = (Wire.read()<<8 | Wire.read()) / 16384.0;

  // compute raw roll & pitch from accel
  float accRoll  = atan2(Ay, Az) * 180.0/PI - AccErrorRoll;
  float accPitch = atan2(-Ax, sqrt(Ay*Ay + Az*Az)) * 180.0/PI - AccErrorPitch;

  // — Read gyro —
  unsigned long now = millis();
  float dt = (now - prevTime) / 1000.0;
  prevTime = now;
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x43);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);
  float Gx = (Wire.read()<<8 | Wire.read()) / 131.0 - GyroErrorX;
  float Gy = (Wire.read()<<8 | Wire.read()) / 131.0 - GyroErrorY;
  float Gz = (Wire.read()<<8 | Wire.read()) / 131.0 - GyroErrorZ;

  // integrate gyro
  gyroAngleX += Gx * dt;
  gyroAngleY += Gy * dt;
  gyroAngleZ += Gz * dt;
  float yaw = gyroAngleZ;

  // complementary filter fusion
  float roll  = 0.96 * gyroAngleX + 0.04 * accRoll;
  float pitch = 0.96 * gyroAngleY + 0.04 * accPitch;

  // — reset drift so LEDs keep responding —
  gyroAngleX = roll;
  gyroAngleY = pitch;

  // debug output
  Serial.print("Roll: ");  Serial.print(roll,  1);
  Serial.print("  Pitch: "); Serial.print(pitch, 1);
  Serial.print("  Yaw: ");   Serial.println(yaw,   1);

  // threshold logic
  bool rPos = (roll  >  TH), rNeg = (roll  < -TH);
  bool pPos = (pitch >  TH), pNeg = (pitch < -TH);
  bool yPos = (yaw   >  TH), yNeg = (yaw   < -TH);

  // clear all axis pixels
  for (int i = 0; i < 6; i++) pixels.setPixelColor(i, 0);

  // Roll → pixels 0 & 1
  if      (rPos) pixels.setPixelColor(0, ROLL_POS_COLOR), pixels.setPixelColor(1, ROLL_POS_COLOR);
  else if (rNeg) pixels.setPixelColor(1, ROLL_NEG_COLOR), pixels.setPixelColor(0, ROLL_NEG_COLOR);

  // Pitch → pixels 2 & 3
  if      (pPos) pixels.setPixelColor(2, PITCH_POS_COLOR), pixels.setPixelColor(3, PITCH_POS_COLOR);
  else if (pNeg) pixels.setPixelColor(3, PITCH_NEG_COLOR), pixels.setPixelColor(2, PITCH_NEG_COLOR);

  // Yaw → pixels 4 & 5
  if      (yPos) pixels.setPixelColor(4, YAW_POS_COLOR),   pixels.setPixelColor(5, YAW_POS_COLOR);
  else if (yNeg) pixels.setPixelColor(5, YAW_NEG_COLOR),   pixels.setPixelColor(4, YAW_NEG_COLOR);

  // pixel 6 stays off
  pixels.setPixelColor(6, 0);

  pixels.show();
  delay(100);
}

void calculate_IMU_error() {
  const int N = 200;
  float sumRoll = 0, sumPitch = 0, sumGx = 0, sumGy = 0, sumGz = 0;
  for (int i = 0; i < N; i++) {
    // read accel
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B); Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDR, 6, true);
    float x = (Wire.read()<<8 | Wire.read()) / 16384.0;
    float y = (Wire.read()<<8 | Wire.read()) / 16384.0;
    float z = (Wire.read()<<8 | Wire.read()) / 16384.0;
    sumRoll  += atan2(y, z) * 180.0/PI;
    sumPitch += atan2(-x, sqrt(y*y + z*z)) * 180.0/PI;

    // read gyro
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x43); Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDR, 6, true);
    sumGx += (Wire.read()<<8 | Wire.read()) / 131.0;
    sumGy += (Wire.read()<<8 | Wire.read()) / 131.0;
    sumGz += (Wire.read()<<8 | Wire.read()) / 131.0;
    delay(5);
  }
  AccErrorRoll  = sumRoll  / N;
  AccErrorPitch = sumPitch / N;
  GyroErrorX    = sumGx    / N;
  GyroErrorY    = sumGy    / N;
  GyroErrorZ    = sumGz    / N;
}
