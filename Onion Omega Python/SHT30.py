# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# SHT30
# This code is designed to work with the SHT30_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/content/Humidity?sku=SHT30_I2CS#tabs-0-product_tabset-2

from OmegaExpansion import onionI2C
import time

# Get I2C bus
i2c = onionI2C.OnionI2C()

# SHT30 address, 0x44(68)
# Send measurement command, 0x2C(44)
#		0x06(06)	High repeatability measurement
data = [0x06]
i2c.writeBytes(0x44, 0x2C, data)

time.sleep(0.5)

# SHT30 address, 0x44(68)
# Read data back from 0x00(00), 6 bytes
# cTemp MSB, cTemp LSB, cTemp CRC, Humididty MSB, Humidity LSB, Humidity CRC
data = i2c.readBytes(0x44, 0x00, 6)

# Convert the data
cTemp = ((((data[0] * 256.0) + data[1]) * 175) / 65535.0) - 45
fTemp = cTemp * 1.8 + 32
humidity = 100 * (data[3] * 256 + data[4]) / 65535.0

# Output data to screen
print "Relative Humidity : %.2f %%RH" %humidity
print "Temperature in Celsius : %.2f C" %cTemp
print "Temperature in Fahrenheit : %.2f F" %fTemp
