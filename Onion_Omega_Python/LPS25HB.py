# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# LPS25HB
# This code is designed to work with the LPS25HB_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/content/Barometer?sku=LPS25HB_I2CS#tabs-0-product_tabset-2

from OmegaExpansion import onionI2C
import time

# Get I2C bus
i2c = onionI2C.OnionI2C()

# LPS25HB address, 0x5C(92)
# Select Control register, 0x20(32)
#		0x90(144)	Active mode, Continous update
i2c.writeByte(0x5C, 0x20, 0x90)

time.sleep(0.1)

# LPS25HB address, 0x5C(92)
# Read data back from 0x28(40), with Command register, 0x80(128)
# 3 bytes, Pressure LSB first
data =i2c.readBytes(0x5C, 0x28 | 0x80, 3)

# Convert the data to hPa
pressure = (data[2] * 65536 + data[1] * 256 + data[0]) / 4096.0

# Output data to screen
print "Barometric Pressure is : %.2f hPa" %pressure
