// calibrate function
void calibrate(){
  AcX_raw = 0;
  AcY_raw = 0;
  AcZ_raw = 0;
  Tmp_raw = 0;
  GyX_raw = 0;
  GyY_raw = 0;
  GyZ_raw = 0;
  Serial.println("Calibrating... DON'T MOVE");
  for (int i = 0; i<100; i ++) {
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B);
    Wire.endTransmission(false); 
    Wire.requestFrom(MPU_addr,7*2,true); 
    AcX_raw += Wire.read()<<8 | Wire.read();
    AcY_raw += Wire.read()<<8 | Wire.read();
    AcZ_raw += Wire.read()<<8 | Wire.read();
    Tmp_raw += Wire.read()<<8 | Wire.read();
    GyX_raw += Wire.read()<<8 | Wire.read();
    GyY_raw += Wire.read()<<8 | Wire.read();
    GyZ_raw += Wire.read()<<8 | Wire.read();
    delay(50);
  }

  // average over iterations...
  offset[0] = AcX_raw / 100.0;
  offset[1] = AcY_raw / 100.0;
  offset[2] = AcZ_raw / 100.0;
  offset[3] = Tmp_raw / 100.0;
  offset[4] = GyX_raw / 100;
  offset[5] = GyY_raw / 100.0;
  offset[6] = GyZ_raw / 100.0;

}

// function takes offsets and reads
// MPU-data

MPUData get_MPU_data(float offset[6]) {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B); // get x-vals
  Wire.endTransmission(false); // don't end
  // request 14 registers (2 each)
  // all at adjacent positions
  Wire.requestFrom(MPU_addr,7*2,true); 

  int16_t AcX_raw = Wire.read()<<8 | Wire.read();
  int16_t AcY_raw = Wire.read()<<8 | Wire.read();
  int16_t AcZ_raw = Wire.read()<<8 | Wire.read();

  int16_t Tmp_raw = Wire.read()<<8 | Wire.read();

  int16_t GyX_raw = Wire.read()<<8 | Wire.read();
  int16_t GyY_raw = Wire.read()<<8 | Wire.read();
  int16_t GyZ_raw = Wire.read()<<8 | Wire.read();

  // converting
  float Tmp = (float)Tmp_raw; //- offset[3] ;
  float AcX = (float)(AcX_raw-offset[0])/4096;
  float AcY = (float)(AcY_raw-offset[1])/4096;
  float AcZ = (float)(AcZ_raw-offset[2])/4096;

  float GyX = (float)(GyX_raw-offset[4]) / 65.5;
  float GyY = (float)(GyY_raw-offset[5]) / 65.5;
  float GyZ = (float)(GyZ_raw-offset[6])/ 65.5;

  return {AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ};

}