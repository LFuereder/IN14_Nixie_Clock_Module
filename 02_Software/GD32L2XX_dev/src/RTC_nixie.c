#include "../inc/RTC_nixie.h"

#define RTC_CLOCK_SOURCE_LXTAL
#define BKP_VALUE    0x32F0

__IO uint32_t prescaler_a = 0, prescaler_s = 0;

ErrStatus status;

/* since the RTC initialisation expects BCD format, 
   we need to adjust the number interpretation from 
   10-basis to 16-basis. I.e., config_minute = 12 needs
   to be interpreted as 0x12. */
static uint8_t convert_to_BCD(uint8_t number)
{
     uint8_t decimal = (number / 10) << 4;
    uint8_t digit = (number % 10);
    return decimal + digit;
}

ErrStatus rtc_setup(uint8_t config_hour, uint8_t config_minute)
{
    rtc_parameter_struct rtc_initparam = {};
    rtc_initparam.factor_asyn = prescaler_a;
    rtc_initparam.factor_syn = prescaler_s;
    rtc_initparam.year = 24;
    rtc_initparam.month = 03;
    rtc_initparam.date = 9;
    rtc_initparam.display_format = RTC_24HOUR;

    rtc_initparam.hour = config_hour;
    rtc_initparam.minute = convert_to_BCD(config_minute);
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

void init_RTC(uint8_t config_hour, uint8_t config_minute)
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
        rtc_setup(config_hour, config_minute);
    }
}