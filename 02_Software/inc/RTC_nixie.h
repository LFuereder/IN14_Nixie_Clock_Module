#ifndef RTCNIXIE
#define RTCNIXIE

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<gd32l23x.h>

#include "watch_config.h"
#include "IN14_nixie.h"

/// @brief Initializes the Real-Time Clock (RTC). This 
///        enables the peripheral clock and sets all 
///        parameters to default values. Using the 
///        current_time parameter, the current hour, 
///        minute and second is set.    
/// @param current_time This parameter contains the 
///                     values for the hour, minute and 
///                     second to start the RTC from. 
void init_RTC(rtc_parameter_struct current_time);

#endif