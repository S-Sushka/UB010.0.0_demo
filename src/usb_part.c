#include "usb_part.h"



const struct device *const uart_cdc = DEVICE_DT_GET_ONE(zephyr_cdc_acm_uart);


int usb_begin(uart_irq_callback_user_data_t rx_callback) 
{
	int err = 0;

	// Инициализация USB 
    if (!device_is_ready(uart_cdc)) 
	{
        SEGGER_RTT_printf(0, " --- USB CDC ERR --- : CDC ACM device not ready\n");
        return -ENODEV;
    }	

	err = usb_enable(NULL);
	if (err != 0) 
	{
		SEGGER_RTT_printf(0, " --- USB CDC ERR --- : Failed to enable USB\n");
		return err;
	}

	// Устанавливаем и включаем прерывание
	err = uart_irq_callback_set(uart_cdc, rx_callback);
	if (err != 0) 
	{
		SEGGER_RTT_printf(0, " --- USB CDC ERR --- : RX Callback set Failed\n");
		return err;
	}
	uart_irq_rx_enable(uart_cdc);	

	SEGGER_RTT_printf(0, " --- USB CDC --- :  Successful Initialized!\n");
	return 0;
}