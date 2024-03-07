// Setup configuration for digital pins as output.
void setup()
{
    for (int i = 12; i > 2; i--)
    {
        pinMode(i, OUTPUT);
    }
}

// Turn off all lights connected to digital pins 3 through 12.
void turnOffAllLEDs()
{
    for (int i = 12; i > 2; i--)
    {
        digitalWrite(i, LOW); // Set pin to LOW, light off.
    }
}

// Main loop that blinks lights in a pattern.
void loop()
{
    // Turn on even-numbered lights.
    for (int i = 12; i > 2; i--)
    {
        if (i % 2 == 0)
        {
            digitalWrite(i, HIGH); // Set pin to HIGH, light on.
        }
    }
    delay(150); // Wait 150 ms
    turnOffAllLEDs(); // function call

    // Turn on odd-numbered lights.
    for (int i = 12; i > 2; i--)
    {
        if (i % 2 != 0)
        {
            digitalWrite(i, HIGH); // Set pin to HIGH, light on.
        }
    }
    delay(150); // Wait for 150 milliseconds.
    turnOffAllLEDs(); // Turn off all lights before repeating the cycle.
}
