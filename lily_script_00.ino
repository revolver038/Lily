
/* LILY IOT SCRIPT 04.07.2020

  The motor is attached to digital pins 8 - 11 of the Arduino.
  A potentiometer is connected to analog input 0.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

*/

//-----------------------------------------------------------------------------------------------Kitabxanalar

//#include <LiquidCrystal.h> // Original lazimsiz
#include <Stepper.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> // Modify edilmis


//---------------------------------------------------------------------------------------------Variable ve sabitler

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int stepsPerRevolution = 200; 
// for your motor
const int ledPin = 7;
//const int ldrPin = A1;
const int wlev = A2;
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 9, 10, 11, 12);
int stepCount = 0;  


//---------------------------------------------------------------------------------------------------------Setup
void setup() {
Serial.begin(9600);
pinMode(ledPin, OUTPUT);
pinMode(wlev, INPUT);

// LCD aktiv edilmesi
  lcd.begin();

  // LCD back light on edilmesi
  lcd.backlight();
}


//-----------------------------------------------------------------------------------------------------------Loop
void loop() {
   // Sensorun oxunmasi
  int sensorReading = analogRead(A0);
 
  int motorSpeed = map(sensorReading, 0, 1023, 0, 100);

  // if (motorSpeed > 0) {
  // myStepper.setSpeed(motorSpeed);

  // myStepper.step(stepsPerRevolution / 100);
  //} 

//int ldrStatus = analogRead(ldrPin);
//if (ldrStatus <=800) { 
//digitalWrite(ledPin, HIGH);
//Serial.println("LDR is DARK, LED is ON");

//}
//else {
//digitalWrite(ledPin, LOW);
//Serial.println("LED OFF");
//myStepper.setSpeed(motorSpeed);
//myStepper.step(2);

// Su seviyyesi sensoru analogdan input
int wlevstatus = analogRead(wlev);
if (wlevstatus > 200) { 
digitalWrite(ledPin, HIGH);

myStepper.setSpeed(motorSpeed);
myStepper.step(2);
}
else {
digitalWrite(ledPin, LOW);

}

// LCD - de lazimi datalarin gorunmesi
Serial.println(wlevstatus);
//lcd.clear();
lcd.setCursor(0,0);
lcd.print("Su seviyyesi :");
lcd.setCursor(0,1);
lcd.print(wlevstatus);
delay(500);
lcd.noCursor();
lcd.clear();
}
