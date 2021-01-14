#include <Servo.h>

Servo servo1;
Servo servo2;

void setup() 
{
  servo1.attach(12);
  servo2.attach(13);

  servo1.writeMicroseconds(1700);
  servo2.writeMicroseconds(1700);
  delay(1180);
  servo1.writeMicroseconds(1500);
  servo2.writeMicroseconds(1500);
  delay(1180);
  
}

void loop() 
{

}
