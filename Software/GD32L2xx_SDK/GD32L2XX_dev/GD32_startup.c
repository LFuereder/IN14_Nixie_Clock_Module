#ifndef int16_t
    typedef short int                   int16_t;
#endif
#ifndef int32_t
    typedef int                         int32_t;
#endif
#ifndef int8_t
    typedef signed char                 int8_t;
#endif
#ifndef uint8_t
    typedef unsigned char               uint8_t;
#endif
#ifndef uint16_t
    typedef unsigned short int          uint16_t;
#endif
#ifndef uint32_t
    typedef unsigned int                uint32_t;
#endif
#ifndef bool 
    typedef enum {false, true} bool;
#endif

#define RAM_START 0x20000000
#define RAM_SIZE 0x8000



#define RAM_END ((RAM_START)+(RAM_SIZE))
#define STACK_START RAM_END

extern uint32_t _etext;
extern uint32_t _edata;
extern uint32_t _sdata;
extern uint32_t _ebss;
extern uint32_t _sbss;

extern void SystemInit(void);
extern int main(void);

void RESET_HANDLER(void);

    void NMI_HANDLER(void)          __attribute__((weak, alias("DEFAULT_HANDLER")));               
    void HardFault_HANDLER(void)    __attribute__((weak, alias("DEFAULT_HANDLER")));         
    void SVC_HANDLER(void)          __attribute__((weak, alias("DEFAULT_HANDLER")));               
    void PendSV_HANDLER(void)       __attribute__((weak, alias("DEFAULT_HANDLER")));            
    void SysTick_HANDLER(void)      __attribute__((weak, alias("DEFAULT_HANDLER")));           
    void WDT_HANDLER(void)          __attribute__((weak, alias("DEFAULT_HANDLER")));               
    void LVD_HANDLER(void)          __attribute__((weak, alias("DEFAULT_HANDLER")));               
    void RTC_TAMPER_HANDLER(void)   __attribute__((weak, alias("DEFAULT_HANDLER")));        
    void RTC_WAKE_HANDLER(void)     __attribute__((weak, alias("DEFAULT_HANDLER")));          
    void FMC_HANDLER(void)          __attribute__((weak, alias("DEFAULT_HANDLER")));               
    void RCU_CTC_HANDLER(void)      __attribute__((weak, alias("DEFAULT_HANDLER")));           
    void EXTI0_HANDLER(void)        __attribute__((weak, alias("DEFAULT_HANDLER")));             
    void EXTI1_HANDLER(void)        __attribute__((weak, alias("DEFAULT_HANDLER")));             
    void EXTI2_HANDLER(void)        __attribute__((weak, alias("DEFAULT_HANDLER")));             
    void EXTI3_HANDLER(void)        __attribute__((weak, alias("DEFAULT_HANDLER")));             
    void EXTI4_HANDLER(void)        __attribute__((weak, alias("DEFAULT_HANDLER")));             
    void DMA0_HANDLER(void)         __attribute__((weak, alias("DEFAULT_HANDLER")));              
    void DMA1_HANDLER(void)         __attribute__((weak, alias("DEFAULT_HANDLER")));              
    void DMA2_HANDLER(void)         __attribute__((weak, alias("DEFAULT_HANDLER")));              
    void DMA3_HANDLER(void)         __attribute__((weak, alias("DEFAULT_HANDLER")));              
    void DMA4_HANDLER(void)         __attribute__((weak, alias("DEFAULT_HANDLER")));              
    void DMA5_HANDLER(void)         __attribute__((weak, alias("DEFAULT_HANDLER")));              
    void DMA6_HANDLER(void)         __attribute__((weak, alias("DEFAULT_HANDLER")));              
    void ADC_HANDLER(void)          __attribute__((weak, alias("DEFAULT_HANDLER")));               
    void USBD_HIGH_HANDLER(void)    __attribute__((weak, alias("DEFAULT_HANDLER")));         
    void USBD_LOW_HANDLER(void)     __attribute__((weak, alias("DEFAULT_HANDLER")));          
    void TIM1_HANDLER(void)         __attribute__((weak, alias("DEFAULT_HANDLER")));              
    void TIM2_HANDLER(void)         __attribute__((weak, alias("DEFAULT_HANDLER")));              
    void TIM8_HANDLER(void)         __attribute__((weak, alias("DEFAULT_HANDLER")));              
    void TIM11_HANDLER(void)        __attribute__((weak, alias("DEFAULT_HANDLER")));             
    void TIM5_HANDLER(void)         __attribute__((weak, alias("DEFAULT_HANDLER")));              
    void TIM6_HANDLER(void)         __attribute__((weak, alias("DEFAULT_HANDLER")));              
    void USART0_HANDLER(void)       __attribute__((weak, alias("DEFAULT_HANDLER")));            
    void USART1_HANDLER(void)       __attribute__((weak, alias("DEFAULT_HANDLER")));            
    void UART3_HANDLER(void)        __attribute__((weak, alias("DEFAULT_HANDLER")));             
    void UART4_HANDLER(void)        __attribute__((weak, alias("DEFAULT_HANDLER")));             
    void I2C0_EVENT_HANDLER(void)   __attribute__((weak, alias("DEFAULT_HANDLER")));        
    void I2C0_ERROR_HANDLER(void)   __attribute__((weak, alias("DEFAULT_HANDLER")));        
    void I2C1_EVENT_HANDLER(void)   __attribute__((weak, alias("DEFAULT_HANDLER")));        
    void I2C1_ERROR_HANDLER(void)   __attribute__((weak, alias("DEFAULT_HANDLER")));        
    void SPI0_HANDLER(void)         __attribute__((weak, alias("DEFAULT_HANDLER")));              
    void SPI1_HANDLER(void)         __attribute__((weak, alias("DEFAULT_HANDLER")));              
    void DAC_HANDLER(void)          __attribute__((weak, alias("DEFAULT_HANDLER")));               
    void I2C2_EVENT_HANDLER(void)   __attribute__((weak, alias("DEFAULT_HANDLER")));        
    void I2C2_ERROR_HANDLER(void)   __attribute__((weak, alias("DEFAULT_HANDLER")));        
    void RTC_ALARM_HANDLER(void)    __attribute__((weak, alias("DEFAULT_HANDLER")));         
    void USBD_WAKE_HANDLER(void)    __attribute__((weak, alias("DEFAULT_HANDLER")));         
    void EXTI5_to_9_HANDLER(void)   __attribute__((weak, alias("DEFAULT_HANDLER")));        
    void EXTI10_to_15_HANDLER(void) __attribute__((weak, alias("DEFAULT_HANDLER")));      
    void DMA_MUX_HANDLER(void)      __attribute__((weak, alias("DEFAULT_HANDLER")));           
    void CMP0_OUT_HANDLER(void)     __attribute__((weak, alias("DEFAULT_HANDLER")));          
    void CMP1_OUT_HANDLER(void)     __attribute__((weak, alias("DEFAULT_HANDLER")));          
    void I2C0_WAKE_HANDLER(void)    __attribute__((weak, alias("DEFAULT_HANDLER")));         
    void I2C2_WAKE_HANDLER(void)    __attribute__((weak, alias("DEFAULT_HANDLER")));         
    void USART0_WAKE_HANDLER(void)  __attribute__((weak, alias("DEFAULT_HANDLER")));       
    void LPUART_HANDLER(void)       __attribute__((weak, alias("DEFAULT_HANDLER")));            
    void CAU_HANDLER(void)          __attribute__((weak, alias("DEFAULT_HANDLER")));               
    void TRNG_HANDLER(void)         __attribute__((weak, alias("DEFAULT_HANDLER")));              
    void SLCD_HANDLER(void)         __attribute__((weak, alias("DEFAULT_HANDLER")));              
    void USART1_WAKE_HANDLER(void)  __attribute__((weak, alias("DEFAULT_HANDLER")));       
    void I2C1_WAKE_HANDLER(void)    __attribute__((weak, alias("DEFAULT_HANDLER")));         
    void LPUART_WAKE_HANDLER(void)  __attribute__((weak, alias("DEFAULT_HANDLER")));       
    void LPTIMER_HANDLER(void)      __attribute__((weak, alias("DEFAULT_HANDLER")));           

//##//

uint32_t vectors[] __attribute__((section(".isr_vector"))) =
{
    STACK_START,                            // 0
    (uint32_t)&RESET_HANDLER,               // 1
    (uint32_t)&NMI_HANDLER,                 // 2
    (uint32_t)&HardFault_HANDLER,           // 3
    0,                                      // 4
    0,                                      // 5
    0,                                      // 6
    0,                                      // 7
    0,                                      // 8
    0,                                      // 9
    0,                                      //10
    (uint32_t)&SVC_HANDLER,                 //11
    0,                                      //12
    0,                                      //13
    (uint32_t)&PendSV_HANDLER,              //14
    (uint32_t)&SysTick_HANDLER,             //15
    (uint32_t)&WDT_HANDLER,                 //16
    (uint32_t)&LVD_HANDLER,                 //17
    (uint32_t)&RTC_TAMPER_HANDLER,          //18
    (uint32_t)&RTC_WAKE_HANDLER,            //19
    (uint32_t)&FMC_HANDLER,                 //20
    (uint32_t)&RCU_CTC_HANDLER,             //21
    (uint32_t)&EXTI0_HANDLER,               //22
    (uint32_t)&EXTI1_HANDLER,               //23
    (uint32_t)&EXTI2_HANDLER,               //24
    (uint32_t)&EXTI3_HANDLER,               //25
    (uint32_t)&EXTI4_HANDLER,               //26
    (uint32_t)&DMA0_HANDLER,                //27
    (uint32_t)&DMA1_HANDLER,                //28
    (uint32_t)&DMA2_HANDLER,                //29
    (uint32_t)&DMA3_HANDLER,                //30
    (uint32_t)&DMA4_HANDLER,                //31
    (uint32_t)&DMA5_HANDLER,                //32
    (uint32_t)&DMA6_HANDLER,                //33
    (uint32_t)&ADC_HANDLER,                 //34
    (uint32_t)&USBD_HIGH_HANDLER,           //35
    (uint32_t)&USBD_LOW_HANDLER,            //36
    (uint32_t)&TIM1_HANDLER,                //37
    (uint32_t)&TIM2_HANDLER,                //38
    (uint32_t)&TIM8_HANDLER,                //39
    (uint32_t)&TIM11_HANDLER,               //40
    (uint32_t)&TIM5_HANDLER,                //41
    (uint32_t)&TIM6_HANDLER,                //42
    (uint32_t)&USART0_HANDLER,              //43
    (uint32_t)&USART1_HANDLER,              //44
    (uint32_t)&UART3_HANDLER,               //45
    (uint32_t)&UART4_HANDLER,               //46
    (uint32_t)&I2C0_EVENT_HANDLER,          //47
    (uint32_t)&I2C0_ERROR_HANDLER,          //48
    (uint32_t)&I2C1_EVENT_HANDLER,          //49
    (uint32_t)&I2C1_ERROR_HANDLER,          //50
    (uint32_t)&SPI0_HANDLER,                //51
    (uint32_t)&SPI1_HANDLER,                //52
    (uint32_t)&DAC_HANDLER,                 //53
    0,                                      //54
    (uint32_t)&I2C2_EVENT_HANDLER,          //55
    (uint32_t)&I2C2_ERROR_HANDLER,          //56
    (uint32_t)&RTC_ALARM_HANDLER,           //57
    (uint32_t)&USBD_WAKE_HANDLER,           //58
    (uint32_t)&EXTI5_to_9_HANDLER,          //59
    0,                                      //60
    0,                                      //61
    (uint32_t)&EXTI10_to_15_HANDLER,        //63
    0,                                      //64
    0,                                      //65
    0,                                      //66
    0,                                      //67
    0,                                      //68
    0,                                      //69
    0,                                      //70
    (uint32_t)&DMA_MUX_HANDLER,             //71
    (uint32_t)&CMP0_OUT_HANDLER,            //72
    (uint32_t)&CMP1_OUT_HANDLER,            //73
    (uint32_t)&I2C0_WAKE_HANDLER,           //74
    (uint32_t)&I2C2_WAKE_HANDLER,           //75
    (uint32_t)&USART0_WAKE_HANDLER,         //76
    (uint32_t)&LPUART_HANDLER,              //77
    (uint32_t)&CAU_HANDLER,                 //78
    (uint32_t)&TRNG_HANDLER,                //79
    (uint32_t)&SLCD_HANDLER,                //80
    (uint32_t)&USART1_WAKE_HANDLER,         //81
    (uint32_t)&I2C1_WAKE_HANDLER,           //82
    (uint32_t)&LPUART_WAKE_HANDLER,         //83
    (uint32_t)&LPTIMER_HANDLER,             //84
};

void DEFAULT_HANDLER(void)
{
    while(true)
    {
        __asm("nop");
    }
}
void RESET_HANDLER(void)
{
    uint32_t size = &_edata - &_sdata;
    uint32_t *pDest = (uint32_t*)&_sdata;
    uint32_t *pSrc= (uint32_t*)&_etext;
    for(uint32_t i =0;i<size;i++)
    {
        *pDest++=*pSrc++;
    }
    //init bss
    size = &_ebss - &_sbss;
    pDest = (uint32_t*)&_sbss;
    for(uint32_t i =0;i<size;i++)
    {
        *pDest++=0;
    }

    SystemInit();
    //call main
    main();
}