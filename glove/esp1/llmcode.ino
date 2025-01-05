#include <Wire.h>

// MPU9250 and AK8963 registers
#define MPU9250_ADDR              0x68
#define PWR_MGMT_1               0x6B
#define INT_PIN_CFG              0x37
#define ACCEL_XOUT_H             0x3B
#define GYRO_XOUT_H              0x43
#define AK8963_ADDR              0x0C
#define AK8963_CNTL              0x0A
#define AK8963_XOUT_L            0x03

// Variables for sensor data
int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t mx, my, mz;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  
  // Wake up MPU9250
  Wire.beginTransmission(MPU9250_ADDR);
  Wire.write(PWR_MGMT_1);
  Wire.write(0x00);
  Wire.endTransmission(true);
  delay(100);
  
  // Configure MPU9250 to allow magnetometer access
  Wire.beginTransmission(MPU9250_ADDR);
  Wire.write(INT_PIN_CFG);
  Wire.write(0x02);    // Enable bypass mode
  Wire.endTransmission(true);
  delay(10);
  
  // Configure magnetometer
  Wire.beginTransmission(AK8963_ADDR);
  Wire.write(AK8963_CNTL);
  Wire.write(0x16);    // 16-bit output, 100Hz continuous measurement
  Wire.endTransmission(true);
  delay(10);
}

void loop() {
  // Read accelerometer
  Wire.beginTransmission(MPU9250_ADDR);
  Wire.write(ACCEL_XOUT_H);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU9250_ADDR, 6, true);
  
  ax = Wire.read() << 8 | Wire.read();
  ay = Wire.read() << 8 | Wire.read();
  az = Wire.read() << 8 | Wire.read();
  
  // Read gyroscope
  Wire.beginTransmission(MPU9250_ADDR);
  Wire.write(GYRO_XOUT_H);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU9250_ADDR, 6, true);
  
  gx = Wire.read() << 8 | Wire.read();
  gy = Wire.read() << 8 | Wire.read();
  gz = Wire.read() << 8 | Wire.read();
  
  // Read magnetometer
  Wire.beginTransmission(AK8963_ADDR);
  Wire.write(AK8963_XOUT_L);
  Wire.endTransmission(false);
  Wire.requestFrom(AK8963_ADDR, 6, true);
  
  mx = Wire.read() | Wire.read() << 8;
  my = Wire.read() | Wire.read() << 8;
  mz = Wire.read() | Wire.read() << 8;
  
  // Print values
  Serial.print("Accel (x,y,z): ");
  Serial.print(ax); Serial.print(",");
  Serial.print(ay); Serial.print(",");
  Serial.print(az); Serial.print(" | ");
  
  Serial.print("Gyro (x,y,z): ");
  Serial.print(gx); Serial.print(",");
  Serial.print(gy); Serial.print(",");
  Serial.print(gz); Serial.print(" | ");
  
  Serial.print("Mag (x,y,z): ");
  Serial.print(mx); Serial.print(",");
  Serial.print(my); Serial.print(",");
  Serial.println(mz);
  
  delay(100);
}
