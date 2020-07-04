
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
int stepsPerRevolution = 200; 

// QIRMIZI ledpin Bu led qurgunun xeberdarliq siqnali verme funksiyasini dasiyir
const int ledPin = 7;

// YASIL ledpin Bu led qurgunun acildigi halda, aciq oldugu halda ve baglandigi halda yanacaqdir. Qurgu tamamile baglandiqdan sonra led sonecekdir
const int ledPin2 = 5;

//Su sensoru analog input
const int wlev = A2;

// Ses xeberdarliq sensoru output 6
const int sndPin = 6;
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int zaman = 0;

// vez = qurgunun, lcdnin ardicilligini mueyyen edin deyisken
int vez = 0;
// qurgunun qapaginin baglnmasi ve acilmasi ardiciligini teyin eden deyisken
int ardic = 0;

//timex = millis();
//LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 9, 10, 11, 12);
int stepCount = 0;  


//---------------------------------------------------------------------------------------------------------Setup
void setup() {
Serial.begin(9600);
pinMode(ledPin, OUTPUT);
pinMode(ledPin2, OUTPUT);
pinMode(wlev, INPUT);
pinMode(sndPin, OUTPUT);
// LCD aktiv edilmesi
lcd.begin();
tone(sndPin, 500);
delay(500);
noTone(sndPin);
  // LCD back light on edilmesi
  lcd.backlight();
  lcd.setCursor(0,0);
lcd.print("Qurgunun qapagi :");
lcd.setCursor(0,1);
lcd.print("Baglidir");
}

void update() {

}

//-----------------------------------------------------------------------------------------------------------Loop
void loop() {
// Sensorlarin oxunmasi
  int sensorReading = analogRead(A0);
  int motorSpeed = map(sensorReading, 0, 1023, 0, 100);

// Su seviyyesi sensoru analogdan input
int wlevstatus = analogRead(wlev);


Serial.println(zaman);
if (wlevstatus > 300) {
  if (ardic == 0){
vez = 1;
  }
}
else {
vez = 0;
}

// vez = 1 yeni sensordan inputla qurgunun qapaginin acilmasi prosesi
if (vez ==1) {
digitalWrite(ledPin2, HIGH);
//Ardicilligi mueyyen etmek ucun zamanlama
zaman = zaman + 1;

// Acilmadan evvel siqnalla qapagin acilmasinin xeber edilmesi
if (zaman ==5) {
tone(sndPin, 500);
digitalWrite(ledPin, HIGH);
delay(500);
noTone(sndPin);
digitalWrite(ledPin, LOW);
delay(500);
tone(sndPin, 500);
digitalWrite(ledPin, HIGH);
delay(500);
noTone(sndPin);
digitalWrite(ledPin, LOW);
delay(500);
tone(sndPin, 500);
digitalWrite(ledPin, HIGH);
delay(500);
noTone(sndPin);
digitalWrite(ledPin, LOW);
delay(500);
tone(sndPin, 500);
digitalWrite(ledPin, HIGH);
delay(500);
noTone(sndPin);
digitalWrite(ledPin, LOW);
delay(500);
}

// Step motorun perdenin acilisina gore hereketi
stepsPerRevolution = -200;

myStepper.setSpeed(motorSpeed);
myStepper.step(stepsPerRevolution/100);
if (zaman > 11000) {
stepsPerRevolution = 0;
vez =2;
ardic = 1;

// Acildiqdan sonra siqnalla qapagin tam acildiginin xeber edilmesi
tone(sndPin, 500);
digitalWrite(ledPin, HIGH);
delay(500);
noTone(sndPin);
digitalWrite(ledPin, LOW);
delay(500);
tone(sndPin, 500);
digitalWrite(ledPin, HIGH);
delay(500);
noTone(sndPin);
digitalWrite(ledPin, LOW);
delay(500);
zaman = 0;
}

} 
else if (vez == 0) {
  if (ardic ==1) {
  zaman = zaman + 1;

// Baglanmadan evvel siqnalla qapagin baglanmasinin xeber edilmesi
if (zaman ==5) {
tone(sndPin, 500);
digitalWrite(ledPin, HIGH);
delay(500);
noTone(sndPin);
digitalWrite(ledPin, LOW);
delay(500);
tone(sndPin, 500);
digitalWrite(ledPin, HIGH);
delay(500);
noTone(sndPin);
digitalWrite(ledPin, LOW);
delay(500);
tone(sndPin, 500);
digitalWrite(ledPin, HIGH);
delay(500);
noTone(sndPin);
digitalWrite(ledPin, LOW);
delay(500);
tone(sndPin, 500);
digitalWrite(ledPin, HIGH);
delay(500);
noTone(sndPin);
digitalWrite(ledPin, LOW);
delay(500);
}

// Reverse hereket. Ona gore stepsPerRevolution =  200 olaraq menfi deyer verildi
stepsPerRevolution = 200;
myStepper.setSpeed(motorSpeed);
myStepper.step(stepsPerRevolution/100);
if (zaman > 8200) {
stepsPerRevolution = 0;
ardic = 0;

// Baglandiqdan sonra siqnalla qapagin tam baglanildiginin xeber edilmesi
tone(sndPin, 500);
digitalWrite(ledPin, HIGH);
delay(500);
noTone(sndPin);
digitalWrite(ledPin, LOW);
delay(500);
tone(sndPin, 500);
digitalWrite(ledPin, HIGH);
delay(500);
noTone(sndPin);
digitalWrite(ledPin, LOW);
delay(500);

digitalWrite(ledPin2, LOW);
delay(500);
lcd.setCursor(0,0);
lcd.print("Qurgunun qapagi :");
lcd.setCursor(0,1);
lcd.print("Baglidir");
delay(2000);
lcd.clear();
zaman = 0;
}
  } 
  else {
  }

} 


// LCD - de lazimi datalarin gorunmesi
//Serial.println(wlevstatus);
//lcd.clear();
if (vez == 2) {
lcd.setCursor(0,0);
lcd.print("Qurgunun qapagi :");
lcd.setCursor(0,1);
lcd.print("Aciqdir");
delay(2000);
lcd.noCursor();
lcd.clear();
vez = 3;
}

if (vez == 3) {
lcd.setCursor(0,0);
lcd.print("Su seviyyesi :");
lcd.setCursor(0,1);
lcd.print(wlevstatus);
delay(2000);
lcd.noCursor();
lcd.clear();
vez = 4;
}

if (vez == 4) {
lcd.setCursor(0,0);
lcd.print("Anbar_1 su sev :");
lcd.setCursor(0,1);
lcd.print(wlevstatus);
delay(2000);
lcd.noCursor();
lcd.clear();
vez = 5;
}

if (vez == 5) {
lcd.setCursor(0,0);
lcd.print("Anbar_2 su sev :");
lcd.setCursor(0,1);
lcd.print(wlevstatus);
delay(2000);
lcd.noCursor();
lcd.clear();
vez = 2;
}

}
