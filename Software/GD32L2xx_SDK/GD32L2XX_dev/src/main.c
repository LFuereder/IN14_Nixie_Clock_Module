#include <main.h>
#include <inttypes.h>
#include <stdbool.h>

#include <gd32l23x.h>
#include <gd32l23x_gpio.h>

#include "../inc/IN14_nixie.h"
#include "../inc/RTC_nixie.h"
#include "../inc/UART_com.h"
#include "../inc/BTN_nixie.h"

#define ever ;;

rtc_parameter_struct current_time;

/* global variables for clock configuration */
uint8_t config_state = 0;
uint8_t config_hour = 0; 
uint8_t config_minute = 0;

/* Nixie Clock position and status flags: */
bool show_minutes = false;
bool clock_cfg_mode = false;


void configure_time()
{
    for(ever)
    {
        reset_tube(NIXIE_IN14_1);
        reset_tube(NIXIE_IN14_2);

        display_number(config_minute);
        transmit_current_hour(config_hour);

        if(!clock_cfg_mode)
        {
            break;
        }
    }

    init_RTC(config_hour, config_minute);
}

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

void display_hours()
{
    for(ever)
    {
        uint8_t current_hour=0;
        if(uart_updateNumber(&current_hour))
        {
            reset_tube(NIXIE_IN14_1);
            reset_tube(NIXIE_IN14_2);

            display_number(current_hour);
        }

    }
}

int main(void)
{  
    /* initialize NIXIE tube drivers */
    init_nixie(NIXIE_IN14_1);
    init_nixie(NIXIE_IN14_2);

    /* initialize the com */
    configure_DMA();
    init_UART();
    init_buttons();
    configure_UART_IRQ();

    /*interrupt configuration */
    nvic_irq_enable(USART0_IRQn, 0);
    nvic_irq_enable(EXTI0_IRQn, 0);
    nvic_irq_enable(EXTI1_IRQn, 0);
    nvic_irq_enable(EXTI4_IRQn, 0);
    nvic_irq_enable(EXTI5_9_IRQn, 0);

    get_clk_position(&show_minutes);
    if(!show_minutes) display_hours();

    init_RTC(config_hour, config_minute);

    while(1)
    {
        if(clock_cfg_mode) configure_time();

        reset_tube(NIXIE_IN14_1);
        reset_tube(NIXIE_IN14_2);
        
        transmit_current_hour(config_minute);

        rtc_current_time_get(&current_time);
        display_time(&current_time);
    }
}