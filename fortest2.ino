#include <Servo.h> // Include servo library
#define trigPin 3
#define echoPin 2

Servo servoLeft;
Servo servoRight;
int status = 0;
int speaker = 5;
int herz = 100;
int SL = 9;
int SR = 10;
int SC = 11;
int sta = 0;
int prev_sta = 0;

int led_R = 4;
int led_L = 6;

int pos = 0;

int SONAR()
{
  long duration, cm;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  return cm;
}
long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
void FORWARD()
{
  servoLeft.writeMicroseconds(1520);
  servoRight.writeMicroseconds(1480);
}
void BACK()
{
  servoLeft.writeMicroseconds(1480);
  servoRight.writeMicroseconds(1520);
}
void LEFT()
{
  servoLeft.writeMicroseconds(1480);
  servoRight.writeMicroseconds(1480);
}
void RIGHT()
{
  servoLeft.writeMicroseconds(1520);
  servoRight.writeMicroseconds(1520);
}
void TURN()
{
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1400);
}
void STOP()
{
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  delay(30);
}

void setup() 
{ 
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led_L, OUTPUT);
  pinMode(led_R, OUTPUT);
  pinMode(SL, INPUT);
  pinMode(SR, INPUT);
  pinMode(SC, INPUT);
  
  
  servoLeft.attach(12);
  servoRight.attach(13);

}

void loop() 
{
  
  int LV = digitalRead(SL);
  int RV = digitalRead(SR);
  int CV = digitalRead(SC);
  
  if(LV == HIGH && RV == HIGH)
  {
    if((pos%2) == 0)
    {
      TURN();
      delay(610);
      pos++;
    }
    else
    {
      FORWARD();
      pos++;
      delay(1000);
    }
  }
  else if(LV == HIGH && RV == LOW)
  {
    LEFT();
  }
  else if(LV == LOW && RV == HIGH)
  {
    RIGHT();
  }
  else
  {
    FORWARD();
  }
}   
