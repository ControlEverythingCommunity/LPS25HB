// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// LPS25HB
// This code is designed to work with the LPS25HB_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Barometer?sku=LPS25HB_I2CS#tabs-0-product_tabset-2

import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class LPS25HB
{
	public static void main(String args[]) throws Exception
	{
		// Create I2C bus
		I2CBus bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, LPS25HB I2C address is 0x5C(72)
		I2CDevice device = bus.getDevice(0x5C);
		
		// Active mode, Continuous Update
		device.write(0x20, (byte)0x90);
		Thread.sleep(500);
		
		// Read 3 bytes of data from address 0x28(40), lsb first
		byte[] data = new byte[3];
		device.read(0x28 | 0x80, data, 0, 3);
		
		// Convert data to hPa
		double pressure = (((data[2] & 0xff) * 65536) + ((data[1] & 0xff) * 256) + (data[0] & 0xff)) / 4096.0;
		
		// Output to the screen
		System.out.printf("Pressure is : %.2f hPa %n", pressure);
	}
}
