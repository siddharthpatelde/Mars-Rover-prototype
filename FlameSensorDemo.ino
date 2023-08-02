#include <Servo.h>
const int buzzerPin = 12;
const int flamePin = 11;
const int servoPin = 10;
int Flame = LOW;
Servo myservo;
void setup() 
{
  myservo.attach(servoPin);
  pinMode(buzzerPin, OUTPUT);
  pinMode(flamePin, INPUT);
  Serial.begin(9600);
}

void loop() 
{
  Flame = digitalRead(flamePin);
  if (Flame== LOW)
  {
    Serial.println("Fire!!!");
    digitalWrite(buzzerPin, HIGH);
    myservo.write(180);
  }
  else
  {
    Serial.println("No worries");
    digitalWrite(buzzerPin, LOW);
    myservo.write(0);
  }
}
