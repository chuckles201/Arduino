// setting up LCD
#include <LiquidCrystal.h>
LiquidCrystal lcd(11,12,5,4,3,2);

// acceleromoter:
// Idea is that when tilted,
// work done (although ball doesn;t move)
// and when tilted and ball does move, calculate
// current for this

#include <Wire.h>
const int MPU_addr = 0x68;

// accelerator and gyroscope values
struct MPUData {
  float AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
};
// store offsets
float offset[7];

// for float-conversion : /65.5, 4096 for accel
float AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
float AcX_raw,AcY_raw,AcZ_raw,Tmp_raw,GyX_raw,GyY_raw,GyZ_raw;



// calibrate our vars...




void setup() {
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("X:");
  lcd.setCursor(0, 1);
  lcd.print("Y:");
  lcd.setCursor(8, 1);
  lcd.print("Z:");

  // start I2C protocol
  Wire.begin();
  // start talking to Gyro
  Wire.beginTransmission(MPU_addr);
  // wake up at adress
  Wire.write(0x68);
  Wire.write(0);

  Serial.begin(9600);

  //Calibrate
  calibrate();



}
int second = 0;
void loop() {
  // does all transmission for us
  MPUData data = get_MPU_data(offset);

  

  Serial.print("Accelerometer X: ");
  Serial.print(data.AcX);
  Serial.print(" | Accelerometer Y: ");
  Serial.print(data.AcY);
  Serial.print(" | Accelerometer Z: ");
  Serial.print(data.AcZ);
  Serial.println();

  Serial.print("Gyro X: ");
  Serial.print(data.GyX);
  Serial.print(" | Gyro Y: ");
  Serial.print(data.GyY);
  Serial.print(" | Gyro Z: ");
  Serial.print(data.GyZ);
  Serial.println();

  Serial.print("TEMP: ");
  Serial.println(data.Tmp);



  delay(1000);
  // printing Values
  lcd.setCursor(2, 0);
  lcd.print(data.GyX);
  lcd.setCursor(2, 1);
  lcd.print(data.GyY);
  lcd.setCursor(10, 1);
  lcd.print(data.GyZ);

}
