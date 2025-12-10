#pragma once

#include <SEGGER_RTT.h>

#include <zephyr/kernel.h>
#include <zephyr/drivers/uart.h>



int uart_begin(uart_irq_callback_user_data_t rx_callback);