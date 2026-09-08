#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

const int motorFR = 16;
const int motorFL = 17;
const int motorBR = 18;
const int motorBL = 19;
float smoothPitch = 0;
float smoothRoll = 0;
unsigned long previousTime = 0;
const int loopDelay = 20; 

int cmdThrottle = 128;
int cmdPitch = 0;
int cmdRoll = 0;
int cmdYaw = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  if (!mpu.begin()) {
    Serial.println("MPU6050 Failed!");
    while (1) { delay(10); } 
  }
  
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  pinMode(motorFR, OUTPUT);
  pinMode(motorFL, OUTPUT);
  pinMode(motorBR, OUTPUT);
  pinMode(motorBL, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char c = Serial.read();
    
    if (c == 'w') cmdPitch += 10;
    else if (c == 's') cmdPitch -= 10;
    else if (c == 'a') cmdRoll -= 10;
    else if (c == 'd') cmdRoll += 10;
    
    else if (c == 'i') cmdThrottle += 10;
    else if (c == 'k') cmdThrottle -= 10;
    else if (c == 'j') cmdYaw -= 10;
    else if (c == 'l') cmdYaw += 10;

    else if (c == ' ') {
      cmdPitch = 0; cmdRoll = 0; cmdYaw = 0; cmdThrottle = 128;
    }

    else if (c == '\x1B') { 
      delay(5);
      if (Serial.available() && Serial.read() == '[') {
        char arrow = Serial.read();
        if (arrow == 'A') cmdThrottle += 10;
        else if (arrow == 'B') cmdThrottle -= 10;
        else if (arrow == 'D') cmdYaw -= 10;
        else if (arrow == 'C') cmdYaw += 10;
      }
    }
  }

  unsigned long currentTime = millis();
  if (currentTime - previousTime >= loopDelay) {
    previousTime = currentTime; 
    
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    float rawPitch = atan2(a.acceleration.x, a.acceleration.z*-1) * RAD_TO_DEG;
    float rawRoll = atan2(a.acceleration.y, a.acceleration.z*-1) * RAD_TO_DEG;

    smoothPitch = (smoothPitch * 0.8) + (rawPitch * 0.2);
    smoothRoll = (smoothRoll * 0.8) + (rawRoll * 0.2);

    float finalPitch = smoothPitch;
    float finalRoll = smoothRoll;
    if (abs(finalPitch) < 2.0) finalPitch = 0;
    if (abs(finalRoll) < 2.0) finalRoll = 0;

    int pCorr = finalPitch * 6;
    int rCorr = finalRoll * 6;

    int pwmFR = constrain(cmdThrottle + pCorr - rCorr - cmdYaw + cmdPitch - cmdRoll, 0, 255);
    int pwmFL = constrain(cmdThrottle + pCorr + rCorr + cmdYaw + cmdPitch + cmdRoll, 0, 255);
    int pwmBR = constrain(cmdThrottle - pCorr - rCorr + cmdYaw - cmdPitch - cmdRoll, 0, 255);
    int pwmBL = constrain(cmdThrottle - pCorr + rCorr - cmdYaw - cmdPitch + cmdRoll, 0, 255);

    analogWrite(motorFR, pwmFR);
    analogWrite(motorFL, pwmFL);
    analogWrite(motorBR, pwmBR);
    analogWrite(motorBL, pwmBL);
  }
}