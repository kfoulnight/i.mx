#include "i2c.h"
#include "fsl_iomuxc.h"
#include "gpt.h"
// i2cx_I2CR
#define MSTA (5) // 主从模式选择位  置1 之后会发送一个起始信号
#define MTX (4)  // 发送从机地址时，此位总为1 接收为0
#define TXAK (3) // 是否需要应答位 作为发送方 需不需要ACK 作为接收方 需不需要发送ACK
#define RSTA (2) // 重新发起起始信号
// i2c_i2SR
#define ICF (7) // 判断是否在传输  1 传输完毕
#define IBB (5) // 发送完停止位后该位清零，启动前根据此位判断总线是否空闲
#define IAL (4)
#define IIF (1) // 中断标记 无论发送还是接收都需要清零

void init_i2c1(void)
{
    IOMUXC_SetPinMux(IOMUXC_UART4_TX_DATA_I2C1_SCL, 1);
    IOMUXC_SetPinConfig(IOMUXC_UART4_TX_DATA_I2C1_SCL, 0x70B0);
    IOMUXC_SetPinMux(IOMUXC_UART4_RX_DATA_I2C1_SDA, 1);
    IOMUXC_SetPinConfig(IOMUXC_UART4_RX_DATA_I2C1_SDA, 0x70B0);

    I2C1->I2CR &= ~(1 << 7);
    I2C1->IFDR = 0x15;
    I2C1->I2CR |= (1 << 7);
}

void i2c_wirte(I2C_Type *base, unsigned char dev_addr, unsigned char reg_addr, unsigned char *data, int len)
{
    base->I2SR &= ~((1 << IAL) | (1 << IIF));
    while ((base->I2SR & (1 << ICF)) == 0)
        ;
    base->I2CR |= (1 << MSTA) | (1 << MTX);
    base->I2CR &= ~(1 << TXAK);
    base->I2SR &= ~(1 << IIF);
    base->I2DR = dev_addr << 1; // 发送设备地址 7bit 不读所以最后一位为0
    while ((base->I2SR & (1 << IIF)) == 0)
        ;
    base->I2SR &= ~(1 << IIF);
    base->I2DR = reg_addr;
    while ((base->I2SR & (1 << IIF)) == 0)
        ;
    while (len--)
    {
        base->I2SR &= ~(1 << IIF);
        base->I2DR = *data++;
        while ((base->I2SR & (1 << IIF)) == 0)
            ;
    }

    base->I2CR &= ~(1 << MSTA);
    int t = 0;
    while (((base->I2SR & (1 << IBB)) != 0) && t < 10)
    {
        delay_us(100);
        ++t;
    }
}

void i2c_read(I2C_Type *base, unsigned char dev_addr, unsigned char reg_addr, unsigned char *data, int len)
{
    base->I2SR &= ~((1 << IAL) | (1 << IIF));
    while ((base->I2SR & (1 << ICF)) == 0)
        ;
    base->I2CR |= (1 << MSTA) | (1 << MTX);
    base->I2CR &= ~(1 << TXAK);

    base->I2SR &= ~(1 << IIF);
    base->I2DR = dev_addr << 1;
    while ((base->I2SR & (1 << IIF)) == 0)
        ;
    base->I2SR &= ~(1 << IIF);
    base->I2DR = reg_addr;
    while ((base->I2SR & (1 << IIF)) == 0)
        ;
    base->I2CR |= (1 << RSTA);
    base->I2SR &= ~(1 << IIF);
    base->I2DR = dev_addr << 1 | 1;
    while ((base->I2SR & (1 << IIF)) == 0)
        ;
    base->I2SR &= ~(1 << IIF);
    base->I2CR &= ~(1 << MTX);

    if (1 == len)
    {
        base->I2CR |= (1 << TXAK);
    }
    *data = base->I2DR; // 假读
    while (len--)
    {
        while ((base->I2SR & (1 << IIF)) == 0)
            ;

        if (1 == len)
        {
            base->I2CR |= (1 << TXAK);
        }
        else if (0 == len)
        {
            base->I2CR &= ~((1 << MSTA) | (1 < TXAK));
            int t = 0;
            while (((base->I2SR & (1 << IBB)) != 0) && t < 10)
            {
                delay_us(100);
                ++t;
            }
        }
        base->I2SR &= ~(1 << IIF);
        *data++ = base->I2DR;
    }
}