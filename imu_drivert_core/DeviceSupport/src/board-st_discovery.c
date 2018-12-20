#include <stdint.h>
#include "board-st_discovery.h"

int get_tick_count(unsigned long *count)
{
    /*
    nrf_drv_systick_state_t pstate;
    nrf_drv_systick_get(&pstate);
    count[0] = pstate.time;
    */
    count[0] = d_tim_get_stamp_data();

    return 0;
}


