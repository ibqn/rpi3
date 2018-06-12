void setup()
{
    Serial.begin(9600);
    Serial.println("UNO is ready!");
}

void loop()
{
    int adc_value = analogRead(A0);

    float v = adc_value * 5.0f / 1023;
    // calculate resistance of thermistor
    float rt = 10 * v / (5.0f - v);
    float temp_k = 1 / (log(rt / 10) / 3950 + 1 / (273.15f + 25));
    float temp_c = temp_k - 273.15f;

    Serial.print("Current temperature is: ");
    Serial.print(temp_c);
    Serial.println(" °C");

    delay(2000);
}
