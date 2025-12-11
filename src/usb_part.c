#include "usb_part.h"



const struct device *const usb_cdc = DEVICE_DT_GET_ONE(zephyr_cdc_acm_uart);


int usb_begin(uart_irq_callback_user_data_t rx_callback) 
{
	int err = 0;

	// Инициализация USB 
    if (!device_is_ready(usb_cdc)) 
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
	err = uart_irq_callback_set(usb_cdc, rx_callback);
	if (err != 0) 
	{
		SEGGER_RTT_printf(0, " --- USB CDC ERR --- : RX Callback set Failed\n");
		return err;
	}
	uart_irq_rx_enable(usb_cdc);	

	SEGGER_RTT_printf(0, " --- USB CDC --- :  Successful Initialized!\n");
	return 0;
}

void usb_sendByte(uint8_t data)
{
	uart_poll_out(usb_cdc, data);
}