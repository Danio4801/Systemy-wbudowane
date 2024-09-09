  #include <Wire.h> // Biblioteka do komunikacji I2C
  #include <LCD_I2C.h> // Biblioteka do obsługi wyświetlacza LCD I2C

  // Adres I2C dla wyświetlacza LCD
  LCD_I2C lcd(0x3F, 16, 2); // Inicjalizacja wyświetlacza LCD z adresem 0x3F i rozmiarem 16x2

  // Deklaracje pinów dla przycisków
  const int buttonPin0 = 3;  // D3 - przycisk dla 0
  const int buttonPin1 = 2;  // D2 - przycisk dla 1
  const int buttonPinReset = A1; // A1 - przycisk reset

  // Zmienna do przechowywania wartości binarnej
  int binaryValue = 0; // Przechowywanie wartości binarnej
  int bitCount = 0; // Licznik bitów

  void setup() {
    // Konfiguracja pinów przycisków jako wejścia z podciąganiem
    pinMode(buttonPin0, INPUT_PULLUP); // Konfiguracja D3 jako wejście
    pinMode(buttonPin1, INPUT_PULLUP); // Konfiguracja D2 jako wejście
    pinMode(buttonPinReset, INPUT_PULLUP); // Konfiguracja A1 jako wejście

    // Konfiguracja pinów LED jako wyjścia
    for (int i = 4; i <= 12; i++) {
      pinMode(i, OUTPUT); // Konfiguracja pinów D4 do D12 jako wyjścia
    }

    // Inicjalizacja wyświetlacza LCD
    lcd.begin(); // Inicjalizacja wyświetlacza LCD
    lcd.backlight(); // Włączenie podświetlenia wyświetlacza

    // Inicjalizacja wbudowanej diody LED
    pinMode(13, OUTPUT); // Konfiguracja D13 jako wyjście

    // Wyświetlenie początkowego stanu na LCD
    lcd.setCursor(0, 0); // Ustawienie kursora na pierwszą linię
    lcd.print("DEC: 0"); // Wyświetlenie "DEC: 0" na pierwszej linii
    lcd.setCursor(0, 1); // Ustawienie kursora na drugą linię
    lcd.print("(2)0"); // Wyświetlenie "(2)0" na drugiej linii
  }

  void loop() {
    // Sprawdzenie, czy przycisk 0 został naciśnięty
    if (digitalRead(buttonPin0) == LOW) { // Sprawdzenie, czy przycisk 0 jest wciśnięty
      while (digitalRead(buttonPin0) == LOW); // Czekanie na zwolnienie przycisku
      addBit(0); // Dodanie bitu 0 do wartości binarnej
    }

    // Sprawdzenie, czy przycisk 1 został naciśnięty
    if (digitalRead(buttonPin1) == LOW) { // Sprawdzenie, czy przycisk 1 jest wciśnięty
      while (digitalRead(buttonPin1) == LOW); // Czekanie na zwolnienie przycisku
      addBit(1); // Dodanie bitu 1 do wartości binarnej
    }

    // Sprawdzenie, czy przycisk reset został naciśnięty
    if (digitalRead(buttonPinReset) == LOW) { // Sprawdzenie, czy przycisk reset jest wciśnięty
      while (digitalRead(buttonPinReset) == LOW); // Czekanie na zwolnienie przycisku
      reset(); // Resetowanie wartości binarnej
    }
  }

  void addBit(int bit) {
    // Dodawanie bitu do wartości binarnej
    binaryValue = (binaryValue << 1) | bit; // Przesunięcie w lewo i dodanie bitu
    bitCount++; // Zwiększenie licznika bitów
    updateDisplay(); // Aktualizacja wyświetlacza i panelu LED
  }

  void updateDisplay() {
    // Aktualizacja wyświetlacza LCD
    lcd.clear(); // Czyszczenie wyświetlacza
    lcd.setCursor(0, 0); // Ustawienie kursora na pierwszą linię
    lcd.print("DEC: "); // Wyświetlenie "DEC: " na pierwszej linii
    lcd.print(binaryValue); // Wyświetlenie wartości dziesiętnej

    // Konwersja wartości binarnej na string
    char binString[10]; // Tablica do przechowywania wartości binarnej jako string
    itoa(binaryValue, binString, 2); // Konwersja wartości binarnej na string

    // Wyświetlenie wartości binarnej na drugiej linii
    lcd.setCursor(0, 1); // Ustawienie kursora na drugą linię
    lcd.print("(2)"); // Wyświetlenie "(2)"
    lcd.print(binString); // Wyświetlenie wartości binarnej

    // Aktualizacja panelu LED
    for (int i = 0; i < 9; i++) { // Iteracja przez wszystkie piny LED
      int bit = (binaryValue >> (8 - i)) & 1; // Ekstrakcja odpowiedniego bitu
      digitalWrite(4 + i, bit); // Ustawienie stanu diody LED
    }

    // Sprawdzenie, czy wartość przekroczyła zakres (9 bitów)
    if (bitCount >= 9) { // Sprawdzenie, czy liczba bitów przekroczyła 9
      lcd.clear(); // Czyszczenie wyświetlacza
      lcd.print("zaDuzaLiczbaBin"); // Wyświetlenie komunikatu błędu
      delay(2000); // Czekanie 2 sekundy przed resetem
      reset(); // Resetowanie wartości binarnej
    }
  }

  void reset() {
    // Resetowanie wartości binarnej i licznika bitów
    binaryValue = 0; // Resetowanie wartości binarnej
    bitCount = 0; // Resetowanie licznika bitów
    lcd.clear(); // Czyszczenie wyświetlacza
    lcd.setCursor(0, 0); // Ustawienie kursora na pierwszą linię
    lcd.print("DEC: 0"); // Wyświetlenie "DEC: 0" na pierwszej linii
    lcd.setCursor(0, 1); // Ustawienie kursora na drugą linię
    lcd.print("(2)0"); // Wyświetlenie "(2)0" na drugiej linii

    // Wyłączenie wszystkich diod LED
    for (int i = 4; i <= 12; i++) { // Iteracja przez wszystkie piny LED
      digitalWrite(i, LOW); // Wyłączenie diody LED
    }
  }

  void lightOnboard(void) {
    for (int j = 0; j < 10; j++) { // Miga wbudowaną diodą LED 10 razy
      digitalWrite(13, HIGH); // Włączenie diody LED
      delay(50); // Czekanie 50 ms
      digitalWrite(13, LOW); // Wyłączenie diody LED
    }
  }
