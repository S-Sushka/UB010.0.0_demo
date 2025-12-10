#pragma once

#include <SEGGER_RTT.h>

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>



int button_begin(gpio_callback_handler_t interrupt_handler);
int button_getPin();

int button_getState();

