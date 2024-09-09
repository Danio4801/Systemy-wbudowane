#include <Wire.h>
#include <LCD_I2C.h>

LCD_I2C lcd(0x3F, 16, 2);

const int buttonPin0 = 3;
const int buttonPin1 = 2;
const int buttonPinReset = A1;

// Bin VAR
unsigned long binaryValue = 0;
int bitCount = 0;

void setup() {
  pinMode(buttonPin0, INPUT_PULLUP);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPinReset, INPUT_PULLUP);

  for (int i = 4; i <= 12; i++) {
    pinMode(i, OUTPUT);
  }

  lcd.begin();
  lcd.backlight();

  pinMode(13, OUTPUT);

  updateDisplay();
}

void loop() {
  if (digitalRead(buttonPin0) == LOW) {
    while (digitalRead(buttonPin0) == LOW);
    addBit(0);
  }

  if (digitalRead(buttonPin1) == LOW) {
    while (digitalRead(buttonPin1) == LOW);
    addBit(1);
  }

  if (digitalRead(buttonPinReset) == LOW) {
    while (digitalRead(buttonPinReset) == LOW);
    reset();
  }
}

void addBit(int bit) {
  binaryValue = (binaryValue << 1) | bit;
  bitCount++;
  updateDisplay();
}

void updateDisplay() {
  char binString[33]; // Tablica do przechowywania wartści bin jako string
  itoa(binaryValue, binString, 2);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("DEC: ");
  lcd.print(binaryValue);

  lcd.setCursor(0, 1);
  char displayString[64]; // Zwiększenie rozmiaru bufora
  snprintf(displayString, sizeof(displayString), "(2)%s", binString);

  int len = strlen(displayString);
  for (int pos = 0; pos <= len - 16; pos++) {
    lcd.setCursor(0, 1);
    lcd.print(displayString + pos);
    delay(250);
  }

  for (int i = 0; i < 9; i++) {
    int bit = (binaryValue >> (8 - i)) & 1;
    digitalWrite(4 + i, bit);
  }
}

void reset() {
  binaryValue = 0;
  bitCount = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DEC: 0");
  lcd.setCursor(0, 1);
  lcd.print("(2)0");

  for (int i = 4; i <= 12; i++) {
    digitalWrite(i, LOW);
  }
}

void lightOnboard(void) {
  for (int j = 0; j < 10; j++) {
    digitalWrite(13, HIGH);
    delay(50);
    digitalWrite(13, LOW);
  }
}