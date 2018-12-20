#include <string.h>
#include "pinmux.h"
#include "hw_types.h"
#include "hw_memmap.h"
#include "hw_gpio.h"
#include "pin.h"
#include "rom.h"
#include "rom_map.h"
#include "gpio.h"
#include "prcm.h"

#include "i2c_if.h"
#include "i2c_module.h"

int Sensors_I2C_ReadRegister(unsigned char Address, unsigned char RegisterAddr,
                                          unsigned short RegisterLen, unsigned char *RegisterValue)
{
   I2C_IF_ReadFrom(Address,
            &Address,
            1,
            RegisterValue,
            RegisterLen);
   
   return 0x00;
}


int Sensors_I2C_WriteRegister(unsigned char Address, unsigned char RegisterAddr,
                                           unsigned short RegisterLen, const unsigned char *RegisterValue)
{
	
	I2C_IF_Write(Address, &RegisterAddr,  1, 0);
	I2C_IF_Write(Address, (unsigned char*)RegisterValue,  RegisterLen, 1);
    return 0x00;
}

void i2c_module_init(void)
{
	MAP_PRCMPeripheralClkEnable(PRCM_I2CA0, PRCM_RUN_MODE_CLK);
	 MAP_PRCMPeripheralClkEnable(PRCM_GPIOA0, PRCM_RUN_MODE_CLK);
	//
    // Configure PIN_01 for I2C0 I2C_SCL
    //
	MAP_PinTypeI2C(PIN_01, PIN_MODE_1);
	//
    // Configure PIN_02 for I2C0 I2C_SDA
    //
    MAP_PinTypeI2C(PIN_02, PIN_MODE_1);
	
	I2C_IF_Open(I2C_MASTER_MODE_FST);
}

