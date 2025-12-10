#include "led_part.h"

static const struct device *const led_strip = DEVICE_DT_GET(DT_NODELABEL(led_strip));
#define led_strip_len 	DT_PROP(DT_NODELABEL(led_strip), chain_length)

static struct led_rgb led_pixeles[led_strip_len];



int led_begin() 
{
	if (!device_is_ready(led_strip)) 
	{
		SEGGER_RTT_printf(0, " --- LED ERROR --- : Strip Device is Not Ready!\n");
		return -1;
	}

	return 0;
}


void led_setPixel(int id, struct led_rgb *pixel)
{
    if (id >= led_strip_len)
    {
        return;
    }

	led_pixeles[id].r = pixel->r;
	led_pixeles[id].g = pixel->g;
	led_pixeles[id].b = pixel->b;
}


struct led_rgb *led_getPixel(int id) 
{
    if (id >= led_strip_len)
    {
        return NULL;
    }

    return &led_pixeles[id];
}


int led_update()
{
    return led_strip_update_rgb(led_strip, led_pixeles, led_strip_len);
}


int led_updatePixeles(struct led_rgb *px0, struct led_rgb *px1, struct led_rgb *px2) 
{
    led_setPixel(0, px0);
    led_setPixel(1, px1);
    led_setPixel(2, px2);
    led_update();
}