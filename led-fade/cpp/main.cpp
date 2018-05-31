#include <iostream>
#include <cstdlib>
#include <signal.h>
#include <wiringPi.h>


int main(void)
{
    // GPIO18 is the PWD pin with the 10 bits precision
    const int led_pin = 1;

    if (wiringPiSetup() == -1)
    {
        std::cerr << "Failed to initialize wiringPi!" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "wiringPi initialized successfully" << std::endl;
    // set pin to the PWM output mode
    pinMode(led_pin, PWM_OUTPUT);

    int state = 0;
    int inc = 1;

    while(true)
    {
        pwmWrite(led_pin, state);
        delay(2);
        
        state += inc;
        if (inc <= 0 || inc >= 1024)
        {
            inc = -inc;
            delay(300);
        }
    }

    return EXIT_SUCCESS;
}