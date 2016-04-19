// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// SHT30
// This code is designed to work with the SHT30_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Humidity?sku=SHT30_I2CS#tabs-0-product_tabset-2

#include <application.h>
#include <spark_wiring_i2c.h>

// SHT30 I2C address is 0x44(68)
#define Addr 0x44

float cTemp = 0.0, fTemp = 0.0, humidity = 0.0;
void setup()
{
  // Set variable
  Particle.variable("i2cdevice", "SHT30");
  Particle.variable("cTemp", cTemp);
  Particle.variable("humidity", humidity);

  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);

}

void loop()
{
  unsigned int data[6];

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Send 16-bit command byte
  Wire.write(0x2C);
  Wire.write(0x06);
  // Stop I2C transmission
  Wire.endTransmission();
  delay(300);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Request 6 bytes of data
  Wire.requestFrom(Addr, 6);

  // Read 6 bytes of data
  // temp msb, temp lsb, crc, hum msb, hum lsb, crc
  if (Wire.available() == 6)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
    data[4] = Wire.read();
    data[5] = Wire.read();
  }
  delay(500);

  // Convert the data
  cTemp = ((((data[0] * 256.0) + data[1]) * 175) / 65535.0) - 45;
  fTemp = (cTemp * 1.8) + 32;
  humidity = ((((data[3] * 256.0) + data[4]) * 100) / 65535.0);

  // Output data to dashboard
  Particle.publish("Temperature in Celsius: ",  String(cTemp));
  Particle.publish("Temperature in Fahrenheit: ", String(fTemp));
  Particle.publish("Relative Humidity: ",  String(humidity));
  delay(1000);
}

