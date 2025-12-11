#include <SEGGER_RTT.h>

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/led_strip.h>


#include "led_part.h"
#include "button_part.h"
#include "uart_part.h"
#include "usb_part.h"


void animation_work_handler(struct k_work *work) 
{
	led_updatePixeles(&COLOR_BLACK, &COLOR_BLACK, &COLOR_BLACK);
	k_msleep(200);
	led_updatePixeles(&COLOR_BLUE, &COLOR_BLACK, &COLOR_BLACK);
	k_msleep(200);
	led_updatePixeles(&COLOR_GREEN, &COLOR_BLUE, &COLOR_BLACK);
	k_msleep(200);
	led_updatePixeles(&COLOR_RED, &COLOR_GREEN, &COLOR_BLUE);
	k_msleep(200);
}
K_WORK_DEFINE(animation_work, animation_work_handler);


void button_callback_handler(const struct device *port, struct gpio_callback *cb, gpio_port_pins_t pins) 
{
	if (pins & BIT(button_getPin()))
	{
		if (button_getState() == 0) 
		{
			k_work_submit(&animation_work);
		}
	}
}


static void uart_rx_handler(const struct device *dev, void *user_data)
{
	ARG_UNUSED(user_data);

    uint8_t byteBuf = 0;
    if (uart_irq_update(dev) && uart_irq_rx_ready(dev)) 
	{
		while (uart_fifo_read(dev, &byteBuf, 1))
		{
			usb_sendByte(byteBuf); // Эхо от UARTа к USB
        }
	}	
}


static void usb_rx_handler(const struct device *dev, void *user_data)
{
	ARG_UNUSED(user_data);

    uint8_t byteBuf = 0;
    if (uart_irq_update(dev) && uart_irq_rx_ready(dev)) 
	{
		while (uart_fifo_read(dev, &byteBuf, 1))
		{
            uart_sendByte(byteBuf); // Эхо от USB к UARTу
        }
	}	
}


int main(void)
{
	led_begin();
	button_begin(button_callback_handler);
	
	uart_begin(uart_rx_handler);
	usb_begin(usb_rx_handler);

	while (1) 
	{	
		k_msleep(1000);
	}

	return 0;
}
