#include <Wire.h>
#include <EEPROM.h>
#include "pico/stdlib.h"
//#include <pico/sleep.h>
 // Set System clock to 10000 kHz
//set_sys_clock_khz(10000, false); // Set System clock to 10000 kHz
#define LSM6DSL_ADDR 0x6B
#define LSM6DSL_REG_CTRL1_XL 0x10
#define LSM6DSL_REG_CTRL2_G 0x11
#define LSM6DSL_REG_CTRL10_C 0x19
#define LSM6DSL_REG_TAP_CFG 0x58
#define LSM6DSL_REG_INT1_CTRL 0x0D
#define LSM6DSL_REG_OUTX_L_XL 0x28
#define LSM6DSL_REG_OUTX_H_XL 0x29
#define LSM6DSL_REG_OUTY_L_XL 0x2A
#define LSM6DSL_REG_OUTY_H_XL 0x2B
#define LSM6DSL_REG_OUTZ_L_XL 0x2C
#define LSM6DSL_REG_OUTZ_H_XL 0x2D
#define HIGH_PERF_416HZ_8G 0x6C
#define XL_SCALE_8G 0.244 // scale for ±8g
#define XL_NEG_OFFSET 7.995478
const byte interrupt_pin = 2;
const int eepromSize = 4096;  // define the EEPROM size
int eepromAddress = 0;  // start address for EEPROM
struct AccelData {
  float x;
  float y;
  float z;
};
uint16_t readHLRegisters(uint8_t addr, uint8_t reg_h, uint8_t reg_l) {
  Wire.beginTransmission(addr);
  Wire.write(reg_h);
  Wire.endTransmission();
  Wire.requestFrom(addr, 1);
  int8_t hb = Wire.read();
  Wire.beginTransmission(addr);
  Wire.write(reg_l);
  Wire.endTransmission();
  Wire.requestFrom(addr, 1);
  int8_t lb = Wire.read();
  int16_t byte_value = (hb << 8) | lb;
  if (hb & 0x80)
  {
    byte_value = (~byte_value)+1;
    int ibyte_value = -byte_value;
    return ibyte_value;
  }
  else
  {
    return byte_value;
    }
}
void setup() {
  Wire.begin();
  Serial.begin(9600);
  EEPROM.begin(eepromSize);
  delay(1000);
  Serial.println("Berfore init");
  Wire.beginTransmission(LSM6DSL_ADDR);
  Wire.write(LSM6DSL_REG_CTRL1_XL);
  Wire.write(HIGH_PERF_416HZ_8G);
  int x = Wire.endTransmission();
  Serial.println(x);
  Wire.beginTransmission(LSM6DSL_ADDR);
  Wire.write(LSM6DSL_REG_CTRL10_C);
  Wire.write(0b10000100);
  Wire.endTransmission();
  /*Wire.beginTransmission(LSM6DSL_ADDR);
  Wire.write(LSM6DSL_REG_TAP_CFG);
  Wire.write(0x40);
  Wire.endTransmission();
  Wire.beginTransmission(LSM6DSL_ADDR);
  Wire.write(LSM6DSL_REG_INT1_CTRL);
  Wire.write(0x40);
  Wire.endTransmission();
  */
  Wire.beginTransmission(LSM6DSL_ADDR);
  Wire.write(0x0B);
  Wire.write(0x1);
  Wire.endTransmission();
  Wire.beginTransmission(LSM6DSL_ADDR);
  Wire.write(0x50);
  Wire.write(25);
  Wire.endTransmission();
//0x54 default
    Wire.beginTransmission(LSM6DSL_ADDR);
  Wire.write(0x59);
  Wire.write(0b00001000);
  Wire.endTransmission();
  pinMode(interrupt_pin, INPUT_PULLUP);
  attachInterrupt(interrupt_pin, interrupt_handler, FALLING);
  Serial.println("Going to sleep. Waiting for movement to wake up.");
}
void get_accel(float* x_val, float* y_val, float* z_val) {
  int16_t x_byte_val = readHLRegisters(LSM6DSL_ADDR, LSM6DSL_REG_OUTX_H_XL, LSM6DSL_REG_OUTX_L_XL);
  int16_t y_byte_val = readHLRegisters(LSM6DSL_ADDR, LSM6DSL_REG_OUTY_H_XL, LSM6DSL_REG_OUTY_L_XL);
  int16_t z_byte_val = readHLRegisters(LSM6DSL_ADDR, LSM6DSL_REG_OUTZ_H_XL, LSM6DSL_REG_OUTZ_L_XL);
  *x_val = ((x_byte_val*0.244)/1000)*9.81;
  *y_val = ((y_byte_val*0.244)/1000)*9.81;
  *z_val = ((z_byte_val*0.244)/1000)*9.81;
}
void interrupt_handler() {
    // set_sys_clock_khz(125000, false);
  Serial.println("Motion detected, reading acceleration data...");
    AccelData data;
  unsigned long interruptTime = millis();  // save the current time
  // keep reading and storing data for 5 seconds
  while (millis() - interruptTime < 2000) {
    get_accel(&data.x, &data.y, &data.z);
    // check if we've reached the end of the EEPROM
    if (eepromAddress > eepromSize - sizeof(AccelData)) {
      eepromAddress = 0;  // start over from the beginning
    }
    EEPROM.put(eepromAddress, data);  // write the AccelData structure to EEPROM
    eepromAddress += sizeof(AccelData);  // increase the address for the next write
    EEPROM.commit();  // commit changes to flash
  }
  Serial.println("Acceleration data stored. Going back to sleep.");
  //set_sys_clock_khz(10000, false);
    delay(6000);
    //sleep_goto_dormant_until_level_high(2);
}
void loop() {
  for(int i=0;i<100;i++)
  {
      float x_val, y_val, z_val;
      get_accel(&x_val, &y_val, &z_val);
  Serial.print("X: ");
  Serial.print(x_val);
  Serial.print("  Y: ");
  Serial.print(y_val);
  Serial.print("  Z: ");
  Serial.println(z_val);
  }
  //sleep_goto_dormant_until_level_high(2);
  //tight_loop_contents();
}