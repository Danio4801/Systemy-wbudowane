#define pushSwitchPinAddress 2

int previousButtonState = HIGH;
int buttonState;
bool isAutoMode = false;
bool isDeviceOn = false;
unsigned long buttonPressStartTime = 0;

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
        buttonPressStartTime = millis();
    }

    if (buttonState == HIGH && previousButtonState == LOW)
    {
        unsigned long buttonPressDuration = millis() - buttonPressStartTime;

        if (buttonPressDuration >= 4000 && buttonPressDuration <= 10000)
        {
            isDeviceOn = !isDeviceOn;
            if (!isDeviceOn)
            {
                isAutoMode = !isAutoMode;
            }
            if (isDeviceOn)
            {
                Serial.println("Urządzenie włączone");
            }
            else
            {
                Serial.println("Urządzenie wyłączone");
            }
        }
    }

    if (isDeviceOn)
    {
        if (isAutoMode)
        {
            Serial.println("Tryb pracy: Auto");
        }
        else
        {
            Serial.println("Tryb pracy: Manual");
        }
    }

    previousButtonState = buttonState;

    delay(50);
}
