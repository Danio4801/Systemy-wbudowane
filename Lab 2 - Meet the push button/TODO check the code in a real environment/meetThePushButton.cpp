#define pushSwitchPinAddress 2

int previousButtonState = HIGH;
int buttonState;
bool isAutoMode = false;

void setup()
{
    Serial.begin(9600);
    pinMode(pushSwitchPinAddress, INPUT);
}

void loop()
{
    buttonState = digitalRead(pushSwitchPinAddress);

    if (buttonState == LOW && previousButtonState == HIGH)
    {
        isAutoMode = !isAutoMode;
        if (isAutoMode)
        {
            Serial.println("Auto");
        }
        else
        {
            Serial.println("Manual");
        }
    }
    previousButtonState = buttonState;
    delay(50);
}
