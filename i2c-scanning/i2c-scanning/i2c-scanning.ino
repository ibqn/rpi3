#include <Wire.h>
 
 
void setup()
{
  Wire.begin();
  Serial.begin(9600);
  Serial.println("I2C address scanning");
}
 
 
void loop()
{
  byte error;
  int n_devices = 0;
 
  Serial.println("scanning...");
  for (byte address = 1; address < 127; address++)
  {
    // The i2c_scanning uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      n_devices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
    } 
    else
    {
      continue;
    }
    if (address < 16)
    {
      Serial.print("0");
    }
    Serial.print(address, HEX);
    Serial.println("  !");    
  }
  if (n_devices == 0)
  {
    Serial.println("no I2C devices found");
  }
  else
  {
    Serial.println("done");
  }
  // wait 5 seconds for next scan
  delay(5000);
}
