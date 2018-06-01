#include <wiringPi.h>
#include <pcf8591.h>
#include <cstdio>
#include <cstdlib>


// PCF8591 default I^2C address
const int address = 0x48;

const int pinbase = 64;

const int A0 = pinbase + 0;
const int A1 = pinbase + 1;
const int A2 = pinbase + 2;
const int A3 = pinbase + 3;


int main(void)
{
    int raw_value;
    float voltage;

    wiringPiSetup();
    pcf8591Setup(pinbase, address);

    while(true)
    {
        // read analog value from pin A0
        raw_value = analogRead(A0);
        analogWrite(pinbase, raw_value);
        voltage = 3.3f * raw_value / 255.0f;
        printf("ADC value: %d, Voltage: %.2fV\n", raw_value, voltage);
        delay(100);
    }
    return EXIT_SUCCESS;
}