// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// LPS25HB
// This code is designed to work with the LPS25HB_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Barometer?sku=LPS25HB_I2CS#tabs-0-product_tabset-2

#include<Wire.h>

// LPS25HB I2C address is 0x5C(92)
#define Addr 0x5C

void setup() 
{
  // Initialise I2C communication as MASTER 
  Wire.begin();
  // Initialise Serial communication, set baud rate = 9600
  Serial.begin(9600);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select control register 1
  Wire.write(0x20);
  // Set active mode, continuous Update
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
  
  // Request 2 bytes of data
  Wire.requestFrom(Addr, 3);

  // Read 3 bytes of data, lsb first
  if(Wire.available() == 3)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
  }
  delay(300);
    
  // Convert pressure data
  float pressure = ((data[2] * 65536) + (data[1] * 256) + data[0]) / 4096.0;
  
  // Output data to serial monitor
  Serial.print("Pressure is : ");
  Serial.print(pressure);
  Serial.println(" hPa"); 
  delay(1000);
}


