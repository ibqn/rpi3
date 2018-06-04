#include "dht.hpp";

#include <iostream>
#include <cstdio>
#include <cstdlib>

//define the pin of sensor
const int dht11_pin  = 0;


int main(void)
{
    if (wiringPiSetup() == -1)
    {
        std::cerr << "Failed to initialize wiringPi!" << std::endl;
        return EXIT_FAILURE;
    }

    DHT dht(dht11_pin);
    DHTState state;

    while (true)
    {
        // read DHT11 and get a return value. Then determine whether data read is normal according to the return value.
        state = dht.readSensor(); 
        switch(state)
        {
            // if the return value is OK, show data
            case DHTState::OK:     
                std::cout << "DHT11,OK!" << std::endl; 
                printf("Humidity is %.2f %%, \t Temperature is %.2f *C\n", dht.humidity, dht.temperature);
                break;
            case DHTState::ERROR_CHECKSUM:     //data check has errors
                std::cerr << "DHT11 checksum error!" << std::endl;
                break;
            case  DHTState::ERROR_TIMEOUT:      //reading DHT times out
                std::cerr << "DHT11 read timeout!" << std::endl;
                break;
        }

        delay(2000);
    }

    return EXIT_SUCCESS;
}