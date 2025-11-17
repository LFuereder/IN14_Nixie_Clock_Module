/*!
    \file    main.c
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


#include "../inc/main.h"

/* Global object containing the current time */
rtc_parameter_struct current_time;

/* Global variable for clock configuration */
uint8_t config_state = 0;

/* Nixie-Clock position and status flag */
bool show_minutes = false;


#if ENABLE_COM
/* In case communication with another controller
   is enabled, this function checks for available 
   data in the UART0 buffer. */
void check_for_new_timeValues()
{
        if(show_minutes)
        {
            if(update_current_time(&current_time.hour))
            {
                init_RTC(current_time);
            }
        }
        else
        {
            if(update_current_time(&current_time.minute))
            {
                init_RTC(current_time);
            }
        }
}
#endif

/* This application checks, which time value to 
   to display by checking, if the PA15/PC13 
   jumber is bridged. If so, the PCB displays the 
   the current hour, otherwise it displays the 
   current minute of time. */
void get_clk_position(bool* show_minutes)
{
    gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_13);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, GPIO_PIN_13);
    gpio_bit_set(GPIOC, GPIO_PIN_13);

    gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_PIN_15);
    
    if(gpio_input_bit_get(GPIOA, GPIO_PIN_15) == SET)
    {
        *show_minutes = false;
    }
    else
    {
        *show_minutes = true;
    }

    gpio_bit_reset(GPIOA, GPIO_PIN_13);
}

int main(void)
{  
    /* setup default time values */
    current_time.hour=0;
    current_time.minute=0;
    current_time.second=0;

    /* initialize NIXIE tube drivers */
    init_nixie(NIXIE_IN14_1);
    init_nixie(NIXIE_IN14_2);

#if ENABLE_COM
    /* initialize the com */
    init_UART();
#endif

    /* initialize buttons */
    init_buttons();

#if ENABLE_COM
    /* UART interrupt configuration */
    nvic_irq_enable(USART0_IRQn, 0);
#endif

    /* check clock position */
    get_clk_position(&show_minutes);

    /* initialize RTC */
    init_RTC(current_time);

    for(ever)
    {
        reset_tube(NIXIE_IN14_1);
        reset_tube(NIXIE_IN14_2);

#if ENABLE_COM
        check_for_new_timeValues();
#endif

        rtc_current_time_get(&current_time);
        display_time(&current_time, show_minutes);
    }
}