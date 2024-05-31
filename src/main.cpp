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

void zMoveUp(int pos)
{
  digitalWrite(dirPinZ, HIGH);
  Serial.println("Z Moving up");
  for (int i = 0; i < stepsPerRevolution * pos; i++)
  {
    digitalWrite(stepPinZ, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPinZ, LOW);
    delayMicroseconds(500);
    if (digitalRead(uLimitZ) == 0)
    {
      Serial.println("Limit switch hit");
      break;
    }
  }
}

void zMoveDown(int pos)
{
  digitalWrite(dirPinZ, LOW);
  Serial.println("Z Moving Down");
  for (int i = 0; i < stepsPerRevolution * pos; i++)
  {
    digitalWrite(stepPinZ, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPinZ, LOW);
    delayMicroseconds(500);
    if (digitalRead(lLimitZ) == 0)
    {
      Serial.println("Limit switch hit");
      break;
    }
  }
}

// X movement
void xMoveUp(int pos)
{
  digitalWrite(dirPinX, HIGH);
  Serial.println("X Move Up");
  for (int i = 0; i < stepsPerRevolution * pos; i++)
  {
    digitalWrite(stepPinX, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPinX, LOW);
    delayMicroseconds(1000);
    if (digitalRead(uLimitX) == 0)
    {
      Serial.println("Limit switch hit");
      break;
    }
  }
}

void xMoveDown(int pos)
{
  digitalWrite(dirPinX, LOW);
  Serial.println("X Move Down");
  for (int i = 0; i < stepsPerRevolution * pos; i++)
  {
    digitalWrite(stepPinX, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPinX, LOW);
    delayMicroseconds(1000);
    if (digitalRead(lLimitX) == 0)
    {
      Serial.println("Limit switch hit");
      break;
    }
  }
}

// Y movement
void yMoveUp(int pos)
{
  digitalWrite(dirPinY, HIGH);
  Serial.println("Y Move Up");
  for (int i = 0; i < stepsPerRevolution * pos; i++)
  {
    digitalWrite(stepPinY, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPinY, LOW);
    delayMicroseconds(1000);
    if (digitalRead(uLimitY) == 0)
    {
      Serial.println("Limit switch hit");
      break;
    }
  }
}

void yMoveDown(int pos)
{
  digitalWrite(dirPinY, LOW);
  Serial.println("Y Move Down");
  for (int i = 0; i < stepsPerRevolution * pos; i++)
  {
    digitalWrite(stepPinY, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPinY, LOW);
    delayMicroseconds(1000);
    if (digitalRead(lLimitY) == 0)
    {
      Serial.println("Limit switch hit");
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

void checkState(String axisName, int pos)
{

  if (axisName == "ZU")
  {
    if (digitalRead(uLimitZ) == 1)
    {
      zMoveUp(pos);
    }
  }
  else if (axisName == "ZD")
  {
    if (digitalRead(lLimitZ) == 1)
    {
      zMoveDown(pos);
    }
  }
  else if (axisName == "XU")
  {
    if (digitalRead(uLimitX) == 1)
    {
      xMoveUp(pos);
    }
  }
  else if (axisName == "XD")
  {
    if (digitalRead(lLimitX) == 1)
    {
      xMoveDown(pos);
    }
  }
  else if (axisName == "YU")
  {
    if (digitalRead(uLimitY) == 1)
    {
      yMoveUp(pos);
    }
  }
  else if (axisName == "YD")
  {
    if (digitalRead(lLimitZ) == 1)
    {
      yMoveDown(pos);
    }
  }
  else
  {
    String message = "There is no axis name such as this....";
    Serial.println(message);
  }
}

boolean IsNumeric(String str)
{
  if (str.length() < 1)
  {
    return false;
  }
  bool bPoint = false;
  for (unsigned char i = 0; i < str.length(); i++)
  {
    if (!(isDigit(str.charAt(i)) || str.charAt(i) == '.') || bPoint)
    {
      return false;
    }
    if (str.charAt(i) == '.')
    {
      bPoint = true;
    };
  }
  return true;
}

void loop()
{
  if (Serial.available() > 0)
  {
    String message = Serial.readStringUntil('\n');

    if (message != "")
    {
      int endString = message.length();
      String axisName = message.substring(0, 2);
      Serial.println(axisName);
      String posString = message.substring(2, endString);
      int pos = 0;
      if (IsNumeric(posString))
      {
        pos = posString.toInt();
      }
      else
      {
        Serial.println("There should not be any numeric in position");
      }
      Serial.println(pos);
      checkState(axisName, pos);
    }
  }
}
