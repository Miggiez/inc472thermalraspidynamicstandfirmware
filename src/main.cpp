#include <Arduino.h>

// stepper motor
const int dirPinZ = 2;
const int stepPinZ = 3;
const int dirPinX = 4;
const int stepPinX = 5;
const int dirPinY = 7;
const int stepPinY = 8;

// limit switch
const int uLimitZ = 9;
const int lLimitZ = 10;
const int uLimitX = 11;
const int lLimitX = 12;
const int uLimitY = A0;
const int lLimitY = A3;

// constant
const long stepsPerRevolution = 200;

void setup()
{

  Serial.begin(9600);

  // stepper motor setup
  pinMode(dirPinZ, OUTPUT);
  pinMode(dirPinX, OUTPUT);
  pinMode(dirPinY, OUTPUT);
  pinMode(stepPinZ, OUTPUT);
  pinMode(stepPinX, OUTPUT);
  pinMode(stepPinY, OUTPUT);

  // limit switch setup
  pinMode(uLimitZ, INPUT_PULLUP);
  pinMode(lLimitZ, INPUT_PULLUP);
  pinMode(uLimitX, INPUT_PULLUP);
  pinMode(lLimitX, INPUT_PULLUP);
  pinMode(uLimitY, INPUT_PULLUP);
  pinMode(lLimitY, INPUT_PULLUP);
}

// Z movement

void zMoveUp()
{
  digitalWrite(dirPinZ, HIGH);
  for (int i = 0; i < stepsPerRevolution * 1; i++)
  {
    digitalWrite(stepPinZ, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPinZ, LOW);
    delayMicroseconds(500);
    if (digitalRead(uLimitZ) == 0)
    {
      break;
    }
  }
}

void upLimitZ()
{
  while (digitalRead(uLimitZ) == 1)
  {
    zMoveUp();
  }
}

void zMoveDown()
{
  digitalWrite(dirPinZ, LOW);
  for (int i = 0; i < stepsPerRevolution * 1; i++)
  {
    digitalWrite(stepPinZ, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPinZ, LOW);
    delayMicroseconds(500);
    if (digitalRead(lLimitZ) == 0)
    {
      break;
    }
  }
}

void lowLimitZ()
{
  while (digitalRead(lLimitZ) == 1)
  {
    zMoveDown();
  }
}

// X movement
void xMoveUp()
{
  digitalWrite(dirPinX, HIGH);
  for (int i = 0; i < stepsPerRevolution * 10; i++)
  {
    digitalWrite(stepPinX, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPinX, LOW);
    delayMicroseconds(1000);
    if (digitalRead(uLimitX) == 0)
    {
      break;
    }
  }
}

void upLimitX()
{
  while (digitalRead(uLimitX) == 1)
  {
    xMoveUp();
  }
}

void xMoveDown()
{
  digitalWrite(dirPinX, LOW);
  for (int i = 0; i < stepsPerRevolution * 10; i++)
  {
    digitalWrite(stepPinX, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPinX, LOW);
    delayMicroseconds(1000);
    if (digitalRead(lLimitX) == 0)
    {
      break;
    }
  }
}

void lowLimitX()
{
  while (digitalRead(lLimitX) == 1)
  {
    xMoveDown();
  }
}

// Y movement
void yMoveUp()
{
  digitalWrite(dirPinY, HIGH);
  for (int i = 0; i < stepsPerRevolution * 10; i++)
  {
    digitalWrite(stepPinY, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPinY, LOW);
    delayMicroseconds(1000);
    if (digitalRead(uLimitY) == 0)
    {
      break;
    }
  }
}

void upLimitY()
{
  while (digitalRead(uLimitY) == 1)
  {
    yMoveUp();
  }
}

void yMoveDown()
{
  digitalWrite(dirPinY, LOW);
  for (int i = 0; i < stepsPerRevolution * 10; i++)
  {
    digitalWrite(stepPinY, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPinY, LOW);
    delayMicroseconds(1000);
    if (digitalRead(lLimitY) == 0)
    {
      break;
    }
  }
}

void lowLimitY()
{
  while (digitalRead(lLimitY) == 1)
  {
    yMoveDown();
  }
}

// Testing

void limitSwitchTest()
{
  int val = digitalRead(lLimitY);
  Serial.println(val);
  delay(1000);
}

void normal()
{
  digitalWrite(dirPinY, HIGH);
  for (int i = 0; i < stepsPerRevolution * 100; i++)
  {
    digitalWrite(stepPinY, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPinY, LOW);
    delayMicroseconds(1000);
  }

  delay(1000);

  digitalWrite(dirPinY, LOW);
  for (int i = 0; i < stepsPerRevolution * 100; i++)
  {
    digitalWrite(stepPinY, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPinY, LOW);
    delayMicroseconds(1000);
  }
  delay(1000);
}

void loop()
{
  // upLimitZ();
  // delay(1000);
  // lowLimitZ();
  // delay(1000);
  upLimitY();
  delay(1000);
  lowLimitY();
  delay(1000);
  // upLimitX();
  // delay(1000);
  // lowLimitX();
  // delay(1000);
  // limitSwitchTest();
  // normal();
}