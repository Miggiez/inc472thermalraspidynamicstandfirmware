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

int msgRec;

void setup()
{

  Serial.begin(9600);
  while (!Serial)
  {
    Serial.println("Connection with raspberrypi is not connected");
  }

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
  if (Serial.available() > 0)
  {
    String message = Serial.readStringUntil('\n');
    if (message != "")
    {
      msgRec = message.toInt();
    }
  }
  else
  {
    msgRec = 999;
  }

  switch (msgRec)
  {
  case 1:
    if (digitalRead(uLimitZ) == 1)
    {
      zMoveUp();
    }
    break;
  case 2:
    if (digitalRead(lLimitZ) == 1)
    {
      zMoveDown();
    }
    break;
  case 3:
    if (digitalRead(uLimitX) == 1)
    {
      xMoveUp();
    }
    break;
  case 4:
    if (digitalRead(lLimitX) == 1)
    {
      xMoveDown();
    }
    break;
  case 5:
    if (digitalRead(uLimitY) == 1)
    {
      yMoveUp();
    }
    break;
  case 6:
    if (digitalRead(lLimitZ) == 1)
    {
      yMoveDown();
    }
    break;
  case 0:
    digitalWrite(stepPinZ, LOW);
    digitalWrite(stepPinX, LOW);
    digitalWrite(stepPinY, LOW);
    msgRec = 999;
    break;
  default:
    break;
  }
}