#include <AFMotor.h>

#define no_dust 0.35 // 초기값
#define moter1 8
#define moter2 9
#define moterPWM 10
#define sw1 3
#define sw2 4
int v_led=7; // 미세먼지 검출 led

int state=0, now_state=0; // 창문이 닫혀있으면 0, 열려있으면 1

AF_DCMotor motor(3);

void setup() 
{
  motor.setSpeed(100);
  motor.run(RELEASE);
  pinMode(moter1,OUTPUT);
  pinMode(moter2,OUTPUT);
  pinMode(sw1,INPUT);
  pinMode(sw2,INPUT);
  pinMode(v_led, OUTPUT);
  Serial.begin(9600); // 시리얼 통신 시작
}

void loop() 
{
  digitalWrite(v_led, LOW);
  delayMicroseconds(280);
  float vo_value = analogRead(A0); // 미세먼지 데이터 읽기
  delayMicroseconds(40);
  digitalWrite(v_led, HIGH);
  delayMicroseconds(9680);

  float dust = get_dust_density(get_voltage(vo_value)); // 아날로그 값을 미세먼지 농도로 변환
 
  Serial.print(", dust - ");
  Serial.print(dust);
  
  if(digitalRead(sw2) == 0 && dust > 400)  state=1; // 하나라도 감지 되는 순간, state에 1대입
  
  if(now_state==1) { // 창문이 열려 있을때만 - 5초간 데이터 측정
    float dust_sum=0;
    int rain_sum=0;
    
    for(int i=0; i<10; i++) { // 10번 데이터 측정
      digitalWrite(v_led, LOW);
      delayMicroseconds(280);
      float vo_value = analogRead(A0); // 미세먼지 데이터 읽기
      delayMicroseconds(40);
      digitalWrite(v_led, HIGH);
      delayMicroseconds(9680);
      float dust = get_dust_density(get_voltage(vo_value));
      dust_sum += dust;
      
      delay(500);
    }
    dust_sum/=10; // 평균값 구하기
     
    if(dust_sum < 200 && digitalRead(sw1) == 0) { // 5초가 측정한 데이터가 기준에 맞으면 state에 0대입
      state=0;
      Serial.println("The weather is fine for 5 seconds");
    }
  }

  if(state != now_state) { // 상태가 바뀌었을 때
    if(state==0) { // 창문을 열기 위해서 시계 방향으로 회전
      motor.run(FORWARD);
      while(digitalRead(sw2) != 1){

      }
      motor.run(RELEASE);
      Serial.println("open");
    }
    else { // 창문을 닫기 위해서 반시계 방향으로 회전
       motor.run(BACKWARD);
      while(digitalRead(sw1) != 1){

      }
       motor.run(RELEASE);
      Serial.println("close");
    }
    delay(1000);
  }
  now_state = state;
  delay(500);
}

float get_voltage(float value)
{
 // 아날로그 값을 전압 값으로 바꿈
 float V= value * 5.0 / 1024; 
 return V;
}

float get_dust_density(float voltage)
{
 // 데이터 시트에 있는 미세 먼지 농도(ug) 공식 기준
 float dust=(voltage-no_dust) / 0.005;
 return dust;
}
