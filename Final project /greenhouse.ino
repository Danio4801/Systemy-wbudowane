#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
#include <Adafruit_AM2320.h>

#define LCD_ADDRESS 0x3F
#define LCD_ROWS 2
#define LCD_COLUMNS 16
#define BACKLIGHT 255

LiquidCrystal_PCF8574 lcdI2C(LCD_ADDRESS);
Adafruit_AM2320 am2320;

// Deklaracja pinu dla czujnika wilgotności gleby
const int soilMoisturePin = A0;

void setup() 
{
    Serial.begin(9600);
    while (!Serial);
    Serial.println("start");
    
    lcdI2C.begin(LCD_COLUMNS, LCD_ROWS);
    lcdI2C.setBacklight(BACKLIGHT);
    
    if (!am2320.begin()) {
        Serial.println("Couldn't find AM2320 sensor");
        while (1);
    }
}

void loop() 
{
    lcdI2C.clear();

    // Odczyt temperatury i wilgotności z AM2320
    float temperature = am2320.readTemperature();
    float humidity = am2320.readHumidity();

    // Odczyt wilgotności gleby z pinu analogowego
    int soilMoistureValue = analogRead(soilMoisturePin);
    float soilMoisturePercent = map(soilMoistureValue, 1020, 0, 0, 100); // Zakładamy, że 0 to maksymalna wilgotnosc a 1200 to sucho 

    if (isnan(temperature) || isnan(humidity)) {
        lcdI2C.print("error");
        lcdI2C.setCursor(0, 1);
        lcdI2C.print("from AM2320");
    } else {
        lcdI2C.setCursor(0, 0);
        lcdI2C.print("Temp: ");
        lcdI2C.print(temperature);
        lcdI2C.print(" C");
        
        lcdI2C.setCursor(0, 1);
        lcdI2C.print("Humidity: ");
        lcdI2C.print(humidity);
        lcdI2C.print(" %");
    }

    delay(2000);  // Wyświetlanie danych przez 2 sekundy

    lcdI2C.clear();

    // Wyświetlanie wilgotności gleby na LCD
    lcdI2C.setCursor(0, 0);
    lcdI2C.print("Soil Moisture:");
    lcdI2C.setCursor(0, 1);
    lcdI2C.print(soilMoisturePercent);
    lcdI2C.print(" %");

    delay(2000);  // Wyświetlanie danych przez 2 sekundy
}
