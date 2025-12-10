#pragma once

#include <SEGGER_RTT.h>

#include <zephyr/kernel.h>

#include <zephyr/drivers/uart.h>

#include <zephyr/usb/usb_device.h>
#include <zephyr/usb/usbd.h>


int usb_begin(uart_irq_callback_user_data_t rx_callback);