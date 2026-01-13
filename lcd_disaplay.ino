#include <Wire.h>
#include <LiquidCrystal_I2C.h>
char Q;
// Set the LCD address to 0x27 or 0x3F (depends on your module)
// Try 0x27 first, if display not working try 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();           // Initialize the LCD
  lcd.backlight();      // Turn on the backlight
  lcd.setCursor(0, 0);  // First row, first column
  lcd.print("Hello, World!");
  
  lcd.setCursor(0, 1);  // Second row, first column
  lcd.print("I2C LCD 16x2");
  Serial.begin(9600);
}

void loop() {
  // Nothing here, text will stay on screen
  Serial.available()) {
    Q = Serial.read();
    lcd.print(Q);
  
}
