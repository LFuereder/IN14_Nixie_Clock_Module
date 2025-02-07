#ifndef IN14NIXIE
#define IN14NIXIE

#include <stdio.h>
#include <gd32l23x.h>
#include <gd32l23x_gpio.h>

typedef struct nixie_Pindef nixie_Pindef_T;

enum nixie_tube
{
    NIXIE_IN14_1=0,
    NIXIE_IN14_2
};

struct nixie_Pindef 
{
    uint32_t PIN;
    uint32_t PORT;
};


/* public Methods */
void init_nixie(enum nixie_tube);

void reset_tube(enum nixie_tube);

void display_time(rtc_parameter_struct* time);
void display_number(uint8_t number);

#endif