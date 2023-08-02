#include <MQ2.h>
#include <Wire.h> 
int Analog_Input = A1;
int lpg, co, smoke;

MQ2 mq2(Analog_Input);
void setup(){
  Serial.begin(9600);

}
void loop(){
  float* values= mq2.read(false); //set it false if you don't want to print the values in the Serial
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

//#define MQ2pin (0)
//
//float sensorValue;  //variable to store sensor value
//
//void setup()
//{
//  Serial.begin(9600); // sets the serial port to 9600
//  Serial.println("Gas sensor warming up!");
//  delay(20000); // allow the MQ-6 to warm up
//}
//
//void loop()
//{
//  sensorValue = analogRead(MQ2pin); // read analog input pin 0
//  
//  Serial.print("Sensor Value: ");
//  Serial.print(sensorValue);
//  
//  if(sensorValue > 300)
//  {
//    Serial.print(" | Smoke detected!");
//  }
//  
//  Serial.println("");
//  delay(2000); // wait 2s for next reading
//}
