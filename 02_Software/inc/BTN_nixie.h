/*!
    \file    BTN_nixie.h
    \brief   button functionality of the IN14-nixie-clock module 

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

#ifndef BTNNIXIE
#define BTNNIXIE

#include <stdio.h>
#include <gd32l23x.h>
#include <gd32l23x_gpio.h>

#include "watch_config.h"
#include "IN14_nixie.h"
#include "RTC_nixie.h"
#include "UART_com.h"

/* The button priority of the button_0 IRQ is the 
   highest, since it terminates the configurations 
   state of the clock. Furthermore, button_1 and 
   button_2 IRQs need to be higher than the button_3 
   IRQ, in order to increase or decrease the value 
   correctly. */
#define BTN_0_PRIORITY 1
#define BTN_1_PRIORITY 2
#define BTN_2_PRIORITY 2
#define BTN_3_PRIORITY 3

/// @brief The button_3 IRQ initializes the configuration
///        mode of the clock. In this mode the other button 
///        IRQs increase or decrease the display value or 
///        stop the configuration mode.
void btn_3_irq_handler();

/// @brief The button_2 IRQ decreases the displayed time 
///        value (e.g. if show_minutes is true, the minutes 
///        otherwise the hours).
void btn_2_irq_handler();

/// @brief The button_1 IRQ increases the displayed time 
///        value.
void btn_1_irq_handler();

/// @brief The button_0 IRQ terminates the configuration mode. 
///        In case the ENABLE_COM define is set to true, this
///        triggers a transmit of the new time value to the 
///        other controller.
void btn_0_irq_handler();

/// @brief Initializes the GPIO-pins of the thre buttons to 
///        external-IRQ sources with the corresponding priorities
///        defined above.
void init_buttons();

#endif