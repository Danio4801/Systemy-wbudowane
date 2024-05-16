int pushSwitchPinAddress = 2;

int previousButtonState = HIGH;
int buttonState;
bool isAutoMode = false;
bool isSystemOn = true; // Zmienna do przechowywania stanu systemu
bool longPressHandled = false; // Flaga do kontrolowania przełączenia stanu po długim naciśnięciu
unsigned long buttonPressTime = 0;
const unsigned long longPressDuration = 5000; // 5 seconds

void setup()
{
    Serial.begin(9600);
    pinMode(pushSwitchPinAddress, INPUT_PULLUP); // Użycie wewnętrznego rezystora podciągającego
}

void loop()
{
    buttonState = digitalRead(pushSwitchPinAddress);

    if (buttonState == LOW && previousButtonState == HIGH)
    {
        buttonPressTime = millis(); // Zapisanie czasu wciśnięcia przycisku
        longPressHandled = false; // Resetowanie flagi przy nowym wciśnięciu
    }

    if (buttonState == LOW && !longPressHandled && (millis() - buttonPressTime >= longPressDuration))
    {
        isSystemOn = !isSystemOn; // Zmiana stanu systemu
        if (isSystemOn)
        {
            Serial.println("ON");
        }
        else
        {
            Serial.println("OFF");
        }
        longPressHandled = true; // Ustawienie flagi, aby uniknąć ponownego przełączenia
    }

    if (buttonState == HIGH && previousButtonState == LOW)
    {
        if (!longPressHandled)
        {
            if (isSystemOn) // Zmiana trybu tylko jeśli system jest w stanie ON
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
        }
    }

    previousButtonState = buttonState;
    delay(50);
}
