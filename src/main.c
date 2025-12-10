#include <SEGGER_RTT.h>

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/led_strip.h>


#include "led_part.h"
#include "button_part.h"



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



int main(void)
{
	led_begin();
	button_begin(button_callback_handler);
	

	while (1) 
	{
		k_msleep(K_FOREVER);
	}

	return 0;
}
