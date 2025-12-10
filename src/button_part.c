#include "button_part.h"

static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET_OR(DT_NODELABEL(button_main), gpios, {0});
static struct gpio_callback button_callback;


int button_begin(gpio_callback_handler_t interrupt_handler) 
{
	int err = 0;
	
	if (!gpio_is_ready_dt(&button)) 
	{
		SEGGER_RTT_printf(0, " --- BTN ERROR --- : Button Device is Not Ready!\n");
		return -1;
	}


	err = gpio_pin_configure_dt(&button, GPIO_INPUT | GPIO_PULL_UP);
	if (err < 0) 
	{
		SEGGER_RTT_printf(0, " --- BTN ERROR --- : Button Config Failed!\n");
		return err;
	}

	err = gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_BOTH);
	if (err < 0) 
	{
		SEGGER_RTT_printf(0, " --- BTN ERROR --- : Button Interrupt Config Failed!\n");
		return err;
	}

	gpio_init_callback(&button_callback, interrupt_handler, BIT(button.pin));
	err = gpio_add_callback_dt(&button, &button_callback);
	if (err < 0) 
	{
		SEGGER_RTT_printf(0, " --- BTN ERROR --- : Button Adding Callback Failed!\n");
		return err;
	}

	return 0;
}

int button_getPin() 
{
    return button.pin;
}


int button_getState() 
{
    return gpio_pin_get_dt(&button);
}