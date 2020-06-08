/* 
 * File:   imu.c
 * Author: scott
 *
 * Created on June 8, 2020, 8:46 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "imu.h"

void imu_setup(){
    unsigned char who = 0;
    char message[50];

    // Read from WHOAMI register
    i2c_master_start();
    i2c_master_send(IMU_ADDR_WRITE);
    i2c_master_send(IMU_WHOAMI);
    i2c_master_restart();
    i2c_master_send(IMU_ADDR_READ);
    who = i2c_master_recv();
    i2c_master_ack(1);
    i2c_master_stop();
    
    if (who != 0b01101001){
        while(1)
        {
            ssd1306_clear();
            sprintf(message,"HERE");
            drawString(message,5,5);
            ssd1306_update();
        }
    }

    // init IMU_CTRL1_XL
    i2c_write(IMU_ADDR_WRITE,0b10000010,IMU_CTRL1_XL); 
    
    // init IMU_CTRL2_G
    i2c_write(IMU_ADDR_WRITE,0b10001000,IMU_CTRL2_G);

    // init IMU_CTRL3_C
    i2c_write(IMU_ADDR_WRITE,0b00000100,IMU_CTRL3_C);

}

signed short imu_read(unsigned char reg){
    
    unsigned char data1;
    unsigned char data2;
    
    signed short data;
    
    data1 = i2c_read_multiple(IMU_ADDR_WRITE,IMU_ADDR_READ,reg);
    data2 = i2c_read_multiple(IMU_ADDR_WRITE,IMU_ADDR_READ,reg+0x01);
    
    data = (data2 << 8) | data1;
    
    return data;
}

void bar_y(signed short val){
    
    int scaledVal = 16 * val/16383;
    int i;
    
    if ( scaledVal > 0 ){
        for (i = 0; i < scaledVal; i ++){
            ssd1306_drawPixel(64,16+i,1);
        }
    } else {
        for (i = scaledVal; i <= 0; i++){
            ssd1306_drawPixel(64,16+i,1);
        }
    }
        
        
}

void bar_x(signed short val){
    int scaledVal = 16 * val/16383;
    int i;
    
    if ( scaledVal > 0 ){
        for (i = 0; i < scaledVal; i ++){
            ssd1306_drawPixel(64+i,16,1);
        }
    } else {
        for (i = scaledVal; i <= 0; i++){
            ssd1306_drawPixel(64+i,16,1);
        }
    }
}

int main() {

    __builtin_disable_interrupts(); // disable interrupts while initializing things

    // set the CP0CONFIG register to indicate that kseg0 is cacheable (0x3)
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);

    // 0 data  RAM access wait states
    BMXCONbits.BMXWSDRM = 0x0;

    // enable multi vector interrupts
    INTCONbits.MVEC = 0x1;

    // disable JTAG to get pins back
    DDPCONbits.JTAGEN = 0;

    // do your TRIS and LAT commands here
    TRISAbits.TRISA4 = 0;
    LATAbits.LATA4 = 1;
    
    i2c_init();
    ssd1306_setup();
    imu_setup();
    
    __builtin_enable_interrupts();
    
    char message[50];
    _CP0_SET_COUNT(0);
    
    while (1) {     
        signed short tData = imu_read(IMU_OUT_TEMP_L);
        signed short gxData = imu_read(IMU_OUTX_L_G);
        signed short gyData = imu_read(IMU_OUTY_L_G);
        signed short gzData = imu_read(IMU_OUTZ_L_G);
        signed short xlxData = imu_read(IMU_OUTX_L_XL);
        signed short xlyData = imu_read(IMU_OUTY_L_XL);
        signed short xlzData = imu_read(IMU_OUTZ_L_XL);
        
        ssd1306_clear();
        
//        sprintf(message,"t: %d",tData);
//        drawString(message,5,25);
//        
//        sprintf(message,"g: %d %d %d",gxData,gyData,gzData);
//        drawString(message,5,5);
//        
//        sprintf(message,"a: %d %d %d",xlxData,xlyData,xlzData);
//        drawString(message,5,15);
        
        bar_y(xlxData);
        bar_x(-xlyData);
        ssd1306_update();

        
        LATAbits.LATA4 = !LATAbits.LATA4;
        
        _CP0_SET_COUNT(0);
        while (_CP0_GET_COUNT() < 48000000/2/20){;}
    }
}

