const int trigPin = 2; // Def pinu do wysyłania sygnału ultradźwiękowego
const int echoPin = 3; // Def pinu do odbierania sygnału ultradźwiękowego

const int thresholdMultiplier = 4; //odleglosc - wartosc progrowa
float duration, distance; // Deklaracja zmiennych do przechowywania czasu trwania impulsu oraz odległości

void setup()
{
    pinMode(trigPin, OUTPUT); // Ustawienie pinu trigPin jako wyjście
    pinMode(echoPin, INPUT); // Ustawienie pinu echoPin jako wejście
    Serial.begin(9600); // Inicjalizacja komunikacji szeregowej (do debugowania)

    // Konfiguracja pinów LED
    for (int i = 12; i > 4; i--)
    {
        pinMode(i, OUTPUT); // Ustawienie pinów od 12 do 5 jako wyjścia (do sterowania diodami LED)
    }
}

void loop()
{
    digitalWrite(trigPin, LOW); // Wysłanie impulsu niskiego na pin trigPin
    delayMicroseconds(2); // Poczekanie 2 mikrosekundy
    digitalWrite(trigPin, HIGH); // Wysłanie impulsu wysokiego na pin trigPin
    delayMicroseconds(10); // Poczekanie 10 mikrosekundy
    digitalWrite(trigPin, LOW); // Wyłączenie impulsu na pinie trigPin

    duration = pulseIn(echoPin, HIGH); // Pomiar czasu trwania impulsu na pinie echoPin
    distance = (duration * 0.0340) / 2; // Obliczenie odległości na podstawie czasu trwania impulsu
    Serial.print("Distance: "); // Wyświetlenie komunikatu "Distance: " w monitorze szeregowym
    Serial.println(distance); // Wyświetlenie zmierzonej odległości w monitorze szeregowym

    // Warunek dla mnożnika wartości progowej
    for (int i = 1; i < 10; i++)
    {
        if (distance < (thresholdMultiplier * i))
        {
            digitalWrite(4 + i, HIGH); // Włączenie diody LED, która odpowiada obecnemu wartości mnożnika
        }
        else
        {
            digitalWrite(4 + i, LOW); // Wyłączenie diody LED, która odpowiada obecnemu wartości mnożnika
        }
    }

    delay(50); // Poczekanie 50 milisekund przed kolejną iteracją pętli loop()
}
