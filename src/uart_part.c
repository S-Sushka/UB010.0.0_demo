#include "uart_part.h"

#include <zephyr/drivers/gpio.h>



const struct device *uart = DEVICE_DT_GET(DT_NODELABEL(uart1));


int uart_begin(uart_irq_callback_user_data_t rx_callback) 
{
    int err = 0;


    if (!device_is_ready(uart)) 
    {
        SEGGER_RTT_printf(0, " --- UART ERR --- : UART Device is not Ready!\n");
        return -1;
    }

	// Устанавливаем и включаем прерывание
	err = uart_irq_callback_set(uart, rx_callback);
	if (err != 0) 
	{
        SEGGER_RTT_printf(0, " --- UART ERR --- : RX Callback set Failed!\n");
		return err;
	}
	uart_irq_rx_enable(uart);	

    return 0;
}