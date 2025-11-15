#include"../inc/IN14_nixie.h"

/* Pin mapping of the correct GPIOs to the correspoing 
   values displayed by the nixie tube. Depending, weather 
   or not the mirror layout is used (this is the case, if 
   the tubes are mounted on the back of the PCB) the mapping 
   changes accordingly. */
#if !NIXIE_MIRROR_LAYOUT
const nixie_Pindef_T NIXIE_1_PINS[12] =
{
    (nixie_Pindef_T){.PORT=GPIOB, .PIN=GPIO_PIN_14},    // 0
    (nixie_Pindef_T){.PORT=GPIOC, .PIN=GPIO_PIN_12},    // 1
    (nixie_Pindef_T){.PORT=GPIOA, .PIN=GPIO_PIN_12},    // 2
    (nixie_Pindef_T){.PORT=GPIOA, .PIN=GPIO_PIN_11},    // 3
    (nixie_Pindef_T){.PORT=GPIOA, .PIN=GPIO_PIN_10},    // 4
    (nixie_Pindef_T){.PORT=GPIOA, .PIN=GPIO_PIN_9},     // 5
    (nixie_Pindef_T){.PORT=GPIOA, .PIN=GPIO_PIN_8},     // 6
    (nixie_Pindef_T){.PORT=GPIOC, .PIN=GPIO_PIN_7},     // 7
    (nixie_Pindef_T){.PORT=GPIOC, .PIN=GPIO_PIN_6},     // 8
    (nixie_Pindef_T){.PORT=GPIOB, .PIN=GPIO_PIN_15},    // 9
    (nixie_Pindef_T){.PORT=GPIOB, .PIN=GPIO_PIN_3},     // ._
    (nixie_Pindef_T){.PORT=GPIOB, .PIN=GPIO_PIN_13}     // _.
};
#else 
const nixie_Pindef_T NIXIE_1_PINS[12] =
{
    (nixie_Pindef_T){.PORT=GPIOC, .PIN=GPIO_PIN_12},    // 0
    (nixie_Pindef_T){.PORT=GPIOB, .PIN=GPIO_PIN_14},    // 1
    (nixie_Pindef_T){.PORT=GPIOB, .PIN=GPIO_PIN_15},    // 2
    (nixie_Pindef_T){.PORT=GPIOC, .PIN=GPIO_PIN_6},     // 3
    (nixie_Pindef_T){.PORT=GPIOC, .PIN=GPIO_PIN_7},     // 4
    (nixie_Pindef_T){.PORT=GPIOA, .PIN=GPIO_PIN_8},     // 5    
    (nixie_Pindef_T){.PORT=GPIOA, .PIN=GPIO_PIN_9},     // 6
    (nixie_Pindef_T){.PORT=GPIOA, .PIN=GPIO_PIN_10},    // 7
    (nixie_Pindef_T){.PORT=GPIOA, .PIN=GPIO_PIN_11},    // 8
    (nixie_Pindef_T){.PORT=GPIOA, .PIN=GPIO_PIN_12},    // 9
    (nixie_Pindef_T){.PORT=GPIOB, .PIN=GPIO_PIN_13},    // _.
    (nixie_Pindef_T){.PORT=GPIOB, .PIN=GPIO_PIN_3},     // ._
};
#endif

/* Pin mapping of the correct GPIOs to the correspoing 
   values displayed by the nixie tube. Depending, weather 
   or not the mirror layout is used (this is the case, if 
   the tubes are mounted on the back of the PCB) the mapping 
   changes accordingly. */
#if !NIXIE_MIRROR_LAYOUT
const nixie_Pindef_T NIXIE_2_PINS[12] =
{
    (nixie_Pindef_T){.PORT=GPIOA, .PIN=GPIO_PIN_3},     // 0
    (nixie_Pindef_T){.PORT=GPIOB, .PIN=GPIO_PIN_11},    // 1
    (nixie_Pindef_T){.PORT=GPIOB, .PIN=GPIO_PIN_10},    // 2
    (nixie_Pindef_T){.PORT=GPIOB, .PIN=GPIO_PIN_2},     // 3
    (nixie_Pindef_T){.PORT=GPIOB, .PIN=GPIO_PIN_1},     // 4
    (nixie_Pindef_T){.PORT=GPIOB, .PIN=GPIO_PIN_0},     // 5
    (nixie_Pindef_T){.PORT=GPIOA, .PIN=GPIO_PIN_7},     // 6
    (nixie_Pindef_T){.PORT=GPIOA, .PIN=GPIO_PIN_6},     // 7
    (nixie_Pindef_T){.PORT=GPIOA, .PIN=GPIO_PIN_5},     // 8
    (nixie_Pindef_T){.PORT=GPIOA, .PIN=GPIO_PIN_4},     // 9
    (nixie_Pindef_T){.PORT=GPIOB, .PIN=GPIO_PIN_12},    // ._
    (nixie_Pindef_T){.PORT=GPIOA, .PIN=GPIO_PIN_2}      // _.
};
#else
const nixie_Pindef_T NIXIE_2_PINS[12] =
{
    (nixie_Pindef_T){.PORT=GPIOB, .PIN=GPIO_PIN_11},    // 0
    (nixie_Pindef_T){.PORT=GPIOA, .PIN=GPIO_PIN_3},     // 1
    (nixie_Pindef_T){.PORT=GPIOA, .PIN=GPIO_PIN_4},     // 2
    (nixie_Pindef_T){.PORT=GPIOA, .PIN=GPIO_PIN_5},     // 3
    (nixie_Pindef_T){.PORT=GPIOA, .PIN=GPIO_PIN_6},     // 4
    (nixie_Pindef_T){.PORT=GPIOA, .PIN=GPIO_PIN_7},     // 5
    (nixie_Pindef_T){.PORT=GPIOB, .PIN=GPIO_PIN_0},     // 6
    (nixie_Pindef_T){.PORT=GPIOB, .PIN=GPIO_PIN_1},     // 7
    (nixie_Pindef_T){.PORT=GPIOB, .PIN=GPIO_PIN_2},     // 8
    (nixie_Pindef_T){.PORT=GPIOB, .PIN=GPIO_PIN_10},    // 9
    (nixie_Pindef_T){.PORT=GPIOA, .PIN=GPIO_PIN_2},     // ._
    (nixie_Pindef_T){.PORT=GPIOB, .PIN=GPIO_PIN_12},    // _.
};
#endif

/* Initializes DIR, DEN and DATA registers 
   for all pins of the tube. */
static void init_pins(enum nixie_tube tube)
{
    if(tube == NIXIE_IN14_1)
    {
        /* set output mode of nixie 1 pins */
        gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_8  | 
                                                               GPIO_PIN_9  |
                                                               GPIO_PIN_10 |
                                                               GPIO_PIN_11 |
                                                               GPIO_PIN_12);

        gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_3  |
                                                               GPIO_PIN_13 |
                                                               GPIO_PIN_14 |
                                                               GPIO_PIN_15);

        gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_6  |
                                                               GPIO_PIN_7  |
                                                               GPIO_PIN_12);
        
        /* set output mode to push-pull */
        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, GPIO_PIN_8  | 
                                                                        GPIO_PIN_9  |
                                                                        GPIO_PIN_10 |
                                                                        GPIO_PIN_11 |
                                                                        GPIO_PIN_12);

        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, GPIO_PIN_3  |
                                                                        GPIO_PIN_13 |
                                                                        GPIO_PIN_14 |
                                                                        GPIO_PIN_15);
                                                                    
        gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, GPIO_PIN_6  |
                                                                        GPIO_PIN_7  |
                                                                        GPIO_PIN_12);

        /* reset pin state of all pins */
        gpio_bit_reset(GPIOA, GPIO_PIN_8  | 
                              GPIO_PIN_9  |
                              GPIO_PIN_10 |
                              GPIO_PIN_11 |
                              GPIO_PIN_12);

        gpio_bit_reset(GPIOB, GPIO_PIN_3  |
                              GPIO_PIN_13 |
                              GPIO_PIN_14 |
                              GPIO_PIN_15);

        gpio_bit_reset(GPIOC, GPIO_PIN_6  |
                              GPIO_PIN_7  |
                              GPIO_PIN_12);
    }
    else if(tube == NIXIE_IN14_2)
    {
        /* set output mode of nixie 1 pins */
        gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_2  | 
                                                               GPIO_PIN_3  |
                                                               GPIO_PIN_4  |
                                                               GPIO_PIN_5  |
                                                               GPIO_PIN_6  |
                                                               GPIO_PIN_7);

        gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_0  |
                                                               GPIO_PIN_1  |
                                                               GPIO_PIN_2  |
                                                               GPIO_PIN_10 |
                                                               GPIO_PIN_11 |
                                                               GPIO_PIN_12);
        
        /* set output mode to push-pull */
        gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, GPIO_PIN_2  | 
                                                                        GPIO_PIN_3  |
                                                                        GPIO_PIN_4  |
                                                                        GPIO_PIN_5  |
                                                                        GPIO_PIN_6  |
                                                                        GPIO_PIN_7);

        gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, GPIO_PIN_0  |
                                                                        GPIO_PIN_1  |
                                                                        GPIO_PIN_2  |
                                                                        GPIO_PIN_10 |
                                                                        GPIO_PIN_11 |
                                                                        GPIO_PIN_12);

        /* reset pin state of all pins */
        gpio_bit_reset(GPIOA, GPIO_PIN_2  | 
                              GPIO_PIN_3  |
                              GPIO_PIN_4  |
                              GPIO_PIN_5  |
                              GPIO_PIN_6  |
                              GPIO_PIN_7);

        gpio_bit_reset(GPIOB, GPIO_PIN_0  |
                              GPIO_PIN_1  |
                              GPIO_PIN_2  |
                              GPIO_PIN_10 |
                              GPIO_PIN_11 |
                              GPIO_PIN_12);
    }
}

/* Enables the clock of and all necessary 
   registers for the pins connected to the 
   nixie tube. */
void init_nixie(enum nixie_tube tube)
{
    if(tube == NIXIE_IN14_1)
    {
        /* activate the clock for relevant ports */
        rcu_periph_clock_enable(RCU_GPIOA);
        rcu_periph_clock_enable(RCU_GPIOB);
        rcu_periph_clock_enable(RCU_GPIOC);
    }
    else if(tube == NIXIE_IN14_2)
    {
        /* activate the clock for relevant ports */
        rcu_periph_clock_enable(RCU_GPIOA);
        rcu_periph_clock_enable(RCU_GPIOB);
    }

    /* activate pins of the nixie tube */
    init_pins(tube);
}

/* Resets all pins associated with the tube 
   passed as parameter to the function. */
void reset_tube(enum nixie_tube tube)
{
    if(tube == NIXIE_IN14_1)
    {
        gpio_bit_reset(GPIOA, GPIO_PIN_8  | 
                              GPIO_PIN_9  |
                              GPIO_PIN_10 |
                              GPIO_PIN_11 |
                              GPIO_PIN_12);

        gpio_bit_reset(GPIOB, GPIO_PIN_3  |
                              GPIO_PIN_13 |
                              GPIO_PIN_14 |
                              GPIO_PIN_15);

        gpio_bit_reset(GPIOC, GPIO_PIN_6  |
                              GPIO_PIN_7  |
                              GPIO_PIN_12);
    }
    else if(tube == NIXIE_IN14_2)
    {
        gpio_bit_reset(GPIOA, GPIO_PIN_2  | 
                              GPIO_PIN_3  |
                              GPIO_PIN_4  |
                              GPIO_PIN_5  |
                              GPIO_PIN_6  |
                              GPIO_PIN_7);
        
        gpio_bit_reset(GPIOB, GPIO_PIN_0  |
                              GPIO_PIN_1  |
                              GPIO_PIN_2  |
                              GPIO_PIN_10 |
                              GPIO_PIN_11 |
                              GPIO_PIN_12);
    }
}

/* Display Functions */

/* This function uses the time parameter, 
   as well as the display value flag, in 
   order to calculate the time value back 
   from BCD-format and display the decimal 
   and digit value on the nixie tubes. */
void display_time(rtc_parameter_struct * time, bool show_minutes)
{
    uint8_t decimal;
    uint8_t digit;

    if(show_minutes)
    {
        decimal = (time->minute / 16);
        digit = (time->minute % 16);
    }
    else
    {
        decimal = (time->hour / 16);
        digit = (time->hour % 16);
    }

#if !NIXIE_MIRROR_LAYOUT
    gpio_bit_set(NIXIE_1_PINS[decimal].PORT, NIXIE_1_PINS[decimal].PIN);
    gpio_bit_set(NIXIE_2_PINS[digit].PORT, NIXIE_2_PINS[digit].PIN);
#else
    gpio_bit_set(NIXIE_1_PINS[digit].PORT, NIXIE_1_PINS[digit].PIN);
    gpio_bit_set(NIXIE_2_PINS[decimal].PORT, NIXIE_2_PINS[decimal].PIN);
#endif
}

/* This function takes the number parameter 
   directly and displays it on the tubes without 
   a conversion from BCD to decimal. */
void display_number(uint8_t number)
{
    uint8_t decimal = (number / 10);
    uint8_t digit = (number % 10);

#if !NIXIE_MIRROR_LAYOUT
    gpio_bit_set(NIXIE_1_PINS[decimal].PORT, NIXIE_1_PINS[decimal].PIN);
    gpio_bit_set(NIXIE_2_PINS[digit].PORT, NIXIE_2_PINS[digit].PIN);
#else
    gpio_bit_set(NIXIE_1_PINS[digit].PORT, NIXIE_1_PINS[digit].PIN);
    gpio_bit_set(NIXIE_2_PINS[decimal].PORT, NIXIE_2_PINS[decimal].PIN);
#endif
}