const int sensorPin = A1;

void setup() {
    Serial.begin(9600);
}

void loop() {
    int sensorValue = analogRead(sensorPin);
    float voltage = sensorValue * (5.0 / 1023.0);
    float temperatureC = voltage * 100.0;
    Serial.print("Temperatura: ");
    Serial.print(temperatureC);
    Serial.println(" °C");
    delay(1000);
}


