#include "../inc/UART_com.h"

#define USART0_RDATA_ADDRESS      ((uint32_t)&USART_RDATA(USART0))

/* Global indicator, weather the controller 
   shall display minutes or hours. */
extern bool show_minutes;

/* Rx-Buffer used to temporarily store 
   the values sent from the other 
   controller to this one. */
uint8_t rxbuffer[256];

/* Number of bytes received and transmitted 
   via the UART0. */
uint8_t rx_count = 0;
uint8_t tx_count = 0;

/* This flag is set, in case new data is 
   available in the Rx-Buffer. This flag is 
   checked regularly in the update_current_time() 
   function. */
__IO uint8_t receive_flag = 0;

/* Update function called periodically in the 
   main routine of the nixie-clock. In case the 
   function assigns a new value to the referenced 
   time_value, it returns true. Otherwise it 
   returns false. */
bool update_current_time(uint8_t* time_value)
{
    /* if the flag is set, we received a new time value */
    if(receive_flag == SET) 
    {     
        receive_flag = RESET;
        *time_value = rxbuffer[0];
        return true;
    }

    return false;
}

/* In case the ENABLE_COM flag is set to true, 
   this function transmits the value from the 
   time_value parameter to the other controller. */
void transmit_current_time(uint8_t time_value)
{
    usart_data_transmit(USART0, time_value);
}

/* This function configures the idle line interrupt 
   for communication with the other controller of 
   the clock. */
static void configure_UART_IRQ()
{
    /* wait IDLEF set and clear it */
    while(RESET == usart_flag_get(USART0, USART_FLAG_IDLE)) 
    {
        __asm("nop");
    }

    usart_flag_clear(USART0, USART_FLAG_IDLE);
    usart_interrupt_enable(USART0, USART_INT_IDLE);
}

/* This function configures the DMA-channel 1 for 
   fast memory copy from the Rx-Buffer to the main 
   memory and sets the receive_flag to SET. */
static void configure_DMA(void)
{
    dma_parameter_struct dma_init_struct;
    
    /* enable DMA clock */
    rcu_periph_clock_enable(RCU_DMA);

    /* initialize DMA channel 1 */
    dma_deinit(DMA_CH1);
    dma_struct_para_init(&dma_init_struct);
    dma_init_struct.request      = DMA_REQUEST_USART0_RX;
    dma_init_struct.direction    = DMA_PERIPHERAL_TO_MEMORY;
    dma_init_struct.memory_addr  = (uint32_t)rxbuffer;
    dma_init_struct.memory_inc   = DMA_MEMORY_INCREASE_ENABLE;
    dma_init_struct.memory_width = DMA_MEMORY_WIDTH_8BIT;
    dma_init_struct.number       = 256;
    dma_init_struct.periph_addr  = (uint32_t)USART0_RDATA_ADDRESS;
    dma_init_struct.periph_inc   = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.periph_width = DMA_PERIPHERAL_WIDTH_8BIT;
    dma_init_struct.priority     = DMA_PRIORITY_ULTRA_HIGH;
    dma_init(DMA_CH1, &dma_init_struct);

    /* configure DMA mode */
    dma_circulation_disable(DMA_CH1);
    dma_memory_to_memory_disable(DMA_CH1);
    /* disable the DMAMUX_MUXCH1 synchronization mode */
    dmamux_synchronization_disable(DMAMUX_MUXCH1);

    /* enable DMA channel 1 */
    dma_channel_enable(DMA_CH1);
}

/* Entry-point of the UART configuration. This 
   function sets the UART0 pins correctly and 
   configures the UART mode to 8N1 with 115200 
   baud. */
void init_UART()
{
    /* configure DMA channel */
    configure_DMA();

    /* enable USART clock */
    rcu_periph_clock_enable(RCU_USART0);

    /* connect port to USART TX */
    gpio_af_set(GPIOB, GPIO_AF_7, GPIO_PIN_6);
    /* connect port to USART RX */
    gpio_af_set(GPIOB, GPIO_AF_7, GPIO_PIN_7);

    /* configure USART TX as alternate function push-pull */
    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_6);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, GPIO_PIN_6);

    /* configure USART RX as alternate function push-pull */
    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_7);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, GPIO_PIN_7);

    /* USART configure */
    usart_deinit(USART0);
    usart_word_length_set(USART0, USART_WL_8BIT);
    usart_stop_bit_set(USART0, USART_STB_1BIT);
    usart_parity_config(USART0, USART_PM_NONE);
    usart_baudrate_set(USART0, 115200U);
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
    usart_dma_receive_config(USART0, USART_RECEIVE_DMA_ENABLE);
    usart_dma_transmit_config(USART0, USART_TRANSMIT_DMA_ENABLE);
    
    /* enable UART0 */
    usart_enable(USART0);
    
    /* configure UART Idle-Line IRQ */
    configure_UART_IRQ();
}