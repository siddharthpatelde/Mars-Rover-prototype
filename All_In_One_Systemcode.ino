#include <DHT.h>
#include <Servo.h>
#include <MQ2.h>

// Sensor pins
#define DHTPIN 4     // DHT11 digital pin
#define echoPin 2    // Ultrasonic Echo pin
#define trigPin 3    // Ultrasonic Trig pin
#define Analog_Input A1 // MQ2 analog pin
#define flamePin 11  // Flame sensor pin

// Sensor objects
DHT dht(DHTPIN, DHT11);
MQ2 mq2(Analog_Input);

// Flame sensor variables
int Flame = LOW;
const int buzzerPin = 12;
const int servoPin = 10;
Servo myservo;

// Function prototypes
void readSoilMoisture();
void readDHT11();
void readUltrasonicSensor();
void readMQ2Sensor();
void readFlameSensor();

void setup() {
  Serial.begin(9600);
  Serial.println("Select a sensor to read:");
  Serial.println("1. Soil Moisture");
  Serial.println("2. DHT11 Temperature and Humidity");
  Serial.println("3. Ultrasonic Sensor");
  Serial.println("4. MQ2 Gas Sensor");
  Serial.println("5. Flame Sensor");
  Serial.println("6. Exit");
  dht.begin();
  myservo.attach(servoPin);
  pinMode(buzzerPin, OUTPUT);
  pinMode(flamePin, INPUT);
}

void loop() {
  if (Serial.available() > 0) {
    int selectedSensor = Serial.parseInt();
    Serial.println(selectedSensor);

    switch (selectedSensor) {
      case 1:
        readSoilMoisture();
        break;
      case 2:
        readDHT11();
        break;
      case 3:
        readUltrasonicSensor();
        break;
      case 4:
        readMQ2Sensor();
        break;
      case 5:
        readFlameSensor();
        break;
      case 6:
        Serial.println("Select a sensor to read:");
        Serial.println("1. Soil Moisture");
        Serial.println("2. DHT11 Temperature and Humidity");
        Serial.println("3. Ultrasonic Sensor");
        Serial.println("4. MQ2 Gas Sensor");
        Serial.println("5. Flame Sensor");
        Serial.println("6. Exit");
        break;
      default:
        Serial.println("Invalid sensor number, try again...");
        break;
    }
  }
}

void readSoilMoisture() {
  int sensorValue;

  Serial.println("Reading Soil Moisture Sensor...");
  while (Serial.available()) Serial.read(); // Flush any remaining characters in the input buffer

  while (true) {
    if (Serial.available() > 0) {
      int input = Serial.parseInt();
      if (input == 6) {
        Serial.println("Select a sensor to read:");
        Serial.println("1. Soil Moisture");
        Serial.println("2. DHT11 Temperature and Humidity");
        Serial.println("3. Ultrasonic Sensor");
        Serial.println("4. MQ2 Gas Sensor");
        Serial.println("5. Flame Sensor");
        Serial.println("6. Exit");
        break;
      }
    }
    sensorValue = analogRead(A0);
    Serial.print("Analog Value : ");
    Serial.println(sensorValue);
    delay(1000);
  }
}

void readDHT11() {
  Serial.println("Reading DHT11 Sensor...");
  while (Serial.available()) Serial.read(); // Flush any remaining characters in the input buffer

  while (true) {
    if (Serial.available() > 0) {
      int input = Serial.parseInt();
      if (input == 6) {
        Serial.println("Select a sensor to read:");
        Serial.println("1. Soil Moisture");
        Serial.println("2. DHT11 Temperature and Humidity");
        Serial.println("3. Ultrasonic Sensor");
        Serial.println("4. MQ2 Gas Sensor");
        Serial.println("5. Flame Sensor");
        Serial.println("6. Exit");
        break;
      }
    }
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float f = dht.readTemperature(true);

    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println("Failed to read from DHT sensor!");
      break;
    }

    float hic = dht.computeHeatIndex(t, h, false);
    
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print("%  Temperature: ");
    Serial.print(t);
    Serial.print("°C ");
    Serial.print(f);
    Serial.print("°F  Heat index: ");
    Serial.print(hic);
    Serial.print("°C ");
    Serial.println("°F");
    delay(2000);
  }
}

void readUltrasonicSensor() {
  long duration;
  int distance;

  Serial.println("Reading Ultrasonic Sensor...");
  while (Serial.available()) Serial.read(); // Flush any remaining characters in the input buffer

  while (true) {
    if (Serial.available() > 0) {
      int input = Serial.parseInt();
      if (input == 6) {
        Serial.println("Select a sensor to read:");
        Serial.println("1. Soil Moisture");
        Serial.println("2. DHT11 Temperature and Humidity");
        Serial.println("3. Ultrasonic Sensor");
        Serial.println("4. MQ2 Gas Sensor");
        Serial.println("5. Flame Sensor");
        Serial.println("6. Exit");
        break;
      }
    }
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(1000);
  }
}

void readMQ2Sensor() {
  int lpg, co, smoke;

  Serial.println("Reading MQ2 Gas Sensor...");
  while (Serial.available()) Serial.read(); // Flush any remaining characters in the input buffer

  while (true) {
    if (Serial.available() > 0) {
      int input = Serial.parseInt();
      if (input == 6) {
        Serial.println("Select a sensor to read:");
        Serial.println("1. Soil Moisture");
        Serial.println("2. DHT11 Temperature and Humidity");
        Serial.println("3. Ultrasonic Sensor");
        Serial.println("4. MQ2 Gas Sensor");
        Serial.println("5. Flame Sensor");
        Serial.println("6. Exit");
        break;
      }
    }
    float* values = mq2.read(true);
    lpg = mq2.readLPG();
    co = mq2.readCO();
    smoke = mq2.readSmoke();
    
    Serial.print("LPG: ");
    Serial.print(lpg);
    Serial.print(" ppm, CO: ");
    Serial.print(co);
    Serial.print(" ppm, Smoke: ");
    Serial.print(smoke);
    Serial.println(" ppm");
    delay(1000);
  }
}

void readFlameSensor() {
  Serial.println("Reading Flame Sensor...");
  while (Serial.available()) Serial.read(); // Flush any remaining characters in the input buffer

  while (true) {
    if (Serial.available() > 0) {
      int input = Serial.parseInt();
      if (input == 6) {
        Serial.println("Select a sensor to read:");
        Serial.println("1. Soil Moisture");
        Serial.println("2. DHT11 Temperature and Humidity");
        Serial.println("3. Ultrasonic Sensor");
        Serial.println("4. MQ2 Gas Sensor");
        Serial.println("5. Flame Sensor");
        Serial.println("6. Exit");
        break;
      }
    }
    Flame = digitalRead(flamePin);
    if (Flame == LOW) {
      Serial.println("Fire!!!");
      digitalWrite(buzzerPin, HIGH);
      myservo.write(180);
    } else {
      Serial.println("No worries");
      digitalWrite(buzzerPin, LOW);
      myservo.write(0);
    }
    delay(1000);
  }
}
