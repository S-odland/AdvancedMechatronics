/* 
 * File:   i2c_master_noint.h
 * Author: scott
 *
 * Created on May 18, 2020, 5:06 PM
 */

#ifndef I2C_MASTER_NOINT_H
#define	I2C_MASTER_NOINT_H

#include <xc.h>

void i2c_master_steup(void); // set up I@C1 as a master
void i2c_master_start(void); // send a START signal
void i2c_master_restart(void); // send a RESTART signal
void i2c_master_send(unsigned char byte); // send a byte (address or data)
unsigned char i2c_master_recv(void); // receive a byte of date
void i2c_master_ack(int val); // send an ACk (0) or NACk (1))
void i2c_master_stop(void); // send a stop

// functions made by scott

void i2c_init(void); // initializes the mcp23017 
unsigned char i2c_read(void); // for reading from mcp
void i2c_write(int in); // for writing to mcp

#endif