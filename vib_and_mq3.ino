#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // 0x27 is common I2C address

// SIM800L
SoftwareSerial sim800l(10, 11); // RX, TX (SIM800L TX -> D10, RX -> D11)

// Pins
int mq3Pin = A0;        // MQ3 alcohol sensor
int vibrationPin = A1;   // Vibration sensor digital output
int buzzerPin = 3;      // Buzzer

// Thresholds
int alcoholThreshold = 300; 
bool accidentDetected = false;

void setup() {
  Serial.begin(9600);
  sim800l.begin(9600);

  pinMode(mq3Pin, INPUT);
  pinMode(vibrationPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("System Ready");

  delay(2000);
  lcd.clear();
}

void loop() {
  int alcoholValue = analogRead(mq3Pin);
  int vibrationValue =  analogRead(A1);

  lcd.setCursor(0,0);
  lcd.print("Alcohol:");
  lcd.print(alcoholValue);

  lcd.setCursor(0,1);
  lcd.print("vib:");
  lcd.print(vibrationValue);

  // Alcohol detection
  if (alcoholValue > 500) {
    lcd.setCursor(0,1);
    lcd.print("ALCOHOL ALERT  ");
    buzzAlert(2000); // buzzer for 2s
    sendSMS("ALERT: Alcohol detected in vehicle!");
    delay(5000);
  }

  // Accident detection
  if (vibrationValue  > 400) {
    lcd.setCursor(0,1);
    lcd.print("Vib:");
    lcd.print(vibrationValue);
    buzzAlert(3000); // buzzer for 3s
    sendSMS("ALERT: Crash detected! Immediate help required.");
    delay(10000);
  }

  delay(500);
}

void buzzAlert(int duration) {
  digitalWrite(buzzerPin, HIGH);
  delay(duration);
  digitalWrite(buzzerPin, LOW);
}

void sendSMS(String message) {
  sim800l.println("AT+CMGF=1"); // set text mode
  delay(1000);
  sim800l.println("AT+CMGS=\"+94721912028" "" ); // <-- replace with your phone number
  delay(1000);
  sim800l.println(message);
  delay(100);
  sim800l.write(26); // Ctrl+Z
  delay(5000);
}
