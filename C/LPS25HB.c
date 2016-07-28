// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// LPS25HB
// This code is designed to work with the LPS25HB_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Barometer?sku=LPS25HB_I2CS#tabs-0-product_tabset-2

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void main()
{
	// Create I2C bus
	int file;
	char *bus = "/dev/i2c-1";
	if((file = open(bus, O_RDWR)) < 0)
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, LPS25HB I2C address is 0x5C(72)
	ioctl(file, I2C_SLAVE, 0x5C);
	
	// Select control register(0x20)
	// Active mode, Continuous Update(0x90)
	char config[2] = {0};
	config[0] = 0x20;
	config[1] = 0x90;
	write(file, config, 2); 
	sleep(1);

	// Read 3 bytes of data from register(0x28)
	// Pressure lsb first
	char reg[1] = {0x28 | 0x80};
	write(file, reg, 1);
	char data[3] = {0};
	if(read(file, data, 3) != 3)
	{
		printf("Error : Input/Output error \n");
	}
	else
	{
		// Convert the data
		float pressure = ((data[2] * 65536) + ((data[1] * 256) + data[0])) / 4096.0;

		// Output data to screen
		printf("Pressure is : %.2f hPa \n", pressure);
	}
}
