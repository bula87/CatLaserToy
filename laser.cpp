#include "VarSpeedServo.h"
#include "laser.h"
#include "config.h"
#include <Arduino.h>

// Global variables and defines
// object initialization
VarSpeedServo servo9g1;
VarSpeedServo servo9g2;

int S1_value1, S1_value2;
int S2_value1, S2_value2;

bool autoplayState = 0;
bool laserState = 0;

const int servoSpeed = 10;
const int seqIntervalDelta = 50;
const int manualyServoMinStep = 5;
const int manualyServoMaxStep = 20;
const int minimalRangeSize = 10;

// Change these parameters to define the rectangular play area
int servo1Min = 80;
int servo1Max = 110;
int servo2Min = 20;
int servo2Max = 50;

int servo1pos = (servo1Min + servo1Max) / 2;
int servo2pos = (servo2Min + servo2Max) / 2;
int delayVal = 300;

bool check_autoplay()
{
  return autoplayState;
}

void pin_init()
{
  servo9g1.attach(SERVO9G1_PIN_SIG);         // 1. attach the servo to correct pin to control it.
  servo9g2.attach(SERVO9G2_PIN_SIG);         // 1. attach the servo to correct pin to control it.
  pinMode(LASER_PIN_S, OUTPUT);
  // start with laser off
  digitalWrite(LASER_PIN_S, laserState);
  servo9g2.write(servo2pos , servoSpeed);
  servo9g1.write(servo1pos , servoSpeed);
}

bool checkCommand(String cmd)
{
  bool res = false;
  if(!check_autoplay()) if(cmd.indexOf("/cmd_toggle") > 0) { toggleLaser(); res = true; }
  if(cmd.indexOf("/cmd_speed_up") > 0) { speedUp(); res = true; }
  if(cmd.indexOf("/cmd_speed_down") > 0) { speedDown(); res = true; }
  if(cmd.indexOf("/cmd_autoplay") > 0) { autoplay(); res = true; }
  //if(cmd.indexOf("/cmd_autoplay_random_pos") > 0) autoplay_randomPos();
  if(cmd.indexOf("/cmd_extend_area") > 0) { extend_area(); res = true; }
  if(cmd.indexOf("/cmd_shrink_area") > 0) { shrink_area(); res = true; }
  if(!check_autoplay()) if(cmd.indexOf("/cmd_manual_up") > 0) { manual_up(); res = true; }
  if(!check_autoplay()) if(cmd.indexOf("/cmd_manual_down") > 0) { manual_down(); res = true; }
  if(!check_autoplay()) if(cmd.indexOf("/cmd_manual_left") > 0) { manual_left(); res = true; }
  if(!check_autoplay()) if(cmd.indexOf("/cmd_manual_right") > 0) { manual_right(); res = true; }
  return res;
}

void toggleLaser()
{
  Serial.println("toggleLaser");
  laserState = !laserState;
  digitalWrite(LASER_PIN_S, laserState);
  Serial.print("Laser: ");
  Serial.println(laserState);
}

void speedUp()
{  
  Serial.println("speedUp");
  if(delayVal > 0) delayVal -= seqIntervalDelta;
  Serial.print("delay: ");
  Serial.println(delayVal);
}

void speedDown()
{  
  Serial.println("speedDown");
  if(delayVal < 1000) delayVal += seqIntervalDelta;
  Serial.print("delay: ");
  Serial.println(delayVal);
}

void autoplay()
{
  Serial.println("autoplay");
  autoplayState = !autoplayState;
  Serial.print("AutoPlay: ");
  Serial.println(autoplayState);
}

// Functionality
void autoplay_randomPos()
{
  Serial.println("autoplay_randomPos");
    servo9g1.write(random(servo1Min, servo1Max), servoSpeed);
    servo9g2.write(random(servo2Min, servo2Max), servoSpeed);
    servo9g1.wait();
    servo9g2.wait();
    delay(random(delayVal, delayVal * 5));
}

void extend_area()
{
    servo1Min -= 5;
    servo1Max += 5;
    servo2Min -= 5;
    servo2Max += 5;

    servo1Min  = constrain(servo1Min, 0, servo1Max);
    servo1Max  = constrain(servo1Max, servo1Min, 180);
    servo2Min  = constrain(servo2Min, 0, servo2Max);
    servo2Max  = constrain(servo2Max, servo2Min, 180);
    Serial.print("Area +: ");
    char buf[20];
    sprintf(buf, "%d,%d,%d,%d", servo1Min, servo1Max, servo2Min, servo2Max);
    Serial.println(buf);
}
  // tighten the servo margins
void shrink_area()
{
    if (servo1Max - servo1Min > minimalRangeSize)
    {
      servo1Min += 5;
      servo1Max -= 5;
    }
    if (servo2Max - servo2Min > minimalRangeSize)
    {
      servo2Min += 5;
      servo2Max -= 5;
    }
    Serial.print("Area -: ");
    char buf[20];
    sprintf(buf, "%d,%d,%d,%d", servo1Min, servo1Max, servo2Min, servo2Max);
    Serial.println(buf);
}

void manual_up()
{
  Serial.println("autoplay_up");
  servo2pos += random(manualyServoMinStep, manualyServoMaxStep);
  servo2pos = constrain(servo2pos, servo2Min, servo2Max);
  servo9g2.write(servo2pos, servoSpeed);
  servo9g2.wait();
  Serial.println(servo2pos);
}

void manual_down()
{
  Serial.println("autoplay_down");
  servo2pos -= random(manualyServoMinStep, manualyServoMaxStep);
  servo2pos = constrain(servo2pos, servo2Min, servo2Max);
  servo9g2.write(servo2pos, servoSpeed);
  servo9g2.wait();
  Serial.println(servo2pos);
}


void manual_left()
{
  Serial.println("autoplay_left");
  servo1pos += random(manualyServoMinStep, manualyServoMaxStep);
  servo1pos = constrain(servo1pos, servo1Min, servo1Max);
  servo9g1.write(servo1pos, servoSpeed);
  servo9g1.wait();
}

void manual_right()
{
  Serial.println("autoplay_right");
  servo1pos -= random(manualyServoMinStep, manualyServoMaxStep);
  servo1pos = constrain(servo1pos, servo1Min, servo1Max);
  servo9g1.write(servo1pos, servoSpeed);
  servo9g1.wait();
}
