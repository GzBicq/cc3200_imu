#ifndef UART_MODULE_H_
#define UART_MODULE_H_

#define UART_MODULE_BAUD_RATE  		115200
#define SYSCLK          			80000000
#define UART_MODULE_CONSOLE         UARTA0_BASE
#define UART_MODULE_CONSOLE_PERIPH  PRCM_UARTA0

#define app_uart_put(c)       uart_module_send_data(&c,1)


void uart_module_send_data(char *pdata, int len);
unsigned char uart_module_read(void);
void uart_module_init(void);

#endif 