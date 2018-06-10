#include <Arduino.h>


const uint8_t LED = 13;
bool state = true;

void setup()
{
    pinMode(LED, OUTPUT);
}

void loop()
{
    digitalWrite(LED, (uint8_t)state);
    delay(1000);
    state = !state;
}
