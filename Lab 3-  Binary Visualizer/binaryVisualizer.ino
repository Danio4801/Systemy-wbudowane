  #include <LCD_I2C.h>

  LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according

  void setup() 
  {
      //Display LCD
      lcd.begin(); // If you are using more I2C devices using the Wire library use lcd.begin(false)
                  // this stop the library(LCD_I2C) from calling Wire.begin()
      lcd.backlight();

      //Led light panel
      for (int i = 12; i > 2; i--) 
      {
          pinMode(i, OUTPUT); // addresses, change according
      }

      //arduino nano control light onboard 
      pinMode(13, OUTPUT);
  }

  void loop() 
  {
    lightOnboard();
    int x = 42; // Our decimal value
    decToBinConversion(x);
  }


    void lightOnboard(void)
    {

      for (int j = 0; j < 10; j++) 
      {
			digitalWrite(13, HIGH);
			delay(50);
			digitalWrite(13, LOW);
      }
    }

void decToBinConversion(int x) {

	//x value check
    if (x <= 0 || x > 1023) 
    {
        lcd.clear(); 
        lcd.print("ERROR: x out of range");
        return; 
    }

    lcd.clear(); 
    
    // Our goal is to print the dec value on the LCD screen 
    lcd.print("DEC: "); //
    lcd.print(x); // 

    //disp the bin value on LED lights
    for (int i = 12; i >= 2; i--) 
    {
		//we are extracting the appropriate bit from the binary representation of var 'x'
        int bit = (x >> (12 - i)) & 1; 
        
        // Set the state of the LED based on the extracted bit value
		digitalWrite(i, bit); // LED set
    }
}
