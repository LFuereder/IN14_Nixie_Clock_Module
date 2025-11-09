#ifndef BTNNIXIE
#define BTNNIXIE

#include <stdio.h>
#include <gd32l23x.h>
#include <gd32l23x_gpio.h>

#include "IN14_nixie.h"
#include "RTC_nixie.h"
#include "UART_com.h"

void btn_3_irq_handler();
void btn_2_irq_handler();
void btn_1_irq_handler();
void btn_0_irq_handler();

void init_buttons();

#endif