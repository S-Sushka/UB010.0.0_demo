#pragma once

#include <SEGGER_RTT.h>

#include <zephyr/kernel.h>
#include <zephyr/drivers/led_strip.h>


#define COLOR(red, green, blue) (struct led_rgb){ .r = red, .g = green, .b = blue }

#define COLOR_BLACK		COLOR(0, 0, 0)
#define COLOR_BLUE		COLOR(0, 0, 255)
#define COLOR_RED		COLOR(255, 0, 0)
#define COLOR_PINK      COLOR(255, 0, 255)
#define COLOR_GREEN		COLOR(0, 255, 0)
#define COLOR_CYAN      COLOR(0, 255, 255)
#define COLOR_YELLOW    COLOR(255, 255, 0)
#define COLOR_WHITE		COLOR(255, 255, 255)



int led_begin();

void led_setPixel(int id, struct led_rgb *pixel);
struct led_rgb *led_getPixel(int id);

int led_update();
int led_updatePixeles(struct led_rgb *px0, struct led_rgb *px1, struct led_rgb *px2);