#include "../inc/UART_com.h"

#define USART0_RDATA_ADDRESS      ((uint32_t)&USART_RDATA(USART0))

uint8_t rxbuffer[256];
uint8_t rx_count = 0;
uint8_t tx_count = 0;
__IO uint8_t receive_flag = 0;

bool uart_updateNumber(uint8_t* current_hour)
{
    if(receive_flag == SET) 
    {     
        receive_flag = RESET;
        *current_hour = rxbuffer[0];

        return true;
    }

    return false;
}

void transmit_current_hour(uint8_t current_hour)
{
    usart_data_transmit(USART0, current_hour);
}

void configure_UART_IRQ()
{
    /*wait IDLEF set and clear it*/
    while(RESET == usart_flag_get(USART0, USART_FLAG_IDLE)) 
    {
        __asm("nop");
    }

    usart_flag_clear(USART0, USART_FLAG_IDLE);
    usart_interrupt_enable(USART0, USART_INT_IDLE);
}

void configure_DMA(void)
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

void init_UART()
{
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

    usart_enable(USART0);
}