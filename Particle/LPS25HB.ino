// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// LPS25HB
// This code is designed to work with the LPS25HB_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Barometer?sku=LPS25HB_I2CS#tabs-0-product_tabset-2

#include <application.h>
#include <spark_wiring_i2c.h>

// LPS25HB I2C address is 0x5C(92)
#define Addr 0x5C

float pressure = 0;
void setup()
{
  // Set variable
  Particle.variable("i2cdevice", "LPS25HB");
  Particle.variable("pressure", pressure);

  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise Serial communication, set baud rate = 9600
  Serial.begin(9600);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select control register 1
  Wire.write(0x20);
  // Set active mode, continuous update
  Wire.write(0x90);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(300);
}

void loop()
{
  unsigned int data[3];
  
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select pressure data register
  Wire.write(0x28 | 0x80);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Request 3 bytes of data
  Wire.requestFrom(Addr, 3);

  // Read 3 bytes of data, lsb first
  if (Wire.available() == 3)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
  }
  delay (300);

  // Convert pressure data
  pressure = ((data[2] * 65536) + (data[1] * 256) + data[0]) / 4096.0;

  // Output data to dashboard
  Particle.publish("Pressure :  ", String(pressure));
  delay(1000);
}
