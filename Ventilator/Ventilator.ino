#define gasPin A0
#define moterPin1 8
#define moterPin2 9
#define moterPWM_PIN 10
#define RelayPin 3
#define sw 5
int stace = 0;
int stace_sw = 0;
void setup()
{
	pinMode(moterPin1,OUTPUT);
    pinMode(moterPin2,OUTPUT);
    pinMode(RelayPin1,OUTPUT);
   

}


void loop()
{
    if(gas >= 400)
	digitalWrite(RelayPin1,HIGH);
    delay(5000);
    digitalWrite(RelayPin1,LOW);
    delay(5000);
    
}
