#ifndef IMU_H__
#define IMU_H__

#include<xc.h> // processor SFR definitions
#include "i2c_master_noint.h"
#include "ssd1306.h"

#define IMU_WHOAMI 0x0F
#define IMU_ADDR_READ 0b11010111
#define IMU_ADDR_WRITE 0b11010110
#define IMU_CTRL1_XL 0x10
#define IMU_CTRL2_G 0x11
#define IMU_CTRL3_C 0x12
#define IMU_OUT_TEMP_L 0x20
#define IMU_OUTX_L_G 0x22
#define IMU_OUTY_L_G 0x24
#define IMU_OUTZ_L_G 0x26
#define IMU_OUTX_L_XL 0x28
#define IMU_OUTY_L_XL 0x2A
#define IMU_OUTZ_L_XL 0x2C

void imu_setup();
signed short imu_read(unsigned char);
void bar_x(signed short);
void bar_y(signed short);

#endif