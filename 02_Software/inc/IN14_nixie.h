#ifndef IN14NIXIE
#define IN14NIXIE

#include <stdio.h>
#include <stdbool.h>
#include <gd32l23x.h>
#include <gd32l23x_gpio.h>

#include "watch_config.h"

typedef struct nixie_Pindef nixie_Pindef_T;

/* Enum defining the Nixie-tube positions on the PCB. */
enum nixie_tube
{
    NIXIE_IN14_1=0,
    NIXIE_IN14_2
};

/* Definition of the nixie-pin struct. Each pin can 
   be addressed by a port and a pin number. */
struct nixie_Pindef 
{
    uint32_t PIN;
    uint32_t PORT;
};


/// @brief Initializes the corresponding pins of a nixie tube
///        depending on the tube parameter passed to the function.
/// @param nixie_tube Used to specifiy, which of pins associated with 
///                   the two tubes should be initialized.
void init_nixie(enum nixie_tube);


/// @brief Resets the current state of the nixie tube. Depending on 
///        the tube-ID passed to the function, the pins of the tube 
///        will be reset to the default value.
/// @param nixie_tube Specifies, which of the two nixie-tubes should 
///                   be reseted.  
void reset_tube(enum nixie_tube);

/* Display Functions */

/// @brief Displays the current time value selected by the show_minutes
///        flag. The value to display is read from the time paramter 
///        passed to the function. The values read from the time parameter 
///        are converted from BCD to decimal upon display. 
/// @param time Time-object read beforehand from the RTC. This parameter
///             contains both the current hour and current minute to 
///             display. 
/// @param show_minutes Selects, wheater to display the current hour 
///                     or current minute. This parameter is set during 
///                     the initialization of the clock. 
void display_time(rtc_parameter_struct* time, bool show_minutes);

/// @brief Displays a generic number on the nixie-tube. This function 
///        does not perform a confersion and interprets the input from 
///        the paramter as a decimal number.  
/// @param number Decimal number, passed to be displayed on the two 
///               nixie-tubes.
void display_number(uint8_t number);

#endif