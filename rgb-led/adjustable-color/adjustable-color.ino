#include <Arduino.h>


const uint8_t LED_PIN_R = 9;
const uint8_t LED_PIN_G = 10;
const uint8_t LED_PIN_B = 11;
int adc_value;

void setup()
{
    pinMode(LED_PIN_R, OUTPUT);
    pinMode(LED_PIN_G, OUTPUT);
    pinMode(LED_PIN_B, OUTPUT);

    Serial.begin(9600);
    Serial.println("Ich bin bereit");
}

void loop()
{
    adc_value = analogRead(A0);

    Serial.print("R: ");
    Serial.print(adc_value);

    analogWrite(LED_PIN_R, map(adc_value, 0, 1023, 0, 255));
    adc_value = analogRead(A2);
    analogWrite(LED_PIN_G, map(adc_value, 0, 1023, 0, 255));

    Serial.print(" G: ");
    Serial.print(adc_value);

    adc_value = analogRead(A4);
    analogWrite(LED_PIN_B, map(adc_value, 0, 1023, 0, 255));

    Serial.print(" B: ");
    Serial.println(adc_value);

    delay(100);
}
