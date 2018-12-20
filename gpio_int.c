#include <stdlib.h>
#include "hw_types.h"
#include "hw_ints.h"
#include "rom.h"
#include "rom_map.h"
#include "gpio.h"
#include "interrupt.h"
#include "pin.h"
#include "hw_memmap.h"
#include "prcm.h"

#ifdef SL_PLATFORM_MULTI_THREADED  /* If OS-based application */
#include "osi.h"
#endif

#include "gpio_int.h"  
#include "button_if.h"


gpio_handler_t g_m_gpio_handler;


void gpio_hanlder(void)
{

//    unsigned long ulPinState =  GPIOIntStatus(INT_GPIOA2,GPIO_INT_PIN_6);
//
//    if(ulPinState & GPIO_INT_PIN_6)
//    {
//        MAP_GPIOIntClear(GPIOA2_BASE, GPIO_INT_PIN_6);
//        g_m_gpio_handler();
//    }
	g_m_gpio_handler();
	
	Button_IF_EnableInterrupt(SW2);
}


void gpio_int_init(gpio_handler_t m_gpio_handler)
{

	MAP_PinTypeGPIO(PIN_15, PIN_MODE_0, false);
	g_m_gpio_handler = m_gpio_handler;
	Button_IF_Init(gpio_hanlder, NULL);
//	
//	MAP_GPIOIntTypeSet(GPIOA2_BASE,GPIO_PIN_6,GPIO_FALLING_EDGE);
//
//	g_m_gpio_handler = m_gpio_handler;
//	
//	//
//	// Register Interrupt handler
//	//
//#if defined(USE_TIRTOS) || defined(USE_FREERTOS) || defined(SL_PLATFORM_MULTI_THREADED) 
//// USE_TIRTOS: if app uses TI-RTOS (either networking/non-networking)
//// USE_FREERTOS: if app uses Free-RTOS (either networking/non-networking)
//// SL_PLATFORM_MULTI_THREADED: if app uses any OS + networking(simplelink)
//	osi_InterruptRegister(INT_GPIOA2,(P_OSI_INTR_ENTRY)GPIOs2IntHandler, \
//							INT_PRIORITY_LVL_1);
//#else                
//	MAP_IntPrioritySet(INT_GPIOA2, INT_PRIORITY_LVL_1);
//	MAP_GPIOIntRegister(GPIOA2_BASE, gpio_hanlder);
//#endif    
//						
//	//
//	// Enable Interrupt
//	//
//	MAP_GPIOIntClear(GPIOA2_BASE,GPIO_PIN_6);
//	MAP_GPIOIntEnable(GPIOA2_BASE,GPIO_INT_PIN_6);
}
