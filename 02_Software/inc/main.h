/*!
    \file    main.h
    \brief   Entry-point of the IN14-nixie-clock module 

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