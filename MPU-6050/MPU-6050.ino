// MPU-6050 Sketch
//V1.2

#include<Wire.h>
#include <LiquidCrystal.h>

const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup(){
  
  lcd.begin(16, 2);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
}
void loop(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers

  // Collect accelerameter (X,Y,Z) data
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

  // Collect temperature data
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)

  // Collect gyro data (X,Y,Z)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  // Display accelerameter data
  Serial.print(" | AcX = "); Serial.print(AcX/16384.0); Serial.print(" g");
  Serial.print(" | AcY = "); Serial.print(AcY/16384.0); Serial.print(" g");
  Serial.print(" | AcZ = "); Serial.print(AcZ/16384.0); Serial.print(" g");

  // Display temperature data
  lcd.print(" | Tmp = "); lcd.print((Tmp/340.00+36.53)*(1.8)+32); lcd.print("°F"); // temperature conversion to fahrenheit

  // Display gyro data
  Serial.print(" | GyX = "); Serial.print(GyX/131.0); Serial.print("°/s");
  Serial.print(" | GyY = "); Serial.print(GyY/131.0); Serial.print("°/s");
  Serial.print(" | GyZ = "); Serial.print(GyZ/131.0); Serial.println("°/s");

  // Delay and clear lcd
  delay(1000);
  lcd.clear();
}
