#include "Wire.h"


#define PCF8591 (0x90 >> 1) // I2C bus address
#define AIN0 0x00
#define AOUT 0x40

int raw_value = 0;
float voltage = 0.0f;
int count = 0;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
}

void loop()
{
  Wire.beginTransmission(PCF8591); // Start your PCF8591
  Wire.write(AOUT); // Tell it to output DAC value
  Wire.write(raw_value);
  Wire.endTransmission();

  Wire.beginTransmission(PCF8591); // Start your PCF8591
  Wire.write(AIN0); // Tell it to make an analog measurement
  Wire.endTransmission();
  Wire.requestFrom(PCF8591, 1); // Get the measured Data
  raw_value = Wire.read();
  if (raw_value < 0)
  {
    raw_value = 255;
  }
  voltage = (raw_value * 5.0) / 255.0;

  if (count % 5 == 0)
  {
    Serial.print("Raw ADC Value = "); Serial.print(raw_value);
    Serial.print(" Voltage = "); Serial.print(voltage, 3); Serial.println("V");
    count = 0;
  }
  count ++;

  delay(100);
}
