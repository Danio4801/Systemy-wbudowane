// Setup configuration for digital pins as output.
void setup()
{
    pinMode(3, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(11, OUTPUT);
}

void loop()
{
    up();
    delay(50);
    down();
}

void up(void)
{
    for(int j = 0; j <= 255; j += 15)
    {   
        analogWrite(3, j);
        delay(50); 
        analogWrite(5, j);
        delay(50); 
        analogWrite(6, j);
        delay(50);
        analogWrite(9, j);
        delay(50);
        analogWrite(11, j);
    }
}

void down(void)
{
    for (int j = 255; j >= 0; j -= 15)
    {   
        analogWrite(3, j);
        delay(50); 
        analogWrite(5, j);
        delay(50); 
        analogWrite(6, j);
        delay(50);
        analogWrite(9, j);
        delay(50);
        analogWrite(11, j);
    }
}

