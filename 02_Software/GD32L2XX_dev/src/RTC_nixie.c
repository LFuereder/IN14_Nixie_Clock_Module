#include "../inc/RTC_nixie.h"

#define RTC_CLOCK_SOURCE_LXTAL
#define BKP_VALUE    0x32F0

__IO uint32_t prescaler_a = 0, prescaler_s = 0;

ErrStatus status;

ErrStatus rtc_setup(rtc_parameter_struct current_time)
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
    rtc_initparam.second = 0;

    ErrStatus status = rtc_init(&rtc_initparam);

    if(status != SUCCESS)
    {
        printf("RTC time configuration success!\n");
        RTC_BKP0 = BKP_VALUE;
    }

    return status;
}

ErrStatus RTC_pre_config()
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