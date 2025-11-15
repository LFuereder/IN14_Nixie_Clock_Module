#ifndef UARTNIXIE
#define UARTNIXIE

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<gd32l23x.h>

#include "watch_config.h"

/// @brief Function called during the main routine 
///        of the clock to check, if a new value for
///        the display time parameter is available.  
/// @param time_value Pointer to the display time 
///                   parameter. In case a new value 
///                   is available, it is assigned to 
///                   the referenced value. 
/// @return Returns true, if a new value was assigned 
///         to the time parameter. Otherwise, this 
///         function returns false. 
bool update_current_time(uint8_t* time_value);

/// @brief Transmits either the current hour or the 
///        current minute depending on the globally 
///        show_minutes flag defined in the main.c 
///        file. Per default the implementation uses 
///        the UART0. 
/// @param time_value time value to be sent to the 
///                   other PCB. 
void transmit_current_time(uint8_t time_value);

/// @brief Configures the idle line IRQ for the 
///        UART0.  
void configure_UART_IRQ();

/// @brief Configures the DMA channel 1 for the data
///        transfer between the UART0 Tx- and Rx-Buffers 
///        to the main memory.
void configure_DMA();

/// @brief Entry-point of the UART0 initialization. 
///        This function configures the required pins  
///        accordingly and sets the config for 8N1 UART
///        with a baud-rate of 115200. 
void init_UART();

#endif