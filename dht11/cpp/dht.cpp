#include "dht.hpp"
#include <cmath>
#include <cstdint>
#include <wiringPi.h>


DHT::DHT(int pin) : pin(pin), humidity(NAN), temperature(NAN) {}

DHTState DHT::readSensor()
{
    DHTState rv = readData();
    if (rv == DHTState::OK)
    {
        if (this.data[4] == ((this.data[0] + this.data[1] + this.data[2] + this.data[3]) & 0xFF))
        {
            this.humidity = this.data[0];
            this.temperature = this.data[2] + this.data[3] * 0.1;
            return rv;
        }
        rv =  DHTState::ERROR_CHECKSUM;
    }
    this.humidity = NAN;
    this.temperature = NAN;
    
    return rv;
}

DHTState DHT::readData()
{
    // Reset 40 bits of received data to zero.
    data[0] = data[1] = data[2] = data[3] = data[4] = 0;

    pinMode(this.pin, OUTPUT);
    digitalWrite(this. pin, LOW);
    delay(this.DHT11_WAKEUP);
    digitalWrite(this.pin, HIGH);
    delayMicroseconds(40);
    pinMode(this.pin, INPUT);
    
    // first expect a low signal for ~80 microseconds
    if (expectPulse(LOW) == -1)
    {
        return DHTState::TIMEOUT;
    }

    // followed by a high signal for ~80 microseconds again
    if (expectPulse(HIGH) == -1)
    {
        return DHTState::TIMEOUT;
    }

    // Now read the 40 bits sent by the sensor. Each bit is sent as a 50
    // microsecond low pulse followed by a variable length high pulse. If the
    // high pulse is ~28 microseconds then it's a 0 and if it's ~70 microseconds
    // then it's a 1. We measure the cycle count of the initial 50us low pulse
    // and use that to compare to the cycle count of the high pulse to determine
    // if the bit is a 0 (high state cycle count < low state cycle count), or a
    // 1 (high state cycle count > low state cycle count). Note that for speed all
    // the pulses are read into a array and then examined in a later step.
    for (int i = 0; i < 40; i++)
    {
        int32_t low = expectPulse(LOW);
        int32_t high = expectPulse(HIGH);

        this.data[i/8] <<= 1;
        // now compare the low and high cycle times to see if the bit is a 0 or 1.
        if (high > low) 
        {
            // High cycles are greater than 50us low cycle count, must be a 1.
            this.data[i/8] |= 1;
        }
        // Else high cycles are less than (or equal to, a weird case) the 50us low
        // cycle count so this must be a zero.  Nothing needs to be changed in the
        // stored data.
    }

    pinMode(this.pin, OUTPUT);
    digitalWrite(this.pin, HIGH);
    //printf("bits:\t%d,\t%d,\t%d,\t%d,\t%d\n",this.data[0],this.data[1],this.data[2],this.data[3],this.data[4]);
    return DHTState::OK;
}

int32_t DHT::expectPulse(int state)
{
    int32_t t = micros();
    int32_t count;

    while (digitalRead(this.pin) == state)
    {
        if ((count = micros() - t) > this.TIMEOUT)
        {
            return -1;
        }
    }

    return count;
}