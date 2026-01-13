#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pins
int mq3Pin = A0;       // MQ3 alcohol sensor
int vibrationPin = A1; // Vibration sensor analog pin
int buzzerPin = 2;     // Buzzer
int xPin = A2;         // ADXL335 X
int yPin = A3;         // ADXL335 Y
int zPin = A4;         // ADXL335 z
int a = 5000;
// Thresholds
int alcoholThreshold = 460;
int vibrationThreshold = 800;
// vibration sensor limit

// ADXL detection
int xMin = 70, xMax = 70;
int yMin = 45, yMax = 45;
int zMin = 0, zMax = 0;
int xCenter = (xMin + xMax) / 2;
int yCenter = (yMin + yMax) / 2;
int zCenter = (zMin + zMax) / 2;
int tolerance = 25; // how much deviation triggers crash

void setup() {
  Serial.begin(9600);   // Debug serial
  Serial1.begin(9600);  // SIM800L serial

  pinMode(mq3Pin, INPUT);
  pinMode(vibrationPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("System Ready");
  delay(2000);
  lcd.clear();

  // Initialize SIM800L
  Serial1.println("AT"); delay(1000);
  Serial1.println("AT+CMGF=1"); delay(1000);
  Serial1.println("AT+CNMI=1,2,0,0,0"); delay(1000);
}

void loop() {
  int alcoholValue = analogRead(mq3Pin);
  int vibrationValue = analogRead(vibrationPin);
  int xValue = analogRead(xPin);
  int yValue = analogRead(yPin);
  int zValue = analogRead(zPin);

  // Serial debug
  Serial.print("Alcohol: "); Serial.print(alcoholValue);
  Serial.print(" | Vibration: "); Serial.print(vibrationValue);
  Serial.print(" | X: "); Serial.print(xValue);
  Serial.print(" Y: "); Serial.println(yValue);
  Serial.print(" Z: "); Serial.println(zValue);

  // Display on LCD
  lcd.setCursor(0,0);
  lcd.print("Alc:"); lcd.print(alcoholValue);
  lcd.print(" Vib:"); lcd.print(vibrationValue);

  lcd.setCursor(0,1);
  lcd.print("X:"); lcd.print(xValue);
  lcd.print(" Y:"); lcd.print(yValue);
  lcd.print(" Z:"); lcd.print(zValue);

  // Alcohol detection
  if (alcoholValue > alcoholThreshold) {
    lcd.setCursor(0,1);
    lcd.print("ALCOHOL ALERT  ");
    buzzAlert(2000);
    sendSMS("ALERT: Alcohol detected in vehicle!");
    delay(a);
  }

  // Vibration detection
  if (vibrationValue > vibrationThreshold) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Vibration Alert!");
    buzzAlert(2000);
    sendSMS("ALERT: High vibration detected!");
    delay(a);
  }

  // Crash / imbalance detection (simplified)
  if (abs(xValue - xCenter) > tolerance || abs(yValue - yCenter) > tolerance || abs(zValue - zCenter) > tolerance) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Crash Detected!");
    lcd.setCursor(0,1);
    lcd.print("X:"); lcd.print(xValue);
    lcd.print(" Y:"); lcd.print(yValue);
    lcd.print(" Z:"); lcd.print(zValue);
    buzzAlert(3000);
    sendSMS("ALERT: Crash detected! Vehicle out of balance!");
    delay(a);
  }

  delay(500);
}

// Buzzer function
void buzzAlert(int duration) {
  digitalWrite(buzzerPin, HIGH);
  delay(duration);
  digitalWrite(buzzerPin, LOW);
}

// SMS function
void sendSMS(String message) {
  Serial1.println("AT+CMGF=1"); 
  delay(500);
  Serial1.println("AT+CMGS=\"+94721912028\""); // Replace with your number
  delay(500);
  Serial1.print(message);
  delay(500);
  Serial1.write(26); // Ctrl+Z to send
  delay(5000);
}
