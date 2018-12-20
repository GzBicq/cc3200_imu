#ifndef GPIO_INT_H_
#define GPIO_INT_H_


typedef void (*gpio_handler_t)(void);

void gpio_int_init(gpio_handler_t gpio_handler);


#endif