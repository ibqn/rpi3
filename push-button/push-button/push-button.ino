#include <Arduino.h>


const uint8_t LED_PIN = 13;
const uint8_t BTN_PIN = 9;

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    pinMode(BTN_PIN, INPUT);
    Serial.begin(9600);
    Serial.println("Serial connection ready!");
}

void loop()
{
    boolean state = digitalRead(BTN_PIN);

    if (state == LOW)
    {
      digitalWrite(LED_PIN, LOW);
    }
    else
    {
      digitalWrite(LED_PIN, HIGH);
    }
    delay(100);
    Serial.println(state);
}
