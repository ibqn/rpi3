#include <iostream>
#include <cstdlib>
#include <wiringPi.h>


int main(void)
{
    const int led_pin = 0;

    if (wiringPiSetup() == -1)
    {
        std::cerr << "Failed to initialize wiringPi!" << std::endl;
        return EXIT_FAILURE;
    }

    pinMode(led_pin, OUTPUT);

    for (bool state = true; ; state = !state)
    {
        digitalWrite(led_pin, (int) state);
        delay(1000);
    }

    std::cout << "wiringPi initialized successfully" << std::endl;
    return EXIT_SUCCESS;
}
