#include "../inc/BTN_nixie.h"

#define SYSCTL_EXTI_SS1_PB4     0x40010000U
#define ever ;;

#define ENABLE_COM true

#define BTN_0_PRIORITY 1
#define BTN_1_PRIORITY 2
#define BTN_2_PRIORITY 2
#define BTN_3_PRIORITY 3

/* global variables for clock configuration */
extern uint8_t config_state;
extern rtc_parameter_struct current_time; 

/* global indicator, weather the controller 
   shall display minutes or hours. */
extern bool show_minutes;

/* Since the RTC initialisation expects BCD format, 
   we need to adjust the number interpretation from 
   10-basis to 16-basis. I.e., config_minute = 12 needs
   to be interpreted as 0x12. */
static uint8_t convert_to_BCD(uint8_t number)
{
    uint8_t decimal = (number / 10) << 4;
    uint8_t digit = (number % 10);
    return decimal + digit;
}

/* Since we need to adjust the current time in the 
   config mode in decimal, we need a function to 
   convert the current time back to decimal. */
static uint8_t convert_to_DEC(uint8_t number)
{
    uint8_t decimal = (number / 16) * 10;
    uint8_t digit = (number % 16);
    return decimal + digit;
}


/* The Button 3 handler serves as a configuration 
   mode for the clock. If the button is tapped, the 
   clock shall display the current values of hour 
   and minute and wait for termination via Button 0. */
void btn_3_irq_handler()
{
    /* set config state bit to switch to configuration mode. If it should 
    be switched back, press BTN_0 (see btn_0_irq_handler())*/
    config_state = 1;

    while(config_state == 1)
    {
        reset_tube(NIXIE_IN14_1);
        reset_tube(NIXIE_IN14_2);

        display_time(&current_time, show_minutes);
    }
    
#if ENABLE_COM
        if(show_minutes)
        {
            transmit_current_time(current_time.minute);
        }
        else
        {
            transmit_current_time(current_time.hour);
        }
#endif

    init_RTC(current_time);
    return;
}

/* The Button 2 handler reduces the value of the 
   currently displayed number. */
void btn_2_irq_handler()
{
    if(show_minutes)
    {
        if(current_time.minute > 0)
        {
            uint8_t current_minute = convert_to_DEC(current_time.minute);
            current_minute--;
            current_time.minute = convert_to_BCD(current_minute);
        }
        else
        {
            current_time.minute = convert_to_BCD(59);
        }
    }
    else
    {
        if(current_time.hour > 0)
        {
            uint8_t current_hour = convert_to_DEC(current_time.hour);
            current_hour--;
            current_time.hour = convert_to_BCD(current_hour);
        }
        else
        {
            current_time.hour = convert_to_BCD(23);
        }
    }
    
    return;
}

/* The Button 1 handler increases the value of the 
   currently display number. */
void btn_1_irq_handler()
{
    if(show_minutes)
    {
        if(current_time.minute < convert_to_BCD(59)) 
        {
            uint8_t current_minute = convert_to_DEC(current_time.minute);
            current_minute++;
            current_time.minute = convert_to_BCD(current_minute);
        }
        else 
        {
            current_time.minute = 0;
        }
    }
    else
    {
        if(current_time.hour < convert_to_BCD(23)) 
        {
            uint8_t current_hour = convert_to_DEC(current_time.hour);
            current_hour++;
            current_time.hour = convert_to_BCD(current_hour);
        }
        else 
        {
            current_time.hour = 0;
        }
    }

    return;
}

/* The Button 9 handler terminates the configuration 
   mode of the clock by setting the config_state 
   value to zero. */
void btn_0_irq_handler()
{
    config_state = 0;
    return;
}


void configure_btn_irq(exti_line_enum linex)
{
    exti_init(linex, EXTI_INTERRUPT, EXTI_TRIG_FALLING);
    exti_flag_clear(linex);
    exti_interrupt_enable(linex);
}

void init_buttons()
{
    RCU_APB2EN |= 0x01;

    /* Configure all Buttons as input */

    /* BTN-1 (PA0) button setup */
    gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_0);
    syscfg_exti_line_config(EXTI_SOURCE_GPIOA, EXTI_SOURCE_PIN0);
    configure_btn_irq(EXTI_0);
    nvic_irq_enable(EXTI0_IRQn, 1);

    /* BTN-0 (PA1) button setup */
    gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_1);
    syscfg_exti_line_config(EXTI_SOURCE_GPIOA, EXTI_SOURCE_PIN1);
    configure_btn_irq(EXTI_1);
    nvic_irq_enable(EXTI1_IRQn, 0);

    /* BTN-3 (PB4) button setup */
    gpio_mode_set(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_4);
    syscfg_exti_line_config(EXTI_SOURCE_GPIOB, EXTI_SOURCE_PIN4);
    configure_btn_irq(EXTI_4);
    nvic_irq_enable(EXTI4_IRQn, 3);
    
    /* BTN-2 (PB5) button setup */
    gpio_mode_set(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_5);
    syscfg_exti_line_config(EXTI_SOURCE_GPIOB, EXTI_SOURCE_PIN5);
    configure_btn_irq(EXTI_5);
    nvic_irq_enable(EXTI5_9_IRQn, 2);   
}