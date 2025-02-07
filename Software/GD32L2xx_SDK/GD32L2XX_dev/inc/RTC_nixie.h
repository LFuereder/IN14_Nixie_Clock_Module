#ifndef RTCNIXIE
#define RTCNIXIE

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<gd32l23x.h>

#include "IN14_nixie.h"

void init_RTC(uint8_t config_hour, uint8_t config_minute);

#endif