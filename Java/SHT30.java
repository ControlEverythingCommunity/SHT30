// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// SHT30
// This code is designed to work with the SHT30_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Humidity?sku=SHT30_I2CS#tabs-0-product_tabset-2

import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class SHT30
{
	public static void main(String args[]) throws Exception
	{
		// Create I2C bus
		I2CBus Bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, SHT30 I2C address is 0x44(68)
		I2CDevice device = Bus.getDevice(0x44);

		// Send measurement command
		// High repeatability measurement
		byte[] config = new byte[2];
		config[0] = 0x2C;
		config[1] = 0x06;
		device.write(config, 0, 2);
		Thread.sleep(500);

		// Read 6 bytes of data
		// Temp msb, Temp lsb, Temp CRC, Humididty msb, Humidity lsb, Humidity CRC
		byte[] data = new byte[6];
		device.read(data, 0, 6);

		// Convert the data
		int temp = ((data[0] & 0xFF) * 256) + (data[1] & 0xFF);
		double cTemp = -45 + (175 * temp / 65535.0);
		double fTemp = -49 + (315 * temp / 65535.0);
		double humidity = 100 * (((data[3] & 0xFF) * 256) + (data[4]  & 0xFF)) / 65535.0;
		
		// Output data to screen
		System.out.printf("Relative Humidity : %.2f %%RH %n", humidity);
		System.out.printf("Temperature in Celsius : %.2f C %n", cTemp);
		System.out.printf("Temperature in Fahrenheit : %.2f F %n", fTemp);
	}
}
