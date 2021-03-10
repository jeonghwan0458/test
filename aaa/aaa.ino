int digit = 0;
byte digits[10][7] = {
  {1, 1, 1, 1, 1, 1, 0},
  {0, 1, 1, 0, 0, 0, 0},
  {1, 1, 0, 1, 1, 0, 1},
  {1, 1, 1, 1, 0, 0, 1},
  {0, 1, 1, 0, 0, 1, 1},
  {1, 0, 1, 1, 0, 1, 1},
  {0, 0, 1, 1, 1, 1, 1},
  {1, 1, 1, 0, 0, 0, 0},
  {1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 0, 0, 1, 1},
};
 
const int minusButtonPin = 2;
const int plusButtonPin = 3;
 
void setup() {
  //pin mode setup
  for (int i = 4 ; i < 11 ; i++) {
    
      pinMode(i, OUTPUT);

  }
  pinMode(plusButtonPin,INPUT_PULLUP);
  pinMode(minusButtonPin,INPUT_PULLUP);
  attachInterrupt(1,plus,FALLING);
  attachInterrupt(0,minus,FALLING);
  

}
 
void loop() {
 
  outputDigit(digit);
  delay(200);
}
 
//output 7segment number
void outputDigit(int digit) {
  for (int i = 4 ; i < 11 ; i++) {
    for (int j = 0 ; j < 6 ; j++) {
      digitalWrite(i, digits[digit][i - 4]);
    }
  }
}

void minus(){
    if (digitalRead(minusButtonPin) != LOW) return;
    if (digit == 0) {
      digit = 9;
    }
    else {
      digit--;
    }
  }


void plus(){
    delayMicroseconds(2000);
    if (digitalRead(plusButtonPin) != LOW) return;
    
       if (digit == 9) {
      digit = 0;
    }
    else {
      digit++;
    }
  }
 
