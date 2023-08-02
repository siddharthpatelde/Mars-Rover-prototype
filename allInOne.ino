#include "DHT.h"
#include <MQ2.h>
#include <Wire.h> 
#include <Servo.h>
#define DHTPIN 4     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04

//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

const int buzzerPin = 12;
const int flamePin = 11;
const int servoPin = 10;
int Flame = LOW;

int Analog_Input = A1;
int lpg, co, smoke;
MQ2 mq2(Analog_Input);

Servo myservo;

int led = 13;
int pin = 2;
int value = 0;
int pirState = LOW;

int sensorValue; 

long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

char c = "";
String toStr;
int ch;
void setup() {
  Serial.begin(9600);
  dht.begin();

  myservo.attach(servoPin);
  pinMode(buzzerPin, OUTPUT);
  pinMode(flamePin, INPUT);

  mq2.begin();

  pinMode(led, OUTPUT);
  pinMode(pin, INPUT);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT

  Serial.println("Enter 1 for Flame Sensor");
  Serial.println("Enter 2 for DHT11 Sensor");
  Serial.println("Enter 3 for MQ2 Gas Sensor");
  Serial.println("Enter 4 for PIR Sensor");
  Serial.println("Enter 5 for Soil Moisture");
  Serial.println("Enter 6 for Ultra Sonic");
  while(Serial.available() == 0){
      ch = Serial.parseInt();
    }
  //toStr = String(c);
  //ch = toStr.toInt();
  //ch = c - '0';
  //ch = parseInt(c);
  Serial.print(ch);
}

void loop() {
//  Serial.println("Enter 1 for Flame Sensor");
//  Serial.println("Enter 2 for DHT11 Sensor");
//  Serial.println("Enter 3 for MQ2 Gas Sensor");
//  Serial.println("Enter 4 for PIR Sensor");
//  Serial.println("Enter 5 for Soil Moisture");
//  Serial.println("Enter 6 for Ultra Sonic");
//  if(Serial.available() == 0){
//      ch = Serial.read();
//    }
  switch(ch){
    case 1:
      FlameSensor();
      break;
     case 2:
      DHT11Sensor();
      break;
     case 3:
      MQ2Sensor();
      break;
     case 4:
      PIRSensor();
      break;
     case 5:
      SoilMoistureSensor();
      break;
     case 6:
      UltraSonicSensor();
      break;
     case 0:
      Serial.end();
      break;
  }
}

void FlameSensor(){
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


void DHT11Sensor(){
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F(" Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("C "));
  Serial.print(f);
  Serial.print(F("F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("C "));
  Serial.print(hif);
  Serial.println(F("F"));
}

void MQ2Sensor(){
  float* values= mq2.read(true); //set it false if you don't want to print the values in the Serial
  //lpg = values[0];
  lpg = mq2.readLPG();
  //co = values[1];
  co = mq2.readCO();
  //smoke = values[2];
  smoke = mq2.readSmoke();
//  lcd.setCursor(0,0);
//  lcd.print("LPG:");
//  lcd.print(lpg);
//  lcd.print(" CO:");
//  lcd.print(co);
//  lcd.setCursor(0,1);
//  lcd.print("SMOKE:");
//  lcd.print(smoke);
//  lcd.print(" PPM");
  delay(1000);
}

void PIRSensor(){
  value = digitalRead(pin);

  if (value == HIGH) {
    digitalWrite(led, HIGH);

    if (pirState == LOW) {
      Serial.println("Motion Detected!");
      pirState = HIGH;
    }
  }else{
    digitalWrite(led, LOW);

    if(pirState == HIGH){
      Serial.println("Motion Ended!");
      pirState = LOW;
      }
    }
}

void SoilMoistureSensor(){
  sensorValue = analogRead(A0); 
 Serial.println("Analog Value : ");
 Serial.println(sensorValue);
 delay(1000);
}

void UltraSonicSensor(){
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}
