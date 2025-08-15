#ifndef _I2C_H__
#define _I2C_H__

#include "MCIMX6Y2.h"
extern void i2c_wirte(I2C_Type *base, unsigned char dev_addr, unsigned char reg_addr, unsigned char *data, int len);
extern void i2c_read(I2C_Type *base, unsigned char dev_addr, unsigned char reg_addr, unsigned char *data, int len);

extern void init_i2c1(void);
#endif