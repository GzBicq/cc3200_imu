
#include "hw_types.h"
#include "hw_memmap.h"
#include "hw_ints.h"
#include "debug.h"
#include "interrupt.h"
#include "timer.h"
#include "rom.h"
#include "rom_map.h"
#include "prcm.h"
#include "timer_if.h"
#include "dTim.h"

unsigned long g_ulTimerInts = 0;

void TimerBaseIntHandler(void)
{
    Timer_IF_InterruptClear(TIMERA0_BASE);
    g_ulTimerInts ++;
}

void timer_init(void)
{
	Timer_IF_Init(PRCM_TIMERA0, TIMERA0_BASE, TIMER_CFG_PERIODIC, TIMER_A, 0);
	Timer_IF_IntSetup(TIMERA0_BASE, TIMER_A, TimerBaseIntHandler);
	Timer_IF_Start(TIMERA0_BASE, TIMER_A, 1);
}

unsigned long d_tim_get_stamp_data()
{
	return g_ulTimerInts;
}

void HAL_Delay(unsigned long m_delay)
{
	g_ulTimerInts = 0;
	
	while(m_delay > g_ulTimerInts);
}