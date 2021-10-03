/*
   Gamepad module provides three different mode namely Digital, JoyStick and Accerleometer.

   You can reduce the size of library compiled by enabling only those modules that you want to
   use. For this first define CUSTOM_SETTINGS followed by defining INCLUDE_modulename.

   Explore more on: https://thestempedia.com/docs/dabble/game-pad-module/
*/

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#define PWM_Left 0
#define PWM_Right 1
#define PWM_Res 8
#define PWM_Freq 1000

#define ServoMotorControl 4

#include <ESP32Servo.h>
#include <MotorProfile.cpp>
#include <Arduino.h>
#include <DabbleESP32.h>


const int Motor1_P = 23;
const int Motor1_N = 22;

const int Motor2_P = 21;
const int Motor2_N = 19;

const int Motor1_E = 5;
const int Motor2_E = 18;

Servo ServoFrontCar;
int ServoValue = 0;

M_Profile CarMotor;
void setup()
{
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ServoFrontCar.setPeriodHertz(50); // Standard 50hz servo
  ServoFrontCar.attach(ServoMotorControl, 500, 2400);

  Serial.begin(9600);
  //motor code pwm setup
  ledcAttachPin(Motor1_E, PWM_Left);
  ledcAttachPin(Motor2_E, PWM_Right);
  ledcSetup(PWM_Left, PWM_Freq, PWM_Res);
  ledcSetup(PWM_Right, PWM_Freq, PWM_Res);

  //motor direction setup
  pinMode(Motor1_P, OUTPUT);
  pinMode(Motor1_N, OUTPUT);
  pinMode(Motor2_P, OUTPUT);
  pinMode(Motor2_N, OUTPUT);
  pinMode(ServoMotorControl, OUTPUT);

  //
  Dabble.begin("MyEsp32"); //set bluetooth name of your device
}

void loop()
{
  Dabble.processInput(); //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  Serial.print("KeyPressed: ");

  if (GamePad.isUpPressed())
  {
    Serial.print("Up");
    digitalWrite(Motor1_P, LOW);
    digitalWrite(Motor1_N, HIGH);
    digitalWrite(Motor2_P, LOW);
    digitalWrite(Motor2_N, HIGH);
    ledcWrite(PWM_Left, CarMotor.GetSpeedValue());
    ledcWrite(PWM_Right, CarMotor.GetSpeedValue());
    delay(100);
  }

  else if (GamePad.isDownPressed())
  {
    Serial.print("Down");
    digitalWrite(Motor1_P, HIGH);
    digitalWrite(Motor1_N, LOW);
    digitalWrite(Motor2_P, HIGH);
    digitalWrite(Motor2_N, LOW);
    ledcWrite(PWM_Left, CarMotor.GetSpeedValue());
    ledcWrite(PWM_Right, CarMotor.GetSpeedValue());
    delay(100);
  }

  else if (GamePad.isLeftPressed())
  {
    Serial.print("Left");
    digitalWrite(Motor1_P, HIGH);
    digitalWrite(Motor1_N, LOW);
    digitalWrite(Motor2_P, LOW);
    digitalWrite(Motor2_N, HIGH);
    ledcWrite(PWM_Left, CarMotor.GetSpeedValue());
    ledcWrite(PWM_Right, CarMotor.GetSpeedValue());
    ServoFrontCar.write(0); //To The Left
    delay(100);
  }

  else if (GamePad.isRightPressed())
  {
    Serial.print("Right");
    digitalWrite(Motor1_P, LOW);
    digitalWrite(Motor1_N, HIGH);
    digitalWrite(Motor2_P, HIGH);
    digitalWrite(Motor2_N, LOW);
    ledcWrite(PWM_Left, CarMotor.GetSpeedValue());
    ledcWrite(PWM_Right, CarMotor.GetSpeedValue());
    ServoFrontCar.write(180); //To The Right
    delay(100);
  }

  else if (GamePad.isSquarePressed())
  {
    Serial.print("Square");
  }

  else if (GamePad.isCirclePressed())
  {
    Serial.print("Circle");
  }

  else if (GamePad.isCrossPressed())
  {
    Serial.print("Cross");
  }

  else if (GamePad.isTrianglePressed())
  {
    Serial.print("Triangle");
  }

  else if (GamePad.isStartPressed())
  {
    CarMotor.SetSpeedValueHigher();
    Serial.print("Start");
    Serial.println((int)(CarMotor.GetSpeedValue()));
  }

  else if (GamePad.isSelectPressed())
  {
    CarMotor.SetSpeedValueLower();
    Serial.print("Select");
    Serial.println((int)(CarMotor.GetSpeedValue()));
  }

  else
  {
    digitalWrite(Motor1_P, LOW);
    digitalWrite(Motor1_N, LOW);
    digitalWrite(Motor2_P, LOW);
    digitalWrite(Motor2_N, LOW);
    ledcWrite(PWM_Left, 0);
    ledcWrite(PWM_Right, 0);
    ServoFrontCar.write(90); //To The Center
    delay(100);
  }
  Serial.print('\t');
}
