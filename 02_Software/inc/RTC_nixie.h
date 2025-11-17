/*!
    \file    RTC_nixie.h
    \brief   RTC implementation of the IN14-nixie-clock module 

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

#ifndef RTCNIXIE
#define RTCNIXIE

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<gd32l23x.h>

#include "watch_config.h"
#include "IN14_nixie.h"

/// @brief Initializes the Real-Time Clock (RTC). This 
///        enables the peripheral clock and sets all 
///        parameters to default values. Using the 
///        current_time parameter, the current hour, 
///        minute and second is set.    
/// @param current_time This parameter contains the 
///                     values for the hour, minute and 
///                     second to start the RTC from. 
void init_RTC(rtc_parameter_struct current_time);

#endif