#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// Driverlib includes
#include "hw_types.h"
#include "hw_memmap.h"
#include "prcm.h"
#include "pin.h"
#include "uart.h"
#include "rom.h"
#include "rom_map.h"
#include "uart_module.h"

#include "hw_ints.h"
#include "interrupt.h"

#define UartGetChar()        MAP_UARTCharGet(UART_MODULE_CONSOLE)
#define UartPutChar(c)       MAP_UARTCharPut(UART_MODULE_CONSOLE,c)



void uart_module_send_data(char *pdata, int len)
{
	for(int i = 0; i < len; i++)
	{
		UARTCharPutNonBlocking(UART_MODULE_CONSOLE, pdata[i]);	
	}

}

void uart_module_handler(void)
{	
	unsigned long ch = UARTCharGetNonBlocking(UART_MODULE_CONSOLE);
	UARTCharPutNonBlocking(UART_MODULE_CONSOLE,ch);	
	MAP_UARTIntClear(UARTA0_BASE,UART_INT_RX);
	
}

void uart_module_register(void)
{
	UARTIntRegister(UART_MODULE_CONSOLE, uart_module_handler);
	UARTIntEnable(UART_MODULE_CONSOLE, UART_INT_RX);
	MAP_IntPrioritySet(INT_UARTA0, INT_PRIORITY_LVL_1);
}

unsigned char uart_module_read(void)
{
	return (unsigned char)UartGetChar();
}

void uart_module_init(void)
{
    //
    // Enable Peripheral Clocks 
    //
    MAP_PRCMPeripheralClkEnable(PRCM_UARTA0, PRCM_RUN_MODE_CLK);

    //
    // Configure PIN_55 for UART0 UART0_TX
    //
    MAP_PinTypeUART(PIN_55, PIN_MODE_3);

    //
    // Configure PIN_57 for UART0 UART0_RX
    //
    MAP_PinTypeUART(PIN_57, PIN_MODE_3);
	
#ifndef NOTERM
  MAP_UARTConfigSetExpClk(UART_MODULE_CONSOLE,MAP_PRCMPeripheralClockGet(UART_MODULE_CONSOLE_PERIPH), 
                  UART_MODULE_BAUD_RATE, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                   UART_CONFIG_PAR_NONE));
#endif
  
  	uart_module_register();

}