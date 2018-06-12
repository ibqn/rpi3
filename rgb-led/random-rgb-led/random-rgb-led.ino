const uint8_t LED_PIN_RED = 9;
const uint8_t LED_PIN_GREEN = 10;
const uint8_t LED_PIN_BLUE = 11;

void setup()
{
    pinMode(LED_PIN_RED, OUTPUT);
    pinMode(LED_PIN_GREEN, OUTPUT);
    pinMode(LED_PIN_BLUE, OUTPUT);

    // if analog input pin A0 is unconnected, random analog
    // noise will cause the call to randomSeed() to generate
    // different seed numbers each time the sketch runs.
    // randomSeed() will then shuffle the random function.
    randomSeed(analogRead(A0));
}

void loop()
{
    rgb_led_show(
        constrain(random(256), 0, 255),
        constrain(random(256), 0, 255),
        constrain(random(256), 0, 255)
    );

    delay(2000);
}

void rgb_led_show(uint8_t red, uint8_t green, uint8_t blue)
{
    analogWrite(LED_PIN_RED, red);
    analogWrite(LED_PIN_GREEN, green);
    analogWrite(LED_PIN_BLUE, blue);
}
