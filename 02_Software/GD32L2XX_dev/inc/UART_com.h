#ifndef UARTNIXIE
#define UARTNIXIE

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<gd32l23x.h>

void init_UART();

void configure_UART_IRQ();

void configure_DMA();

bool update_current_time(uint8_t* time_value);

void transmit_current_time(uint8_t time_value);

#endif