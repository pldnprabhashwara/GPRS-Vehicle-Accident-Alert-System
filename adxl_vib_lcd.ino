#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD setup (check I2C address: usually 0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ADXL335 pins
const int xPin = A1;
const int yPin = A2;
const int zPin = A3;

// Vibration sensor pin
const int vibrationPin = 2;

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(vibrationPin, INPUT);

  lcd.setCursor(0, 0);
  lcd.print("System Ready");
  delay(2000);
}

void loop() {
  // Read accelerometer
  int xVal = analogRead(xPin);
  int yVal = analogRead(yPin);
  int zVal = analogRead(zPin);

  // Read vibration sensor
  int vibrationState = digitalRead(vibrationPin);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("X:");
  lcd.print(xVal);
  lcd.print(" Y:");
  lcd.print(yVal);

  lcd.setCursor(0, 1);
  lcd.print("Z:");
  lcd.print(zVal);

  // Show vibration status
  if (vibrationState == HIGH) {
    lcd.print(" Vib!");
  } else {
    lcd.print(" -");
  }

  delay(500);
}
