// BMP280 Sketch
// V1.0

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <LiquidCrystal.h>

Adafruit_BMP280 bmp; // use I2C interface
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
   lcd.begin(16, 2);
  Serial.begin(9600);
  Serial.println(F("BMP280 Sensor event test"));

  if (!bmp.begin(0x76)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  bmp_temp->printSensorDetails();
}

void loop() {
  sensors_event_t temp_event, pressure_event;
  bmp_temp->getEvent(&temp_event);
  bmp_pressure->getEvent(&pressure_event);
  
  Serial.print(F("Temperature = "));
  Serial.print(temp_event.temperature*(1.8)+32);
  Serial.println(" *F");

  Serial.print(F("Pressure = "));
  Serial.print(pressure_event.pressure);
  Serial.println(" hPa");

  Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1021.42)*3.3); /* Adjusted to local forecast! */
    Serial.println(" ft");
    lcd.print(bmp.readAltitude(1021.42)*3.3);

  //Serial.println();
  delay(100);
  lcd.clear();
}
