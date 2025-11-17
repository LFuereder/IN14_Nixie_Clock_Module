/*!
    \file    RTC_nixie.c
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

#include "../inc/RTC_nixie.h"

#define RTC_CLOCK_SOURCE_LXTAL
#define BKP_VALUE    0x32F0

/* Default Pre-Scaler values, globally set to zero */
__IO uint32_t prescaler_a = 0, prescaler_s = 0;

/* Global error-code to assert during the 
   initialization of the RTC. */
ErrStatus status;

/* Assigns default values to the RTC parameter. For the 
   current hour, minute and second, it takes the values 
   from the parameter. Returns an error code other than 
   SUCCESS, in case of an error. */
static ErrStatus rtc_setup(rtc_parameter_struct current_time)
{
    rtc_parameter_struct rtc_initparam = {};
    rtc_initparam.factor_asyn = prescaler_a;
    rtc_initparam.factor_syn = prescaler_s;
    rtc_initparam.year = 24;
    rtc_initparam.month = 03;
    rtc_initparam.date = 9;
    rtc_initparam.display_format = RTC_24HOUR;

    rtc_initparam.hour = current_time.hour;
    rtc_initparam.minute = current_time.minute;
    rtc_initparam.second = current_time. second;

    ErrStatus status = rtc_init(&rtc_initparam);

    if(status != SUCCESS)
    {
        printf("RTC time configuration success!\n");
        RTC_BKP0 = BKP_VALUE;
    }

    return status;
}

/* Activates the clock source from the external 
   oxcillator. This function assigns new values 
   to the prescaler-variables and starts the RTC. */
   static ErrStatus RTC_pre_config()
{
    /* activate LXTAL oscillator and verify stable functionality */
    rcu_osci_on(RCU_LXTAL);
    status = rcu_osci_stab_wait(RCU_LXTAL);
    rcu_rtc_clock_config(RCU_RTCSRC_LXTAL);
    
    /* set prescaler values for LXTAL crystal */
    prescaler_s = 0xFF;
    prescaler_a = 0x7F;
    
    /* activate clock for RTC component */
    rcu_periph_clock_enable(RCU_RTC);
    status = rtc_register_sync_wait();

    return status;
}

/* Entry-point of the initialization of the RTC. This 
   function assigns all values to the RTC registers 
   and assigns the hour, minute and second values from 
   the current_time parameter. */
void init_RTC(rtc_parameter_struct current_time)
{
    /* enable PMU and BKP clock */
    rcu_periph_clock_enable(RCU_PMU);
    rcu_periph_clock_enable(RCU_BKP);
    
    /* enable the access of the RTC registers */
    pmu_backup_write_enable();

    /* get RTC clock entry selection */
    uint32_t RTCSRC_FLAG = GET_BITS(RCU_BDCTL, 8, 9);
    ErrStatus status = RTC_pre_config();

    if(status != SUCCESS)
    {
        printf("pre-config unsuccessful...");
        return;
    }

    /* check if RTC has aready been configured */
    if((BKP_VALUE != RTC_BKP0) || (0x00 == RTCSRC_FLAG)) 
    {
        /* backup data register value is not correct or not yet programmed
        or RTC clock source is not configured (when the first time the program 
        is executed or data in RCU_BDCTL is lost due to Vbat feeding) */
        rtc_setup(current_time);
    }
}