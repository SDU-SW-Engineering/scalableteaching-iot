#ifndef PUMP_H
#define PUMP_H
#include "pump.h"
#endif

void pump_turn_on(gpio_num_t pin)
{
	gpio_set_level(pin, 0);
	return;
}

void pump_turn_off(gpio_num_t pin)
{
	gpio_set_level(pin, 1);
	return;
}
