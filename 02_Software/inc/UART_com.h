/*!
    \file    UART_com.h
    \brief   UART implementation of the IN14-nixie-clock module 

    \version 2025-11-17, V1.0.0, IN14_NIXIE_CLOCK_MODULE
*/

/*

/*
   Copyright 2025 Lukas Füreder

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

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

/// @brief Entry-point of the UART0 initialization. 
///        This function configures the required pins  
///        accordingly and sets the config for 8N1 UART
///        with a baud-rate of 115200. 
void init_UART();

#endif