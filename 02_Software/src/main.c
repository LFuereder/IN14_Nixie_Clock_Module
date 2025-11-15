#include <main.h>
#include <inttypes.h>
#include <stdbool.h>

#include <gd32l23x.h>
#include <gd32l23x_gpio.h>

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
    configure_DMA();
    init_UART();
    configure_UART_IRQ();
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