#pragma once

#ifndef GPIO_H
#define GPIO_H
#include "gpio.h"
#endif

// Turns ON a pump connected via pin passed as parameter
void pump_turn_on(gpio_num_t pin);

// Turns OFF a pump connected via pin passed as parameter
void pump_turn_off(gpio_num_t pin);