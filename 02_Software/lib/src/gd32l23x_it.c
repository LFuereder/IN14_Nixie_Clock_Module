/*!
    \file    gd32l23x_it.c
    \brief   interrupt service routines

    \version 2024-03-25, V2.0.2, firmware for GD32L23x, add support for GD32L235
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include <stdbool.h>
#include "gd32l23x_it.h"

#define BTN_DEBOUNCE_TIME 1280

extern uint8_t rx_count;
extern uint8_t receive_flag;

/* custom irq handler defined in BTN_nixie.h */
extern void btn_3_irq_handler();
extern void btn_2_irq_handler();
extern void btn_1_irq_handler();
extern void btn_0_irq_handler();


/*!
    \brief      this function handles NMI exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void NMI_HANDLER(void)
{
    /* if NMI exception occurs, go to infinite loop */
    while(1){
    }
}

/*!
    \brief      this function handles HardFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void HardFault_HANDLER(void)
{
    /* if Hard Fault exception occurs, go to infinite loop */
    while(1)
    {
        __asm("nop");
    }
}

/*!
    \brief      this function handles SVC exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SVC_HANDLER(void)
{
    /* if SVC exception occurs, go to infinite loop */
    while(1){
    }
}

/*!
    \brief      this function handles PendSV exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void PendSV_HANDLER(void)
{
    /* if PendSV exception occurs, go to infinite loop */
    while(1){
    }
}

/*!
    \brief      this function handles USART RBNE interrupt request and TBE interrupt request
    \param[in]  none
    \param[out] none
    \retval     none
*/
void USART0_HANDLER(void)
{
    if(RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_IDLE))
    {
        usart_interrupt_flag_clear(USART0, USART_INT_FLAG_IDLE);

        /* number of data received */
        rx_count = 256 - (dma_transfer_number_get(DMA_CH1));
        receive_flag = 1;

        /* disable DMA and reconfigure */
        dma_channel_disable(DMA_CH1);
        dma_transfer_number_config(DMA_CH1, 256);
        dma_channel_enable(DMA_CH1);
    }
}

/*!
    \brief      this function handles BTN 1 interrupt request and increments minute display
    \param[in]  none
    \param[out] none
    \retval     none
*/

void EXTI0_HANDLER(void)
{
    for(uint16_t i = 0; i < BTN_DEBOUNCE_TIME; i++) __asm("nop");

    if(RESET != exti_interrupt_flag_get(EXTI_0))
    {
        btn_1_irq_handler();
        exti_interrupt_flag_clear(EXTI_0);    
    }
}

/*!
    \brief      this function handles BTN 0 interrupt request and enables configuration state
    \param[in]  none
    \param[out] none
    \retval     none
*/

void EXTI1_HANDLER(void)
{
    for(uint16_t i = 0; i < BTN_DEBOUNCE_TIME; i++) __asm("nop");
    
    if(RESET != exti_interrupt_flag_get(EXTI_1))
    {
        exti_interrupt_flag_clear(EXTI_1);
        btn_0_irq_handler();
    }
}

/*!
    \brief      this function handles BTN 3 interrupt request and enables configuration state
    \param[in]  none
    \param[out] none
    \retval     none
*/

void EXTI4_HANDLER(void)
{
    for(uint16_t i = 0; i < BTN_DEBOUNCE_TIME; i++) __asm("nop");
    
    if(RESET != exti_interrupt_flag_get(EXTI_4))
    {
        btn_3_irq_handler();
        exti_interrupt_flag_clear(EXTI_4);
    }
}

/*!
    \brief      this function handles BTN 2 interrupt request and enables configuration state
    \param[in]  none
    \param[out] none
    \retval     none
*/

void EXTI5_to_9_HANDLER(void)
{
    for(uint16_t i = 0; i < BTN_DEBOUNCE_TIME; i++) __asm("nop");
    
    if(RESET != exti_interrupt_flag_get(EXTI_5))
    {
        btn_2_irq_handler();
        exti_interrupt_flag_clear(EXTI_5);
    }
}