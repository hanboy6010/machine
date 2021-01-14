#include <Servo.h> // Include servo library
#define trigPin 3
#define echoPin 2

Servo servoLeft;
Servo servoRight;

int start = 0; // 출발점인지 아닌지 판단하는 변수
int stat = 0;  // 차체의 위치가 정류장 안에 있는지 밖에 코스를 돌고 있는지 구분해주는 변수
int SL = 9;
int SR = 10;
int SC = 11;    
int station = 0; //나의 현재 위치
int dest[8] = {6,1,6,2,7,3,1,0}; // 목적지 순서 배열
int len[8] = {42,28,68,76,69,4,26,82}; // 각 목적지 사이 간의 거리
int total_len = 395; // 목적지 간 거리의 총합
int sum_len; // 한 방향으로 진행했을 때의 거리의 합
int remain_len; // 나머지 방향으로 진행했을 때의 거리의 합
int dir = 2; // 1일 때 왼쪽으로 라인트레이싱 진행, 2일 때 오른쪽으로 라인트레이싱 진행
int i = 0; // 배열에서 가리키는 인덱스

int speaker = 5;
int led_R = 4;
int led_L = 6;

int SONAR()  // 초음파 센서를 이용하여 거리 측정하는 함수
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
long microsecondsToCentimeters(long microseconds)  // 초음파 센서를 이용하여 받은 시간을 거리로 변환해주는 함수
{
  return microseconds / 29 / 2;
}
void FORWARD()  // 전진
{
  servoLeft.writeMicroseconds(1530);
  servoRight.writeMicroseconds(1470);
}
void BACK()  // 후진
{
  servoLeft.writeMicroseconds(1470);
  servoRight.writeMicroseconds(1530);
}
void LEFT()  // 왼쪽으로 틀기
{
  servoLeft.writeMicroseconds(1470);
  servoRight.writeMicroseconds(1470);
}
void RIGHT()  // 오른쪽으로 틀기
{
  servoLeft.writeMicroseconds(1543);
  servoRight.writeMicroseconds(1530);
}
void TURN_LEFT()  // 좌회전
{
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1400);
}
void TURN_RIGHT()  // 우회전
{
  servoLeft.writeMicroseconds(1600);
  servoRight.writeMicroseconds(1500);
}
void UTURN()  // 180도 뒤로 회전
{
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1700);
}
void STOP() // 정지
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
  sum_len = 0; // 거리의 합들을 처음에 0으로 초기화
  remain_len = 0;
  int LV = digitalRead(SL);  // 계속해서 적외선 센서를 이용하여 라인 위에 있는지 측정한다.
  int RV = digitalRead(SR);
  int CV = digitalRead(SC);
  
  
  if(LV == HIGH && RV == HIGH)  // 왼쪽 오른쪽 다 라인 위에 있을 때
  {
    if(start == 0 || station == dest[i])  // 시작상태 이거나 현재 위치와 들러야 할 스테이션이 같다면 회전
    {
      if(dir == 1)  // 왼쪽으로 라인트레이싱 진행
      {
        start++; // 시작이 아니기 때문에 start에 1 더해줌 
        TURN_LEFT();
        digitalWrite(led_L, HIGH);
        delay(610);
        digitalWrite(led_L, LOW);
        station++; // 왼쪽으로 라인트레이싱을 진행하면 교차로 하나 지날때마다 현재 상태에 1씩 더해줌
        if(station == 8)  // 만약 현재 상태가 8이면 다시 0으로 초기화 해줌
        {
          station = 0;
        }
      }
      else if(dir == 2)  // 오른쪽으로 라인트레이싱 진행
      {
        start++;  // 시작이 아니기 때문에 start에 1 더해줌 
        TURN_RIGHT();
        digitalWrite(led_R, HIGH);
        delay(610);
        digitalWrite(led_R, LOW);
        station--;  // 오른쪽으로 라인트레이싱을 진행하면 교차로 하나 지날때마다 현재 상태에 1씩 더해줌
        if(station == -1)  // 만약 현재 상태가 음수로 내려가면 다시 최대값인 7로 설정
        {
          station = 7;
        }
      }
    }
    else if(stat == 1)  // 정류장 안에 있으면 현재 상태와 목적지가 같지 않아도 왼쪽 오른쪽 모두 라인에 있으면 회전하도록 설정
    {
      if(dir == 1)  // 왼쪽으로 라인트레이싱 진행
      {
        start++;
        TURN_LEFT();
        digitalWrite(led_L, HIGH);
        delay(610);
        digitalWrite(led_L, LOW);
        station++;  // 왼쪽으로 라인트레이싱을 진행하면 교차로 하나 지날때마다 현재 상태에 1씩 더해줌
        stat = 0;  // 정류장에서 나갈 때 stat을 다시 0으로 설정
        if(station == 8)  // 만약 현재 상태가 8이면 다시 0으로 초기화 해줌
        {
          station = 0;
        }
      }
      else if(dir == 2)  // 오른쪽으로 라인트레이싱 진행
      {
        start++;
        TURN_RIGHT();
        digitalWrite(led_R, HIGH);
        delay(610);
        digitalWrite(led_R, LOW);
        station--;  // 오른쪽으로 라인트레이싱을 진행하면 교차로 하나 지날때마다 현재 상태에 1씩 더해줌
        stat = 0;  // 정류장에서 나갈 때 stat을 다시 0으로 설정
        if(station == -1)  // 만약 현재 상태가 음수로 내려가면 다시 최대값인 7로 설정
        {
          station = 7;
        }
      }
    }
    else  // 교차로인데 현재 상태와 목적지가 같지 않으면 회전하지 않고 그냥 직진하게 만드는 함수
    {
      FORWARD();
      digitalWrite(led_L, HIGH);
      digitalWrite(led_R, HIGH);
      delay(610);
      digitalWrite(led_L, LOW);
      digitalWrite(led_R, LOW);
      
      if(dir == 1)  // 왼쪽으로 라인트레이싱 진행
      {
        station++;  // 왼쪽으로 라인트레이싱을 진행하면 교차로 하나 지날때마다 현재 상태에 1씩 더해줌
        if(station == 8)
        {
          station = 0;
        }
      }
      if(dir == 2)  // 오른쪽으로 라인트레이싱 진행
      {
        station--;  // 오른쪽으로 라인트레이싱을 진행하면 교차로 하나 지날때마다 현재 상태에 1씩 더해줌
        if(station == -1)
        {
          station = 7;
        }
      }
      delay(1000);
    }
  }
  else if(LV == HIGH && RV == LOW)  // 왼쪽 센서에만 라인이 있다고 읽히면 왼쪽으로 틀어주기
  {
    LEFT();
  }
  else if(LV == LOW && RV == HIGH)  // 오른쪽 센서에만 라인이 있다고 읽히면 오른쪽으로 틀어주기
  {
    RIGHT();
  }
  else  // 중앙 센서에만 라인이 읽힐 때
  {
    if(SONAR() <= 5)  // 만약 초움파센서를 이용하여 읽은 거리의 값이 5이하이면
    {
      tone(speaker, 260, 1200);  // 소리를 내고
      UTURN();  // 유턴한다
      delay(1180);  // 정확히 유턴을 하는 시간동안 딜레이를 준다
      FORWARD();  // 그 다음에 서보모터의 동작을 직진으로 바꿔준다
      delay(300);
      if(dir == 1)  // 왼쪽으로 라인트레이싱 진행
      {
        station--;  // 밖으로 나갈 때도 1이 더해지기 때문에 미리 1을 줄여준다
        if(station == -1)
        {
          station = 7;
        }
      }
      else if(dir == 2)  // 오른쪽으로 라인트레이싱 진행
      {
        station++;  // 밖으로 나갈 때도 1이 빼지기 때문에 미리 1을 늘려준다
        if(station == 8)
        {
          station = 0;
        }
      }
      i++;  // 정류장을 방문했기 때문에 다음 정류장을 방문하기 위해 배열의 인덱스를 증가시켜준다
      stat = 1;  // 정류장 안에 있기 때문에 stat을 1로 설정해준다
      if(station < dest[i])  // 현재 있는 정류장이 다음 목적지보다 작으면
      {
        for(int j = station; j < dest[i]; j++)  // 한 방향의 거리 총합을 구한다
        {
          sum_len += len[j];
        }
        remain_len = total_len - sum_len;  // 나머지 방향의 거리 총합을 구한다
        if(remain_len < sum_len)  // 둘 중 거리가 더 작은 쪽으로 진행하기 위해 dir 값을 바꿔준다
        {
          dir = 2;
        }
        else
        {
          dir = 1;
        }
      }
      else  // 현재 있는 정류장이 다음 목적지보다 크면
      {
        for(int j = station; j > dest[i]; j--)  // 한 방향의 거리 총합을 구한다
        {
          sum_len += len[j-1];
        }
        remain_len = total_len - sum_len;  // 나머지 방향의 거리 총합을 구한다
        if(remain_len > sum_len)  // 둘 중 거리가 더 작은 쪽으로 진행하기 위해 dir 값을 바꿔준다
        {
          dir = 2;
        }
        else
        {
          dir = 1;
        }
      }
    }
    else
    {
      FORWARD();  // 초음파 센서로 읽은 값이 5보다 크면 직진으로 진행
    }
  }
}   
