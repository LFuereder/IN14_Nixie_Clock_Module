#ifndef UARTNIXIE
#define UARTNIXIE

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<gd32l23x.h>

void init_UART();

void configure_UART_IRQ();

void configure_DMA();

bool uart_updateNumber(uint8_t* current_hour);

void transmit_current_hour(uint8_t current_hour);

#endif