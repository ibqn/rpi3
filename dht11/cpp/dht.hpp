#ifndef _DHT_H_
#define _DHT_H_


#include <cstdint>


enum class DHTState
{
    OK = 0,
    ERROR_CHECKSUM,
    ERROR_TIMEOUT,
};

class DHT
{      
public:
    DHT(int pin);
    // use to store temperature and humidity data read
    float humidity, temperature;
    DHTState readSensor(); // read from DHT11

private:
    uint32_t _lastread;
    uint8_t data[5]; // buffer for received data
    DHTState readData();
    int pin;
    
    const int32_t TIMEOUT = 100;
    const int DHT11_WAKEUP = 18;
};

#endif