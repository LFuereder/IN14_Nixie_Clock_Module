#include "../inc/BTN_nixie.h"
#define SYSCTL_EXTI_SS1_PB4     0x40010000U

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
    gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_0);
    syscfg_exti_line_config(EXTI_SOURCE_GPIOA, EXTI_SOURCE_PIN0);
    configure_btn_irq(EXTI_0);
    
    gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_1);
    syscfg_exti_line_config(EXTI_SOURCE_GPIOA, EXTI_SOURCE_PIN1);
    configure_btn_irq(EXTI_1);

    gpio_mode_set(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_4);
    syscfg_exti_line_config(EXTI_SOURCE_GPIOB, EXTI_SOURCE_PIN4);
    configure_btn_irq(EXTI_4);

    gpio_mode_set(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_5);
    syscfg_exti_line_config(EXTI_SOURCE_GPIOB, EXTI_SOURCE_PIN5);
    configure_btn_irq(EXTI_5);
}