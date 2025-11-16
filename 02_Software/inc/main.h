#ifndef __main_h__
#define __main_h__

#include <inttypes.h>
#include <stdbool.h>

#include <gd32l23x.h>
#include <gd32l23x_gpio.h>

#include "watch_config.h"
#include "IN14_nixie.h"
#include "RTC_nixie.h"
#include "UART_com.h"
#include "BTN_nixie.h"

/// @brief Entry-point of the application of the watch.
///        This function initializes all peripherals of 
///        the PCB and triggers the main routine. 
/// @return The function should never return, since it 
///         contains an endless loop... 
int main();


#endif