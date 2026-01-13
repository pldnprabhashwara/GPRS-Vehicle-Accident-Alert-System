#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);


// Pins
int mq3Pin = A0;       // MQ3 alcohol sensor
int vibrationPin = A1; // Vibration sensor analog pin
int buzzerPin = 2;     // Buzzer
int xPin = A2;         // ADXL335 X
int yPin = A3;         // ADXL335 Y

// Thresholds
int alcoholThreshold = 700;
int vibrationThreshold = 550; // vibration sensor limit
int xMin = 350, xMax = 400;
int yMin = 350, yMax = 400;

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

  // SIM module init
  sim800l.println("AT"); delay(1000);
  sim800l.println("AT+CMGF=1"); delay(1000);
  sim800l.println("AT+CNMI=1,2,0,0,0"); delay(1000);
}

void loop() {
  int alcoholValue = analogRead(mq3Pin);
  int vibrationValue = analogRead(vibrationPin);
  int xValue = analogRead(xPin);
  int yValue = analogRead(yPin);
  
  // Serial debug
  Serial.println("Alcohol: "); Serial.print(alcoholValue);
  Serial.println(" | Vibration: "); Serial.print(vibrationValue);
  Serial.println(" | X: "); Serial.print(xValue);
  Serial.println(" Y: "); Serial.print(yValue);

  // Display on LCD
  lcd.setCursor(0,0);
  lcd.print("Alc:");
  lcd.print(alcoholValue);
  lcd.print(" Vib:");
  lcd.print(vibrationValue);

  lcd.setCursor(0,1);
  lcd.print("X:");
  lcd.print(xValue);
  lcd.print(" Y:");
  lcd.print(yValue);

  // Alcohol detection
  if (alcoholValue > alcoholThreshold) {
    lcd.setCursor(0,1);
    lcd.print("ALCOHOL ALERT  ");
    buzzAlert(2000);
    sendSMS("ALERT: Alcohol detected in vehicle!");
    delay(5000);
  }

  // Vibration sensor detection
  if (vibrationValue > vibrationThreshold) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Vibration Alert!");
    buzzAlert(2000);
    sendSMS("ALERT: High vibration detected!");
    delay(5000);
  }

  // Crash / imbalance detection using ADXL335
  if ((xValue <= xMin && xValue >= xMax &&
        yValue <= yMin && yValue >= yMax )) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Crash Detected!");
    lcd.setCursor(0,1);
    lcd.print("X:");
    lcd.print(xValue);
    lcd.print(" Y:");
    lcd.print(yValue);
    buzzAlert(3000);
    sendSMS("ALERT: Crash detected! Vehicle out of balance!");
    delay(100);
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
  sim800l.println("AT+CMGF=1"); 
  delay(500);
  sim800l.println("AT+CMGS=""+94721912028"); // Replace with your number
  delay(500);
  sim800l.print(message);
  delay(500);
  sim800l.write(26); // Ctrl+Z to send
  delay(5000);
}
