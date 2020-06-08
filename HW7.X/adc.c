#include "adc.h"
#include <stdio.h>

#define SAMPLE_TIME 10 // in core timer ticks, use a minimum of 250 ns

unsigned int adc_sample_convert(int pin) {
    unsigned int elapsed = 0, finish_time = 0;
    AD1CHSbits.CH0SA = pin; // connect chosen pin to MUXA for sampling
    AD1CON1bits.SAMP = 1; // start sampling
    elapsed = _CP0_GET_COUNT();
    finish_time = elapsed + SAMPLE_TIME;
    while (_CP0_GET_COUNT() < finish_time) {
        ; // sample for more than 250 ns
    }
    AD1CON1bits.SAMP = 0; // stop sampling and start converting
    while (!AD1CON1bits.DONE) {
        ; // wait for the conversion process to finish
    }
    return ADC1BUF0; // read the buffer with the result
}

void adc_setup() {
    // set analog pins with ANSEL
    
    ANSELBbits.ANSB3 = 1; // ANSEL pin of AN5
    ANSELBbits.ANSB2 = 1;
    
    AD1CON3bits.ADCS = 1; // ADC clock period is Tad = 2*(ADCS+1)*Tpb = 2*2*20.3ns = 83ns > 75ns
    IEC0bits.AD1IE = 0; // Disable ADC interrupts
    AD1CON1bits.ADON = 1; // turn on A/D converter
}

void ctmu_setup() {
    // base level current is about 0.55uA
    CTMUCONbits.IRNG = 0b11; // 100 times the base level current
    CTMUCONbits.ON = 1; // Turn on CTMU

    // 1ms delay to let it warm up
    _CP0_SET_COUNT(0);
    while (_CP0_GET_COUNT() < 48000000 / 2 / 1000) {
    }
}

int ctmu_read(int pin, int delay) {
    int start_time = 0;
    AD1CHSbits.CH0SA = pin;
    AD1CON1bits.SAMP = 1; // Manual sampling start
    CTMUCONbits.IDISSEN = 1; // Ground the pin
    // Wait 1 ms for grounding
    start_time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < start_time + 48000000 / 2 / 1000) {
    }
    CTMUCONbits.IDISSEN = 0; // End drain of circuit

    CTMUCONbits.EDG1STAT = 1; // Begin charging the circuit
    // wait delay core ticks
    start_time = _CP0_GET_COUNT();
    while (_CP0_GET_COUNT() < start_time + delay) {
    }
    AD1CON1bits.SAMP = 0; // Begin analog-to-digital conversion
    CTMUCONbits.EDG1STAT = 0; // Stop charging circuit
    while (!AD1CON1bits.DONE) // Wait for ADC conversion
    {}
    AD1CON1bits.DONE = 0; // ADC conversion done, clear flag
    return ADC1BUF0; // Get the value from the ADC
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
//    TRISB = 0x0000;
//    LATB = 0x0000;
//    PORTB = 0x0000;
    
    TRISAbits.TRISA4 = 0;
    TRISBbits.TRISB3 = 1 ;
    LATAbits.LATA4 = 1;
    
    i2c_init();
    ssd1306_setup();
    imu_setup();
    ctmu_setup();
    adc_setup();
    
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
        
        int i;
        int j;
        int rBuf5 = 0;
        int aBuf5 = 0;
        int rBuf4 = 0,aBuf4 = 0;
        
        for (j = 0; j < 9; j++){
            for (i = 0; i < 20; i++){
                rBuf5 += ctmu_read(5,48000000/4000);
            }
            aBuf5 += rBuf5/20;
        }
        for (j = 0; j < 9; j++){
            for (i = 0; i < 20; i++){
                rBuf4 += ctmu_read(4,48000000/4000);
            }
            aBuf4 += rBuf4/20;
        }
        
        if (aBuf5 < 45900){
            i2c_write(0b01000000,0xFF,0x14);

        } else if (aBuf4 < 45900) {
            i2c_write(0b01000000,0xFF,0x15);
        } else {
            i2c_write(0b01000000,0x00,0x15);
            i2c_write(0b01000000,0x00,0x14);
        }
        
        ssd1306_clear();
        
//        sprintf(message,"t: %d",tData);
//        drawString(message,5,25);
//        
//        sprintf(message,"g: %d %d %d",gxData,gyData,gzData);
//        drawString(message,5,5);
//        
//        sprintf(message,"a: %d %d %d",xlxData,xlyData,xlzData);
//        drawString(message,5,15);
        
        sprintf(message,"G-Clip: %d",aBuf5);
        drawString(message,5,5);
        sprintf(message,"B-Clip: %d",aBuf4);
        drawString(message,5,15);
        
//        bar_y(xlxData);
//        bar_x(-xlyData);
        ssd1306_update();

        
        LATAbits.LATA4 = !LATAbits.LATA4;
//        
//        _CP0_SET_COUNT(0);
//        while (_CP0_GET_COUNT() < 48000000/2/20){;}
    }
}