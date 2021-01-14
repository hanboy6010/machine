#include <Servo.h>
#define trigPin 3
#define echoPin 2

Servo servoLeft;
Servo servoRight;

char S_L = A0;
char S_R = A1;
char S_C = A2;
int SL_val, SR_val, SC_val;
float L_cm, R_cm, C_cm;

void setup() 
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servoLeft.attach(12);
  servoRight.attach(13);
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

void loop() 
{
  long duration, cm;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  Serial.print(cm);
  Serial.print(" cm\n");
  SL_val = map(analogRead(S_L), 0, 1023, 0, 5000);
  SR_val = map(analogRead(S_R), 0, 1023, 0, 5000);
  SC_val = map(analogRead(S_C), 0, 1023, 0, 5000);
  L_cm = (24.61 / (SL_val - 0.1696)) * 1000.0;
  R_cm = (24.61 / (SR_val - 0.1696)) * 1000.0;
  C_cm = (24.61 / (SC_val - 0.1696)) * 1000.0;
  Serial.print(L_cm);
  Serial.print(" L_cm");
  Serial.print("\n");
  Serial.print(R_cm);
  Serial.print(" R_cm");
  Serial.print("\n");
  Serial.print(C_cm);
  Serial.print(" C_cm");
  Serial.print("\n");
  delay(1500);
}
